## Process this file with automake to produce Makefile.in

SUBDIRS = src po

EXTRA_DIST = \
	autogen.sh \
	gdictthai.glade \
	gdictthai.gladep \
	gdictthai.desktop

install-data-local:
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir)
	$(mkinstalldirs) $(DESTDIR)$(datadir)/pixmaps/
	$(mkinstalldirs) $(DESTDIR)$(datadir)/applications/
	$(INSTALL_DATA) gdictthai.glade $(DESTDIR)$(pkgdatadir)
	$(INSTALL_DATA) $(srcdir)/pixmaps/gdictthai.svg $(DESTDIR)$(pkgdatadir)
	$(INSTALL_DATA) $(srcdir)/pixmaps/gdictthai.png $(DESTDIR)$(pkgdatadir)
	$(INSTALL_DATA) $(srcdir)/pixmaps/gdictthai.png $(DESTDIR)$(datadir)/pixmaps/
	$(INSTALL_DATA) $(srcdir)/gdictthai.desktop $(DESTDIR)$(datadir)/applications/
	if test -d $(srcdir)/dictionary; then \
	  $(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/dictionary; \
	  for dictionary in $(srcdir)/dictionary/*; do \
	    if test -f $$dictionary; then \
	      $(INSTALL_DATA) $$dictionary $(DESTDIR)$(pkgdatadir)/dictionary; \
	    fi \
	  done \
	fi

dist-hook:
	if test -d pixmaps; then \
	  mkdir $(distdir)/pixmaps; \
	  for pixmap in pixmaps/*; do \
	    if test -f $$pixmap; then \
	      cp -p $$pixmap $(distdir)/pixmaps; \
	    fi \
	  done \
	fi
	if test -d dictionary; then \
	  mkdir $(distdir)/dictionary; \
	  for dictionary in dictionary/*; do \
	    if test -f $$dictionary; then \
	      cp -p $$dictionary $(distdir)/dictionary; \
	    fi \
	  done \
	fi


