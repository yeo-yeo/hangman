char *load_and_choose_word();

bool check_if_won(char *word_to_guess, char *already_guessed);

bool check_and_record_guess(char guess, char *word_to_guess, char *correct_guesses, char *incorrect_guesses);

void print_current_state(char *word_to_guess, char *correct_guesses);

bool has_been_guessed(char guess, char *correct_guesses, char *incorrect_guesses);

extern char *hangmen[];