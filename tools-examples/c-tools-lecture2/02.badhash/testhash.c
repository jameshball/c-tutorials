/*
 * testhash.c: unit test program for the hash module.
 *
 *	       specifically, let's have a hash : string->string
 *
 * (C) Duncan C. White, 1996-2020 although it seems longer:-)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "hash.h"


/* this version dumps not to a file, but into a "dump buffer" */

#define DUMPBUFSIZE (100*1024)
#define DUMPENTRIES 1024

static char dumpbuf[DUMPBUFSIZE];
static char *dumpptr = dumpbuf;
static int dumpleft = DUMPBUFSIZE-1;
static char *dumpentries[DUMPENTRIES];
static int dumpnentries = 0;


static void resetdump( void )
{
	*dumpbuf = '\0';
	dumpptr = dumpbuf;
	dumpleft = DUMPBUFSIZE-1;
	dumpnentries = 0;
}


/* testing "Print" - append to the dumpbuf instead, forming a csv list */
void myPrint( FILE *out, hashkey k, hashvalue v )
{
	char line[1024];
	sprintf( line, "%s:%s", k, (char *)v );
	int l = strlen(line);
	assert( dumpleft>l+1 );

	dumpentries[dumpnentries] = dumpptr;
	assert( dumpnentries < DUMPENTRIES );
	strcpy( dumpptr, line );
	dumpptr += l+1;
	dumpnentries++;
}


static void myFree( hashvalue v )
{
	free( v );
}


static hashvalue myCopyValue( hashvalue v )
{
	return strdup(v);
}


/*
 * test( testdescription, h, k, expectedvalue );
 *	given a test description, a hash, a key, and an expectedvalue
 *	(NULL if the key should not be present in the hash), lookup k in h,
 *	and report on what you find, in testutils format.
 */
void test( char *description, hash h, hashkey k, char *expectedvalue )
{
	hashvalue v = hashFind( h, k );
	printf( "T %s lookup - key '%s'", description, k );
	if( v != NULL )
	{
		if( expectedvalue == NULL )
		{
			printf( " found unexpectedly: FAIL" );
		} else if( strcmp((char *)v,expectedvalue) == 0 )
		{
			printf( ", correct value ('%s') found: OK", (char *)v );
		} else
		{
			printf( ", expected value '%s', found value '%s': FAIL",
				expectedvalue, (char *)v );
		}
	} else
	{
		if( expectedvalue != NULL )
		{
			printf( " not found (should have been): FAIL" );
		} else
		{
			printf( " should not be found, isn't: OK" );
		}
	}
	printf( "\n" );
}


void lookuptest( char *description, hash h, char *x1, char *x2, char *x3, char *x4, char *xaard, char *xgrumble )
{
	printf( "lookup tests for %s:\n", description );
	test( description, h, "one", x1 );
	test( description, h, "two", x2 );
	test( description, h, "three", x3 );
	test( description, h, "four", x4 );
	test( description, h, "aardvark", xaard );
	test( description, h, "grumble", xgrumble );
}


void set( hash h, hashkey k, char *v )
{
	hashSet( h, k, myCopyValue(v) );
}


/* 
 * each_cb: print out a (k,v) pair to the FILE *
 *	    hidden in the arg; used in the main
 *	    program to print the hash ourselves.
 */

static void each_cb( hashkey k, hashvalue v, hashvalue arg )
{
	FILE *out = (FILE *)arg;

	myPrint( out, k, v );
}


// sort/search comparator for strings
static int compare(const void *m1, const void *m2)
{
	char **a = (char **) m1;
	char **b = (char **) m2;
	//printf( "debug: comparing '%s' and '%s'\n", *a, *b );
	return strcmp(*a, *b);
}


//
// Sort dumpentries alphabetically, then join the entries (separated
// by sep) together, into result, which is guaranteed to be big enough.
//
void sort_and_join( char **dumpentries, int dumpnentries, char sep, char *result )
{
	// sort the dumpentries array
	qsort( dumpentries, dumpnentries, sizeof(char *), compare );

	char *p = result;
	*p = '\0';
	if( dumpnentries > 0 )
	{
		strcpy( p, dumpentries[0] );
		//printf( "debug: dumpentry[0] = %s\n", dumpentries[0] );
		p += strlen(p);
		for( int i=1; i<dumpnentries; i++ )
		{
			//printf( "debug: dumpentry[%d] = %s\n", i, dumpentries[i] );
			strcpy( p, "," );
			strcpy( p+1, dumpentries[i] );
			p += strlen(p);
		}
	}
	//printf( "debug: result=%s\n", result );
}


// join all dumpentries in SORTED order together with commas separating
// them, and test whether the result is exactly the same string as expected.
void test_dump_has_entries( char *description, char *expected )
{
	char result[DUMPBUFSIZE];

	sort_and_join( dumpentries, dumpnentries, ',', result );
	if( strcmp( result, expected ) == 0 )
	{
		printf( "T %s dump-has-entries (%s): OK\n", description, result );
	} else
	{
		printf( "T %s dump-has-entries (%s expected, %s found): FAIL\n", description, expected, result );
	}
}


int main( int argc, char **argv )
{
	hash h1 = hashCreate( myPrint, myFree, myCopyValue );

	if( argc > 1 )
	{
		malloc(strlen(argv[1]));
	}

	set( h1, "one", "eeny" );
	set( h1, "two", "meeny" );
	set( h1, "three", "miny" );
	set( h1, "four", "mo" );

	printf( "initial hash:\n" );
	resetdump();
	hashDump( NULL, h1 );
	test_dump_has_entries( "initial hash", "four:mo,one:eeny,three:miny,two:meeny" );

	lookuptest( "initial hash", h1, "eeny", "meeny", "miny", "mo", NULL, NULL );

	printf( "modify hash a bit:\n" );
	set( h1, "one", "alone" );
	set( h1, "aardvark", "ant" );
	set( h1, "three", "several" );

	printf( "modified hash:\n" );
	resetdump();
	hashDump( NULL, h1 );
	test_dump_has_entries( "modified hash", "aardvark:ant,four:mo,one:alone,three:several,two:meeny" );

	lookuptest( "modified hash", h1, "alone", "meeny", "several", "mo", "ant", NULL );

	printf( "\nprint the hash out using an explicit foreach loop:\n" );
	resetdump();
	hashForeach( h1, &each_cb, stdout );
	test_dump_has_entries( "modified hash foreach", "aardvark:ant,four:mo,one:alone,three:several,two:meeny" );

	printf( "copy the hash\n" );
	hash h2 = hashCopy( h1 );

	printf( "modify both hashes a bit:\n" );
	set( h1, "one", "solitary" );
	set( h2, "one", "lonely" );

	lookuptest( "cloned modified h1", h1, "solitary", "meeny", "several", "mo", "ant", NULL );
	lookuptest( "cloned modified h2", h2, "lonely", "meeny", "several", "mo", "ant", NULL );

	printf( "h1:\n" );
	resetdump();
	hashDump( NULL, h1 );
	test_dump_has_entries( "hash h1", "aardvark:ant,four:mo,one:solitary,three:several,two:meeny" );

	printf( "h2:\n" );
	resetdump();
	hashDump( NULL, h2 );
	test_dump_has_entries( "hash h2", "aardvark:ant,four:mo,one:lonely,three:several,two:meeny" );

	printf( "free h1\n" );
	hashFree( h1 );

	printf( "h2 after free h1:\n" );
	resetdump();
	hashDump( NULL, h2 );
	test_dump_has_entries( "hash h2 after free h1", "aardvark:ant,four:mo,one:lonely,three:several,two:meeny" );

	printf( "free the copy\n" );
	hashFree( h2 );

	exit(0);
	return 0;
}
