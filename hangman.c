#include<time.h>
#include <stdio.h>
#include <stdbool.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

bool checkIfWon(char* wordToGuess, char* alreadyGuessed);
bool haveGuessedLetter(char letter, char* alreadyGuessed);
void add_guess_to_already_guessed(char guess, char* already_guessed);
bool check_if_error(char* word_to_guess, char guess);
void print_current_state(char* word_to_guess, char* already_guessed);

// originally tried to put in another file - try again because i think the compiler issues i had were not related to being in another file
char* hangmen[] = {
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


int main(void) {
    printf("Welcome! Let's play hangman.\n");

    // run fn that chooses word.. it returns word (and letter count? not really nec)
    // fn that does a turn... inputs: word, remaining no of turns, guesses so far


    FILE *file = fopen("wordlist_test.txt", "r");
    // need to make array of arrays (strings) to load wordlist into?
    char words[80000][40]; // how to make it dynamic?
    int i = 0;
    while(fgets(words[i], 40, file) != NULL) {
	words[i][strlen(words[i]) - 1] = '\0';
         i++;	
		    }
    fclose(file);


   //  char wordToGuess[] = "rolo";
   //  TODO: should exclude word if its say less than 3 chars
   // also exlcude words with apostrophes (and any other punc) 
   // to avoid the word being corvette every single time
    srand(time(NULL));
    int wordToGuessIndex = rand() % i;
printf("word to guess index %i \n", wordToGuessIndex);
    char *wordToGuess = words[wordToGuessIndex];

    printf("word to guess %s \n", wordToGuess);

    int max_errors = 10;
    int errors_made = 0;
    bool hasWon = false;

    char alreadyGuessed[10];


    // this seems very dumb
    for (int i = 0; i < max_errors; i++) {
        alreadyGuessed[i] = '?';
    }
 

    // start playing! show them how long the word is
    print_current_state(wordToGuess, alreadyGuessed);



    while (hasWon == false && errors_made < max_errors) {

	    // get next turn's input
// need to do something to make them only enter one letter
    	    char *guess = get_string("Next guess please: ");

	printf("\n\n\n\n\n\n\n");

	// add it to the array
	add_guess_to_already_guessed(guess[0], alreadyGuessed);
	bool isError = check_if_error(wordToGuess, guess[0]);
	if (isError) {
	        errors_made++;
	}

	if (errors_made > 0) {	
	printf("%s", hangmen[errors_made - 1]);
	}

	print_current_state(wordToGuess, alreadyGuessed);
	// check if they've won
	hasWon = checkIfWon(wordToGuess, alreadyGuessed); 
        
   
    }

    if (hasWon) {
    printf("You win!\n");
    }

    if (!hasWon && errors_made == max_errors) {
    printf("You lose! The word was '%s'\n", wordToGuess);
    }

    return 1;

}

bool checkIfWon(char* wordToGuess, char* alreadyGuessed) {
	// for each letter of the reference word
	for (int i = 0; wordToGuess[i] != '\0'; i++) {
		// check if it's in the already guessed array
		bool found = false;
		for (int j = 0; j < sizeof(alreadyGuessed); j++) {
			if (wordToGuess[i] == alreadyGuessed[j]) {
			found = true;
			break;
			}
			// either youve returned early because it's true
			// if you've checked every letter and its still false, you havent won
		}
		  if (found == false) {
	      		  return false;
                        }
	}
	// still here? must have found everything!
	return true;
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

bool check_if_error(char* word_to_guess, char guess) {
	for (int i = 0; i <= sizeof(word_to_guess); i++) {
	if (guess == word_to_guess[i]) {
	   return false;
	} 
	}
	return true;
}

void print_current_state(char* word_to_guess, char* already_guessed) {
// loop through word to guess and display __ or guessed letters    
	for (int i = 0; word_to_guess[i] != '\0'; i++) {
  		if (haveGuessedLetter(word_to_guess[i], already_guessed)) {
		    printf("%c ", word_to_guess[i]);
		 } else {
		 printf("_ ");
		 }
	    }
	    printf("\n\n");
}
