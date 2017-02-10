#ifndef __CRYPTO_MEMCMP_H__
#define __CRYPTO_MEMCMP_H__

#ifndef CRYPTO_memcp
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
#endif

#endif
