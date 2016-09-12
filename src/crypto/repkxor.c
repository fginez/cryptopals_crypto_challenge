#include "repkxor.h"

int repkxor(const unsigned char* key, const unsigned int klen,
            const unsigned char* in,  const unsigned int ilen,
            unsigned char* out, unsigned int *olen)
{
	int i = 0;
	int j = 0;
	do
	{
		out[i] = in[i]^key[j];
		i++;
		j++;
		if ( j == klen )
			j=0;

	} while(i < ilen);
	
	*olen = i;

	return i;
}