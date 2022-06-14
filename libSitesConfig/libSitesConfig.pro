include (../config/cbrlib.pro)

TARGET   = sitesConfig

#INCLUDEPATH += ../libStringUtilities/src
INCLUDEPATH += ../libCbrTypes/src
INCLUDEPATH += ../libCbrDate/src
INCLUDEPATH += $$(BOOSTDIR)

HEADERS += src/CbrPit.h \
        src/Code.h \
        src/Detector.h \
        src/Exception.h \
        src/Range.h \
        src/RiverKm.h \
        src/Site.h \
        src/Sites.h

SOURCES +=	src/CbrPit.cpp \
        src/Code.cpp \
        src/Detector.cpp \
        src/Exception.cpp \
        src/Range.cpp \
        src/RiverKm.cpp \
        src/Site.cpp \
        src/Sites.cpp

CONFIG(debug, debug|release) {
#    LIBS += -L../libStringUtilities/debug
    LIBS += -L../libCbrDate/debug
    LIBS += -L../libCbrTypes/debug
} else {
#    LIBS += -L../libStringUtilities/release
    LIBS += -L../libCbrDate/release
    LIBS += -L../libCbrTypes/release
}
