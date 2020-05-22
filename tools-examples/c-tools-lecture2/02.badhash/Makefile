CC	=	gcc
#CC	=	gcc -fsanitize=undefined -fno-sanitize-recover -fsanitize=address
CFLAGS	=	-Wall -g
LDFLAGS = 	
BUILD	=	testhash iterate

all:	$(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core

iterate:	iterate.o hash.o
testhash:	testhash.o hash.o

hash.o:		hash.h
testhash.o:	hash.h
iterate.o:	hash.h
