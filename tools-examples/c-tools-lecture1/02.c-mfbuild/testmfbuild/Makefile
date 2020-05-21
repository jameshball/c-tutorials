# Standard Declarations for mfbuild

CC	=	gcc
CFLAGS	=	-g -Wall

EXECS	=	avgwordlen

all:	$(EXECS)

avgwordlen.o:	avgwordlen.c intlist.h defns.h

intlist.o:	intlist.c intlist.h

OBJS	=	 avgwordlen.o intlist.o

clean:
	/bin/rm -f $(EXECS) $(OBJS) core a.out .nfs*

avgwordlen:		$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o avgwordlen $(LDFLAGS)
