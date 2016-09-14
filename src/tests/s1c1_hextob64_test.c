#include "../include/cryptopals.h"
#include "../include/hextob64.h"

#define NUM_TEST_STRINGS    4

#ifndef min
#define min(a,b) (a<b?a:b)
#endif

char* s1c1_getdesc()
{
	return "Challenge 1 Convert hex to base64";
}


int s1c1_main(int argc, char** argv)
{
    int i;
    
    const unsigned char test_array[NUM_TEST_STRINGS][49]={"M\0",
                                                          "Ma\0"
                                                          "Man\0",
                                                          {0x49, 0x27, 0x6D, 0x20, 0x6B, 0x69, 0x6C, 
                                                           0x6C, 0x69, 0x6E, 0x67, 0x20, 0x79, 0x6F, 
                                                           0x75, 0x72, 0x20, 0x62, 0x72, 0x61, 0x69, 
                                                           0x6E, 0x20, 0x6C, 0x69, 0x6B, 0x65, 0x20, 
                                                           0x61, 0x20, 0x70, 0x6F, 0x69, 0x73, 0x6F, 
                                                           0x6E, 0x6F, 0x75, 0x73, 0x20, 0x6D, 0x75, 
                                                           0x73, 0x68, 0x72, 0x6F, 0x6F, 0x6D, 0x00} };

    const unsigned char res_array[NUM_TEST_STRINGS][66]= {"TQ==\0", 
                                                          "TWE=\0",
                                                          "TWFu\0",
                                                          "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t\0"};

	const unsigned char test_array2[NUM_TEST_STRINGS][20] = {"AwI=\0",
		                                                     "/w==\0",
		                                                     "MTIzNDU2Nzg5\0",
		                                                     "QUJDREU=\0" };
		                                                     
		
	const unsigned char res_array2[NUM_TEST_STRINGS][10] = {{ 0x03, 0x02, 0x00},
		                                                    { 0xFF, 0x00 } ,
		                                                    { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x00 },
		                                                    { 0x41, 0x42, 0x43, 0x44, 0x45, 0x00 } };
		                                                    
		

    for(i=0; i<NUM_TEST_STRINGS;i++)
    {
		unsigned char* pOutput = (unsigned char*) malloc(hextob64_sizehelper(sizeof(test_array[i])));
    	printf("Testing hex to base64 convertion\n");
        if ( NULL != pOutput )
        {
            int out_len;
            out_len = hextob64(test_array[i], strlen((char*)test_array[i]), pOutput);
            if (out_len)
            {
                printf("Testing string %d...", i);
                if ( 0 == strncmp((char*)pOutput, (char*)res_array[i], min((size_t)out_len, strlen((char*)res_array[i]) ) ) )
                {
                    printf("SUCCESS\n");
                }
                else
                {
                    printf("FAIL\n");
                }                    
            }
            else
            {
                printf("	FATAL! Encode string %d error\n", i);
            }
            
            free(pOutput);
            pOutput = NULL;
        }
    }

	printf("\n\n");

    for(i=0; i<NUM_TEST_STRINGS;i++)
    {
		unsigned char* pOutput = (unsigned char*) malloc(b64tohex_sizehelper(sizeof(test_array2[i])));
    	printf("Testing base64 to hex convertion\n");        
        if ( NULL != pOutput )
        {
            int out_len;
            out_len = b64tohex(test_array2[i], strlen((char*)test_array2[i]), pOutput);
            if (out_len)
            {
                printf("Testing string %d...", i);
                if ( 0 == strncmp((char*)pOutput, (char*)res_array2[i], min((size_t)out_len, strlen((char*)res_array2[i]) ) ) )
                {
                    printf("SUCCESS\n");
                }
                else
                {
					int j=0;
                    printf("FAIL - outlen=%d expected=%d out: ", out_len, strlen((char*)res_array2[i]));                    
                    for(j=0; j<out_len; j++) 
                    {
                    	printf("%c", *(pOutput+j));	
                    }
                    printf("\n");
                }                    
            }
            else
            {
                printf("	FATAL! Encode string %d error\n", i);
            }
            
            free(pOutput);
            pOutput = NULL;
        }
    }

    return 0;
}
