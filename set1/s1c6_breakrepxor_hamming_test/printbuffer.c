#include "printbuffer.h"

void print_chars(const unsigned char *in, const unsigned int len)
{
    int i;
    for (i=0; i<len; i++)
        printf("%c", in[i]);    
}

void print_hex(const unsigned char *in, const unsigned int len)
{
    int i;
    for (i=0; i<len; i++)
        printf("%02.2X", in[i]);
}
