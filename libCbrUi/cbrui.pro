include (../config/cbrlib.pro)
TARGET  = cbrui
DEFINES += QWT_DLL
RESOURCES += src/cbrui.qrc
INCLUDEPATH += ../libCbrThread/src
#INCLUDEPATH += ../libQtReport/src
#INCLUDEPATH += ../libQtSqlite/src

INCLUDEPATH += $$(QWTDIR)/src
INCLUDEPATH += $$(BOOSTDIR)

# Input
FORMS   += src/CbrMainWindow.ui

HEADERS += \
        src/CbrMainWindow.h \
        src/CbrPlotControls.h \
        src/CbrQtSettingsProxy.h \
        src/CbrSettings.h \
        src/CbrSettingsProxy.h \
        src/CbrStyle.h \
        src/CbrSubWidget.h \
        src/NavPanelItem.h \
        src/NavPanelModel.h \
        src/NavPanelView.h \
        src/OutputDockWidget.h

SOURCES += \
        src/CbrMainWindow.cpp \
        src/CbrPlotControls.cpp \
        src/CbrQtSettingsProxy.cpp \
        src/CbrSettings.cpp \
        src/CbrStyle.cpp \
        src/CbrSubWidget.cpp \
        src/NavPanelItem.cpp  \
        src/NavPanelModel.cpp  \
        src/NavPanelView.cpp  \
        src/OutputDockWidget.cpp
