#include "../include/fixed_xor.h"

int fixed_xor(const unsigned int len, const unsigned char* a, const unsigned char* b, unsigned char* c)
{
    unsigned int i;

    for (i=0; i<len; i++)
        c[i] = a[i]^b[i];
    
    return 1;
}
