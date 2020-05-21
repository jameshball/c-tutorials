/*
 * simple list-of-integers module: the implementation
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "intlist.h"


#define NEW(t) ((t)malloc(sizeof(struct t)))


intlist intlist_cons( int first, intlist next )
{
	intlist	new = NEW(intlist);
	new->first = first;
	new->next = next;
	return new;
}


kind_of_intlist intlist_kind( intlist this )
{
	if( this == NULL )
	{
		return intlist_is_nil;
	}
	return intlist_is_cons;
}


void get_intlist_cons( intlist this, int *first, intlist *next )
{
	*first = this->first;
	*next = this->next;
}


void print_intlist( FILE *f, intlist p )
{
	fputs( "[ ", f );
	while( p != NULL )
	{
		fprintf( f, "%d", p->first );
		if( p->next != NULL )
		{
			fputs( ",", f );
		}
		p = p->next;
	}
	fputs( " ]", f );
}


void sprint_intlist( char *s, intlist p )
{
	strcpy( s, "[ " );
	while( p != NULL )
	{
		char tempstr[100];
		sprintf( tempstr, "%d", p->first );
		strcat( s, tempstr );
		if( p->next != NULL )
		{
			strcat( s, "," );
		}
		p = p->next;
	}
	strcat( s, " ]" );
}


void foreach_intlist( foreach_intlist_callback cb, void *data, intlist p )
{
	while( p != NULL )
	{
		(*cb)( p->first, data );
		p = p->next;
	}
}


void free_intlist( intlist p )
{
	while( p != NULL )
	{
		intlist pn = p->next;
		free( p );
		p = pn;
	}
}


