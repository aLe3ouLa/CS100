#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LENGTH  50

void findFrequencies(char **words, int *frequences, int N);
void findMaxPosition(int *frequency, int *maxFreq, int *maxFreqPosition, int N);

int main(void){
	int N = 0, i = 0, maxFreq = 0, maxFreqPosition = 0;
	char **words;
	int *frequency;

	/* Read the number of words, that must be readen */
	scanf("%d", &N);

	/* In case of negative N, we type an error message, and wait user to type an non-negative number. */
	while (N<0){
		printf("Negative number. Give N again: \n");
		scanf("%d", &N);
		/* In case of N == 0, the user doesn't want to give any words, so the program will be terminated. */
		if (N == 0) {
			printf("Exiting...");
			return 0;
		}
	}
	/* In case of N == 0, the user doesn't want to give any words, so the program will be terminated. */
	if (N == 0) {
		printf("Exiting...");
		return 0;
	}

	/* Allocate space for 2-Dimensional array. In this array we will store the words.*/
	words = malloc(N*sizeof(char*));
	if(words!=NULL){
		for (i = 0; i<N; i++){
			words[i] = malloc(WORD_LENGTH*sizeof(char));
			if(words[i] == NULL){
				printf("Memory allocation failed. Exiting.");
				exit(1);
			}
		}
	}
	else {
		printf("Memory allocation failed. Exiting.");
		exit(1);
	}

	/* Allocate the array, that help us find the most frequent word. */
	frequency = malloc (N*sizeof(int));
	if (frequency == NULL){
		printf("Memory allocation failed. Exiting.");
		exit(1);
	}

	/* Initialization */
	for (i = 0; i < N; i++){
		frequency[i] = 0;
	}

	for (i = 0; i < N; i++){
		scanf("%s", words[i]);
	}


	findFrequencies(words, frequency, N);
	findMaxPosition(frequency, &maxFreq, &maxFreqPosition, N);

	printf("%s\n", words[maxFreqPosition]);

	/* Deallocate the malloc'ed space. */
	for (i = 0; i < N; i++){
		free(words[i]);
	}
	free(words);
	free (frequency);


	return 0;
}

void findFrequencies(char **words, int *frequency, int N){
	/* This function finds the frequency of every word given.
	   Firstly, every word will appear at least one time. So, we compare the i-sth word with the words in i+1..N.
	   If there is other appearences of this word the frequency[i] will be increased by one.
	   So, in the end we will have frequences of every word.
	*/

	int i, j;
	for (i = 0; i < N; i++){
		frequency[i]++; /* The word in i position will appear at least one time. */
		for (j = i+1; j < N; j++){
			if (!strcmp(words[i],words[j])){ /* if the word will be seen again in the next positions we increase the value of frequancy array*/
				frequency[i]++;
			}
		}

	}

}

void findMaxPosition(int *frequency, int *maxFreq, int *maxFreqPosition, int N){
	/* This function finds the cell of array where the string with maximum appearences is.
		We want the position of it, so we can type the word.*/
	int i = 0;
	*maxFreq = frequency[0];
	for (i = 1; i < N; i++){
		if (*maxFreq < frequency[i]){
			*maxFreq = frequency[i];
			*maxFreqPosition = i;
		}
	}
}
