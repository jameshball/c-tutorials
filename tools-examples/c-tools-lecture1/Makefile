LIBDIR = $(TOOLDIR)/lib/$(ARCH)
BINDIR = $(TOOLDIR)/bin/$(ARCH)
INCDIR = $(TOOLDIR)/include
MAN1DIR = $(TOOLDIR)/man/man1
MAN3DIR = $(TOOLDIR)/man/man3
DESTDIR	= $(HOME)/public_html/c-tools-2020/lecture1
TARBALLNAME	=	c-tools-lecture1

mkdir:
	mkdir -p $(BINDIR) $(LIBDIR) $(INCDIR) $(MAN1DIR) $(MAN3DIR)

clean:
	-for i in */; do \
		(cd $$i; test -f Makefile && make clean); \
	done

install:
	-mkdir -p $(DESTDIR)
	install -m0644 index.html $(DESTDIR)
	install -m0755 $(TARBALLNAME).tgz $(DESTDIR)
	install -m0644 lecture.pdf lecture-handout.pdf $(DESTDIR)

tarball:	clean
	-mkdir -p tarball/$(TARBALLNAME)
	cp -pr [01]* lecture Makefile README tarball/$(TARBALLNAME)
	cd tarball; tar -czf ../$(TARBALLNAME).tgz --exclude .git --exclude email_from_tony $(TARBALLNAME)
	rm -rf tarball
