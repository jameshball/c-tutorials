#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#include "testutils.h"


void testbool( bool condition, char *testname )
{
        printf( "T %s: %s\n", testname, condition?"OK":"FAIL" );
}

void testint( int got, int expected, char *testname )
{
        printf( "T %s (expected=%d, got=%d): %s\n",
		testname, expected, got, expected==got?"OK":"FAIL" );
}

void testlong( long got, long expected, char *testname )
{
        printf( "T %s (expected=%ld, got=%ld): %s\n",
		testname, expected, got, expected==got?"OK":"FAIL" );
}

void testdouble( double got, double expected, char *testname )
{
        printf( "T %s (expected=%g, got=%g): %s\n",
		testname, expected, got, expected==got?"OK":"FAIL" );
}

void teststring( char *got, char *expected, char *testname )
{
        printf( "T %s (expected='%s', got='%s'): %s\n",
		testname, expected, got, strcmp(expected,got)==0?"OK":"FAIL" );
}
