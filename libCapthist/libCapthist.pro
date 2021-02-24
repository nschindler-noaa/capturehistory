include (../config/cbrlib.pro)

TARGET = capthist

QT += xml network

INCLUDEPATH += ../libCbrTypes/src
INCLUDEPATH += ../libcbrqt4/src ../libcbrqt4/tmp
INCLUDEPATH += ../libpp/src ../libpp/tmp
INCLUDEPATH += ../libStringUtilities/src
INCLUDEPATH += ../libSitesConfig/src
INCLUDEPATH += ../libCbrUi/src
INCLUDEPATH += ../libCbrDate/src
INCLUDEPATH += ../libPitObs/src
#INCLUDEPATH +=  $$(BOOSTDIR)

SOURCES	=  src/PPBatch.cpp \
    src/PPRunConfig.cpp \
    src/PPGetOpts.cpp \
    src/PPBatchOutputMaker.cpp

HEADERS	=  src/PPBatch.h \
    src/PPRunConfig.h \
    src/PPGetOpts.h \
    src/PPBatchOutputMaker.h
