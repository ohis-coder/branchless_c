#include <stdio.h>

int main() {
	int x = -11;
	int y = 4;
	
	printf("pre-ABS X: %d\n", x);
	printf("pre-ABS Y: %d\n", y);
	
	x = (x ^ (x >> 31)) - (x >> 31);
	y = (y ^ (y >> 31)) - (y >> 31);
	
	printf("ABS X: %d\n", x);
	printf("ABS Y: %d\n", y);
	return 0;
}