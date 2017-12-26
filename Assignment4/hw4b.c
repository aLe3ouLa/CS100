#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMaze(char **maze, int N, int M);
void makeMaze(char **maze, int N, int M, int x, int y, int x_previous, int y_previous);


int main(void){
    int N, M, i,j;
    char **maze;

    srand (time(NULL)); /*The pseudo-random number generator is initialized using the argument passed as seed.*/

	/* Read the dimensions of array */

    scanf("%d",&N);
    while (N<0){
        /* error case */
        printf("Negative dimensions. Give N again: ");
        scanf("%d",&N);
    }
    scanf("%d",&M);
    while (M < 0){
        /* error case */
        printf("Negative dimensions. Give M again: ");
        scanf("%d",&M);

    }

    /* We cannot make a maze with dimension less than 3. */
     if (N < 3 || M < 3){
        printf("Can't make a maze.\n");
        return 0;
    }

	/* Allocate space for maze */
    maze = malloc (N*sizeof(char*));
	if (maze!= NULL){
		for (i = 0; i < N; i++){
			maze[i] = malloc (N * sizeof(char));
			if(maze[i] == NULL){
				printf("Memory allocation failed. Exiting.");
				exit(1);
			}
		}
	}
	else {
		printf("Memory allocation failed. Exiting.");
		exit(1);
	}

	/* Initialize the maze with X's */
    for (i = 0; i < N; i++){
        for (j = 0; j < M; j++){
            maze[i][j] = 'X';
        }
    }

    /* Print the orginal state of the maze*/
	printMaze(maze, N, M);

    /* We find the exit of the maze. */
    maze[0][1] = ' ';
    maze[1][1] = ' ';

    /* Call the recursive function to make the maze*/
    makeMaze(maze, N, M,1,1,1,1);

    /* Print the final state of the maze */
	printMaze(maze, N,M);

	/*	Deallocate malloc'ed space */
    for (i = 0; i < N; i++){
        free(maze[i]);
    }
    free(maze);
    return 0;
}

void makeMaze(char **maze, int N, int M, int x, int y,int x_previous, int y_previous){

    int choices [4][2],choice = 0, i, counter = 0;

	/* Find the possible routes in the maze */
    /* left */
    choices[0][1]  = y - 2;
    choices[0][0]  = x;
    /* right */
    choices[1][1] = y + 2;
    choices[1][0] = x;
    /* up */
    choices[2][0] = x - 2;
    choices[2][1] = y;
    /* down */
    choices[3][0] = x + 2;
    choices[3][1] = y;

	/* Check if the routes are out of bounds, if this happens we have to exclude these routes.*/
	if (choices[0][1] < 0){
		choices[0][1] = -1;
	}
	if (choices[1][1] > M-2){
		choices[1][1] = -1;
	}

	if (choices[2][0] < 0){
		choices[2][0] = -1;
	}

	if (choices[3][0] > N-2){
		choices[3][0] = -1;
	}
	/*  Check if we have passed over this cell of the array. If we have done this, the cell will contain a space character.
	If we have been in that cell before, we have to exclude it from the routes.*/

	for (i = 0; i < 4; i++){
	    int temp_x, temp_y;
	    temp_x = choices[i][0];
	    temp_y = choices[i][1];
	    if (temp_x != -1 && temp_y != -1){
            if (maze[temp_x][temp_y] == ' '){
                choices[i][0] = -1;
                choices[i][1] = -1;
            }

	    }
	}
    /* Count how many routes are available */
	for (i = 0; i < 4; i++){
            if(choices[i][0] == -1 || choices[i][1] == -1){
               counter++;
            }
    }

    /* If we cannot go anywhere, return to the previous state. */
    if (counter == 4){
        return;
    }

    /* If we have routes available, pick one randomly.*/
	while (choice!= -1){
	    i = rand()%4;
	    if (choices[i][0] != -1 && choices[i][1] != -1){
            choice = i;
            break;
	    }
	}

    /* Proceed to that route */
    maze[choices[choice][0]][choices[choice][1]] = ' ';
    if ( choice == 0){
        int x,y;
        x = choices[choice][0];
        y = choices[choice][1] + 1;
        maze[x][y] = ' ';
    }else if ( choice == 1){
        int x,y;
        x = choices[choice][0];
        y = choices[choice][1] - 1;
        maze[x][y] = ' ';

    }else if (choice == 2){
        int x,y;
        x = choices[choice][0] + 1;
        y = choices[choice][1];
        maze[x][y] = ' ';

    }else if (choice == 3){
        int x,y;
        x = choices[choice][0] - 1;
        y = choices[choice][1];
        maze[x][y] = ' ';
    }else{
        printf("error");
    }

     if ((choices[choice][0] == 1 && choices[choice][1] == 1) || (choices[choice][0] == 0 && choices[choice][1] == 1)){
         /* if we have reached the end we have find the way out of the maze! */
        return;
    }
    else{
        /* double recursion in order to implement 'going back' in case we're stuck in a certain route. */
        makeMaze(maze,N,M,choices[choice][0], choices[choice][1],x,y);
        makeMaze(maze,N,M,x,y,choices[choice][0], choices[choice][1]);

    }

}


void printMaze(char **maze, int N, int M){
    /* This function prints the array maze. */
	int i, j;
	for (i = 0; i < N; i++){
        for (j = 0; j < M; j++){
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }

	  printf("\n");
}
