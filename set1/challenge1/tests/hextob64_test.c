#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hextob64.h"

#define NUM_TEST_STRINGS    4

#ifndef min
#define min(a,b) (a<b?a:b)
#endif

int main(int argc, char* argv)
{
    int i;
    
    const unsigned char test_array[NUM_TEST_STRINGS][49]={"M\0", 
                                                          "Ma\0",
                                                          "Man\0",
                                                          {0x49, 0x27, 0x6D, 0x20, 0x6B, 0x69, 0x6C, 
                                                           0x6C, 0x69, 0x6E, 0x67, 0x20, 0x79, 0x6F, 
                                                           0x75, 0x72, 0x20, 0x62, 0x72, 0x61, 0x69, 
                                                           0x6E, 0x20, 0x6C, 0x69, 0x6B, 0x65, 0x20, 
                                                           0x61, 0x20, 0x70, 0x6F, 0x69, 0x73, 0x6F, 
                                                           0x6E, 0x6F, 0x75, 0x73, 0x20, 0x6D, 0x75, 
                                                           0x73, 0x68, 0x72, 0x6F, 0x6F, 0x6D, 0x00} };

    const unsigned char res_array[NUM_TEST_STRINGS][65]= {"TQ==\0", 
                                                        "TWE=\0",
                                                        "TWFu\0",
                                                        "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t\0"};

    for(i=0; i<NUM_TEST_STRINGS;i++)
    {
        unsigned char* pOutput = (unsigned char*) malloc(hextob64_sizehelper(sizeof(test_array[i])));
        if ( NULL != pOutput )
        {
            int out_len;
            out_len = hextob64(test_array[i], strlen((char*)test_array[i]), pOutput);
            if (out_len)
            {
                printf("Testing string %d...", i);
                if ( 0 == strncmp((char*)pOutput, (char*)res_array[i], min(out_len, strlen((char*)res_array[i]) ) ) )
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

    return 0;
}
