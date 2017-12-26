#include <stdio.h>

#define SIZE 100

int isMagicSquare(int magicSquare[][100], int N);

int main(void){

    int N,i,j, flag;
    int magicSquare[SIZE][SIZE];

    /* Read N, and check it. It must be between [0-100] so we don't get out of array bounds. */
    printf("Enter N: (Must be in range [0-100]) \n");
    scanf("%d", &N);

    while(N < 0 || N > 101){
        printf("Number must be in range [0-100].\nGive N: ");
        scanf("%d", &N);
    }

    /* Initialize the array */
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++)
            magicSquare[i][j] = 0;
    }

    printf("\nGive the matrix values: \n");

    /* Enter input. */
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            int temp;
            scanf("%d", &temp);
            magicSquare[i][j] = temp;
        }
    }

    /*  Call the function isMagicSquare to determine if the input is Magic Square or not.(1:Yes,0:No) */

    flag = isMagicSquare(magicSquare, N);
    printf("Is%sa magic square!", (flag)? " ":" not "); /* Depending on the variable flag, type if the given input is a magic square or not.*/

    return 0;
}

int isMagicSquare(int magicSquare[][100], int N){
    /* Function to determine if the input is a magic square */

    int sumRows[SIZE];
    int sumColumns[SIZE];
    int i, j, basicDiag = 0, secondaryDiag = 0,sumofRow = 0, sumofCol = 0;

    for ( i = 0; i < N; i++){
        sumRows[i] = 0;
        sumColumns[i] = 0;
    }

    /* Firstly, check if the input matrix values are correct. The input values must be in range [0,N*N - 1]*/
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            if (magicSquare[i][j] < 0 || magicSquare[i][j] > N*N-1)
                return 0; /* If you found a value that is not in range, is not a magic square!*/
        }
    }

    /* If the numbers are correct, we shall sum the values of the rows & columns.*/
    for (i = 0; i<N; i++){
        for ( j =0; j < N; j++)
            sumRows[i] = sumRows[i] + magicSquare[i][j];
    }

    for (j = 0; j < N; j++){
        for ( i =0; i < N; i++)
            sumColumns[j] = sumColumns[j] + magicSquare[i][j];
    }

    /* ..and find the sum of the 2 diagonals.*/
    for(i=0,j=N-1; i<N || j>=0; i++,j--){
        basicDiag += magicSquare[i][i];
        secondaryDiag+=magicSquare[i][j];
    }

    /*  To make it easy, (and not compare its elements with other in the array) we sum the array sumRows in a variable sumofRow.
        To be a magic square this sum will be equal to N*sumRows[0]
        This happens because if this matrix is magic square the sums of the rows would be same for every row.
        If one row has different sum then the equality sumOfRow == N*sumRows[0] would be false.
        The same happens in Columns.*/

    for (i = 0; i< N; i++){
        sumofRow += sumRows[i];
        sumofCol += sumColumns[i];
    }

    /* So to have magic square the sumofRows must be equal N*sumRows[0] as described before. (Same with columns). Ans SumofRow must be equal to sumofcol.
        Also the 2 diagonals must be equal and same with a element of the array. (it is not needed to be checked the last,
        if the sumofRow == sumofcol && basicDiag == secondaryDiag is definetely a magic square.*/
    if(sumofRow != N*sumRows[0] || sumofCol != N*sumColumns[0] || sumofRow != sumofCol || basicDiag != secondaryDiag)
        return 0;
    else
        return 1;

}
