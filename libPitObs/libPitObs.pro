include (../config/cbrlib.pro)

TARGET   = pitObs

#INCLUDEPATH += ../libStringUtilities/src
INCLUDEPATH += ../libSitesConfig/src
INCLUDEPATH += ../libCbrTypes/src
INCLUDEPATH += ../libCbrDate/src

INCLUDEPATH += $$(BOOSTDIR)


HEADERS +=	src/ErrorFlags.h \
        src/ObsDataRow.h \
        src/ObsErrors.h \
        src/ObsPreProcessor.h \
        src/ObsProcessor.h \
        src/ObsProcessorWriter.h \
        src/ObsReader.h \
        src/SitesMask.h \
        src/ObsSequence.h

SOURCES +=	src/ErrorFlags.cpp \
        src/ObsPreProcessor.cpp \
        src/ObsProcessor.cpp \
        src/SitesMask.cpp \
        src/ObsSequence.cpp
