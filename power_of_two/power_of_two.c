#include <stdio.h>

int main() {
	int x = 1;
	
	int is_power = x > 0 && (x & (x-1)) == 0x00;

	printf("1 for is Power of Two, 0 for is not Power of Two\n");
	printf("%d\n", is_power);
	return 0;
}