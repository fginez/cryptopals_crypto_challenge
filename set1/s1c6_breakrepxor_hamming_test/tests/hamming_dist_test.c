#include <stdio.h>
#include "hamming_dist.h"

#define EXPECTED_DISTANCE	37

int main()
{
	int d;
	const unsigned char a[] = "this is a test";
	const unsigned char b[] = "wokka wokka!!!";

	printf("Checking hamming distance...");
	d = hamming_dist(a,b,sizeof(a));

	if ( EXPECTED_DISTANCE == d )
	{
		printf("SUCCESS!\n");
	}
	else
	{
		printf("FAIL!\n");
	}

	return 0;
}
