#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

void removeSpaces(char *, char *);
void lowerCaseString (char *);
int isPalindrome (char *);

int main(void){
    char mystr[SIZE], nonSpaceStr[SIZE];
    int i;

    /* Initialize the arrays. */
    for (i = 0; i < SIZE; i++){
        mystr[i] = ' ';
        nonSpaceStr[i] = ' ';
    }

    /* Read the string.*/
    printf("Enter a string to check if it is a palindrome or not.\n");
    while (!fgets(mystr,SIZE, stdin)) break;

    removeSpaces(mystr, nonSpaceStr); /* Remove spaces from the string */
    lowerCaseString(nonSpaceStr); /* Make capital letters, lower case.*/

    /* isPalindrome determines if a string is a palindrome or not. (1: Yes, 0: No). */
    (isPalindrome(nonSpaceStr))? printf("YES, it's a palindrome!\n") : printf("NO, it's not a palindrome!\n");

    return 0;
}

void removeSpaces(char * source, char * target){
    /*
    This function take the input string and removes whitespaces.
    In order to do that, we use 2 strings.
    The one is with the input and the other is empty.  SO we start a loop.
    If the source[i] is not a whitespace we copy it in the target[i] but if it is whitespace we ignore it and continue to next loop.
    */

    int i,j;
    char * temp = target;

    for (i=0, j=0; i < SIZE;){
        if (source[i]== '\0')break; /* reached end of string*/
        if ((source[i] == ' ') || (source[i] == '\t')){ /* whitespaces*/
            if (source[i+1]!= '\0')  /* continue to next loop if we haven't reach the end of string*/
                i++;
            else
                break;
        }
        else{
            target[j++] = source[i]; /*not a whitespace: copy the letter in target string */
            if (source[i+1]!= '\0') /* continue to next loop if we haven't reach the end of string*/
                i++;
            else
                break;
        }
    }
    target[j] = '\0'; /* Must add the \0 in the end of the target string*/
    target = temp; /* Point to start of string again. */
}

int isPalindrome (char *target){
    /*  Checks if the string given is a palindrome. The method i use is to compare the first letter with last and continue inward the string.
        Basically we compare the first with Nst letter, the 2nd with the (N-1)st etc.*/

    int i,j;
    for (i = 0,j = strlen(target)-2; i < j; i++, j--){
        if(target[i] != target[j])
            return 0;
    }
    return 1;
}

void lowerCaseString (char * target){
    /* tolower(): Converts the letter to its lowercase equivalent */
    int i;

    for(i = 0; i < SIZE; i++){
        if (target[i]== '\0') break;
        target[i] = tolower(target[i]);
    }

}
