#include "hamming_dist.h"
#include <stdlib.h>

int hamming_dist(const void *in_a, const void *in_b, int len)
{
	size_t i, j;
	unsigned char x;
    const unsigned char *a = in_a;
    const unsigned char *b = in_b;	
	int d=0;

	for(i=0; i<len; i++)
	{		
		x = a[i]^b[i];
		for (j=0; j<8; j++)
		{
			if (1 == (x & 0x01))
			{
				d++;
			}
			x = x>>1;
		}
	}

	return d;
}
