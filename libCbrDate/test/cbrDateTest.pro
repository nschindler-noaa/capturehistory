include (../../config/cbrtestapp.pro)


TARGET = cbrDateTest
CONFIG += qt

INCLUDEPATH += ../src
INCLUDEPATH += ../../libStringUtilities/src
INCLUDEPATH += ../../libCbrTypes/src


INCLUDEPATH +=  $$(BOOSTDIR)

CONFIG(debug, debug|release) {
	LIBS += -L../debug
	LIBS += -L../../libStringUtilities/debug 
} else {
	LIBS += -L../release
	LIBS += -L../../libStringUtilities/release
}

LIBS += -L$$(BOOSTDIR)/lib
LIBS += -lstringUtilities
LIBS += -lcbrDate

HEADERS +=	src/DateConverterTest.h

SOURCES +=	src/main.cpp \
	src/DateConverterTest.cpp 
