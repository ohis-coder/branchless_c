#include <stdio.h>
#include <stdint.h>

#define NUM_STATES 4
#define NUM_TIMES  3

// say no to SELECT allowed FROM rules WHERE time='Night' AND status='Busy' and yes to whatever it is i am doing down there 

// count the states
enum { online, free, busy, offline }; // our y-axis... states dont change 

int main() {
	int user_time = 2; // morning = 0, afternoon/evening = 1, night = 2.. change it to check at diff times
	int mechanic_john_state = 3; // this is hardcoded state of the mechanic.. will be a bit mask lol.. optimisation goes brr
	
	// stride is the number of mechanic states available or sizeof(mechanic_states)
	int stride = NUM_STATES;
	
	// rules.. i cant explain here... read the readme
	uint16_t ruleset = (0b0011 << 8) |  // Night rules
                   	   (0b1110 << 4) |  // Afternoon rules
                       (0b1110 << 0);   // Morning rules; 
	
	// say user wants to book a mechanic named john at user_time...
	// ...with john having a state determined by no other but john here 
	int state = (user_time << 2) + mechanic_john_state; // i use << 2 here to avoid MUL only because i know the stride is 4 o... in your case calculate stride o
	
	int is_allowed_to_book = ruleset >> state & 1;
	
	printf("1 means you can book the mechanic at what ever time you choose, 0 means you can't book the mechanic, for now it is Morning\n");
	printf("The moment of Truth: %d\n", is_allowed_to_book);
	return 0;
}