#ifndef __SBXOR_DECODE_HEADER__
#define __SBXOR_DECODE_HEADER__

#define EN		0
#define PTBR 	1

int sbxor_decode(const unsigned char xoring_byte, unsigned char* data, unsigned int len);
int countoccur(const unsigned char test_char, const unsigned char* data, const unsigned int len);
float calc_score(const unsigned char test_char, const unsigned char* data, const unsigned int len);
void brute_force_sbxor(const int lang, const unsigned char *in, const unsigned int ilen,
                       unsigned char *out, unsigned int *olen,
                       unsigned char *xor_byte, float *score);
#endif
