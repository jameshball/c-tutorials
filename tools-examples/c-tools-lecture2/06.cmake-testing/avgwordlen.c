#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "intlist.h"
#include "defns.h"


/*
 * avgwordlen: find the average length of words in the
 * 	       unix dictionary, using linked lists.
 */

typedef struct {
	int sum;
	int total;
} sum_and_total;


void sumcb( int el, void *stsofar )
{
	sum_and_total *data = (sum_and_total *)stsofar;
	data->sum += el;
	data->total++;
}


int main( void )
{
	intlist l = intlist_nil();
	FILE *dict = fopen( DICTFILE, "r" );
	if( dict == NULL )
	{
		fprintf( stderr, "Can't open dictionary file %s\n", DICTFILE );
		exit(1);
	}
	/* foreach line in <dict> */
	char line[1024];
	while( fgets( line, 1024, dict ) != NULL )
	{
		/* chomp line */
		int len = strlen(line);
		if( line[len-1] == '\n' )
		{
			line[len-1] = '\0';
			len--;
		}
		/* prepend length(line) to l */
		l = intlist_cons( len, l );
	}
	fclose( dict );

	sum_and_total data = { 0, 0 };
	foreach_intlist( sumcb, &data, l );

	printf( "sum(word lengths) = %d, total = %d words, avg = %.2f letters per word\n",
		data.sum, data.total, data.sum/(double)data.total );

	free_intlist( l );

	return(0);
}
