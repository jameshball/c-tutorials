CC	=	gcc
CFLAGS	=	-Wall -pg
LDLIBS	=	-pg
PROGS	=	testhash iterate

all:	$(PROGS)

clean:
	rm -f $(PROGS) *.o gmon.out *~ callgrind.out.*

profile:	./iterate
	valgrind --tool=callgrind ./iterate 1000

testhash:	testhash.o hash.o
iterate:	iterate.o hash.o
testhash.o:	hash.h
hash.o:		hash.h
iterate.o:	hash.h
