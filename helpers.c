#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

char *load_and_choose_word()
{
    int max_word_length = 40;
    FILE *file = fopen("wordlist.txt", "r");
    char words[80000][max_word_length];

    int i = 0;
    while (fgets(words[i], 40, file) != NULL)
    {
        words[i][strlen(words[i]) - 1] = '\0';
        i++;
    }
    fclose(file);

    // so that the word isn't 'corvette' every single time
    srand(time(NULL));
    int word_to_guess_index = rand() % i;

    static char *word_to_guess;
    word_to_guess = malloc(max_word_length);
    strcpy(word_to_guess, words[word_to_guess_index]);

    return word_to_guess;
}

bool check_if_won(char *word_to_guess, char *correct_guesses)
{
    // for each letter of the reference word
    for (int i = 0; word_to_guess[i] != '\0'; i++)
    {
        // check if it's in the already guessed array
        bool found = false;
        for (int j = 0; correct_guesses[j] != '\0'; j++)
        {
            if (word_to_guess[i] == correct_guesses[j])
            {
                found = true;
                break;
            }
            // either you've returned early because it's true
            // if you've checked every letter and its still false, you haven't won
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
    // loop through word to guess and display __ or correctly guessed letters
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
