#include "../include/pkcs7padding.h"

int pkcs7padding_size(const int unpadded_size, const int blocklen)
{
	int extra_bytes = unpadded_size % blocklen;
	int blocks = unpadded_size / blocklen;
	int paddedsize = 0;
	
	if ( 0 == blocks )
	{   // message is shorter than one block
		paddedsize = 1 * blocklen;	
	} 
	else if ( 0 < blocks && 0 == extra_bytes )
	{  // message length is equal to blocklen
		paddedsize = (blocks+1) * blocklen;
	}
	else 
	{  // message length is longer than one block, but blocklength is broken
		paddedsize = (blocks+1) * blocklen;
	}

	return paddedsize;
}

int pkcs7unpadding_size(const int padded_size, const int blocklen)
{
	return 0;
}

int pkcs7padding(const int blocklen, const int inputlen, const unsigned char *input,
				 int* outputlen, const int maxoutputlen, unsigned char *output)
{

	int padding_bytes = 0, paddedlen = 0, n = 0;
	unsigned char pad = 0x00;

	paddedlen = pkcs7padding_size(inputlen, blocklen);
	if ( maxoutputlen < paddedlen )
	{
		return -1;
	}

	if ( NULL != outputlen )
	{
		*outputlen = paddedlen;
	}

	padding_bytes = paddedlen - inputlen;
	pad = (unsigned char) padding_bytes;

	memcpy(output, input, inputlen);
	n = inputlen;
	do
	{
		output[n++] = pad;
	} while( --padding_bytes > 0 );

	return paddedlen;
}

int pkcs7unpadding(const int inputlen, const unsigned char *input,
				   int* outputlen, const int maxoutputlen, unsigned char *output)
{
	return 0;
}