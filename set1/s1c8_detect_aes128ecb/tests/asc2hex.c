#include "asc2hex.h"

int asciib2hexb(const char* in, const int ilen, char* out, int* olen)
{
	int i=0, j=0;

	for (i=0; i<ilen; i+=2)
	{
		if ( i+1 < ilen )
		{
			out[j] = ascii2hex(in[i])<<4 | ascii2hex(in[i+1]);
			j++;
		}		
		else
		{
			break;
		}		
	}
	
	*olen = j;
	
	return j;
}

int ascii2hex(char in)
{
	if ( (in >= '0') && (in <= '9') )
	{
		return (in - 0x30);
	}

	else if ( (in >= 'A') && (in <= 'F') )
	{
		return (in - 0x37);
	}
	else if ( (in >= 'a') && (in <= 'f') )
	{
		return (in - 0x57);
	}
	else
	{
		return 0;
	}
}