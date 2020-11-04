include (../config/cbrlib.pro)

TARGET  = libcbrqt4
INCLUDEPATH	+= tmp ../libcbrstd/src

# Input
FORMS +=	src/TextWindow.ui \
#    src/editwindow.ui \
    src/newEditWindow.ui

HEADERS += 	src/TextWindow.h \
		src/ImageDimSpinBox.h \
		src/FileChooser.h \
		src/ComputationEvent.h \
		src/ComputationThread.h \
		src/parseOutDirectory.h \
		src/RangeLineEdit.h \
		src/RangeLineEditMgr.h \ 
    src/newEditWindow.h
		

SOURCES += 	src/TextWindow.cpp \
		src/ImageDimSpinBox.cpp \
		src/FileChooser.cpp \
		src/ComputationThread.cpp \
		src/parseOutDirectory.cpp\
		src/RangeLineEdit.cpp \
		src/RangeLineEditMgr.cpp \
    src/newEditWindow.cpp
 
			
