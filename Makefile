SRCDIR     = $(.CURDIR)/src
INCDIR     = $(.CURDIR)/include
TESTDIR    = $(.CURDIR)/test
BUILDDIR   = $(.CURDIR)/build
EXAMPLEDIR = $(.CURDIR)/share/which/examples
OBJDIR     = $(BUILDDIR)/obj
LIBDIR     = $(BUILDDIR)/usr/local/lib
CFILES     = $(SRCDIR)/which.c
EFILES     = $(EXAMPLEDIR)/which_example.c $(EXAMPLEDIR)/whichp_example.c

CC = cc
CFLAGS = -fstack-protector-all -I$(INCDIR) -Wall -Wextra -pedantic

##
# Public
libwhich.so: clean obj
	@mkdir -p $(OBJDIR) $(LIBDIR)
	$(CC) -shared $(OBJDIR)/*.o -o $(LIBDIR)/libwhich.so

test:
	$(CC) $(CFLAGS) -I$(INCDIR) $(CFILES) \
	$(TESTDIR)/which_test.c -o $(.CURDIR)/runner

example:
	@for example in $(EFILES); do \
		echo $$(basename $${example}); \
		$(CC) $(CFLAGS) $(CFILES) $${example} -o $(.CURDIR)/example; \
		$(.CURDIR)/example; \
		rm $(.CURDIR)/example; \
	done

##
# Private
obj:
	@for src in $(CFILES); do \
		obj=$$(basename $$(echo "$${src}" | sed 's/\.c$$/\.o/')); \
		$(CC) $(CFLAGS) -c "$${src}" -o "${OBJDIR}/$${obj}" ; \
	done

clean:
	@rm -rf $(BUILDDIR)/*
	@mkdir -p $(BUILDDIR) $(LIBDIR) $(OBJDIR)

.PHONY: test example
