#include "../include/cryptopals.h"
#include "../include/libutil.h"
#include "../include/repkxor.h"

char* s1c5_getdesc()
{
	return "here comes set 1 challenge 5 description";
}

int s1c5_main()
{
	const unsigned char test_data[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
	const unsigned char key[3] = {'I', 'C', 'E'};	
	const unsigned char expected_result[] = {	0x0B, 0x36, 0x37, 0x27, 0x2A, 0x2B, 0x2E, 
												0x63, 0x62, 0x2C, 0x2E, 0x69, 0x69, 0x2A, 
												0x23, 0x69, 0x3A, 0x2A, 0x3C, 0x63, 0x24, 
												0x20, 0x2D, 0x62, 0x3D, 0x63, 0x34, 0x3C, 
												0x2A, 0x26, 0x22, 0x63, 0x24, 0x27, 0x27, 
												0x65, 0x27, 0x2A, 0x28, 0x2B, 0x2F, 0x20, 
												0x43, 0x0A, 0x65, 0x2E, 0x2C, 0x65, 0x2A, 
												0x31, 0x24, 0x33, 0x3A, 0x65, 0x3E, 0x2B, 
												0x20, 0x27, 0x63, 0x0C, 0x69, 0x2B, 0x20, 
												0x28, 0x31, 0x65, 0x28, 0x63, 0x26, 0x30, 
												0x2E, 0x27, 0x28, 0x2F 	};
	unsigned char *out = NULL;
	unsigned int out_len = 0;

	out = (unsigned char*) malloc(sizeof(test_data));
	if ( NULL == out )
	{
		printf("FATAL! Out of memory\n");
		return 0;
	}

	repkxor(key, sizeof(key), test_data, sizeof(test_data) - 1, out, &out_len);

	printf("Generated output: ");
	print_hex(out, out_len);
	printf("\n");
	printf("Checking...");
	if ( 0 == CRYPTO_memcmp( expected_result, out, min(out_len, sizeof(expected_result)-1)) )
	{
		free(out);
		printf("SUCCESS\n");
		return 0;
	}
	else
	{
		free(out);
		printf("FAIL");
		return -1;
	}	
}