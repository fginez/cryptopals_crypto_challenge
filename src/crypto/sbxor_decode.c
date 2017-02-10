#include "../include/cryptopals.h"
#include "../include/sbxor_decode.h"

#define USE_SPACES_IN_ATTEMPTS

#ifdef USE_SPACES_IN_ATTEMPTS
#define ATTEMPTS	8
const unsigned char most_frequent_EN[ATTEMPTS]   = {' ', 'E', 'T', 'A', 'O', 'I', 'N', 'S'};
const unsigned char most_frequent_PTBR[ATTEMPTS] = {' ', 'A', 'E', 'O', 'S', 'I', 'N', 'S'};
#else
#define ATTEMPTS	4
const unsigned char most_frequent_EN[ATTEMPTS]   = {'E', 'T', 'A', 'O'};
const unsigned char most_frequent_PTBR[ATTEMPTS] = {'A', 'E', 'O', 'S'};
#endif



const unsigned char xor_chars[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 |\\,.;/<>:?Á«~]^}¥[`{'\"!@#$%®&*()_+-="};

int sbxor_decode(const unsigned char xoring_byte, unsigned char* data, unsigned int len)
{
    unsigned int i;
    
    for (i=0; i<len; i++)
    {
        data[i] = data[i]^xoring_byte;
    }
    
    return 1;
}

int count_occur(const unsigned char test_char, const unsigned char* data, const unsigned int len)
{
	unsigned int i, c = 0;
	
	for (i=0; i<len; i++)
	{
		if ( data[i] == test_char )
		{
			c++;
		}
	}
	
	return (int)c;
}

float calc_score(const unsigned char test_char, const unsigned char* data, const unsigned int len)
{
	float score;
	
	score = (float)count_occur(test_char, data, len) / (float)len;
	
	return score;	
}

void brute_force_sbxor(const int lang, const unsigned char *in, const unsigned int ilen,
                       unsigned char *out, unsigned int *olen,
                       unsigned char *xor_byte, float *score)
{
	int i, w, ws;
    unsigned char *working_buffer, *freq_letters;
    float scores[sizeof(xor_chars)], winner_score, second_score;
    
    *olen = 0;
    *xor_byte = 0;
    
    switch(lang)
    {
    	case EN:
    		freq_letters = (unsigned char*) most_frequent_EN;
    		break;
    	
    	case PTBR:
    		freq_letters = (unsigned char*) most_frequent_PTBR;
    		break;    	
    	
    	default:
    		return;
    }
    
    working_buffer = (unsigned char*) malloc(ilen);
    if ( NULL == working_buffer )
    	return;
    
    for (i=0; i<sizeof(xor_chars); i++)
    {    	
    	float score = 0;
    	int j;
    	
        memcpy((char*)working_buffer, (char*) in, ilen);
        sbxor_decode(xor_chars[i] , working_buffer, ilen);
        
        for (j=0; j<ATTEMPTS*2; j++)
        {
        	if (j < ATTEMPTS)
        		score += calc_score(freq_letters[j], working_buffer, ilen);
        	else
        		score += calc_score(tolower(most_frequent_EN[j]), working_buffer, ilen);
        }

		scores[i] = score;
    }
    
    w = 0;
	ws = 0;
    winner_score = 0;
	second_score = 0;
	for (i=0; i<sizeof(xor_chars); i++)
	{
		if ( scores[i] > winner_score )
		{
			second_score = winner_score;
			winner_score = scores[i];
			ws = w;
			w = i;
		}
	}
	
	*olen = ilen;
	*xor_byte = xor_chars[w];
	
	sbxor_decode(xor_chars[w] , working_buffer, ilen);
	
	memcpy((char*)out, (char*) working_buffer, *olen);
	*score = winner_score;

	printf("XOR byte=%c score=%f (second option=%c score=%f)\n", *xor_byte, *score, xor_chars[ws], second_score);

	free(working_buffer);	
}
