AUTOMAKE_OPTIONS = foreign

INCLUDES = -I$(includedir) -I$(OFFLINE_MAIN)/include -I$(ROOTSYS)/include

lib_LTLIBRARIES = \
  libfrodo.la

noinst_HEADERS = \
  frodoLinkDef.h

include_HEADERS = \
  AParticle.h \
  AStrip.h \
  APadStrip.h \
  ARing.h \
  frodo.h \
  RingParameter.h \
  Generate.h \
  GenerateNonStd.h \
  GenerateTr1.h \
  GenerateTr2.h \
  Deposit.h \
  DepositTr1.h \
  DepositTr2.h \
  Drawing.h \
  DrawingTr1.h \
  DrawingTr2.h \
  Ringfinder.h \
  Coordinates.h \
  Evaluate.h \
  RingRecEff.h 

libfrodo_la_SOURCES = \
  AStrip.C \
  APadStrip.C \
  AParticle.C \
  ARing.C \
  frodo.C \
  RingParameter.C \
  Generate.C \
  GenerateNonStd.C \
  GenerateTr1.C \
  GenerateTr2.C \
  Deposit.C \
  DepositTr1.C \
  DepositTr2.C \
  Drawing.C \
  DrawingTr1.C \
  DrawingTr2.C \
  Ringfinder.C \
  Evaluate.C \
  RingRecEff.C \
  frodo_Dict.C

libfrodo_la_LIBADD = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib

# Rule for generating CINT dictionaries from class headers.
frodo_Dict.C: \
  AParticle.h \
  AStrip.h \
  APadStrip.h \
  ARing.h \
  RingParameter.h \
  frodo.h \
  Generate.h \
  GenerateNonStd.h \
  GenerateTr1.h \
  GenerateTr2.h \
  Deposit.h \
  DepositTr1.h \
  DepositTr2.h \
  Drawing.h \
  DrawingTr1.h \
  DrawingTr2.h \
  Ringfinder.h \
  Coordinates.h \
  Evaluate.h \
  RingRecEff.h \
  frodoLinkDef.h
	rootcint -f $@ -c $(DEFAULT_INCLUDES) $(INCLUDES) $^

clean-local:
	rm -f *Dict*
