include (../../config/cbrtestapp.pro)

TARGET = cbrTypesTest

INCLUDEPATH += src ../src

CONFIG(debug, debug|release) {
	LIBS += -L../debug
	LIBS += -L../../libCjs/debug
} else {
	LIBS += -L../release
	LIBS += -L../../libCjs/release
}

LIBS += -lcbrTypes

HEADERS +=		src/TestMatrixOperations.h

SOURCES +=		src/main.cpp \
				src/TestMatrixOperations.cpp
