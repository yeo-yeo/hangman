#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "helpers.h"

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define RESET "\x1B[0m"

int main(void)
{
	printf("Welcome! Let's play hangman.\n\n");

	char *word_to_guess = load_and_choose_word();

	// printf("debug: word is %s\n", word_to_guess);

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
		char *guess = get_string(YEL "Next guess please: " RESET);

		bool isSingleLetter = strlen(guess) == 1;
		bool isNewLetter = !has_been_guessed(guess[0], incorrect_guesses, correct_guesses);

		// basic validation checks
		while (!isSingleLetter || !isNewLetter)
		{
			if (!isSingleLetter)
			{
				guess = get_string(RED "Please enter one letter only: " RESET);
				isSingleLetter = strlen(guess) == 1;
				isNewLetter = !has_been_guessed(guess[0], incorrect_guesses, correct_guesses);
			}

			if (!isNewLetter)
			{
				guess = get_string(RED "Please enter a letter you have not guessed yet: " RESET);
				isSingleLetter = strlen(guess) == 1;
				isNewLetter = !has_been_guessed(guess[0], incorrect_guesses, correct_guesses);
			}
		}

		printf("\n\n\n\n\n\n\n");

		// add to array of past guesses and check if it is a correct guess or not
		bool isError = check_and_record_guess(tolower(guess[0]), word_to_guess, correct_guesses, incorrect_guesses);

		if (isError)
		{
			errors_made++;
		}

		// print the next stage of the hangman
		if (errors_made > 0)
		{
			printf("%s", hangmen[errors_made - 1]);
		}

		printf("\n");

		// (re)print the word with correct guesses so far
		print_current_state(word_to_guess, correct_guesses);

		// print the wrong guesses to make it easier to know what you've already tried
		printf("Wrong guesses: ");
		for (int i = 0; i < strlen(incorrect_guesses); i++)
		{
			printf("%c ", incorrect_guesses[i]);
		}

		printf("\n\n");

		// check if player has won
		hasWon = check_if_won(word_to_guess, correct_guesses);
	}

	if (hasWon)
	{
		printf(GRN "You win!\n" RESET);
	}

	if (!hasWon && errors_made == max_errors)
	{
		printf(RED "You lose! The word was '%s'\n" RESET, word_to_guess);
	}

	free(word_to_guess);

	return 1;
}
