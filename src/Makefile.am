## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = gdictthai tdictthai

gdictthai_SOURCES = \
	main.c \
	interface.c interface.h \
	callbacks.c callbacks.h \
	dictionary.c dictionary.h

gdictthai_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

tdictthai_SOURCES = \
	tdictthai.c \
  dictionary.c dictionary.h

tdictthai_LDADD = $(INTLLIBS)
