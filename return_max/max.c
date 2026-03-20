#include <stdio.h> 

int main() {
	int a = -5;
	int b = 3;
	
	int max = a ^ (a ^ b) & (a - b) >> 31;
	printf("The bigger int is: %d", max);
	return 0;
}

