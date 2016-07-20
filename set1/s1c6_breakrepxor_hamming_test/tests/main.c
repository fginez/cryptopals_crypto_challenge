#include <stdio.h>

// prototypes (used external to avoid useless header files)
extern int hamming_dist_test();
extern int repkxor_break_test();

int main()
{
	// check if hamming distance is working fine
	hamming_dist_test();
	
	// break the repeating key xor'ed file 
	repkxor_break_test();
	
	return 0;
}

