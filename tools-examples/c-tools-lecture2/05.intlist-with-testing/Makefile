CC	=	gcc
CFLAGS	=	-Wall -Ilib
LDLIBS	=	-Llib -lintlist
BUILD	=	libs avgwordlen
LIB     =       lib/libintlist.a

all:	$(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core
	cd lib; make clean

$(LIB): $(LIBOBJS)
	ar rc $(LIB) $(LIBOBJS)
	ranlib $(LIB)

test:	$(BUILD)
	cd lib; make test


libs:
	cd lib; make

avgwordlen:	avgwordlen.o
avgwordlen.o:	defns.h
