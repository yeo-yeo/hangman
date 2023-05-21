#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool checkIfWon(char *wordToGuess, char *alreadyGuessed)
{
    // for each letter of the reference word
    for (int i = 0; wordToGuess[i] != '\0'; i++)
    {
        // check if it's in the already guessed array
        bool found = false;
        for (int j = 0; alreadyGuessed[j] != '\0'; j++)
        {
            if (wordToGuess[i] == alreadyGuessed[j])
            {
                found = true;
                break;
            }
            // either youve returned early because it's true
            // if you've checked every letter and its still false, you havent won
        }
        if (found == false)
        {
            return false;
        }
    }
    // still here? must have found everything!
    return true;
}

bool has_been_guessed(char letter, char *correct_guesses, char *incorrect_guesses)
{
    for (int i = 0; i < strlen(correct_guesses); i++)
    {
        if (letter == correct_guesses[i])
        {
            return true;
        }
    }

    // strlen causes memory error
    for (int i = 0; i < strlen(incorrect_guesses); i++)
    {
        if (letter == incorrect_guesses[i])
        {
            return true;
        }
    }

    return false;
}
bool check_and_record_guess(char guess, char *word_to_guess, char *correct_guesses, char *incorrect_guesses)
{
    for (int i = 0; i < strlen(word_to_guess); i++)
    {
        if (guess == word_to_guess[i])
        {
            correct_guesses[strlen(correct_guesses)] = guess;
            return false;
        }
    }
    incorrect_guesses[strlen(incorrect_guesses)] = guess;
    return true;
}

void print_current_state(char *word_to_guess, char *correct_guesses)
{
    // loop through word to guess and display __ or guessed letters
    for (int i = 0; i < strlen(word_to_guess); i++)
    {
        // this is stupid
        char _placeholder = ' ';

        if (has_been_guessed(word_to_guess[i], correct_guesses, &_placeholder))
        {
            printf("%c ", word_to_guess[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n\n");
}

char *hangmen[] = {
    "             \n            \n            \n            \n             \n            \n           \n_________  \n",
    "             \n    |       \n    |       \n    |       \n    |        \n    |       \n    |      \n____|____  \n",
    "    _____    \n    |       \n    |       \n    |       \n    |        \n    |       \n    |      \n____|____  \n",
    "    _____    \n    |   !   \n    |       \n    |       \n    |        \n    |       \n    |      \n____|____  \n",
    "    _____    \n    |   !   \n    |   O   \n    |       \n    |        \n    |       \n    |      \n____|____  \n",
    "    _____    \n    |   !   \n    |   O   \n    |   |   \n    |   |    \n    |       \n    |      \n____|____  \n",
    "    _____    \n    |   !   \n    |   O   \n    |   |   \n    |   |    \n    |  /    \n    | /    \n____|____  \n",
    "    _____    \n    |   !   \n    |   O   \n    |   |   \n    |   |    \n    |  / \\  \n    | /   \\\n____|____  \n",
    "    _____    \n    |   !   \n    |   O   \n    |  /|   \n    | / |    \n    |  / \\  \n    | /   \\\n____|____  \n",
    "    _____    \n    |   !   \n    |   O   \n    |  /|\\  \n    | / | \\  \n    |  / \\  \n    | /   \\\n____|____  \n"};
