# Makefile for program source directory in GNU NLS utilities package.
# Copyright (C) 1995, 1996, 1997 by Ulrich Drepper <drepper@gnu.ai.mit.edu>
# Copyright 2003, 2006, 2007, 2009 Free Software Foundation, Inc.
#
# This file may be copied and used freely without restrictions.  It can
# be used in projects which are not available under the GNU Public License
# but which still want to provide support for the GNU gettext functionality.
# Please note that the actual code is *not* freely available.

PACKAGE = gas
VERSION = 2.23

SHELL = /bin/sh


srcdir = ../../../binutils-2.23/gas/po
top_srcdir = ../../../binutils-2.23/gas
VPATH = ../../../binutils-2.23/gas/po
top_builddir = ..

prefix = /home/stuartb/Projects/os/cross
exec_prefix = ${prefix}
datadir = $(prefix)/
localedir = $(datadir)/locale
gnulocaledir = $(prefix)/share/locale
gettextsrcdir = $(prefix)/share/gettext/po
subdir = po

DESTDIR =

INSTALL = /usr/bin/install -c
INSTALL_DATA = /usr/bin/install -c -m 644
MKINSTALLDIRS = $(top_builddir)/../../binutils-2.23/gas/../mkinstalldirs

CC = gcc
GENCAT = 
GMSGFMT = PATH=../src:$$PATH /usr/bin/msgfmt
MSGFMT = /usr/bin/msgfmt
XGETTEXT = PATH=../src:$$PATH /usr/bin/xgettext
MSGMERGE = PATH=../src:$$PATH msgmerge

DEFS = -DHAVE_CONFIG_H
CFLAGS = -g -O2
CPPFLAGS = 

INCLUDES = -I.. -I$(top_srcdir)/intl

COMPILE = $(CC) -c $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS) $(XCFLAGS)

SOURCES = cat-id-tbl.c
POFILES =  $(srcdir)/fr.po $(srcdir)/tr.po $(srcdir)/es.po $(srcdir)/rw.po $(srcdir)/id.po $(srcdir)/ru.po $(srcdir)/fi.po $(srcdir)/ja.po
GMOFILES =  $(srcdir)/fr.gmo $(srcdir)/tr.gmo $(srcdir)/es.gmo $(srcdir)/rw.gmo $(srcdir)/id.gmo $(srcdir)/ru.gmo $(srcdir)/fi.gmo $(srcdir)/ja.gmo
DISTFILES = ChangeLog Makefile.in.in POTFILES.in $(PACKAGE).pot \
stamp-cat-id $(POFILES) $(GMOFILES) $(SOURCES)

POTFILES = \
     ../../../binutils-2.23/gas/app.c \
     ../../../binutils-2.23/gas/as.c \
     ../../../binutils-2.23/gas/as.h \
     ../../../binutils-2.23/gas/asintl.h \
     ../../../binutils-2.23/gas/atof-generic.c \
     ../../../binutils-2.23/gas/bignum.h \
     ../../../binutils-2.23/gas/bit_fix.h \
     ../../../binutils-2.23/gas/cgen.c \
     ../../../binutils-2.23/gas/cgen.h \
     ../../../binutils-2.23/gas/compress-debug.c \
     ../../../binutils-2.23/gas/compress-debug.h \
     ../../../binutils-2.23/gas/cond.c \
     ../../../binutils-2.23/gas/config/atof-ieee.c \
     ../../../binutils-2.23/gas/config/atof-vax.c \
     ../../../binutils-2.23/gas/config/e-crisaout.c \
     ../../../binutils-2.23/gas/config/e-criself.c \
     ../../../binutils-2.23/gas/config/e-i386aout.c \
     ../../../binutils-2.23/gas/config/e-i386coff.c \
     ../../../binutils-2.23/gas/config/e-i386elf.c \
     ../../../binutils-2.23/gas/config/e-mipsecoff.c \
     ../../../binutils-2.23/gas/config/e-mipself.c \
     ../../../binutils-2.23/gas/config/obj-aout.c \
     ../../../binutils-2.23/gas/config/obj-aout.h \
     ../../../binutils-2.23/gas/config/obj-coff.c \
     ../../../binutils-2.23/gas/config/obj-coff.h \
     ../../../binutils-2.23/gas/config/obj-ecoff.c \
     ../../../binutils-2.23/gas/config/obj-ecoff.h \
     ../../../binutils-2.23/gas/config/obj-elf.c \
     ../../../binutils-2.23/gas/config/obj-elf.h \
     ../../../binutils-2.23/gas/config/obj-evax.c \
     ../../../binutils-2.23/gas/config/obj-evax.h \
     ../../../binutils-2.23/gas/config/obj-fdpicelf.c \
     ../../../binutils-2.23/gas/config/obj-fdpicelf.h \
     ../../../binutils-2.23/gas/config/obj-macho.c \
     ../../../binutils-2.23/gas/config/obj-macho.h \
     ../../../binutils-2.23/gas/config/obj-multi.c \
     ../../../binutils-2.23/gas/config/obj-multi.h \
     ../../../binutils-2.23/gas/config/obj-som.c \
     ../../../binutils-2.23/gas/config/obj-som.h \
     ../../../binutils-2.23/gas/config/tc-alpha.c \
     ../../../binutils-2.23/gas/config/tc-alpha.h \
     ../../../binutils-2.23/gas/config/tc-arc.c \
     ../../../binutils-2.23/gas/config/tc-arc.h \
     ../../../binutils-2.23/gas/config/tc-arm.c \
     ../../../binutils-2.23/gas/config/tc-arm.h \
     ../../../binutils-2.23/gas/config/tc-avr.c \
     ../../../binutils-2.23/gas/config/tc-avr.h \
     ../../../binutils-2.23/gas/config/tc-bfin.c \
     ../../../binutils-2.23/gas/config/tc-bfin.h \
     ../../../binutils-2.23/gas/config/tc-cr16.c \
     ../../../binutils-2.23/gas/config/tc-cr16.h \
     ../../../binutils-2.23/gas/config/tc-cris.c \
     ../../../binutils-2.23/gas/config/tc-cris.h \
     ../../../binutils-2.23/gas/config/tc-crx.c \
     ../../../binutils-2.23/gas/config/tc-crx.h \
     ../../../binutils-2.23/gas/config/tc-d10v.c \
     ../../../binutils-2.23/gas/config/tc-d10v.h \
     ../../../binutils-2.23/gas/config/tc-d30v.c \
     ../../../binutils-2.23/gas/config/tc-d30v.h \
     ../../../binutils-2.23/gas/config/tc-dlx.c \
     ../../../binutils-2.23/gas/config/tc-dlx.h \
     ../../../binutils-2.23/gas/config/tc-epiphany.c \
     ../../../binutils-2.23/gas/config/tc-epiphany.h \
     ../../../binutils-2.23/gas/config/tc-fr30.c \
     ../../../binutils-2.23/gas/config/tc-fr30.h \
     ../../../binutils-2.23/gas/config/tc-frv.c \
     ../../../binutils-2.23/gas/config/tc-frv.h \
     ../../../binutils-2.23/gas/config/tc-h8300.c \
     ../../../binutils-2.23/gas/config/tc-h8300.h \
     ../../../binutils-2.23/gas/config/tc-hppa.c \
     ../../../binutils-2.23/gas/config/tc-hppa.h \
     ../../../binutils-2.23/gas/config/tc-i370.c \
     ../../../binutils-2.23/gas/config/tc-i370.h \
     ../../../binutils-2.23/gas/config/tc-i386.c \
     ../../../binutils-2.23/gas/config/tc-i386.h \
     ../../../binutils-2.23/gas/config/tc-i860.c \
     ../../../binutils-2.23/gas/config/tc-i860.h \
     ../../../binutils-2.23/gas/config/tc-i960.c \
     ../../../binutils-2.23/gas/config/tc-i960.h \
     ../../../binutils-2.23/gas/config/tc-ia64.c \
     ../../../binutils-2.23/gas/config/tc-ia64.h \
     ../../../binutils-2.23/gas/config/tc-ip2k.c \
     ../../../binutils-2.23/gas/config/tc-ip2k.h \
     ../../../binutils-2.23/gas/config/tc-iq2000.c \
     ../../../binutils-2.23/gas/config/tc-iq2000.h \
     ../../../binutils-2.23/gas/config/tc-lm32.c \
     ../../../binutils-2.23/gas/config/tc-lm32.h \
     ../../../binutils-2.23/gas/config/tc-m32c.c \
     ../../../binutils-2.23/gas/config/tc-m32c.h \
     ../../../binutils-2.23/gas/config/tc-m32r.c \
     ../../../binutils-2.23/gas/config/tc-m32r.h \
     ../../../binutils-2.23/gas/config/tc-m68hc11.c \
     ../../../binutils-2.23/gas/config/tc-m68hc11.h \
     ../../../binutils-2.23/gas/config/tc-m68k.c \
     ../../../binutils-2.23/gas/config/tc-m68k.h \
     ../../../binutils-2.23/gas/config/tc-mcore.c \
     ../../../binutils-2.23/gas/config/tc-mcore.h \
     ../../../binutils-2.23/gas/config/tc-mep.c \
     ../../../binutils-2.23/gas/config/tc-mep.h \
     ../../../binutils-2.23/gas/config/tc-microblaze.c \
     ../../../binutils-2.23/gas/config/tc-microblaze.h \
     ../../../binutils-2.23/gas/config/tc-mips.c \
     ../../../binutils-2.23/gas/config/tc-mips.h \
     ../../../binutils-2.23/gas/config/tc-mmix.c \
     ../../../binutils-2.23/gas/config/tc-mmix.h \
     ../../../binutils-2.23/gas/config/tc-mn10200.c \
     ../../../binutils-2.23/gas/config/tc-mn10200.h \
     ../../../binutils-2.23/gas/config/tc-mn10300.c \
     ../../../binutils-2.23/gas/config/tc-mn10300.h \
     ../../../binutils-2.23/gas/config/tc-moxie.c \
     ../../../binutils-2.23/gas/config/tc-msp430.c \
     ../../../binutils-2.23/gas/config/tc-msp430.h \
     ../../../binutils-2.23/gas/config/tc-mt.c \
     ../../../binutils-2.23/gas/config/tc-mt.h \
     ../../../binutils-2.23/gas/config/tc-ns32k.c \
     ../../../binutils-2.23/gas/config/tc-ns32k.h \
     ../../../binutils-2.23/gas/config/tc-openrisc.c \
     ../../../binutils-2.23/gas/config/tc-openrisc.h \
     ../../../binutils-2.23/gas/config/tc-or32.c \
     ../../../binutils-2.23/gas/config/tc-or32.h \
     ../../../binutils-2.23/gas/config/tc-pdp11.c \
     ../../../binutils-2.23/gas/config/tc-pdp11.h \
     ../../../binutils-2.23/gas/config/tc-pj.c \
     ../../../binutils-2.23/gas/config/tc-pj.h \
     ../../../binutils-2.23/gas/config/tc-ppc.c \
     ../../../binutils-2.23/gas/config/tc-ppc.h \
     ../../../binutils-2.23/gas/config/tc-rl78.c \
     ../../../binutils-2.23/gas/config/tc-rl78.h \
     ../../../binutils-2.23/gas/config/tc-rx.c \
     ../../../binutils-2.23/gas/config/tc-rx.h \
     ../../../binutils-2.23/gas/config/tc-s390.c \
     ../../../binutils-2.23/gas/config/tc-s390.h \
     ../../../binutils-2.23/gas/config/tc-score.c \
     ../../../binutils-2.23/gas/config/tc-score.h \
     ../../../binutils-2.23/gas/config/tc-sh.c \
     ../../../binutils-2.23/gas/config/tc-sh.h \
     ../../../binutils-2.23/gas/config/tc-sh64.c \
     ../../../binutils-2.23/gas/config/tc-sh64.h \
     ../../../binutils-2.23/gas/config/tc-sparc.c \
     ../../../binutils-2.23/gas/config/tc-sparc.h \
     ../../../binutils-2.23/gas/config/tc-spu.c \
     ../../../binutils-2.23/gas/config/tc-spu.h \
     ../../../binutils-2.23/gas/config/tc-tic30.c \
     ../../../binutils-2.23/gas/config/tc-tic30.h \
     ../../../binutils-2.23/gas/config/tc-tic4x.c \
     ../../../binutils-2.23/gas/config/tc-tic4x.h \
     ../../../binutils-2.23/gas/config/tc-tic54x.c \
     ../../../binutils-2.23/gas/config/tc-tic54x.h \
     ../../../binutils-2.23/gas/config/tc-tic6x.c \
     ../../../binutils-2.23/gas/config/tc-tic6x.h \
     ../../../binutils-2.23/gas/config/tc-tilegx.c \
     ../../../binutils-2.23/gas/config/tc-tilegx.h \
     ../../../binutils-2.23/gas/config/tc-tilepro.c \
     ../../../binutils-2.23/gas/config/tc-tilepro.h \
     ../../../binutils-2.23/gas/config/tc-v850.c \
     ../../../binutils-2.23/gas/config/tc-v850.h \
     ../../../binutils-2.23/gas/config/tc-vax.c \
     ../../../binutils-2.23/gas/config/tc-vax.h \
     ../../../binutils-2.23/gas/config/tc-xc16x.c \
     ../../../binutils-2.23/gas/config/tc-xc16x.h \
     ../../../binutils-2.23/gas/config/tc-xstormy16.c \
     ../../../binutils-2.23/gas/config/tc-xstormy16.h \
     ../../../binutils-2.23/gas/config/tc-xtensa.c \
     ../../../binutils-2.23/gas/config/tc-xtensa.h \
     ../../../binutils-2.23/gas/config/tc-z80.c \
     ../../../binutils-2.23/gas/config/tc-z80.h \
     ../../../binutils-2.23/gas/config/tc-z8k.c \
     ../../../binutils-2.23/gas/config/tc-z8k.h \
     ../../../binutils-2.23/gas/config/te-386bsd.h \
     ../../../binutils-2.23/gas/config/te-aix5.h \
     ../../../binutils-2.23/gas/config/te-armeabi.h \
     ../../../binutils-2.23/gas/config/te-armlinuxeabi.h \
     ../../../binutils-2.23/gas/config/te-dynix.h \
     ../../../binutils-2.23/gas/config/te-epoc-pe.h \
     ../../../binutils-2.23/gas/config/te-freebsd.h \
     ../../../binutils-2.23/gas/config/te-generic.h \
     ../../../binutils-2.23/gas/config/te-gnu.h \
     ../../../binutils-2.23/gas/config/te-go32.h \
     ../../../binutils-2.23/gas/config/te-hppa.h \
     ../../../binutils-2.23/gas/config/te-hppa64.h \
     ../../../binutils-2.23/gas/config/te-hppalinux64.h \
     ../../../binutils-2.23/gas/config/te-i386aix.h \
     ../../../binutils-2.23/gas/config/te-ia64aix.h \
     ../../../binutils-2.23/gas/config/te-interix.h \
     ../../../binutils-2.23/gas/config/te-lnews.h \
     ../../../binutils-2.23/gas/config/te-lynx.h \
     ../../../binutils-2.23/gas/config/te-mach.h \
     ../../../binutils-2.23/gas/config/te-macos.h \
     ../../../binutils-2.23/gas/config/te-nbsd.h \
     ../../../binutils-2.23/gas/config/te-nbsd532.h \
     ../../../binutils-2.23/gas/config/te-netware.h \
     ../../../binutils-2.23/gas/config/te-pc532mach.h \
     ../../../binutils-2.23/gas/config/te-pe.h \
     ../../../binutils-2.23/gas/config/te-psos.h \
     ../../../binutils-2.23/gas/config/te-riscix.h \
     ../../../binutils-2.23/gas/config/te-solaris.h \
     ../../../binutils-2.23/gas/config/te-sparcaout.h \
     ../../../binutils-2.23/gas/config/te-sun3.h \
     ../../../binutils-2.23/gas/config/te-svr4.h \
     ../../../binutils-2.23/gas/config/te-symbian.h \
     ../../../binutils-2.23/gas/config/te-tmips.h \
     ../../../binutils-2.23/gas/config/te-vms.c \
     ../../../binutils-2.23/gas/config/te-vxworks.h \
     ../../../binutils-2.23/gas/config/te-wince-pe.h \
     ../../../binutils-2.23/gas/config/xtensa-relax.c \
     ../../../binutils-2.23/gas/config/xtensa-relax.h \
     ../../../binutils-2.23/gas/depend.c \
     ../../../binutils-2.23/gas/dw2gencfi.c \
     ../../../binutils-2.23/gas/dw2gencfi.h \
     ../../../binutils-2.23/gas/dwarf2dbg.c \
     ../../../binutils-2.23/gas/dwarf2dbg.h \
     ../../../binutils-2.23/gas/ecoff.c \
     ../../../binutils-2.23/gas/ecoff.h \
     ../../../binutils-2.23/gas/ehopt.c \
     ../../../binutils-2.23/gas/emul-target.h \
     ../../../binutils-2.23/gas/emul.h \
     ../../../binutils-2.23/gas/expr.c \
     ../../../binutils-2.23/gas/expr.h \
     ../../../binutils-2.23/gas/flonum-copy.c \
     ../../../binutils-2.23/gas/flonum-konst.c \
     ../../../binutils-2.23/gas/flonum-mult.c \
     ../../../binutils-2.23/gas/flonum.h \
     ../../../binutils-2.23/gas/frags.c \
     ../../../binutils-2.23/gas/frags.h \
     ../../../binutils-2.23/gas/hash.c \
     ../../../binutils-2.23/gas/hash.h \
     ../../../binutils-2.23/gas/input-file.c \
     ../../../binutils-2.23/gas/input-file.h \
     ../../../binutils-2.23/gas/input-scrub.c \
     ../../../binutils-2.23/gas/itbl-lex.h \
     ../../../binutils-2.23/gas/itbl-ops.c \
     ../../../binutils-2.23/gas/itbl-ops.h \
     ../../../binutils-2.23/gas/listing.c \
     ../../../binutils-2.23/gas/listing.h \
     ../../../binutils-2.23/gas/literal.c \
     ../../../binutils-2.23/gas/macro.c \
     ../../../binutils-2.23/gas/macro.h \
     ../../../binutils-2.23/gas/messages.c \
     ../../../binutils-2.23/gas/obj.h \
     ../../../binutils-2.23/gas/output-file.c \
     ../../../binutils-2.23/gas/output-file.h \
     ../../../binutils-2.23/gas/read.c \
     ../../../binutils-2.23/gas/read.h \
     ../../../binutils-2.23/gas/remap.c \
     ../../../binutils-2.23/gas/sb.c \
     ../../../binutils-2.23/gas/sb.h \
     ../../../binutils-2.23/gas/stabs.c \
     ../../../binutils-2.23/gas/struc-symbol.h \
     ../../../binutils-2.23/gas/subsegs.c \
     ../../../binutils-2.23/gas/subsegs.h \
     ../../../binutils-2.23/gas/symbols.c \
     ../../../binutils-2.23/gas/symbols.h \
     ../../../binutils-2.23/gas/tc.h \
     ../../../binutils-2.23/gas/write.c \
     ../../../binutils-2.23/gas/write.h

CATALOGS = 
CATOBJEXT = 
INSTOBJEXT = 

.SUFFIXES:
.SUFFIXES: .c .o .po .pox .gmo .mo .msg .cat

.c.o:
	$(COMPILE) $<

.po.pox:
	$(MAKE) $(PACKAGE).pot
	$(MSGMERGE) $< $(srcdir)/$(PACKAGE).pot -o $*.pox

.po.mo:
	$(MSGFMT) -o $@ $<

.po.gmo:
	file=`echo $* | sed 's,.*/,,'`.gmo \
	  && rm -f $$file && $(GMSGFMT) -o $$file $<

.po.cat:
	sed -f ../intl/po2msg.sed < $< > $*.msg \
	  && rm -f $@ && $(GENCAT) $@ $*.msg


all: all-no

all-yes: $(CATALOGS) # $(PACKAGE).pot
all-no:

$(srcdir)/$(PACKAGE).pot: $(POTFILES)
	$(XGETTEXT) --default-domain=$(PACKAGE) --directory=$(top_srcdir) \
	  --add-comments --keyword=_ --keyword=N_ \
	  --msgid-bugs-address=bug-binutils@gnu.org \
	  --files-from=$(srcdir)/POTFILES.in
	rm -f $(srcdir)/$(PACKAGE).pot
	mv $(PACKAGE).po $(srcdir)/$(PACKAGE).pot

$(srcdir)/cat-id-tbl.c: stamp-cat-id; @:
$(srcdir)/stamp-cat-id: $(PACKAGE).pot
	rm -f cat-id-tbl.tmp
	sed -f ../intl/po2tbl.sed $(srcdir)/$(PACKAGE).pot \
		| sed -e "s/@PACKAGE NAME@/$(PACKAGE)/" > cat-id-tbl.tmp
	if cmp -s cat-id-tbl.tmp $(srcdir)/cat-id-tbl.c; then \
	  rm cat-id-tbl.tmp; \
	else \
	  echo cat-id-tbl.c changed; \
	  rm -f $(srcdir)/cat-id-tbl.c; \
	  mv cat-id-tbl.tmp $(srcdir)/cat-id-tbl.c; \
	fi
	cd $(srcdir) && rm -f stamp-cat-id && echo timestamp > stamp-cat-id


install: install-exec install-data
install-exec:
install-info:
install-html:
install-pdf:
install-data: install-data-no
install-data-no: all
install-data-yes: all
	if test -r $(MKINSTALLDIRS); then \
	  $(MKINSTALLDIRS) $(DESTDIR)$(datadir); \
	else \
	  $(top_srcdir)/mkinstalldirs $(DESTDIR)$(datadir); \
	fi
	@catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  case "$$cat" in \
	    *.gmo) destdir=$(gnulocaledir);; \
	    *)     destdir=$(localedir);; \
	  esac; \
	  lang=`echo $$cat | sed 's/\$(CATOBJEXT)$$//'`; \
	  dir=$(DESTDIR)$$destdir/$$lang/LC_MESSAGES; \
	  if test -r $(MKINSTALLDIRS); then \
	    $(MKINSTALLDIRS) $$dir; \
	  else \
	    $(top_srcdir)/mkinstalldirs $$dir; \
	  fi; \
	  if test -r $$cat; then \
	    $(INSTALL_DATA) $$cat $$dir/$(PACKAGE)$(INSTOBJEXT); \
	    echo "installing $$cat as $$dir/$(PACKAGE)$(INSTOBJEXT)"; \
	  else \
	    $(INSTALL_DATA) $(srcdir)/$$cat $$dir/$(PACKAGE)$(INSTOBJEXT); \
	    echo "installing $(srcdir)/$$cat as" \
		 "$$dir/$(PACKAGE)$(INSTOBJEXT)"; \
	  fi; \
	  if test -r $$cat.m; then \
	    $(INSTALL_DATA) $$cat.m $$dir/$(PACKAGE)$(INSTOBJEXT).m; \
	    echo "installing $$cat.m as $$dir/$(PACKAGE)$(INSTOBJEXT).m"; \
	  else \
	    if test -r $(srcdir)/$$cat.m ; then \
	      $(INSTALL_DATA) $(srcdir)/$$cat.m \
		$$dir/$(PACKAGE)$(INSTOBJEXT).m; \
	      echo "installing $(srcdir)/$$cat as" \
		   "$$dir/$(PACKAGE)$(INSTOBJEXT).m"; \
	    else \
	      true; \
	    fi; \
	  fi; \
	done
	if test "$(PACKAGE)" = "gettext"; then \
	  if test -r $(MKINSTALLDIRS); then \
	    $(MKINSTALLDIRS) $(DESTDIR)$(gettextsrcdir); \
	  else \
	    $(top_srcdir)/mkinstalldirs $(DESTDIR)$(gettextsrcdir); \
	  fi; \
	  $(INSTALL_DATA) $(srcdir)/Makefile.in.in \
			  $(DESTDIR)$(gettextsrcdir)/Makefile.in.in; \
	else \
	  : ; \
	fi

# Define this as empty until I found a useful application.
installcheck:

uninstall:
	catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed 's/\$(CATOBJEXT)$$//'`; \
	  rm -f $(DESTDIR)$(localedir)/$$lang/LC_MESSAGES/$(PACKAGE)$(INSTOBJEXT); \
	  rm -f $(DESTDIR)$(localedir)/$$lang/LC_MESSAGES/$(PACKAGE)$(INSTOBJEXT).m; \
	  rm -f $(DESTDIR)$(gnulocaledir)/$$lang/LC_MESSAGES/$(PACKAGE)$(INSTOBJEXT); \
	  rm -f $(DESTDIR)$(gnulocaledir)/$$lang/LC_MESSAGES/$(PACKAGE)$(INSTOBJEXT).m; \
	done
	rm -f $(DESTDIR)$(gettextsrcdir)/po-Makefile.in.in

check: all

cat-id-tbl.o: ../intl/libgettext.h

html dvi pdf ps info tags TAGS ID:

mostlyclean:
	rm -f core core.* *.pox $(PACKAGE).po *.old.po cat-id-tbl.tmp
	rm -fr *.o

clean: mostlyclean

distclean: clean
	rm -f Makefile Makefile.in POTFILES *.mo *.msg *.cat *.cat.m

maintainer-clean: distclean
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."
	rm -f $(GMOFILES)

distdir = ../$(PACKAGE)-$(VERSION)/$(subdir)
dist distdir: update-po $(DISTFILES)
	dists="$(DISTFILES)"; \
	for file in $$dists; do \
	  ln $(srcdir)/$$file $(distdir) 2> /dev/null \
	    || cp -p $(srcdir)/$$file $(distdir); \
	done

update-po: Makefile
	$(MAKE) $(PACKAGE).pot
	PATH=`pwd`/../src:$$PATH; \
	cd $(srcdir); \
	catalogs='$(CATALOGS)'; \
	for cat in $$catalogs; do \
	  cat=`basename $$cat`; \
	  lang=`echo $$cat | sed 's/\$(CATOBJEXT)$$//'`; \
	  mv $$lang.po $$lang.old.po; \
	  echo "$$lang:"; \
	  if $(MSGMERGE) $$lang.old.po $(PACKAGE).pot -o $$lang.po; then \
	    rm -f $$lang.old.po; \
	  else \
	    echo "msgmerge for $$cat failed!"; \
	    rm -f $$lang.po; \
	    mv $$lang.old.po $$lang.po; \
	  fi; \
	done

POTFILES: POTFILES.in
	( if test 'x$(srcdir)' != 'x.'; then \
	    posrcprefix='$(top_srcdir)/'; \
	  else \
	    posrcprefix="../"; \
	  fi; \
	  rm -f $@-t $@ \
	    && (sed -e '/^#/d' -e '/^[ 	]*$$/d' \
		    -e "s@.*@	$$posrcprefix& \\\\@" < $(srcdir)/$@.in \
		| sed -e '$$s/\\$$//') > $@-t \
	    && chmod a-w $@-t \
	    && mv $@-t $@ )

POTFILES.in: # ../Makefile
	cd .. && $(MAKE) po/POTFILES.in

Makefile: Make-in ../config.status POTFILES
	cd .. \
	  && CONFIG_FILES=$(subdir)/Makefile.in:$(subdir)/Make-in \
	     CONFIG_HEADERS= $(SHELL) ./config.status

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
