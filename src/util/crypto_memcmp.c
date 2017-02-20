#include "../include/cryptopals.h"
#include "../util/crypto_memcmp.h"

int CRYPTO_memcmp(void* a, void* b, size_t len) 
{
	int res = 0;
	unsigned int i;
	unsigned char *pa, *pb;
	pa = (unsigned char*)a;
	pb = (unsigned char*)b;

	for ( i=0; i<len; i++) {
		if ( *pa != *pb ) {
			res = 1;
		}
	}

	return res;
}
