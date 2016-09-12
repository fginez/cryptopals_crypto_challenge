#include "../include/cryptopals.h"

#define APPLET_PROTO(name)	extern int name##_main(int argc, char** argv); extern char* name##_getdesc()
#define APPLET_ENTRY(name) name##_main
#define APPLET_GETDESCRIPTION(name)	name##_getdesc
#define INSERT_APPLET(name) {&APPLET_ENTRY(name), &APPLET_GETDESCRIPTION(name)}

APPLET_PROTO(s1c1);
APPLET_PROTO(s1c2);

typedef struct applet
{
	int (*entrypoint)(int, char**);
	char* (*desc)();
} APPLET;

const unsigned int NUM_OF_CHALLENGES = 2;

APPLET applet_list[NUM_OF_CHALLENGES] = {
	INSERT_APPLET(s1c1),
	INSERT_APPLET(s1c2),
};

int main(int argc, char** argv)
{
	int nAppletCounter = 0;
	for ( nAppletCounter = 0; nAppletCounter < NUM_OF_CHALLENGES; nAppletCounter++ )
	{
		int iAppletReturnCode;
		printf("%s\n", applet_list[nAppletCounter].desc());
		iAppletReturnCode = applet_list[nAppletCounter].entrypoint();
	}

	return 0;
}
