# TOOLDIR should be in the environment, set to ~/c-tools
INSTDIR =       $(TOOLDIR)
INCDIR  =       $(INSTDIR)/include
LIBDIR  =       $(INSTDIR)/lib/$(ARCH)
CC      =       gcc
CFLAGS  =       -Wall -I$(INCDIR)
LDLIBS  =       -L$(LIBDIR) -ltestlib
LIB	=	libintlist.a
LIBOBJS	=	intlist.o
BUILD	=	testlist $(LIB)

all:	$(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core

$(LIB):		$(LIBOBJS)
	ar rc $(LIB) $(LIBOBJS)
	ranlib $(LIB)

test:	$(BUILD)
	summarisetests ./testlist

testlist:	testlist.o intlist.o
intlist.o:	intlist.h
testlist.o:	intlist.h
