#ifndef __HEXTOBASE64_HEADER__
#define __HEXTOBASE64_HEADER__

int hextob64(const unsigned char *in, const int in_len, unsigned char* out);
int hextob64_sizehelper(const int in_len);

int b64tohex(const unsigned char *in, const int in_len, unsigned char* out);
int b64tohex_sizehelper(const int in_len);

#endif
