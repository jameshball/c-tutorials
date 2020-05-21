#TOOLDIR	=	$(HOME)/c-tools
INSTDIR	=	$(TOOLDIR)
BINFILE	=	$(INSTDIR)/bin/mfbuild
MANFILE	=	$(INSTDIR)/man/man1/mfbuild.1
DEFS	=	$(INSTDIR)/lib/mfbuilddefs

install:	mfbuild.perl
	install -c -m 755 mfbuild.perl $(BINFILE)
	install -c -m 644 mfbuild.man $(MANFILE)
	install -c -m 644 mfbuilddefs $(DEFS)
