#include <stdbool.h>
#include <stdio.h>

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

bool haveGuessedLetter(char letter, char *alreadyGuessed)
{
    for (int i = 0; alreadyGuessed[i] != '\0'; i++)
    {
        if (letter == alreadyGuessed[i])
        {
            return true;
        }
    }
    return false;
}
void add_guess_to_already_guessed(char guess, char *already_guessed)
{
    for (int i = 0; already_guessed[i] != '\0'; i++)
    {
        if (already_guessed[i] == '?')
        {
            already_guessed[i] = guess;
            break;
        }
    }
}

bool check_if_error(char *word_to_guess, char guess)
{
    for (int i = 0; word_to_guess[i] != '\0'; i++)
    {
        if (guess == word_to_guess[i])
        {
            return false;
        }
    }
    return true;
}

void print_current_state(char *word_to_guess, char *already_guessed)
{
    // loop through word to guess and display __ or guessed letters
    for (int i = 0; word_to_guess[i] != '\0'; i++)
    {
        if (haveGuessedLetter(word_to_guess[i], already_guessed))
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
