#include <stdio.h>
#include <stdbool.h>

int main(void) {
    printf("Welcome! Let's play hangman.\n");

    // run fn that chooses word.. it returns word (and letter count? not really nec)
    // fn that does a turn... inputs: word, remaining no of turns, guesses so far
    
    int remainingTurns = 10;
    bool hasWon = false;


    while (hasWon == false && remainingTurns > 0) {
    	// takeTurn(wordToGuess, alreadyGuessed) 
	remainingTurns--;
    }

    if (hasWon) {
    printf("You win!");
    }

    printf("    _____    \n    |   !   \n    |   O   \n    |  /|\\  \n    | / | \\  \n    |  / \\  \n    | /   \\\n____|____  \n");
}
