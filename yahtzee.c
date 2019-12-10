#include <stdio.h>
#include <stdlib.h>

#define LOWER = 1;
#define UPPER = 6;


/**
 * game rules
 */

/**
 * scoring
 */

/**
 * get roll
 */ 
unsigned char get_random_byte(int max) {
         unsigned char c;
         //get_random_bytes(&c, 1);
         return c%max;
}

/**
 * returns a random number between 1 and 6 inclusive
 */
int get_random_die(){
    //random %(upper - lower +1) + lower
    return (rand() % (6-1 + 1)) + 1; //STDLIB call
}

/**
 * read roll
 */
int read_roll_nodrvr(int dice[]){
    int i;
    int rand;
    for(i = 0; i < 6; i++){
        rand = get_random_die();
        dice[i] = rand;
        printf("%s %d = %d\n", "random", i, rand);
    }
    return 0;
}

/**
 * user output
 */

/**prints the contents of an integer array
 * takes the size of the array, and an int array
 * returns 0
 */
void print_int_array(int max, int dice[]){
    printf("Your roll:\n\n");

    int i;
    for(i = 0; i < max-1; i++){
        printf("%d ", dice[i]);
    }
    //print last die with newline
    i++;
    printf("%d\n", dice[i]);
}

/**
 * user input
 */


int main(int argc, char ** argv){
    int dice[5];

    read_roll_nodrvr(dice);
    print_int_array(6, dice);
    return 0;
}

