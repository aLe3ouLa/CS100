/*
 *
 * CS-100 - Introduction to Computer Science
 * Name: Alexandra Barka
 * login: barka
 * AM: 2867
 * Assignment 1: hw2a.c: Adding Fractions.
 *
 */

#include <stdio.h>

int greaterCommonDivisor(int a, int b);

int main (void){

	int numerator1 = 0, numerator2 = 0, denominator1 = 0, denominator2 = 0;
	int resultNumerator = 0, resultDenominator = 0;
	int gcdNum = 0;

    /* Read the first fraction. */
	printf("First fraction: " );
	scanf("%d %d", &numerator1, &denominator1);
	while (denominator1 == 0){
        /* Checks if denominator is zero. If it is, asks for an other value.*/
		printf("\nThe denominator cannot be zero!\nGive another number: ");
		scanf("%d", &denominator1);
	}

	/* Read the second fraction. */
	printf("\nSecond fraction: " );
    scanf("%d %d", &numerator2, &denominator2);
    while (denominator2 == 0){
        /* Checks if denominator is zero. If it is, asks for an other value.*/
            printf("\nThe denominator cannot be zero!\nGive another number: ");
            scanf("%d", &denominator2);
    }
	
	/*
    Using the type:
	a1    a2    a1*b2 + a2*b1
	--  + -- = --------------
	b1    b2        b1*b2

	*/
	resultNumerator = numerator1* denominator2 + numerator2*denominator1;
	resultDenominator = denominator1*denominator2;

	printf("\nResult: ");

	 /* Find the reduction of the fraction. */
    gcdNum = greaterCommonDivisor(resultNumerator,resultDenominator);
  
    if(gcdNum != 1) {
        printf("%d / %d = ", resultNumerator, resultDenominator);
        /* Divide with Greater Common Divisor to simplify the fraction. */
        resultNumerator /= gcdNum;
        resultDenominator /= gcdNum;
    }
 

	printf("%d / %d = %.3lf\n", resultNumerator, resultDenominator, (double) resultNumerator / (double) resultDenominator);

	return 0;
}

int  greaterCommonDivisor(int a, int b){
/*greaterCommonDivisor is the largest positive integer that divides the numbers without a remainder. */
  if (b == 0)
    return a;
  else
    return greaterCommonDivisor(b,a%b);
}
