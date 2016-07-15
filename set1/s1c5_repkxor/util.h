#ifndef __UTIL_H_
#define __UTIL_H_

#ifndef min
#define min(a,b) (a<b?a:b)
#endif

int CRYPTO_memcmp(const void *in_a, const void *in_b, size_t len)
{
   size_t i;
   const unsigned char *a = in_a;
   const unsigned char *b = in_b;
   unsigned char x = 0;

   for (i = 0; i < len; i++)
   {
      x |= a[i] ^ b[i];
      if ( x != 0 )
      	printf("Diff found! %02X %02X\n", a[i], b[i]);
   }
   
   return x;
}

#endif
