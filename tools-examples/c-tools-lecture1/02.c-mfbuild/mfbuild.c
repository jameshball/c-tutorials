#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list_library.h"

#define MAXLINLEN 256

#define MAKEFILENAME		"Makefile"
#define PERSDEFSFILENAME	"mfbuilddefs"
#define THISPROGNAME		"mfbuild"

#define MAIN_C_FILE_MISSING	 1			/* Reason for failure */
#define NEW_LIST_REFUSED	 2			/* Reason for failure */
#define FILE_OPENING_REFUSED	 3			/* Reason for failure */
#define LIST_ATTACH_REFUSED	 4			/* Reason for failure */
#define STRING_SPACE_REFUSED	 5			/* Reason for failure */
#define FILE_WRITE_ERROR	 6			/* Reason for failure */
#define WRONG_CHAR_WRITTEN	 7			/* Reason for failure */

list todos;
list dones;
list nocs;

/* Create a copy, in memory, of a given string.  Return a pointer to the copy.	*/
char *copy_str_mem (char *pgivstring)
{
	char *pmemstring = strdup(pgivstring);
	if (pmemstring == NULL)
		exit (STRING_SPACE_REFUSED);		/* cannot proceed */

	/* memory chunk is now initialised */	
	return pmemstring;
}

/* Check whether or not a file exists.			*/
/* Return TRUE if it does, FALSE if it does not.	*/
bool file_exists (char *pfilename)
{
	FILE *infile;

	infile = fopen (pfilename, "r");		/* open file */
	if (infile == NULL)
	{
		return FALSE;				/* file NOT found */
	}
	else
	{
		fclose (infile);			/* file found */
		return TRUE;
	}
}

/* Copy the contents of one file to another. */
void copy_file (char *pinfilename, FILE *outfile)
{
	FILE *infile;
	int c, wc;
		
	infile = fopen (pinfilename, "r");		/* open input file */
	if (infile == NULL)
	{
		fprintf( stderr, "File '%s' not found.  ",
			pinfilename);/* warn user */
		fprintf( stderr, "We will continue without it.\n");
	}
	else
	{
		/* Read the input file character-by-character */
		while ((c = fgetc (infile)) != EOF)
		{
			/* and write it to the output file */
			if ((wc = fputc (c, outfile)) == EOF)
			{
				fprintf( stderr, "Error in writing to Makefile.\n");
				exit (FILE_WRITE_ERROR);/* cannot proceed */
			}
			if (wc != c)
			{
				fprintf( stderr, "Wrong character written to output file.");
				fprintf( stderr, "  '%d' written instead of '%d'.\n", wc, c);
				exit (WRONG_CHAR_WRITTEN);/* cannot proceed */
			}
		}
		fclose (infile);
	}
}

/* Convert file name strings in list to .o. */
void convert_list_to_dot_o (list conlist)
{
	char *pfilename;
	int fnlen;
	
	/* attach marker to tail of list */
	conlist = incr_list (conlist, "marker");
	if (conlist == NULL)
		exit (LIST_ATTACH_REFUSED);		/* cannot proceed */

	/* detach next file name from head of list */
	behead_list (&conlist, &pfilename);
	
	while (strcmp (pfilename, "marker") != 0)	/* marker not reached yet */
	{
		/* change file name ending to .o */
		fnlen = (int) strlen (pfilename);
		pfilename [fnlen-1] = 'o';

		/* attach file name to tail of list */
		conlist = incr_list (conlist, pfilename);

		/* detach next file name from head of list */
		behead_list (&conlist, &pfilename);
	}
}

/* Remove all strings from a list. */
void destring_list (list destrlist)
{
	char *pstring;

	while (list_mt (destrlist) == FALSE)		/* more in list */
	{
		/* detach next string from tail of list */
		decr_list (&destrlist, &pstring);
		
		free (pstring);				/* release string space */
	}	
}

/* Check whether or not we have a #include "________.h" line.	*/
/* If we do then return pointer to name of .h file within it.	*/
/* If we do NOT then return NULL. 				*/
char *look_at_line (char *pfileline)
{
	char *o, *p, *q, *r;
	
	/* copy original file line string to memory to save it for use later */
	o = copy_str_mem (pfileline);

	/* now tidy up the original! */
	p = pfileline;
	q = pfileline;
	while (*q != '\0')
	{
		if (isspace ((int)*q) == 0)		/* char is NOT space */
			*p++ = *q++;
		else
			q++;				/* char is space */
	}
	*p = '\0';
	
	/* spaces now eliminated from line */
	p = pfileline;
	q = pfileline;
	p = strstr (pfileline, "/*");
	if (p != NULL)					/* aha! a comment */
	{
		/* p now points to start of comment */
		q = strstr (pfileline, "*/");
		if (q != NULL)				/* comment end found */
		{
			q++;
			/* q now points to end of comment */
			q++;
			while (*q != '\0')
			{
				*p++ = *q++;
			}
			*p = '\0';
		}
		else
			*p = '\0';
	}

	/* any comment is now eliminated from line */
	p = strstr (pfileline, "#include\"");
	if (p == NULL)				       /* #include" line NOT found */
		r = p;
	else						/* #include" line found */
	{	
		p += 9;

		/* p now points to start of filename */
		q = strstr (p, ".h");
		if (q == NULL)				/* .h NOT found */
		{
			q = strstr (p, "\"");
			if (q != NULL)			/* " found */
				*q = '\0';
			fprintf (stderr,
				 "%s: Invalid include line '%s'\n",
				 THISPROGNAME, o);
			r = (char *) NULL;
		}
		else					/* .h found */
		{
			q += 2;
			*q = '\0';

			/* p now points to .h filename in string form */
			r = p;
		}
	}

	free (o);
	return r;
}

/* List all the includes found in a given .c file.	*/
/* Return the include list created.			*/
list find_includes (char *pcfilename)
{
	FILE *infile;
	char inputline[MAXLINLEN];
	char *pincfilename, *pmemfilename;
	list includes;
	int lcv;

	includes = new_list ();				/* start include list */
	if (includes == NULL)
		exit (NEW_LIST_REFUSED);		/* cannot proceed */

	infile = fopen (pcfilename, "r");		/* open .c file */
	if (infile == NULL)
		exit (FILE_OPENING_REFUSED);		/* cannot proceed */

	for (lcv = 0; fgets (inputline, MAXLINLEN-1, infile) != NULL; lcv++)
	{
		/* chop off newline at end.. */
		inputline[strlen(inputline)-1] = '\0';

		/* we have a line to check */
		pincfilename = look_at_line (inputline);  /* does it #include "__.h"? */
		if (pincfilename != NULL)		/* yes, it does! */
		{
			/* N.B. pincfilename points to .h file name string in	*/
			/* inputline						*/

			/* copy .h file name string to memory and attach copy	*/
			/* to tail of include list				*/
			pmemfilename = copy_str_mem (pincfilename);
			includes = incr_list (includes, pmemfilename);
			if (includes == NULL)
				exit (LIST_ATTACH_REFUSED);/* cannot proceed */
		}
	}
	fclose (infile);

	return includes;
}

/* Write a makefile dependency line in a file. */
void print_makeline (char *pcfilename, list includes, FILE *outfile)
{
	int cfnlen;
	
	/* write '.o' line to makefile */
	cfnlen = (int) strlen (pcfilename);
	fprintf (outfile, "\n%.*s.o:", cfnlen-2, pcfilename);/* write .o filename */
	fprintf (outfile, "\t%s", pcfilename);		/* write .c filename */
	print_list (includes, outfile);			/* write include list */
	fprintf (outfile, "\n");				/* that's it ! */
}

/* Extract name of main .c file from a given argument and add it to to do list.	*/
/* Return a pointer to the main .c file name.					*/
char *get_main (char *parg)
{
	int arglen;
	char *pmainfilename;
	char *pcfilename;
	int lcv;

	arglen = (int) strlen (parg);

	if (parg [arglen-2] == '.'
	&&  parg [arglen-1] == 'c')		       /* main file name ends '.c' */
	{
		/* copy main .c file name string to memory */
		pmainfilename = copy_str_mem (parg);
	}
	else					      /* main file name omits '.c' */
	{
		/* create a copy, in memory, of main .c file name	*/
		/* with omitted '.c' restored				*/
		pmainfilename = (char *) malloc (arglen+3);
		if (pmainfilename == NULL)
			exit (STRING_SPACE_REFUSED);	/* cannot proceed */

		/* memory chunk is supplied UNinitialised */
		for (lcv = 0; lcv < arglen; lcv++)
			pmainfilename [lcv] = parg [lcv];/* copy string */
		pmainfilename [arglen]   = '.';	/* add .c to name */
		pmainfilename [arglen+1] = 'c';
		pmainfilename [arglen+2] = '\0';
		
		/* memory chunk is now initialised */
	}
	
	if (file_exists (pmainfilename) == FALSE)	/* main .c file NOT found */
	{
		fprintf (stderr,
			 "%s: file '%s' not found.\n",
			 THISPROGNAME, pmainfilename);	/* warn user */
		exit (MAIN_C_FILE_MISSING);		/* cannot proceed */
	}

	/* copy main .c file name string to memory and attach copy to	*/
	/* tail of to do list						*/
	pcfilename = copy_str_mem (pmainfilename);
	todos = incr_list (todos, pcfilename);
	if (todos == NULL)
		exit (LIST_ATTACH_REFUSED);		/* cannot proceed */

	return pmainfilename;
}

/* Dismantle include list, convert filenames from .h to .c and add any that 	*/
/* are not yet in the to do, done or no .c lists to the to do list.  Finally,	*/
/* kill off include list.							*/
void kill_includes_extend_todos (char *pcfilename, list includes)
{
	char *pincfilename;
	int ifnlen;

	while ( ! list_mt (includes) )		/* more in include list */
	{
		/* detach next file name from head of include list */
		behead_list (&includes, &pincfilename);
	
		/* change file name ending from .h to .c */
		ifnlen = (int) strlen (pincfilename);
		pincfilename [ifnlen-1] = 'c';

/* ---------------- text block moved left to keep it on page ! ------------------- */
if ( !in_list (todos, pincfilename) 			/* not in to do list */
&&   !in_list (dones, pincfilename) 			/* not in done list */
&&   !in_list (nocs, pincfilename) 			/* not in no .c list */
&&   strcmp (pcfilename, pincfilename) != 0)		/* not this .c file */
/* ------------------------------------------------------------------------------- */
		{
			/* attach .c file name to tail of to do list */
			todos = incr_list (todos, pincfilename);
			if (todos == NULL)
				exit (LIST_ATTACH_REFUSED);/* cannot proceed */
		}	
		else
		{
			free (pincfilename);		/* release string space */
		}
	}

	/* list is now empty */
	kill_list (includes);
}

/* ------------------------------------------------------------------------------- */
/* argv[1] points to 'main' .c file name */	
int main (int argc, char *argv[])
{
	list includes;
	char *pmainfilename;
	char *pcfilename;
	int mfnlen;
	FILE *output;

	if (argc == 1 || argc > 2 )
	{	
		fprintf (stderr,
			 "Usage: %s: program_name (or main .c file name).\n",
			 THISPROGNAME);
		exit(2);
	}

	/* now for the real work */
	
	output = fopen (MAKEFILENAME, "w");		/* start makefile */
	if (output == NULL)
		exit (FILE_OPENING_REFUSED);		/* cannot proceed */

	todos = new_list ();				/* start to do list */
	if (todos == NULL)
		exit (NEW_LIST_REFUSED);		/* cannot proceed */
		
	dones = new_list ();				/* start done list */
	if (dones == NULL)
		exit (NEW_LIST_REFUSED);		/* cannot proceed */

	nocs = new_list ();				/* start no .c list */
	if (nocs == NULL)
		exit (NEW_LIST_REFUSED);		/* cannot proceed */

	/* copy defsfile to makefile */
	if (file_exists (PERSDEFSFILENAME))	       /* personal defs file found */
		copy_file (PERSDEFSFILENAME, output);	/* so use it */
	else if (file_exists (LIBRDEFSFILENAME))	/* library defs file found */
		copy_file (LIBRDEFSFILENAME, output);	/* so use it */

	/* argv[1] points to main .c file name */	
	/* obtain main .c file name from argument and add it to to do list */
	pmainfilename = get_main (argv[1]);

	/* write 'EXECS' line to makefile */
	mfnlen = (int) strlen (pmainfilename);
	fprintf (output,
		 "\nEXECS\t=\t%.*s\n", mfnlen-2,
		 pmainfilename);

	/* write 'all' line to makefile */
	fprintf (output, "\nall:\t$(EXECS)\n");

	while (list_mt (todos) == FALSE)		/* more to do */
	{
		/* detach next .c file name from head of to do list */
		behead_list (&todos, &pcfilename);

		if (file_exists (pcfilename))		/* .c file found */
		{
			includes = find_includes (pcfilename);
			print_makeline (pcfilename, includes, output);
			kill_includes_extend_todos (pcfilename, includes);
			
			/* attach .c file name to tail of done list */
			dones = incr_list (dones, pcfilename);
			if (dones == NULL)
				exit (LIST_ATTACH_REFUSED);/* cannot proceed */
		}
		else					/* .c file NOT found */
		{
			/* attach .c file name to tail of no .c list */
			nocs = incr_list (nocs, pcfilename);
			if (nocs == NULL)
				exit (LIST_ATTACH_REFUSED);/* cannot proceed */
		}
	}

	/* to do list is now empty, so kill it */
	kill_list (todos);
	
	/* convert file names in done list from .c to .o */
	convert_list_to_dot_o (dones); 

	/* write 'OBJS' line to makefile */
	fprintf (output, "\nOBJS\t=\t");		/* write funny bits */
	print_list (dones, output);			/* write done list */
	fprintf (output, "\n");				/* that's it ! */
	
	destring_list (dones);
	/* list is now empty */
	kill_list (dones);
	
	destring_list (nocs);
	/* list is now empty */
	kill_list (nocs);
	
	/* write 'clean' line to makefile */
	fprintf (output,
		 "\nclean:\n\t/bin/rm -f $(EXECS) $(OBJS) core a.out .nfs*\n");

	/* write 'prog' line to makefile */
	fprintf (output,
		"\n%.*s:\t\t$(OBJS)\n\t$(CC) $(CFLAGS) $(OBJS) -o %.*s $(LDFLAGS)\n",
		 mfnlen-2, pmainfilename, mfnlen-2, pmainfilename);

	fclose (output);				/* end of main */
	return 0;
}
/* ------------------------------------------------------------------------------- */
