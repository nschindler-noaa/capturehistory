# 
# general settings shared by all qmake projects
#

# basic configuration
LANGUAGE  = C++
CONFIG += thread exceptions rtti warn_on windows debug_and_release
#QT     += sql widgets printsupport
QT     += sql core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

# change these to switch between debug and release builds
# Use qmakespec settings to build both debug and release


# src dir and include path
INCLUDEPATH = src
UI_DIR = tmp
MOC_DIR = tmp

# objects dir
CONFIG(debug, debug|release) {
	#message(Parsing debug settings.)
	OBJECTS_DIR = debug
	DESTDIR = debug
} else {
	#message(Parsing release settings.)
	OBJECTS_DIR = release
	DESTDIR = release
}

