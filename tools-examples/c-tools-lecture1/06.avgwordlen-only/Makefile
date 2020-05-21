# TOOLDIR should be in the environment, set to ~/c-tools
INSTDIR	=	$(TOOLDIR)
INCDIR	=	$(INSTDIR)/include
LIBDIR	=	$(INSTDIR)/lib/$(ARCH)
CC	=	gcc
CFLAGS	=	-Wall -I$(INCDIR)
LDLIBS	=	-L$(LIBDIR) -lintlist
BUILD	=	avgwordlen

all:	$(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core

avgwordlen:	avgwordlen.o
avgwordlen.o:	defns.h
