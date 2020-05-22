/*
 * iterate.c: test program for the hash module.
 *
 * (C) Duncan C. White, 1996-2020 although it seems longer:-)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "hash.h"



void myPrint( FILE *out, hashkey k, hashvalue v )
{
	fprintf( out, "%s: %s\n", k, (char *)v );
}


static void myFree( hashvalue v )
{
	free( v );
}


static hashvalue myCopyValue( hashvalue v )
{
	return strdup(v);
}


static hash h1;


void set( hash h, hashkey k, char *v )
{
	hashSet( h, k, myCopyValue(v) );
}


void onerun( void )
{
	h1 = hashCreate( myPrint, myFree, myCopyValue );

	set( h1, "one", "eeny" );
	set( h1, "two", "meeny" );
	set( h1, "three", "miny" );
	set( h1, "four", "mo" );

	set( h1, "one", "alone" );
	set( h1, "aardvark", "ant" );
	set( h1, "three", "several" );

	hash h2 = hashCopy( h1 );

	set( h1, "one", "solitary" );
	set( h2, "one", "lonely" );

	hashFree( h1 );
	hashFree( h2 );
}


int main( int argc, char **argv )
{
	int lim = argc > 1 ? atoi(argv[1]) : 5000;
	int delay = argc > 2 ? atoi(argv[2]) : 0;
	int pauseevery = 4000;
	printf( "running %d iterations, then delay %d seconds\n", lim, delay );
	int timetodelay = pauseevery;
	for( int i=0; i<lim; i++ )
	{
		onerun();
		if( --timetodelay==0 )
		{
			usleep( (useconds_t)100000 );	// 0.1 second pause
			timetodelay = pauseevery;
		}
	}
	sleep( delay );
	exit(0);
	return 0;
}
