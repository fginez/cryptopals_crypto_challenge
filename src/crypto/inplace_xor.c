#include "../include/inplace_xor.h"

void inplace_xor(unsigned char* buffer, const unsigned char* xoring_buffer, const unsigned int len)
{
  unsigned int i = 0;
  for ( i=0; i<len; i++ ){
    buffer[i] = buffer[i] ^ xoring_buffer[i];
  }
}
