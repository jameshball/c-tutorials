/*	Library:	LISTS OF STRINGS				*/


typedef enum {FALSE, TRUE} bool;


struct node;
typedef struct node *list;
struct node {
		char *string;			
		list next;
	    };

	
extern bool list_mt (list l);
/*	Is the list l empty?  
	Returns TRUE if it is empty, FALSE otherwise.			*/


extern bool in_list (list l, char *s);
/*	Is a given string s in the list l?  
	Returns TRUE if string is present, FALSE otherwise.		*/


extern void print_list (list l, FILE *stream);
/*	Writes the list l of strings as output to stream.		*/


extern list new_list (void);
/*	Creates a new empty list which it returns.  
	Returns NULL if the request cannot be satisfied.		*/


extern list cons_list (list l, char *s);
/*	Attach a new string s to the head of the list l.  
	Returns new list if successful.  
	Returns NULL if the request cannot be satisfied.		*/


extern list incr_list (list l, char *s);
/*	Attach a new string s to the tail of the list l.  
	Returns new list if successful.  
	Returns NULL if the request cannot be satisfied.		*/


extern char *behead_list (list *pl, char **ps);
/*	Detach the string at the head of the list pointed to by pl and 
	put that string (address) in the location pointed to by ps.  
	Returns the detached string.  
	Returns NULL if the list is already empty.			*/


extern char *decr_list (list *pl, char **ps);
/*	Detach the string at the tail of the list pointed to by pl and 
	put that string (address) in the location pointed to by ps.  
	Returns the detached string.  
	Returns NULL if the list is already empty.			*/

	
extern int kill_list (list l);
/*	Erases the empty list l. 
	Returns 1 if success (list l is empty and so deleted).
	Returns 0 if failure (list l is NOT empty and NOT deleted).	*/


