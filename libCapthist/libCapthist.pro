include (../config/cbrlib.pro)

TARGET = capthist

QT += xml network

INCLUDEPATH += ../libCbrTypes/src ../libcbrqt4/src
INCLUDEPATH += ../libcbrqt4/tmp ../libpp/src ../libpp/tmp
#INCLUDEPATH += ../libStringUtilities/src
INCLUDEPATH += ../libSitesConfig/src
INCLUDEPATH += ../libCbrUi/src
INCLUDEPATH += ../libCbrDate/src
INCLUDEPATH += ../libPitObs/src
INCLUDEPATH +=  $$(BOOSTDIR)

SOURCES	=  src/PPBatch.cpp src/PPRunConfig.cpp src/PPGetOpts.cpp
HEADERS	=  src/PPBatch.h src/PPRunConfig.h src/PPGetOpts.h src/PPBatchOutputMaker.h
