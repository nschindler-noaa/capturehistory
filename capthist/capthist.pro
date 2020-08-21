include (../config/cbrapp_console.pro)

TARGET = capthistapp

QT += xml network

INCLUDEPATH += ../libCbrTypes/src ../libcbrqt4/src
INCLUDEPATH += ../libcbrqt4/tmp ../libpp/src ../libpp/tmp
INCLUDEPATH += ../libStringUtilities/src
INCLUDEPATH += ../libSitesConfig/src
INCLUDEPATH += ../libCbrUi/src
INCLUDEPATH += ../libCbrDate/src
INCLUDEPATH += ../libPitObs/src
INCLUDEPATH += ../libCapthist/src
INCLUDEPATH +=  $$(BOOSTDIR) 

CONFIG(debug, debug|release) {
    LIBS += -L../libcbrqt4/debug
    LIBS += -L../libpp/debug
    LIBS += -L../libStringUtilities/debug
    LIBS += -L../libPitObs/debug
    LIBS += -L../libSitesConfig/debug
    LIBS += -L../libCbrUi/debug
    LIBS += -L../libCbrDate/debug
#    LIBS += -L../libCbrThread/debug
    LIBS += -L../libCapthist/debug
} else {
    LIBS += -L../libcbrqt4/release
    LIBS += -L../libpp/release
    LIBS += -L../libStringUtilities/release
    LIBS += -L../libPitObs/release
    LIBS += -L../libSitesConfig/release
    LIBS += -L../libCbrUi/release
    LIBS += -L../libCbrDate/release
#    LIBS += -L../libCbrThread/release
    LIBS += -L../libCapthist/release
}

LIBS += -lcapthist -lpp -lcbrqt4 -lpitObs -lsitesConfig -lcbrui -lcbrDate  -lstringUtilities
#LIBS += -lcapthist -lpp -lcbrqt4 -lpitObs -lsitesConfig -lcbrui -lcbrDate  -lstringUtilities
#LIBS += -lcapthist -lpp -lcbrqt4  -lcbrThread  -lpitObs -lsitesConfig -lcbrui -lcbrDate  -lstringUtilities

unix {
  LIBS += -L$$(BOOSTDIR)/lib64
  LIBS += -lboost_system -lboost_regex
}
win32 {
  LIBS += -L$$(BOOSTDIR)/lib 
}


CONFIG(debug, debug|release) {
    PRE_TARGETDEPS += ../libcbrqt4/debug/libcbrqt4.a
    PRE_TARGETDEPS += ../libpp/debug/libpp.a
    PRE_TARGETDEPS += ../libStringUtilities/debug/libstringUtilities.a
    PRE_TARGETDEPS += ../libPitObs/debug/libpitObs.a
    PRE_TARGETDEPS += ../libSitesConfig/debug/libsitesConfig.a
    PRE_TARGETDEPS += ../libCbrUi/debug/libcbrui.a
    PRE_TARGETDEPS += ../libCbrDate/debug/libcbrDate.a
#    PRE_TARGETDEPS += ../libCbrThread/debug/libcbrThread.a
    PRE_TARGETDEPS += ../libCapthist/debug/libcapthist.a
} else {
    PRE_TARGETDEPS += ../libcbrqt4/release/libcbrqt4.a
    PRE_TARGETDEPS += ../libpp/release/libpp.a
    PRE_TARGETDEPS += ../libStringUtilities/release/libstringUtilities.a
    PRE_TARGETDEPS += ../libPitObs/release/libpitObs.a
    PRE_TARGETDEPS += ../libSitesConfig/release/libsitesConfig.a
    PRE_TARGETDEPS += ../libCbrUi/release/libcbrui.a
    PRE_TARGETDEPS += ../libCbrDate/release/libcbrDate.a
#    PRE_TARGETDEPS += ../libCbrThread/release/libcbrThread.a
    PRE_TARGETDEPS += ../libCapthist/release/libcapthist.a
}


SOURCES	=  src/PPBatchMain.cpp
