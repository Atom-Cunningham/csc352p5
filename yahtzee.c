#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int print_int_array(int size, int dice[], int attempt);
/***********************
 * game rules
 */

/**takes an integer array to modify
 * the integers are replaced with random numbers 1 to 6 inclusive
 * and then any of them can be replaced again
 * at the user's requested (cardinal) index up to twice
 * 
 * returns 0
 */
int turn(int dice[]){
    read_roll_nodrvr(6, dice);
    int i;
    for(i = 1; i <= 3; i++){
        print_int_array(6, dice, i);
        if(reroll(dice)){          //user input of 0 returns 1
            return 0;              //to break out
        }    
    }
    return 0;
}

/**returns a 1 if all categories in the scoring section are non-zero
 */
int game_over(int size, int * section){
    int i;
    for(i = 0; i < size; i++){
        if(section[i] == 0){        //empty entry
            return 0;
        }
    }return 1;
}

/**returns true if the integer is between 0 and 6 inclusive
 */
int is_valid_die_idx(int die){
    return die >= 0 && die <7;
}

/***********************
 * scoring
 */

/**calculates the sum of all integers in the array
 * which have the same value as the integer passed in arg1
 * takes an integer, and int[]
 * returns the sum
 */
int get_sum(int num, int * dice){
    int sum = 0;
    int i;
    for(i = 0; i < 6; i++){
        if(dice[i] == num){
            sum += num;
        }
    }
    return sum;
}

/**returns the sum of the integers in an array
 * takes the array size and the array
 */
int sum_array(int size, int * arr){
    int i;
    int sum = 0;
    for(i = 0; i < size; i++){
        sum += arr[i];
    }
    return sum;
}

/**looks for num instances of any number in the array
 * 3,4 instances sums, 5 scores 50 (yahtzee)
 * 
 * returns 0 on failure;
 */
int sum_of_a_kind(int num, int * dice){
    int count;
    int curr;                                //current die
    int i;
    int j;
    for(curr = 1; curr <= 6; curr++){        //loop through die possibilities
        count = 0;
        for(j = 0; j < 6; j++){     //loop through dice
            if(dice[j] == i){
                count++;
            }    
        }
        if(count == num){
            if(count == 5){         //yahtzee
                return 50;
            }
            return get_sum(curr, dice);
        }
    }
    return 0;
}

//sum of a kind 3 != 0
//&& sum of a kind 2 != 0

//&&sum of a kind 3 != soak2 +soak2/2




//qsort dice
//small straight 4
//large straight 5

/**********************
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

/********************************
 * output
 */

/**prints the contents of an integer array
 * takes the size of the array, and an int array
 * returns 0
 */
int print_int_array(int size, int dice[], int attempt){
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
    }printf("\n\n");
    //print last die with newline
    i++;
    printf("%d\n", dice[i]);

    return 0;
}

/**prints out a section, with its labels and current entries
 */
void print_section(int size, char ** labels, int * section){
    int i;
    for(i = 0; i < size; i++){
        if(i%2 == 0){
            printf("%s %d", labels[i], section[i]);
        }
        else{
            printf("%22s %d\n", labels[i], section[i]);
        }
    }printf("\n\n");
}


/****************************************
 * user input
 */

/**takes user input, the index+1 of dice to reroll
 * returns 0 on continue. 1 if the user exits
 */
int reroll(int * dice){

    char in[100];

    int rerolls = 0;
    int idx;
    int i = 0;
    fgets(in, 100, stdin);                      //get user input
    for(i = 0; i < 100 && rerolls < 6; i++){    //while in str bounds, and have die left to reroll
        idx = in[i] - '0';                  
        if(idx == 0){return 1;}                 //0 breaks out
        idx--;                                  //player refers to idx 0 as 1 ect
        
        if(is_valid_die_idx(idx)){              //check idx is valid index
            printf("idx = %d\n", idx);
            rerolls++;                           
            dice[idx] = get_random_die();       //reset idx
        }
    }
    return 0;
}

/**accepts a 1 or 2 as user input
 * returns the input, or 0 if invalid
 */
int get_section(){
    int selection = 0;
    printf("Place dice into:\n1) Upper Section\n2) Lower Section\n\n");
    while(selection != 1 && selection !=2){
        scanf("Selection? %d\n\n", &selection);
    }
    return selection;
}

int upper_entry(int * dice, int * section){
    printf("Place dice into:\n1) Ones\n2) Twos\n3) Threes\n4) Fours\n5) Fives\n6) Sixes\n\n");

    //get selection
    int selection = 0;
        scanf("Selection? %d\n\n", &selection);
    while( selection < 1 || selection > 6){
        scanf("Selection? %d\n\n", &selection);
    }

    section[selection] = get_sum(selection, dice);
}


int lower_entry(int * section){
    printf("1) Three of a Kind\n2) Four of a Kind\n3) Small Straight\n4) Large Strait\n5) Full House\n6) Yahtzee\n7) Chance:\n\n");
    //get selection
    int selection = 0;
        scanf("Selection? %d\n\n", &selection);
    while( selection < 1 || selection > 7){
        scanf("Selection? %d\n\n", &selection);
    }
}

int main(int argc, char ** argv){
    //create necessary arrays
    int dice[5];
    char * upper_labels[6] = {"Ones:","Twos:","Threes:","Fours:","Fives:","Sixes:"};
    int    upper_section[6];

    char * lower_labels[7] = {"Three of a Kind:","Four of a Kind:","Small Straight:",
                             "Large Strait:","Full House:","Yahtzee:","Chance:"};
    int    lower_section[6];

    //initialize zeroes in score sections
    int i = 0;
    for(i = 0; i < 6; i++){
        upper_section[i] = 0;
        lower_section[i] = 0;
    }
    lower_section[++i] = 0;

    int selection = 0;
    int z;
    for(z = 0; z < 10; z++){
        turn(dice);
        selection = get_section() - '1' + 1;
        printf("got selection");
        if(selection == 1){
            upper_entry(dice, upper_section);
        }

        //display current total
        printf("Your score so far is: %d\n\n",
              sum_array(6, upper_section) 
            + sum_array(7, lower_section));
        print_section(6, upper_labels, upper_section);
        print_section(7, lower_labels, lower_section);
        
    }
    return 0;
}

