#include <stdio.h>
#include <stdlib.h>

void load_world_from_file(char *filename); /* Loads the world from file */
void save_world_to_file(char *filename); /* Saves the world into file*/
void next_generation(); /* Calculates the next generation of world */
char get_next_state(int x, int y); /* Gets the next states of the cells of world (dead or alive) */
int num_neighbors(int x, int y); /* Finds the number of neighbors for a given cell */

/* Global Variables */
int m,n; /* The dimensions of the world */
char **world, **new_world; /* The variables that point to world and the world after next generation*/

int main (void){
    int i;
	load_world_from_file("input.txt");

    for (i = 0; i < 50; i++){
        next_generation();
    }

    save_world_to_file("output.txt");

	return 0;
}

void load_world_from_file(char *filename){\
/* This function open the file named filename. At first, it reads the dimensions in first row of the file
   and allocate space with this dimensions. Then it reads the elements, file the array and close the file we are reading from. */
	FILE *fp;
	int i,j;
	char c;

	fp=fopen(filename, "r"); /* We open the file named filename for reading. */
	if(!fp ){
	    /* error checking. */
		perror("filename");
		exit(1);
	}
    /* Read the dimensions. */
	fscanf(fp, "%d", &m);
	fscanf(fp, "%d", &n);

    /* allocate space for world and new_world with the dimensions we just read.*/
	world = malloc(m*sizeof(char*));
	for (i = 0; i < m;i++){
		world[i] = malloc(n*sizeof(char));
	}

	new_world = malloc(m*sizeof(char*));
	for (i = 0; i < m;i++){
		new_world[i] = malloc(n*sizeof(char));
	}
    /* read from file and initialize the array world appropriatly. */
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			while((c = fgetc(fp))){
				if (c != '|' && c!= '\n'){
					world[i][j] = c;
					break;
				}
			}
		}
	}
    /* close the file. */
	fclose(fp);
}

void save_world_to_file(char *filename){
    /* This function opens the file named filename and writes the 2 dimensional world. */
    FILE *fp;
    int i,j;

	fp=fopen(filename, "w"); /* Opens the file for writing. */
	if (!fp){
		perror("fopen");
		exit(1);
	}
	fprintf(fp,"%d %d\n", m,n); /*Writes in the file the dimensions of the array. */

    /* Writes in the file the 2 dimensional world that is described te array world. */
    for (i = 0; i < m; i++){
        fprintf(fp, "%c",'|');
        for ( j= 0; j < n; j++){
            fprintf(fp,"%c|", world[i][j]);
        }
         fprintf(fp,"%c",'\n');
    }
    /* Close the file */
    fclose(fp);

    /* Deallocate the space for 2 dimensional arrays.*/
    for (i = 0; i < m; i++){
       free(world[i]);
    }
    free(world);

    for (i = 0; i < m; i++){
       free(new_world[i]);
    }
    free(new_world);
}
void next_generation(){
    /* This function reads the state of 2 dimensional world from array and calculates the state in
        the next generation following the rules of the game.*/
    int i,j;
    char ** temp = NULL;
    for (i = 0; i < m;i++){
        for (j = 0; j < n; j++){
            /* find the next state of the cell in next generation. */
            new_world[i][j] = get_next_state(i,j);
        }
    }
    /*exchange the values of the 2 global variables.*/
    temp = world;
    world = new_world;
    new_world = temp;
}
char get_next_state(int x, int y){
    int neighbours = 0;
    char next_state = ' ';
    /* calculate how many neighbors has a cell. */
    neighbours = num_neighbors(x,y);
    /* apply the rules of the game. */
    /* if the cell is alive and has less than 2 neighbours it does from loniliness and if it has more than 3 neighbours it dies from overpopulation. */
    if ((world[x][y] == '*' ) && ((neighbours < 2) || (neighbours > 3)) ){
        next_state = ' ';
    }
    /* if the cell is alive and has 2 or 3 neighbours  it stays alive. */
    else if ((world[x][y]  == '*') && (neighbours == 2 || neighbours == 3)){
        next_state = '*';
    }
    /* if the cell is dead and has 3 neighbours it becomes alive. */
    else if (world[x][y] == ' ' && neighbours == 3){
        next_state = '*';
    }
    return next_state;
}

int num_neighbors(int x, int y){
    /* Calculates and returns the number of the alive cells for the cell in position x,y. */
    int i,j, counter;

    counter = 0;
    /* The neighbors are the 8 cells around the cell x,y. */
    for (i = x-1; i <= x+1; i++){
        for (j = y-1; j <= y+1; j++){
            if (i >= 0 && j >= 0 && i < m && j < n){ /* the cells out of bounds considered dead. */
                if (i != x || j != y){ /* we dont want to consider the x,y cell in our counter. */
                    if (world[i][j] == '*'){
                        counter++;
                    }
                }
            }
        }
    }

    return counter;
}
