/*      
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

/*
    Intro: For this MP, we realized that only the three functions, set_seed, start_game, and make_guess, needed to be modified or added to.
    So, we sequentially went through and completed each of them in order. The first two were fairly straight forward. With set_seed, we just
    had to figure out how sscanf worked and what it was returning. This return value determined if there was an error or not. For start_game, 
    we learned how the rand function worked and was used to generate a random position in the pool array to copy a string to the solution list,
    for each location in solution (0-3). Thus, this random function and the string copy, or strcpy, let us create a randomized solution set.
    For make_guess, this function was the most involed because a lot of its aspects were not intuitive at first. We began by following
    the algorithm to use loops to 1. check if there were errors (invalid number of inputs or invalid inputs themselves) 2. see if there were 
    perfect matches 3. see how many misplaced matches. We added the proper scoring system and return values, but we still got errors, so we realized
    that the guess set needed to be multidimensional like the solution array. Lastly, we also realized to account for special cases, like a guess
    with all the same inputs, we needed to have a separate array that marks which locations were already matched for perfect matches so theyre not 
    accounted for again for the misplaced matches nest loops.

    Partners: macraew2, mjzhang3

*/


#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

int guess_number;
int max_score;
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};
/* Show guessing pool -- This function prints "pool" to stdout
 * INPUT: none
 * OUTPUT: none
 */
void print_pool() {
    printf("Valid term to guess:\n\t");
    for(int i = 0; i < 8 ; ++i) {
        printf("%s ", pool[i]);
    }
    printf("\n");
}

/*
 * is_valid -- This function checks whether a string is valid
 * INPUTS: str -- a string to be checked
 * OUTPUTS: none
 * RETURN VALUE: 0 if str is invalid, or 1 if str is valid
 * SIDE EFFECTS: none
 */
int is_valid(char* str) {
    int i = 0;
    if (str == NULL) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (strcmp(str, pool[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]) {
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
    int seed;
    char post[2];
    if (sscanf(seed_str, "%d%1s", &seed, post) != 1) {  // checks if input is NOT exactly one integer and returns 0
        printf("set seed: invalid seed\n");             // error message if input is not one integer
        return 0;
    }
    else{                                               // input is one integer (valid input)
        srand(seed);                                    // sets seed for srand function
        return 1;
    }

}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 *               The score should be initialized to -1.  
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game () {
    
    int rand0 = rand() % 8;                 // uses rand function from stdio library to return random number & modulus' return value with highest number in range to return a random number within range
    strcpy(solutions[0], pool[rand0]);      // copies string from pool array from random location in it to first location in solutions
    int rand1 = rand() % 8;                 // new random location in pool array
    strcpy(solutions[1], pool[rand1]);      // copies string from pool from another random location into second location in solutions
    int rand2 = rand() % 8;
    strcpy(solutions[2], pool[rand2]);      // copies string from pool from another random location into third location in solutions
    int rand3 = rand() % 8;
    strcpy(solutions[3], pool[rand3]);      // copies string from pool from another random location into fourth location in solutions

    max_score = -1;                         // setting highest score
    guess_number = 1;                       // setting number of guesses

}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 strings from pool). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: none
 * RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid, 
 *               or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[]) {
    int perfect_match = 0;
    int misplaced_match = 0;
    int current_score = 0;
    char guess[4][10];       // multidimensional arrya for guesses
    char post[2];            // array for extranoues inputs
    int mark[4] = {0,0,0,0}; // array to mark which inputs are already matched

    /*
    checking if there are four inputs
    copying each of the guess strings into multidimensional array guess[]
    */
    if(sscanf(guess_str, "%s%s%s%s%1s", guess[0], guess[1], guess[2], guess[3], post) != 4){
        printf("make_guess: invalid guess \n");
        return 0;
    }

    // checking if each of the four inputs are valid
    for(int i=0; i<4; i++){                             // iterate through each of four positions
        if(is_valid(guess[i]) == 0){                    // if return value of is_valid is 0 then input is invalid
            printf("make_guess: invalid guess \n");
            return 0;
        }
    }
    for(int i=0; i<4; i++){                             // iterate through each of four positions
        if(strcmp(guess[i],solutions[i]) == 0){         // compare string in guess with string in solutions both in position i
            perfect_match++;                            // increment perfect match
            current_score = current_score +1000;        // add 1000 to current score
            mark[i] = 1;                                // mark position i in mark array as 1 to symbolize position as matched
        }
    }
    for(int i=0; i<4; i++){                             // iterate through each of four positions of guess
        if(mark[i] == 0){
            for(int j=0; j<4; j++){                         // iterate through each of four positions of solutions
                if(strcmp(guess[i],solutions[j]) == 0 && mark[j] ==  0){ // if the guess is equal
                    misplaced_match++;                      // iterate misplaced match
                    current_score = current_score + 100;    // add 100 to current core
                    break;
                }
            }
        }

    }
    
    if(current_score > max_score){                      // update highest score if current score is higher
        max_score = current_score;
    }
    printf("With guess %d, you got %d perfect matches and %d misplaced matches. \n Your score is %d and current max score is %d. \n", guess_number, perfect_match, misplaced_match, current_score, max_score);
    guess_number++;                                     // increment number of guesses
    if(perfect_match == 4){                             // if input is all perfect matches return 2
        return 2;
    }
    else{
        return 1;
    }
}
    
    




