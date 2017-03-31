#include <stdio.h>
#include "printbuffer.h"

char is_printable_char(const unsigned char c)
{
  if ( c >= 0x20 || c==0x0a || c==0x0d ) {
    return 1;
  }

  return 0;
}

void print_chars(const unsigned char *in, const unsigned int len)
{
    int i;
    for (i=0; (unsigned int)i<len; i++) {
        if (is_printable_char(in[i])){
          printf("%c", in[i]);
        }
        else {
          printf("[**Non-printable:0x%2.2x**]", in[i]);
        }
    }
}

void print_hex(const unsigned char *in, const unsigned int len)
{
    int i;
    for (i=0; (unsigned int)i<len; i++)
        printf("%2.2X", in[i]);
}
