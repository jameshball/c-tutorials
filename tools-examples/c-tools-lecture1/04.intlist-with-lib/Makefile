CC	=	gcc
CFLAGS	=	-Wall -Ilib
LDLIBS	=	-Llib -lintlist
BUILD	=	libs avgwordlen

all:	$(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core
	cd lib; make clean

libs:
	cd lib; make

avgwordlen:	avgwordlen.o
avgwordlen.o:	defns.h
