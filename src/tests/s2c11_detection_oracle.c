#include "../include/cryptopals.h"
#include "../include/encryption_oracle.h"

char* s2c11_getdesc()
{
	return "Challenge 9 An ECB/CBC detection oracle";
}

int s2c11_main(int argc, char** argv)
{
	int i, tries = 10;
	for (i=0; i<tries; i++) {
		if (0 != detect_mode()) {
			return -1;
		}
	}
	return 0;
}