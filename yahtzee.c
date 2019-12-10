#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


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

/**populates an int array of size
 * for playing outsized the kernel only
 */
int read_roll_nodrvr(int size, int dice[]){
    int i;
    int rand;
    for(i = 0; i < size; i++){
        rand = get_random_die();
        dice[i] = rand;
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
void print_int_array(int size, int dice[], int attempt){
    char * count = "";
    if(attempt == 2){
        count = "second ";
    }
    if (attempt == 3){
        count = "third ";
    }
    printf("Your %s roll:\n\n", count);

    int i;
    for(i = 0; i < size-2; i++){
        printf("%d ", dice[i]);
    }
    //print last die with newline
    i++;
    printf("%d\n", dice[i]);
}

/**
 * user input
 */

/**takes user input, the index+1 of dice to reroll
 */
int reroll(int * dice){

    int idx;
    int i = 0;
    scanf("die to reroll %d", idx);
    for(i = 0; idx !=0 && i < 5; i++){
        printf("die roll idx %d\ndie = %d", idx, dice[idx]);
        if(idx == 0){
            break;
        }
        dice[idx] = get_random_die();
        scanf("die to reroll %d", idx);
    }
    return 0;
}

/**returns true if the integer is between 0 and 6 inclusive
 */
int is_valid_die_idx(int die){
    return die <= 0 && die <7;
}

int main(int argc, char ** argv){
    int dice[5];

    read_roll_nodrvr(6, dice);
    print_int_array(6, dice);
    return 0;
}

