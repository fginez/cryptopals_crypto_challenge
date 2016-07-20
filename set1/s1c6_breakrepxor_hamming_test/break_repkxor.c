#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hamming_dist.h"
#include "sbxor_decode.h"
#include "printbuffer.h"

void transpose_blocks(const unsigned char* in, unsigned char* out, const int bufferlen, const int keylen);
int discover_keylen(unsigned char* pucBuffer, unsigned int uiLen, int min, int max);

int discover_keylen(unsigned char* pucBuffer, unsigned int uiLen, int min, int max)
{
	int iKeySize;
	int minor_distance = 0;
	int minor_key = 0;

	// Test KEYSIZE
	for ( iKeySize=min; iKeySize<=max; iKeySize++ )
	{
		int iChunkBlocks = 4;
		int iChunkSize = iChunkBlocks * iKeySize; 
		int iHammingDist;
			
		unsigned char* pucBlockA = (unsigned char*) malloc(iChunkSize);
		unsigned char* pucBlockB = (unsigned char*) malloc(iChunkSize);
		
		if ( (NULL == pucBlockA) || (NULL == pucBlockB) ) 
		{
			printf("Out of memory\n");
			return 0;	
		}
		
		// Take the first KEYSIZE worth of bytes 
		memcpy(pucBlockA, pucBuffer + 0, iChunkSize);
		memcpy(pucBlockB, pucBuffer + iChunkSize, iChunkSize);

		// Calculate the hamming distance						
		iHammingDist = hamming_dist(pucBlockA, pucBlockB, iChunkSize) / iChunkBlocks;

		// Normalize it by KEYSIZE
		iHammingDist = (iHammingDist/iKeySize);
		
		free(pucBlockA);
		free(pucBlockB);
		
		if ( 0 == minor_distance )
		{
			minor_distance = iHammingDist;
			minor_key = iKeySize;
		}
		else 
		{
			if ( iHammingDist < minor_distance )
			{
				minor_distance = iHammingDist;
				minor_key = iKeySize;
			}	
		}
	}
	
	return minor_key;
}

void transpose_blocks(const unsigned char* in, unsigned char* out, const int bufferlen, const int keylen)
{
	int iNumOfPicks = bufferlen / keylen;
	int i, j, iTargetIndex, iOutIndex;
		
	for (j=0; j<keylen; j++)
	{
		iTargetIndex = j;
		for (i=0; i<iNumOfPicks; i++)
		{
			if (iTargetIndex < bufferlen)
			{
				out[iOutIndex] = in[iTargetIndex];
			}
			
			iTargetIndex += keylen;		
			iOutIndex++; 
		}
	}
}

void break_it(unsigned char* pucBuffer, unsigned int uiLen)
{
	int i, j;
	int iMinKeyLen = 14;
	int iMaxKeyLen = 40;
	int iTransposedBlockLen = 0;
	int iGuessedKeyLen = 0;
	unsigned char * pucTransposedBuffer;
	unsigned char * pucKey;
	
	printf("Breaking buffer [len=%d]\n", uiLen);
	
	iGuessedKeyLen = discover_keylen(pucBuffer, uiLen, iMinKeyLen, iMaxKeyLen);	
	printf("Guessed key length = %d\n", iGuessedKeyLen);	
	
	pucKey = (unsigned char*) malloc(iGuessedKeyLen);
	
	pucTransposedBuffer = (unsigned char*) malloc(uiLen);
	
	transpose_blocks((const unsigned char*) pucBuffer, 
	                 (unsigned char*) pucTransposedBuffer, 
	                 (const int) uiLen, 
	                 (const int) iGuessedKeyLen);
	
	iTransposedBlockLen = uiLen / iGuessedKeyLen;
	
	printf("Discovering key\n");
	for(i=0; i<iGuessedKeyLen; i++)
	{
		unsigned char* pTempOut = (unsigned char*) malloc(iTransposedBlockLen);
		unsigned int uiOlen;
		
		int iTargetPos = i*iTransposedBlockLen;
				
		printf("bruteforce @ 0x%8.8X [len=%d]\n", iTargetPos, iTransposedBlockLen);
		printf("input begins with: ");
		print_hex(&pucTransposedBuffer[iTargetPos], 10); 
		
		brute_force_sbxor(EN, &pucTransposedBuffer[iTargetPos], iTransposedBlockLen, 
		                  pTempOut, &uiOlen, &pucKey[i]);
		                  
		printf("\t-> Discovered char: %c\n", pucKey[i]);		
		free(pTempOut);
	}
	
	printf("Decoding buffer using the key: ");
	print_chars(pucKey, iGuessedKeyLen); printf("\n");
	
	// Decode buffer	
	for(i=0; i<uiLen; i++)
	{
		*(pucBuffer+i) = *(pucBuffer+i) ^ *(pucKey+(i%iGuessedKeyLen)); 
	}
	
	free(pucKey);
	free(pucTransposedBuffer);	
}


