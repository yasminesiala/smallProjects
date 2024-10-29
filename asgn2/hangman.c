#include "hangman_strings.h"

/*
* Determine whather a char is lower-case.
*
* For this assignment only, YOU MAY NOT USE islower().  I want you to get
* experience in comparing character values.  So you will write code that
* checks whether c is between 'a' and 'z'.
*/
bool is_lowercase_letter(char c) {
    // Replace this comment with your source code.
    return false;
}

/*
* Determine whether a string contains the character that is given in the
* parameter "ch".  To determine whether the string contains the given
* character, you may use a "for" loop and strlen(), or you may use
* strchr().  Use the commands "man 3 strlen" and "man 3 strchr" to read
* more about these functions.  Look near the end of the man page for
* "RETURN VALUE" for the best summary.
*/
bool string_contains_character(const char *string, char ch) {
    // Replace this comment with your source code.
    return false;
}

/*
* Determine whether the length and contents of a secret are valid.  As
* described in the assignment PDF, valid secrets have a length that is no
* more than MAX_LENGTH (which already is defined for you in
* hangman_strings.h), and they must consist of only lower-case letters and
* the three punctuation characters '-', '\'', and ' '.
*
* 1. Use strlen() to confirm that the length of the secret does not exceed
*    MAX_LENGTH.  If it does, use printf() and MSG_LONG_SECRET_d to print
*    an error and return false.  (Look in hangman_strings.h to see what
*    MSG_LONG_SECRET_d represents.)
*
* 2. Using a "for" loop, verify that all of the secret's characters are
*    valid.  That is, that they are lower-case letters and the three kinds
*    of punctuation.  If any of the characters is illegal, then use
*    printf() and MSG_INVALID_CHAR_c to print an error and return false.
*    (Look in hangman_strings.h to see what
*    MSG_LONG_SECRET_d represents.)
*
* 3. If the secret is valid, then return true.
*
* Hint:  You can test that a character of the string is punctuation
* using individual "==" comparisions, or you can use your function
* string_contains_character() and the string "punctuation" (which is
* defined for you in hangman_strings.h).
*/
bool is_valid_secret(const char *secret) {
    // Replace this comment with your source code.
    return false;
}

/*
* Prompt for and return a character.
*
* 1. Use printf() and MSG_PROMPT to print the prompt.
* 2. In a loop, use getchar() to read an int.  (The function is called
*    getchar(), but it also might return EOF, and so we need to store its
*    return value in an int.)
* 3. If the character is '\n', then stay in the loop and call getchar()
*    again.
* 4. If the character is EOF, then call exit(1).
* 5. Return the character.
*/
char prompt_for_and_read_character(void) {
    // Replace this comment with your source code.
    return 0;
}

/*
* See Section 2 of the assignment PDF.
*/
void run_hangman(const char *secret) {
    // Replace this comment with your source code.
}

/*
* 1. Check the value of argc to confirm that the user runs hangman with a
*    "secret" on the command line.  If the user puts the wrong number of
*    arguments on the command line, then using printf() and
*    MSG_WRONG_NUM_ARGS to report an error, and then "return 1".
* 2. Call is_valid_secret().  If the function returns false, then 
*    "return 1;".
* 3. Call run_hangman(secret).
* 4. Return 0.
*/
int main(int argc, char **argv) {
    // Replace this comment with your source code.
    return 0;
}
