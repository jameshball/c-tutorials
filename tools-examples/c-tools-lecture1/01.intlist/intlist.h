/*
 * intlist: simple list-of-integers module
 */

typedef struct intlist *intlist;
struct intlist {
	int	first;
	intlist	next;
};


typedef enum {
	intlist_is_nil,
	intlist_is_cons,
} kind_of_intlist;


typedef void (*foreach_intlist_callback)( int, void * );


#define intlist_nil() ((intlist)NULL)

extern intlist intlist_cons( int first, intlist next );
extern kind_of_intlist intlist_kind( intlist this );
extern void get_intlist_cons( intlist this, int * first, intlist * next );
extern void print_intlist( FILE * f, intlist p );
extern void sprint_intlist( char * s, intlist p );
extern void foreach_intlist( foreach_intlist_callback cb, void * data, intlist p );
extern void free_intlist( intlist p );
