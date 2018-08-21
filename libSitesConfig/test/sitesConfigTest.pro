include (../../config/cbrtestapp.pro)


TARGET = sitesConfigTest
QT += sql xml
CONFIG += qt

INCLUDEPATH += ../src
INCLUDEPATH += ../../libCbrTypes/src
INCLUDEPATH += ../../libCbrDate/src

INCLUDEPATH +=  $$(BOOSTDIR)

CONFIG(debug, debug|release) {
	LIBS += -L../../libStringUtilities/debug 
		LIBS += -L../../libSitesConfig/debug
	LIBS += -L../../libCbrDate/debug
} else {
	LIBS += -L../../libStringUtilities/release
		LIBS += -L../../libSitesConfig/release
	LIBS += -L../../libCbrDate/release
}

LIBS += -L$$(BOOSTDIR)/lib
LIBS +=  -lsitesConfig -lstringUtilities -lcbrDate

HEADERS +=	src/SiteTest.h 

SOURCES +=	src/main.cpp \
		src/SiteTest.cpp

