#TOOLDIR	=	$(HOME)/c-tools
INSTDIR	=	$(TOOLDIR)
BINDIR	=	$(INSTDIR)/bin/$(ARCH)/mfbuild
MANDIR	=	$(INSTDIR)/man/man1/mfbuild.1
DEFS	=	$(INSTDIR)/lib/mfbuilddefs
CC	=	gcc
CFLAGS	=	-g -Wall -DLIBRDEFSFILENAME=\"$(DEFS)\"
EXECS	=	mfbuild
OBJS	=	mfbuild.o list_library.o

all:	$(EXECS)

clean:
	/bin/rm -f $(EXECS) $(OBJS) core a.out .nfs*

install:	$(EXECS)
	install -c -m 755 mfbuild $(BINDIR)
	install -c -m 644 mfbuild.man $(MANDIR)
	install -c -m 644 mfbuilddefs $(DEFS)

mfbuild.o:	mfbuild.c list_library.h
list_library.o:	list_library.c list_library.h

mfbuild:		$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o mfbuild $(LDFLAGS)
