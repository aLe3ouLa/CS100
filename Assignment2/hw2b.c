/*
 *
 * CS-100 - Introduction to Computer Science
 * Name: Alexandra Barka
 * login: barka
 * AM: 2867
 * Assignment 2: hw2b.c: Triangles.
 *
 */
#include <stdio.h>
#include <ctype.h>

void printTriangleStars(int N);

int main(void){

    int N = 0;
    /* Read and print the number given by user */
    printf("N: ");
    scanf("%d", &N);
    while (N < 0){
        /* Check for negative input. We assume that the input is integer. */
        printf("Wrong input. Give a number: ");
        scanf("%d", &N);
    }
    printf("\n");

    /*Print the triangle*/
    printTriangleStars(N);

    return 0;
}

void printTriangleStars(int N){
    int i, j;
    /* Printing the reversed triangle*/
    for (i = N; i >= 1;i--){
        /* Print spaces (in order to shape a reverse-pyramid */
        for(j = 0; j < N - i; j++)
            printf(" ");
        /* Print star part of triangle according to the formula i*2+1*/
        for (j = i*2 ;j > 1;j--)
            printf("*");
        /* must put a line break between iterations to avoid printing everything in a single line */
        printf("\n");
    }
}
