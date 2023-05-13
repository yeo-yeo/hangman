#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>

bool checkIfWon(char* wordToGuess, char* alreadyGuessed);
bool haveGuessedLetter(char letter, char* alreadyGuessed);
void add_guess_to_already_guessed(char guess, char* already_guessed);

int main(void) {
    printf("Welcome! Let's play hangman.\n");

    // run fn that chooses word.. it returns word (and letter count? not really nec)
    // fn that does a turn... inputs: word, remaining no of turns, guesses so far
    
    char wordToGuess[] = "rolo";

    int total_turns = 10;
    // is this going to assoc reference
    int remainingTurns = total_turns;
    bool hasWon = false;

    char alreadyGuessed[10];


    // this seems very dumb
    for (int i = 0; i < total_turns; i++) {
        alreadyGuessed[i] = '?';
    }

    while (hasWon == false && remainingTurns > 0) {

	printf("Current state: ");
	
// loop through word to guess and display __ or guessed letters    
	for (int i = 0; wordToGuess[i] != '\0'; i++) {
	      if (haveGuessedLetter(wordToGuess[i], alreadyGuessed)) {
		    printf("%c ", wordToGuess[i]);
		 } else {
		 printf("_ ");
		 }
	    }
	    printf("\n");;

	    // get next turn's input
// need to do something to make them only enter one letter
    	    char *guess = get_string("Next guess please: ");
	
	// add it to the array
	add_guess_to_already_guessed(guess[0], alreadyGuessed);
	

	// check if they've won
	hasWon = checkIfWon(wordToGuess, alreadyGuessed); 
	remainingTurns--;
    }

    if (hasWon) {
    printf("You win!");
    }

    if (!hasWon && remainingTurns == 0) {
    printf("You lose!");
    }

    printf("    _____    \n    |   !   \n    |   O   \n    |  /|\\  \n    | / | \\  \n    |  / \\  \n    | /   \\\n____|____  \n");

    return 1;

}

bool checkIfWon(char* wordToGuess, char* alreadyGuessed) {
	printf("Checking...\n");
	return false;
}

bool haveGuessedLetter(char letter, char* alreadyGuessed) {
	for (int i = 0; i < sizeof(alreadyGuessed); i++) {
	    if (letter == alreadyGuessed[i]) {
	    return true;
	    } 
	}
	return false;
}
void add_guess_to_already_guessed(char guess, char* already_guessed) {
	for (int i = 0; i < sizeof(already_guessed); i++) {
	    if (already_guessed[i] == '?') {
		already_guessed[i] = guess;
	        break;
	}
	}
}
