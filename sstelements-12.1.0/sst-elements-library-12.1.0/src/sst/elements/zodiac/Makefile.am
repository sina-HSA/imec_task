# -*- Makefile -*-
#
#

AM_CPPFLAGS += \
	$(MPI_CPPFLAGS) \
	-I$(top_srcdir)/src

compdir = $(pkglibdir)
comp_LTLIBRARIES = libzodiac.la
libzodiac_la_SOURCES = \
	ztrace.cc \
	ztrace.h \
	zevent.h \
	zevent.cc \
	zsendevent.h \
	zsendevent.cc \
	zrecvevent.h \
	zrecvevent.cc \
	siriusreader.h \
	siriusreader.cc \
	sirius/siriusconst.h \
	zsirius.h \
	zsirius.cc \
	zbarrierevent.h \
	zbarrierevent.cc \
	zcomputeevent.h \
	zcomputeevent.cc \
	zinitevent.h \
	zinitevent.cc \
	zirecvevent.h \
	zirecvevent.cc \
	zwaitevent.h \
	zwaitevent.cc \
	zfinalizeevent.h \
	zfinalizeevent.cc \
	zallredevent.h \
	zallredevent.cc \
	zcollective.h \
	zcollective.cc

EXTRA_DIST = \
	test/allreduce/allreduce.py \
	sirius/tests/refFiles/test_Sirius_allred_128.out \
	sirius/tests/refFiles/test_Sirius_allred_16.out \
	sirius/tests/refFiles/test_Sirius_allred_27.out \
	sirius/tests/refFiles/test_Sirius_allred_4x4.out \
	sirius/tests/refFiles/test_Sirius_allred_64.out \
	sirius/tests/refFiles/test_Sirius_allred_8x8.out \
	sirius/tests/refFiles/test_Sirius_allred_8x8x2.out \
	test/testsuite_default_SiriusZodiacTrace.py

libzodiac_la_LDFLAGS = -module -avoid-version

if USE_OTF
libzodiac_la_SOURCES += \
	otfreader.h \
	otfreader.cc \
	zotf.h \
	zotf.cc

AM_CPPFLAGS += \
	$(shell $(OTF_CONFIG_TOOL) --includes)

libzodiac_la_LDFLAGS += \
	$(shell $(OTF_CONFIG_TOOL) --libs)
endif

if USE_DUMPI
libzodiac_la_SOURCES += \
	zdumpi.cc \
	zdumpi.h \
	dumpireader.h \
	dumpireader.cc \
	dumpifunc.h

AM_CPPFLAGS += \
	$(DUMPI_CPPFLAGS)

libzodiac_la_LDFLAGS += \
	$(DUMPI_LDFLAGS)
endif

install-exec-hook:
	$(SST_REGISTER_TOOL) SST_ELEMENT_SOURCE     zodiac=$(abs_srcdir)
	$(SST_REGISTER_TOOL) SST_ELEMENT_TESTS      zodiac=$(abs_srcdir)/test
