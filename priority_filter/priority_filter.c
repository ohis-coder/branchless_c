#include <stdio.h>

// say there are 3 buckets to redirect user input... 
// ...the main db file is 5kb slot allocated to name...
// ...but if user input is > we have to redirect to another file using
// ...i * j + (the new list location).
// the other files have slots that are 10kb, 30kb, 50kb each
// find the right bucket branchless style

int main() {
	// user input is x...
	// ...we allocate s1,s2,s3 for the other buckets each
	int x = 8240;
	int s1 = 10240;
	int s2 = 30240;
	int s3 = 50240;
	// we are just jumping into the looking for other bucket option... 
	// ...cba to start writing the jump with strides to find out that the original bucket will not fit..
	// ...but you get that it will just be  (default_size - user_input) >> 31...
	// ...0 means will fit, 1 means won't fit
	
	// now we need the mask to find the bucket fit from the others...
	// ...but for the start we believe that anything will fit into the biggest bucket (s3)...
	// ...buckle up for this logic...
	// ...we check if the s2 was a fit... if it was we use the inverse of the result to allow the selection change
	// we do the exact same thing with s1... we can do this for as many as we like...
	// ...hmm idk but this feels inefficient but whatever.. learning purposes is my cover...
	
	int current_selection = s3;
	
	int s2_mask = (s2 - x) >> 31;
	current_selection ^= (current_selection ^ s2) & ~s2_mask;
	int s1_mask = (s1 - x) >> 31;
	current_selection ^= (current_selection ^ s1) & ~s1_mask;
	
	printf("The perfect fit is bucket %d\n", current_selection);

		
	return 0;
}