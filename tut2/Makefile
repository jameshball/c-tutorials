CC = gcc
CFLAGS = -Wall -Wextra -g -pedantic
PROGS = pointers

all: $(PROGS)

clean:
	rm -f $(PROGS) *.o *~ callgrind.out.*

pointers: pointers.o pointer_arithmetic.o
pointers.o: pointer_arithmetic.h
pointer_arithmetic.o: pointer_arithmetic.h
