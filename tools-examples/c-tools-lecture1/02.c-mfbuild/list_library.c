#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list_library.h"

#define LISTEND NULL
#define NOSTRING NULL

/* Is a list empty? */
bool list_mt (list plist)				/* done */
{
	if (plist->next == LISTEND && plist->string == NOSTRING)
		return TRUE;
	else
		return FALSE;
}

/* Is a given string in a list? */
bool in_list (list plist, char *pfindstring)		/* done */
{
	list pnode;
	
	if (list_mt (plist) == TRUE)
		return FALSE;				/* list is empty */	
	for (pnode = plist; pnode->next != LISTEND; pnode = pnode->next)
	{
		if (strcmp (pnode->string, pfindstring) == 0)
			return TRUE;
	}	
	/* we are now at last node in list */
	if (strcmp (pnode->string, pfindstring) == 0)
		return TRUE;	

	return FALSE;
}

/* Print a list of strings in a file */
void print_list (list plist, FILE *filout)		/* done */
{
	list pnode;
	
	if (list_mt (plist) == FALSE)			/* list is NOT empty */
	{
		for (pnode = plist; pnode->next != LISTEND; pnode = pnode->next)
		{
			fprintf (filout, " %s", pnode->string);
		}	
		/* we are now at last node in list */
		fprintf (filout, " %s", pnode->string);
	}
}

/* Create a new empty list */
list new_list (void)					/* done */
{
	list plist;
	
	plist = (list) malloc (sizeof (struct node));
	if (plist == NULL)
		return plist;		     /* calling function must handle error */

	/* memory chunk is supplied UNinitialised */
	plist->string = NOSTRING;
	plist->next = LISTEND;

	/* memory chunk is now initialised */	
	return plist;
}

/* Attach a string to the head of a list */
list cons_list (list plist, char *pnewstring)		/* done */
{
	list pnewnode;
	
	if (list_mt (plist) == TRUE)			/* list is empty */
	{
		plist->string = pnewstring;		/* so use sole node in it */
		return plist;
	}
	else						/* add another node */
	{
		pnewnode = (list) malloc (sizeof (struct node));
		if (pnewnode == NULL)
			return pnewnode;     /* calling function must handle error */
			
		/* memory chunk is supplied UNinitialised */
		pnewnode->string = pnewstring;
		pnewnode->next = plist;			/* attach node to head */

		/* memory chunk is now initialised */	
		return pnewnode;
	}
}

/* Attach a string to the tail of a list */
list incr_list (list plist, char *pnewstring)		/* done */
{
	list pnode, pnewnode;
	
	if (list_mt (plist) == TRUE)			/* list is empty */
	{
		plist->string = pnewstring;		/* so use sole node in it */
	}
	else						/* add another node */
	{
		for (pnode = plist; pnode->next != LISTEND; pnode = pnode->next)
			/* for loop body intentionally empty */	;
		/* we are now at last node in list */
		pnewnode = (list) malloc (sizeof (struct node));
		if (pnewnode == NULL)
			return pnewnode;     /* calling function must handle error */

		/* memory chunk is supplied UNinitialised */
		pnewnode->string = pnewstring;
		pnewnode->next = LISTEND;
		pnode->next = pnewnode;			/* attach node to tail */

		/* memory chunk is now initialised */	
	}
	
	return plist;
}

/* Detach the string at the head of a list */
char *behead_list (list *pplist, char **ppdetstring)	/* done */
{
	list pjunknode;

	if (list_mt (*pplist) == TRUE)			/* list is empty */
	{
		*ppdetstring = (char *) NULL;		/* error: list empty */
	}
	else if ((*pplist)->next == LISTEND)		/* one-node list */
	{
		*ppdetstring = (*pplist)->string;
	/*	*pplist = *pplist;		*/	/* *pplist is unchanged */
		(*pplist)->string = NOSTRING;
	}
	else						/* multi-node list */
	{
		pjunknode = *pplist;
		*ppdetstring = (*pplist)->string;
		*pplist = (*pplist)->next;
		free (pjunknode);
	}

	return *ppdetstring;
}

/* Detach the string at the tail of a list */
char *decr_list (list *pplist, char **ppdetstring)	/* done */
{
	list pnode, pprevnode;
		
	if (list_mt (*pplist) == TRUE)			/* list is empty */
	{
		*ppdetstring = (char *) NULL;		/* error: list empty */
	}
	else if ((*pplist)->next == LISTEND)		/* one-node list */
	{
		*ppdetstring = (*pplist)->string;
	/*	*pplist = *pplist;		*/	/* *pplist is unchanged */
		(*pplist)->string = NOSTRING;
	}
	else						/* multi-node list */
	{
		for (pnode = *pplist; pnode->next != LISTEND; pnode = pnode->next)
			pprevnode = pnode;		/* note previous node */
		/* we are now at last node in list */
		pprevnode->next = LISTEND;
		*ppdetstring = pnode->string;
		free (pnode);
	}
	
	return *ppdetstring;
}

/* Erase an empty list */
int kill_list (list plist)				/* done */
{
	if (list_mt (plist) == TRUE)			/* list is empty */
	{
		free (plist);				/* so delete it */
		return 1;				/* show success */
	}
	else						/* list is NOT empty */
	{
		return 0;				/* show failure */
	}	
}

