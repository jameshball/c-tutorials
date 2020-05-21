# destination: install into TOOLDIR (env var, eg ~/c-tools)
DEST	=	$(TOOLDIR)
INCDIR	=	$(DEST)/include
LIBDIR	=	$(DEST)/lib/$(ARCH)
CC	=	gcc
CFLAGS	=	-Wall
LIB	=	libintlist.a
LIBOBJS	=	intlist.o
BUILD	=	testlist $(LIB)

all:	$(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core

$(LIB):	$(LIBOBJS)
	ar rcs $(LIB) $(LIBOBJS)

install:	$(LIB)
	install -m 644 $(LIB) $(LIBDIR)
	install -m 644 intlist.h $(INCDIR)

testlist:	testlist.o intlist.o
intlist.o:	intlist.h
testlist.o:	intlist.h
