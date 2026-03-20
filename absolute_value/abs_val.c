#import <stdio.h>

// return the positive value of whatever decimal inputed by the user without if condition

int main() {
	// create a bucket for the decimal input 
	// make it a char so it is 1 byte and readable as binary.... 
	// int is 4 bytes 
	char str[10];
	scanf("%s", str);
	
	// check if it is negative without if so we claim the str is - as true (1) and not - is false as (0)
	// on bit we just >> 31 for mask which act as a wall of 1s or 0s but for int we negate the neg 
	// negate the neg means 
	// -(1) that is ~1 + 1 that is ~00000001 + 1 that is 11111111
	// -(0) that is ~0 + 1 that is ~00000000 + 1 that is 00000000 
	int is_neg = (str[0] == '-');
	int mask = -is_neg;
	
	// this is tricky but i is 1 if the user inputed a negative number so we start counting from 1
	// if the user did not input a negative number we count from 0
	// so -5 is neg so i is 1 so we count from 5 
	// the val is also tricky but you can understand it as i have... 
	// if the user inputs 5 nice but 52 would be 5 + 2 = 7 
	// and we dont want to process prematurely so 0*5 + the number (5) is 5 cool 
	// now val is 5, if user inputs 2 we do 5 * 10 + 2 that is 52.. we are converting to base 10 basically
	// the str[i] - 0, its just like the c - 'a' to get the actual index of the letter in 0-26
	// what i am saying is that if the i is 4 that is not 4 to the pc that is 52 so to normalize...
	// ... we sub it by the first number that is 0 which is 48 therefore, 52-48 is 4 
	// we increment i by one to chec the next string which will be 1 or 2 
	// computers are weirdly autists
	int i = is_neg;
	int val = 0;
	
	// we check the user input for a digit to start the operation.. at [0] or [1]
	while (str[i] >= '0' && str[i] <= '9'){
		val = val * 10 + (str[i] - '0');
		i++;
	}
	
	// equivalent to the x = (x ^ mask) + mask
	// but apparently mask is 0xFF while is_neg is 1 or zero easy for adding than 11111111
	// one thing i did to truly master XOR is think of it as a ghost..
	// a ^ b = ghost..
	// that ghost can scare a into b or b into a..
	// a ^ ghost = b; 
	// b ^ ghost = a;
	// so when we look at this we have something funny and intuitive
	// val ^ mask will give us a ghost and when we add the 1 we get the positive 
	// if the mask was 0 meaning it was positive we allow it go through and add nothing 
	// no need for the the bitwise logic we already handled the - 
	// int positive_val = (val ^ mask) + is_neg;
	
	printf("Your positive number is: %d\n", val);

	return 0;
}