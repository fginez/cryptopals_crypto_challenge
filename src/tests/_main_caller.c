#include "../include/cryptopals.h"

#define APPLET_PROTO(name)	extern int name##_main(int argc, char** argv); extern char* name##_getdesc()
#define APPLET_ENTRY(name) name##_main
#define APPLET_GETDESCRIPTION(name)	name##_getdesc
#define INSERT_APPLET(name) {&APPLET_ENTRY(name), &APPLET_GETDESCRIPTION(name)}
typedef struct applet
{
	int (*entrypoint)(int, char**);
	char* (*desc)();
} APPLET;

#define NUM_OF_CHALLENGES 13
APPLET_PROTO(s1c1);
APPLET_PROTO(s1c2);
APPLET_PROTO(s1c3);
APPLET_PROTO(s1c4);
APPLET_PROTO(s1c5);
APPLET_PROTO(s1c6);
APPLET_PROTO(s1c7);
APPLET_PROTO(s1c8);
APPLET_PROTO(s2c9);
APPLET_PROTO(s2c10);
APPLET_PROTO(s2c11);
APPLET_PROTO(s2c12);
APPLET_PROTO(s2c15);

APPLET applet_list[NUM_OF_CHALLENGES] = {
	INSERT_APPLET(s1c1),
	INSERT_APPLET(s1c2),
	INSERT_APPLET(s1c3),
	INSERT_APPLET(s1c4),
	INSERT_APPLET(s1c5),
	INSERT_APPLET(s1c6),
	INSERT_APPLET(s1c7),
	INSERT_APPLET(s1c8),
	INSERT_APPLET(s2c9),
	INSERT_APPLET(s2c10),
	INSERT_APPLET(s2c11),
	INSERT_APPLET(s2c12),
	INSERT_APPLET(s2c15),
};

void put_screen_divisor()
{
	const int len = 50;
	int n;
	printf("\n");
	for ( n=0; n<len; n++ )
		printf("-");
	printf("\n");
}

int main(int argc, char** argv)
{
	int nAppletCounter = 0, iChallengeResult[NUM_OF_CHALLENGES];

	for ( nAppletCounter = 0; nAppletCounter < NUM_OF_CHALLENGES; nAppletCounter++ )
	{
		printf("Running test function for challenge %02d\n", nAppletCounter + 1 );
		printf("%-60s\n", applet_list[nAppletCounter].desc());
		iChallengeResult[nAppletCounter] = applet_list[nAppletCounter].entrypoint(1, NULL);
		put_screen_divisor();
	}

	// Show results summary
	printf("\n-----------------[ SUMMARY OF TEST RESULTS ]-----------------\n\n");
	for ( nAppletCounter = 0; nAppletCounter < NUM_OF_CHALLENGES; nAppletCounter++ )
	{
		printf("%-60s ", applet_list[nAppletCounter].desc());
		printf("[%7s]\n", (iChallengeResult[nAppletCounter]?"FAIL":"SUCCESS"));
	}

	return 0;
}
