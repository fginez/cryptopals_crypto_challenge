#include "../include/cryptopals.h"
#include "../include/libutil.h"
#include "../include/sbxor_decode.h"

char* s1c3_getdesc()
{
	return "here comes set 1 challenge 3 description";
}

int s1c3_main()
{
    unsigned int out_len;
    unsigned char c;

    const unsigned char encoded_string[34] = {0x1B, 0x37, 0x37, 0x33, 0x31, 0x36, 0x3F, 0x78, 0x15, 0x1B, 0x7F, 0x2B, 0x78, 0x34, 0x31, 0x33, 0x3D, 0x78, 0x39, 0x78, 0x28, 0x37, 0x2D, 0x36, 0x3C, 0x78, 0x37, 0x3E, 0x78, 0x3A, 0x39, 0x3B, 0x37, 0x36};
	unsigned char out[sizeof(encoded_string) + 1];
	
	memset((char*)out, 0, sizeof(out));
	brute_force_sbxor(EN, encoded_string, sizeof(encoded_string), out, &out_len, &c);
	
	printf("Results of brute force single byte XOR\n");
	printf("XOR byte: '%c'\n", c);
	printf("Secret message: ");
	print_chars(out, out_len);
	printf("\n");
    
    return 1;
}


