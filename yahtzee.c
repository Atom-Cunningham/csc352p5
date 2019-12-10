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

int read_roll_nodrvr(int * dice){
    int i;
    for(i = 0; i < 6; i++){
        dice[i] = get_random_die();
    }
    return 0;
}

/**
 * read roll
 */
int main(int argc, char ** argv){
    int * dice[5];
    int i;
    for(i = 0; i < 6; i++){
        printf("%d",*dice[i]);
    }
    return 0;
}

