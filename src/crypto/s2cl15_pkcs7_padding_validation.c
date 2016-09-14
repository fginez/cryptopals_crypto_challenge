#include "../include/cryptopals.h"
#include "../include/libutil.h"
#include "../include/pkcs7padding.h"

#define SAMPLES 3

char* s2c15_getdesc()
{
	return "Challenge 15 PKCS#7 padding validation";
}

int s2c15_main(int argc, char** argv)
{
	unsigned char inputs[SAMPLES][20] = { "ICE ICE BABY\x04\x04\x04\x04",
								     	  "ICE ICE BABY\x05\x05\x05\x05",
									      "ICE ICE BABY\x01\x02\x03\x04" };

	unsigned char expected[SAMPLES][20] = { "ICE ICE BABY" ,
									        "ICE ICE BABY" ,
									        "ICE ICE BABY" };

	int results[SAMPLES] = { 12, -1, -1 };

	int n, outlen, maxoutlen;
	unsigned char* output;

	printf("Validating PKCS#7 paddings\n");
	for( n=0; n<SAMPLES; n++ )
	{
		int ret;

		maxoutlen = strlen((char*) inputs[n]);
		output = (unsigned char*) malloc(maxoutlen);
		if ( NULL == output )
		{
			printf("Out of memory. FAILED!\n");
			return -1;
		}

		ret = pkcs7unpadding(strlen((char*)inputs[n]), inputs[n], &outlen, maxoutlen, output);
		printf("test case #%d: padding is %s\n", n, (ret==-1?"INVALID":"VALID"));
		if( results[n] != ret )
		{
			printf("Error during unpadding (ret=%d exp=%d). FAILED!\n", ret, results[n]);
			free(output);
			return -1;
		}

		free(output);

	}

	return 0;
}
