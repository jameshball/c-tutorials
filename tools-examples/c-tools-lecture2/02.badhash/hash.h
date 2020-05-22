/*
 * hash.h: hash storage for C..
 *  a hash (aka a map) is a hash table of (hashkey, hashvalue) trees..
 *  here hashkey == string, hashvalue == void * (generic pointer)
 *
 * (C) Duncan C. White, 1996-2020 although it seems longer:-)
 */


typedef struct hash_s *hash;
typedef void *hashvalue;
typedef char *hashkey;

typedef void (*hashprintfunc)( FILE *, hashkey, hashvalue );
typedef void (*hashforeachcbfunc)( hashkey, hashvalue, void * );
typedef void (*hashfreefunc)( hashvalue );
typedef hashvalue (*hashcopyfunc)( hashvalue );

extern hash hashCreate( hashprintfunc p, hashfreefunc f, hashcopyfunc c );
extern void hashEmpty( hash a );
extern hash hashCopy( hash h );
extern void hashFree( hash h );
extern void hashSet( hash a, hashkey k, hashvalue v );
extern int hashPresent( hash a, hashkey k, hashvalue * v );
extern hashvalue hashFind( hash a, hashkey k );
extern void hashForeach( hash a, hashforeachcbfunc cb, void * arg );
extern void hashDump( FILE * out, hash a );
extern int hashMembers( hash h );
extern int hashIsEmpty( hash h );

/*  calculate the min, max and average depth of all non-empty trees */
extern void hashMetrics( hash h, int * min, int * max, double * avg );
