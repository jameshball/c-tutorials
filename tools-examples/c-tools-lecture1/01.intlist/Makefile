CC	=	gcc
CFLAGS	=	-Wall
BUILD	=	testlist avgwordlen

all:	$(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core

testlist:	testlist.o intlist.o
avgwordlen:	avgwordlen.o intlist.o
intlist.o:	intlist.h
testlist.o:	intlist.h
avgwordlen.o:	intlist.h defns.h
