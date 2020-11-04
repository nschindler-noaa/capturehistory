include (../config/cbrlib.pro)

TARGET   = pp

QT += xml network

RESOURCES += \
    src/icons.qrc

INCLUDEPATH += ../libpp/src ../libCbrTypes/src
INCLUDEPATH += ../libStringUtilities/src 
INCLUDEPATH += ../libSitesConfig/src
INCLUDEPATH += ../libPitObs/src
INCLUDEPATH += ../libCbrDate/src
INCLUDEPATH += ../libCbrUi/src ../libCbrUi/tmp
INCLUDEPATH += ../libCbrThread/src


INCLUDEPATH += $$(BOOSTDIR) $$(XERCESDIR)/include

FORMS	= \
	src/PitProWindow.ui \
	src/SitesConfigDialog.ui \
	src/UpdateManager.ui \
    src/configwidget.ui \
    src/dataconverter.ui \
    src/csvconverterdialog.ui \
    src/infodialog.ui \
    src/resultmanager.ui \
    src/ResultsManager_old.ui

HEADERS	+= src/CapthistRun.h \
	src/CaptureHistoryMap.h \
	src/CjsEstimates.h \
	src/CjsStatistics.h \
	src/CjsReport.h \
	src/CjsUnformattedReport.h \
	src/CjsCaptureHistory.h \
	src/ErrorObject.h \
	src/GlobalDefs.h \
	src/Parser.h \
	src/ParseError.h \
	src/Token.h \
	src/Tokenizer.h \
	src/TokenizerIterator.h \
	src/ReportElement.h \
	src/Dsplit.h \
	src/OFile.h \
	src/portability.h \
	src/PCode.h \
	src/PPData.h \
	src/PPDdOutput.h \
	src/PPDefs.h \
	src/PPErrors.h \
	src/PPErrorsOutput.h \
	src/PPFileOutput.h \
	src/PPFishData.h \
	src/PPObs.h \
	src/PPOutputMaker.h \
	src/PPRecap.h \
	src/PPRel.h \
	src/PPRunInfo.h \
	src/PPSeqOutput.h \
	src/PPSurphOutput.h \
	src/PPTag.h \
	src/PPTtOutput.h \
	src/PPVersion.h \
	src/PitProSettings.h \
	src/ReportBuilder.h \
	src/RunConfigVector.h \
	src/Settings.h \
	src/SitesConfigDialog.h \
	src/Statistics.h \
	src/SurphData.h \
	src/TaggingData.h \
	src/Utilities.h \
	src/ConfigWidgetImpl.h \
	src/CsvConverter.h \
	src/CsvConverterDialogImpl.h \
	src/DataConverterCT.h \
	src/DataConverterImpl.h \
	src/FileTableItem.h \
	src/PPComputationThread.h \
	src/PPSystemSettings.h \
	src/PitProUtilities.h \
	src/PitProWindowImpl.h \
	src/ResultsManagerImpl.h \
	src/UpdateManagerImpl.h \
    src/ComputationEvent.h \
    src/ComputationThread.h \
    src/configwidget.h \
    src/dataconverter.h \
    src/csvconverterdialog.h \
    src/infodialog.h \
    src/resultmanager.h
	
SOURCES	+= src/CapthistRun.cpp \
	src/CjsEstimates.cpp \
	src/CjsStatistics.cpp \
	src/CjsReport.cpp \
	src/CjsUnformattedReport.cpp \
	src/CjsCaptureHistory.cpp \
	src/ErrorObject.cpp \
	src/GlobalDefs.cpp \
	src/Parser.cpp \
	src/Tokenizer.cpp \
	src/TokenizerIterator.cpp \
	src/ParseError.cpp \
	src/Dsplit.cpp \
	src/OFile.cpp \
	src/PCode.cpp \
	src/PPData.cpp \
	src/PPDdOutput.cpp \
	src/PPErrors.cpp \
	src/PPErrorsOutput.cpp \
	src/PPFileOutput.cpp \
	src/PPFishData.cpp \
	src/PPObs.cpp \
	src/PPOutputMaker.cpp \
	src/PPRecap.cpp \
	src/PPRel.cpp \
	src/PPRunInfo.cpp \
	src/PPSeqOutput.cpp \
	src/PPSurphOutput.cpp \
	src/PPTag.cpp \
	src/PPTtOutput.cpp \
	src/PPVersion.cpp \
	src/PitProSettings.cpp \
	src/ReportBuilder.cpp \
	src/Settings.cpp \
	src/SitesConfigDialog.cpp \
	src/Statistics.cpp \
	src/SurphData.cpp \
	src/ConfigWidgetImpl.cpp \
	src/CsvConverter.cpp \
	src/CsvConverterDialogImpl.cpp \
	src/DataConverterCT.cpp \
	src/DataConverterImpl.cpp \
	src/FileTableItem.cpp \
	src/PPComputationThread.cpp \
	src/PPSystemSettings.cpp \
	src/PitProUtilities.cpp \
	src/PitProWindowImpl.cpp \
	src/ResultsManagerImpl.cpp \
	src/UpdateManagerImpl.cpp \
    src/ComputationThread.cpp \
    src/configwidget.cpp \
    src/dataconverter.cpp \
    src/csvconverterdialog.cpp \
    src/infodialog.cpp \
    src/resultmanager.cpp
	










