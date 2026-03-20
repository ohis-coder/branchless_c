#include <stdio.h>

int main() {
	int flag = 1;
	int a = 23;
	int b = 33;
	int val = a ^ ((a ^ b) & -flag);
	printf("Flag is %d\n", flag); 
	printf("We are returning %d\n", val);
	return 0;
}