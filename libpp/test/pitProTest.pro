include (../../config/cbrtestapp.pro)

TARGET = pitProTest
QT += sql xml
CONFIG += qt

INCLUDEPATH += ../../libpp/src
INCLUDEPATH += ../../libCbrTypes/src
INCLUDEPATH += ../../libPitObs/src
INCLUDEPATH += ../../libCbrDate/src

INCLUDEPATH +=  $$(BOOSTDIR)

CONFIG(debug, debug|release) {
	LIBS += -L../../libpp/debug
	LIBS += -L../../libStringUtilities/debug 
	LIBS += -L../../libSitesConfig/debug
	LIBS += -L../../libPitObs/debug
	LIBS += -L../../libCbrDate/debug
	LIBS += -L../../libCbrUi/debug
} else {
	LIBS += -L../../libpp/release 
	LIBS += -L../../libStringUtilities/release
	LIBS += -L../../libSitesConfig/release
	LIBS += -L../../libPitObs/release
	LIBS += -L../../libCbrDate/release
	LIBS += -L../../libCbrUi/release
}

LIBS += -L$$(BOOSTDIR)/lib
LIBS += -lpp -lsitesConfig -lstringUtilities -lcbrui
LIBS += -lpitObs -lcbrDate

HEADERS +=	src/PPRunInfoTest.h \	
		src/SettingsTest.h

SOURCES +=	src/main.cpp \
		src/PPRunInfoTest.cpp \
		src/SettingsTest.cpp 

