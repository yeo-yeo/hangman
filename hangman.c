#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

int main(void)
{
	printf("Welcome! Let's play hangman.\n");

	FILE *file = fopen("wordlist.txt", "r");
	// need to make array of arrays (strings) to load wordlist into?
	char words[80000][40]; // how to make it dynamic?
	int i = 0;
	while (fgets(words[i], 40, file) != NULL)
	{
		words[i][strlen(words[i]) - 1] = '\0';
		i++;
	}
	fclose(file);

	// to avoid the word being corvette every single time
	srand(time(NULL));
	int wordToGuessIndex = rand() % i;
	char *wordToGuess = words[wordToGuessIndex];

	printf("debug: word to guess %s \n", wordToGuess);

	int max_errors = 10;
	int errors_made = 0;
	bool hasWon = false;

	int alphabet_length = 26;
	char alreadyGuessed[alphabet_length + 1];
	// correct here!

	// this seems very dumb
	for (int i = 0; i < alphabet_length; i++)
	{
		alreadyGuessed[i] = '?';
	}
	alreadyGuessed[alphabet_length] = '\0';

	// start playing! show them how long the word is
	print_current_state(wordToGuess, alreadyGuessed);

	while (hasWon == false && errors_made < max_errors)
	{

		// get next turn's input
		// TODO need to do something to make them only enter one letter
		// and reject a letter thats already been given
		char *guess = get_string("Next guess please: ");

		printf("guess is %lu\n", strlen(guess));

		while (strlen(guess) > 1)
		{
			guess = get_string("Please enter one letter only: ");
		}
		printf("\n");
		printf("~ ~ ~ ~ ~");
		printf("\n\n\n\n\n\n\n");
		// add it to the array
		add_guess_to_already_guessed(guess[0], alreadyGuessed);
		bool isError = check_if_error(wordToGuess, guess[0]);
		if (isError)
		{
			errors_made++;
		}

		if (errors_made > 0)
		{
			printf("%s", hangmen[errors_made - 1]);
		}

		print_current_state(wordToGuess, alreadyGuessed);
		// TODO also print letters that have been guessed so far
		// check if they've won
		hasWon = checkIfWon(wordToGuess, alreadyGuessed);
	}

	if (hasWon)
	{
		printf("You win!\n");
	}

	if (!hasWon && errors_made == max_errors)
	{
		printf("You lose! The word was '%s'\n", wordToGuess);
	}

	return 1;
}
