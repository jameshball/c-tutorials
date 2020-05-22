#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define STRSIZE 8

char *p;
char str[STRSIZE];
char *q;

bool append( char *str, char *app, int maxlen )
{
	if( (strlen(str) + strlen(app)) >= maxlen )
	{
		return false;	/* failure: not enough space */
      	}
	strcat( str, app );
	return true;
}


int main( void )
{
	p = q = str;
	strcpy(str, "hello ");

	assert( append(str, "there", STRSIZE) );

	printf("str = %s\n", str);
	printf("p   = %s\n", p);
	printf("q   = %s\n", q);
	return 0;
}
