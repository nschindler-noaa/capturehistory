include (cbrapp_console.pro)

QT += sql

INCLUDEPATH += src 
INCLUDEPATH += $$(GMOCKDIR)/gtest/include
INCLUDEPATH += $$(GMOCKDIR)/include

CONFIG(debug, debug|release) {
	LIBS += -L../debug 
	LIBS += -l$$(GMOCKDIR)/gtest/msvc/gtest-md/Debug/gtestd
#	LIBS += -l$$(GMOCKDIR)/msvc/2010/Debug/gmock
} else {
	LIBS += -L../release 
	LIBS += -l$$(QWTDIR)/lib/qwtd
	LIBS += -l$$(GMOCKDIR)/gtest/msvc/gtest-md/Release/gtestd
#	LIBS += -l$$(GMOCKDIR)/msvc/2010/Release/gmock
}




