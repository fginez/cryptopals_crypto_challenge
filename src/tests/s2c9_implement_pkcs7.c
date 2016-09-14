#include "../include/cryptopals.h"
#include "../include/libutil.h"
#include "../include/pkcs7padding.h"

char* s2c9_getdesc()
{
	return "Challenge 9 Implement PKCS#7 padding";
}

int s2c9_main(int argc, char** argv)
{
	int n;
	const int  tests = 9;
	const int  insizes[] = {7, 8 ,9,15,16,17,31,32,33};
	const int  blsizes[] = {8, 8 ,8,16,16,16,32,32,32};
	const int  ousizes[] = {8,16,16,16,32,32,32,64,64};

	const char input[] = "YELLOW SUBMARINE";
	const char expected[] = "YELLOW SUBMARINE\x04\x04\x04\x04";
	const int  block_length = 20;
	int paddedlen, outlen;
	char* output;


	printf("Testing padded message output sizes\n");
	for( n=0; n<tests; n++ )
	{
		printf("%2d input bytes and %2d block len bytes must result into %2d bytes at output...",
			   insizes[n], blsizes[n], ousizes[n] );
		if ( pkcs7padding_size(insizes[n], blsizes[n]) == ousizes[n] )
		{
			printf("SUCCESS\n");
		}
		else
		{
			printf("FAILED!\n");
			return -1;
		}
	}

	printf("Testing padding\n");
	paddedlen = pkcs7padding_size(strlen(input), 20);
	output = (char*) malloc(paddedlen + 1);
	if ( NULL == output )
	{
		printf("Out of memory. FAILED!\n");
		return -1;
	}

	memset(output, 0, paddedlen + 1);

	if (0>= pkcs7padding(20, strlen(input), (const unsigned char*)input, &outlen, paddedlen, (unsigned char*) output))
	{
		printf("Error during padding. FAILED!\n");
		free(output);
		return -1;
	}

	if ( 0 == strncmp(expected, output, strlen(expected) ) )
	{
		printf("SUCCESS!\n");
		free(output);
		return 0;
	}
	else
	{
		printf("Output is not equal to expected. FAILED!\n");
		free(output);
		return -1;
	}	
}
