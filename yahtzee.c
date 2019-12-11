#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int cmpfunc (const void * a, const void * b);
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
    for(i = 1; i < 3; i++){
        print_int_array(6, dice, i);
        if(reroll(dice)){          //user input of 0 returns 1
            return 0;              //to break out
        }    
    }print_int_array(6, dice, i-1);
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
    return die >= 0 && die <= 5;
}

/***********************
 * scoring
 */

/**calculates the sum of all integers in the array
 * which have the same value as the integer passed in arg1
 * takes an integer, and int[]
 * returns the sum
 */
int get_sum_of_dicetype(int num, int * dice){
    int sum = 0;
    int i;
    for(i = 0; i < 6; i++){
        if(dice[i] == num){
            sum += num;
        }
    }
    printf("sum is: %d\n",sum);
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
        printf("new Sum = %d\n", sum);
    }
    return sum;
}

/**looks for num instances of any number in the array
 * 3,4 instances sums all dice, 5 scores 50 (yahtzee)
 * 
 * returns 0 on failure;
 */
int x_of_a_kind(int num, int * dice){
    int count;
    int curr;                                //current die
    int i;
    int j;
    for(curr = 1; curr <= 6; curr++){        //loop through die possibilities
        count = 0;
        for(j = 0; j < 5; j++){     //loop through dice
            if(dice[j] == i){
                count++;
            }    
        }
        if(count >= num){
            if(count == 5){         //yahtzee
                return 50;
            }
            return sum_array(5, dice);
        }
    }
    return 0;
}

/**checks for two of a kind, and three of another kind
 * returns 25 if found both
 * else 0
 */
int full_house(int * dice){
    qsort(dice, 5, sizeof(int), cmpfunc);
    
    int count = 0;
    int two_of = 0;
    int three_of = 0;
    int i = 0;
    for (i = 1; i <= 6; i++){//loop through possibilities
        count = get_instances_of(i, 5, dice);
        if(count == 2){
            two_of = i;
        }
        if (count == 3){
            three_of = i;
        }
    }
    if(two_of && three_of){
        return 25;
    }return 0;
}

/**given an int, count the number of times that in appears in a list
 */
int get_instances_of(int num, int size, int * dice){
    //TODO DRY implement this in x_of_a_kind if you feel like it
    int i = 0;
    int count = 0;
    for (i = 0; i < size; i++){
        if (dice[i] == num){count++;}
    }return count;
}

/**compares two ints
 */
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}



/**if there are (int length) ascending dice in a row 
 * return an appropriate score, else 0;
 */
int straight(int length, int * dice){
    qsort(dice, 6, sizeof(int),cmpfunc);
    int i = 0;
    int count = 0;
    while(dice[i] < dice[i+1] && i++ < 5){
        count++;
    }i++; //count the last one

    if(count >= length){
        if (length == 4){
            return 30;
        }
        if (length == 5){
            return 40;
        }
    }
    return 0;
}
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
    }
    //print last die with newline
    i++;
    printf("%d\n\n", dice[i]);

    return 0;
}

/**prints a section and its score
 */
void print_entry_occupied(char* label, int score, int buffer){
    if (buffer){
        printf("%22s %d\n", label, score);
    }else{
        printf("%s %d", label, score);
    }
}

/**
 */
void print_entry_empty(char* label, int buffer){
    if (buffer){
        printf("%22s\n", label);
    }else{
        printf("%s", label);
    }
}

/**prints out a section, with its labels and current entries
 */
void print_section(int size, char ** labels, int * section){
    int i;
    int buffer;
    for(i = 0; i < size; i++){
        buffer = (i%2 == 1);
        if(section[i] >= 0){
            print_entry_occupied(labels[i], section[i], buffer);
        }else{
            print_entry_empty(labels[i], buffer);
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

    char in[64];
    int i;
    for(i = 0; i<64; i++){
        in[i] = 0;
    }

    int rerolls = 0;
    int idx;
    printf("Which dice to reroll? ");
    fgets(in, 100, stdin);
    printf("\n");                               //get user input
    for(i = 0; i < 100 && rerolls < 6; i++){    //while in str bounds, and have die left to reroll
        idx = in[i] - '0';                  
        if(idx == 0){return 1;}                 //0 breaks out
        idx--;                                  //player refers to idx 0 as 1 ect
        
        printf("idx before is_valid = %d\n",idx);
        if(is_valid_die_idx(idx)){              //check idx is valid index
            printf("idx = %d\n", idx);
            rerolls++;                           
            dice[idx] = get_random_die();       //reset@ idx
            printf("idx after get random die = %d\n",idx);
        }
    }
    return 0;
}

/**reads an int from stdio
 */
int read_int(){
    char buf[64];
    int i;
    for (i = 0; i < 64; i++){buf[i] = 0;};
    return fgets(buf, 100, stdin)[0] - '1' + 1;
}

/**accepts a 1 or 2 as user input
 * returns the input, or 0 if invalid
 */
int get_section(int max){
    char str[100];
    int selection = -1;
    while(selection < 0 || selection > max){
        printf("Selection? "); 
        selection = read_int();
        printf("selection read:%d\n", selection);
    }
    printf("\n\n");
    return selection;
}

int upper_entry(int * dice, int * section){
    printf("Place dice into:\n1) Ones\n2) Twos\n3) Threes\n4) Fours\n5) Fives\n6) Sixes\n\n");
    //get selection
    int selection = get_section(6);
    section[selection-1] = get_sum_of_dicetype(selection, dice);//cardinal to idx
    printf("selection %d set to %d", selection, section[selection]);
    return 0;
}


int lower_entry(int * dice,int * section){
    printf("1) Three of a Kind\n2) Four of a Kind\n3) Small Straight\n4) Large Strait\n5) Full House\n6) Yahtzee\n7) Chance:\n\n");
    //get selection
    int selection = get_section(7);
    
    return 0;
}

int main(int argc, char ** argv){
    //seed random
    srand(time(0));

    //create necessary arrays
    int dice[5];
    char * upper_labels[6] = {"Ones:","Twos:","Threes:","Fours:","Fives:","Sixes:"};
    int    upper_section[6];
    char * lower_labels[7] = {"Three of a Kind:","Four of a Kind:","Small Straight:",
                             "Large Strait:","Full House:","Yahtzee:","Chance:"};
    int    lower_section[7];

    //initialize zeroes in score sections
    int i = 0;
    //set the section values to -1;
    for(i = 0; i < 6; i++){
        upper_section[i] = -1;
        lower_section[i] = -1;
    }
    lower_section[6] = -1;

    int selection = 0;
    int z;
    for(z = 0; z < 10; z++){
        turn(dice);
        printf("Place dice into:\n1) Upper Section\n2) Lower Section\n\n");
        selection = get_section(2);
        if(selection == 1){
            upper_entry(dice, upper_section);
        }else if(selection == 2){
            lower_entry(dice, lower_section);
        }

        //display current total
        printf("Your score so far is: %d\n\n",
              (sum_array(6, upper_section) 
            +  sum_array(7, lower_section)));
        print_section(6, upper_labels, upper_section);
        print_section(7, lower_labels, lower_section);
        
    }
    return 0;
}

