#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <testutils.h>
#include "intlist.h"


void sumcb( int el, void *sumsofar )
{
	int *data = (int *)sumsofar;
	(*data) += el;
}


int main( void )
{
	intlist l = intlist_nil();
	testbool( intlist_kind( l ) == intlist_is_nil,
		"kind(nil) == nil" );

	l = intlist_cons( 100, l );
	testbool( intlist_kind( l ) == intlist_is_cons,
		"kind([100]) == cons" );

	intlist tail;
	int head;
	get_intlist_cons( l, &head, &tail );
	testint( head, 100, "head([100]) == 100" );
	testbool( intlist_kind( tail ) == intlist_is_nil,
		"kind(tail([100])) == nil" );

	l = intlist_cons( 200, l );
	get_intlist_cons( l, &head, &tail );
	testint( head, 200, "head([200,100]) == 200" );
	get_intlist_cons( tail, &head, &tail );
	testint( head, 100, "head(tail([200,100])) == 100" );

	l = intlist_cons( 300, l );
	l = intlist_cons( 400, l );

	char result[1000];
	sprint_intlist( result, l );
	teststring( result, "[ 400,300,200,100 ]", "sprint test" );

	int sum = 0;
	foreach_intlist( sumcb, (void *)&sum, l );
	testint( sum, 1000, "sum 1000" );

	free_intlist( l );

	return(0);
}
