#include "../include/cryptopals.h"
#include "../include/libutil.h"
#include "../include/hextob64.h"
#include "../include/aes_common.h"
#include "../include/encryption_oracle.h"
#include "../include/pkcs7padding.h"

unsigned char base_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ .,;´`'\"?!";
unsigned char dictionary[sizeof(base_chars)][BLOCK_LEN];
unsigned char encoded_input[] = "Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkgaGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBqdXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUgYnkK";

char* s2c12_getdesc()
{
	return "Challenge 12 Byte-at-a-time ECB decryption (Simple)";
}

char get_char_from_dictionary(unsigned char* cryptogram)
{
	int len = sizeof(base_chars);
	int i;

	for(i=0; i<len; i++) {
		if (0 == CRYPTO_memcmp(cryptogram, dictionary[i], BLOCK_LEN) ) {
			return base_chars[i];
		}
	}

	return ' ';
}

int s2c12_main(int argc, char** argv)
{
	int i, outlen, decoded_in_len, ciphertext_len;
	unsigned char input[16], ciphertext[16];
	unsigned char* decoded_in;


	// Build dictionary
	for(i=0; i<sizeof(base_chars); i++) {
		memset(input, 0, sizeof(input));
		input[BLOCK_LEN-1] = base_chars[i];
		if (0 != aes128ecb_oracle(input, BLOCK_LEN, 
								  dictionary[i], (unsigned int*) &outlen, BLOCK_LEN) ) {
			return -1;
		}
	}

	decoded_in_len = b64tohex_sizehelper(sizeof(encoded_input));
	decoded_in = (unsigned char*) malloc(decoded_in_len);
	if ( NULL == decoded_in ){
		return -1;
	}

	// Decode input from b64 to hex
	decoded_in_len = b64tohex(encoded_input, strlen((char*)encoded_input), decoded_in);
	printf("Breaking cryptogram:\n");
	for(i=0; i<decoded_in_len;i++) {
		memset(input, 0, sizeof(input));
		input[BLOCK_LEN-1] = decoded_in[i];	

		// Encrypt it
		if ( 0 != aes128ecb_oracle(input, BLOCK_LEN, ciphertext, (unsigned int*) &ciphertext_len, BLOCK_LEN) ) {
			return -1;
		}

		printf("%c", get_char_from_dictionary(ciphertext));
	}

	return 0;
}
