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
	int word_to_guess_index = rand() % i;
	char *word_to_guess = words[word_to_guess_index];

	printf("debug: word to guess %s \n", word_to_guess);

	int max_errors = 10;
	int errors_made = 0;
	int alphabet_length = 26;
	bool hasWon = false;

	char incorrect_guesses[max_errors + 1];
	char correct_guesses[alphabet_length - errors_made + 1];
	memset(incorrect_guesses, 0, sizeof(incorrect_guesses));
	memset(correct_guesses, 0, sizeof(correct_guesses));

	// start playing! show them how long the word is
	print_current_state(word_to_guess, correct_guesses);

	while (hasWon == false && errors_made < max_errors)
	{
		// get next turn's input
		// and handle upper/lower cases
		char *guess = get_string("Next guess please: ");

		bool isSingleLetter = strlen(guess) == 1;
		bool isNewLetter = !has_been_guessed(guess[0], incorrect_guesses, correct_guesses);

		while (!isSingleLetter || !isNewLetter)
		{
			if (!isSingleLetter)
			{
				guess = get_string("Please enter one letter only: ");
				isSingleLetter = strlen(guess) == 1;
				isNewLetter = !has_been_guessed(guess[0], incorrect_guesses, correct_guesses);
			}

			if (!isNewLetter)
			{
				guess = get_string("Please enter a letter you have not guessed yet: ");
				isSingleLetter = strlen(guess) == 1;
				isNewLetter = !has_been_guessed(guess[0], incorrect_guesses, correct_guesses);
			}
		}

		printf("\n");
		printf("~ ~ ~ ~ ~");
		printf("\n\n\n\n\n\n\n");

		bool isError = check_and_record_guess(guess[0], word_to_guess, correct_guesses, incorrect_guesses);

		if (isError)
		{
			errors_made++;
		}

		if (errors_made > 0)
		{
			printf("%s", hangmen[errors_made - 1]);
		}

		print_current_state(word_to_guess, correct_guesses);

		printf("\nWrong guesses: ");
		for (int i = 0; i < strlen(incorrect_guesses); i++)
		{
			printf("%c ", incorrect_guesses[i]);
		}

		printf("\n\n");

		hasWon = checkIfWon(word_to_guess, correct_guesses);
	}

	if (hasWon)
	{
		printf("You win!\n");
	}

	if (!hasWon && errors_made == max_errors)
	{
		printf("You lose! The word was '%s'\n", word_to_guess);
	}

	return 1;
}
