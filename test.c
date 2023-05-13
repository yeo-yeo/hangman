#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>

int checkIfWon(char* wordToGuess, char* alreadyGuessed);

int main(void) {
    printf("Welcome! Let's play hangman.\n");

    // run fn that chooses word.. it returns word (and letter count? not really nec)
    // fn that does a turn... inputs: word, remaining no of turns, guesses so far
    
    char wordToGuess[] = "rolo";

    int remainingTurns = 10;
    bool hasWon = false;

    char alreadyGuessed[10];

    char *guess = get_string("Next guess please: ");

    while (hasWon == false && remainingTurns > 0) {
    	checkIfWon(wordToGuess, alreadyGuessed); 
	remainingTurns--;
    }

    if (hasWon) {
    printf("You win!");
    }

    printf("    _____    \n    |   !   \n    |   O   \n    |  /|\\  \n    | / | \\  \n    |  / \\  \n    | /   \\\n____|____  \n");

    return 1;

}

int checkIfWon(char* wordToGuess, char* alreadyGuessed) {
	printf("Checking...\n");
	return 1;
}
