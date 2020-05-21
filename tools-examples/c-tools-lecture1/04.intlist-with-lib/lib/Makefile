CC	=	gcc
CFLAGS	=	-Wall
LIB	=	libintlist.a
LIBOBJS	=	intlist.o
BUILD	=	testlist $(LIB)

all:	$(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core

$(LIB):		$(LIBOBJS)
	ar rcs $(LIB) $(LIBOBJS)

testlist:	testlist.o intlist.o
intlist.o:	intlist.h
testlist.o:	intlist.h
