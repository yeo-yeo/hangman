bool checkIfWon(char *wordToGuess, char *alreadyGuessed);
bool haveGuessedLetter(char letter, char *alreadyGuessed);
void add_guess_to_already_guessed(char guess, char *already_guessed);
bool check_if_error(char *word_to_guess, char guess);
void print_current_state(char *word_to_guess, char *already_guessed);
extern char *hangmen[];