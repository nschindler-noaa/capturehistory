include (../config/cbrlib.pro)
TARGET  = stringUtilities
INCLUDEPATH += src 

# Input
HEADERS +=	src/parseOutDirectory.h \
		src/StringManip.h \
		src/StringTok.h \
		src/StringUtil.h

SOURCES +=	src/parseOutDirectory.cpp \
		src/StringManip.cpp \
		src/StringUtil.cpp \
    src/stringtok.cpp
