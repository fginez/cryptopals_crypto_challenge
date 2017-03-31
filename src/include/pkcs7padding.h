#ifndef PKCS7PADDING_H_
#define PKCS7PADDING_H_

#include "../include/cryptopals.h"

int pkcs7padding_size(const int unpadded_size, const int blocklen);

int pkcs7unpadding_size(const unsigned char* input, const int padded_size, const int blocklen);

int pkcs7padding(const int blocklen, const int inputlen, const unsigned char *input,
				 int* outputlen, const int maxoutputlen, unsigned char *output);

int pkcs7unpadding(const int inputlen, const unsigned char *input,
				   int* outputlen, const int maxoutputlen, unsigned char *output);

#endif
