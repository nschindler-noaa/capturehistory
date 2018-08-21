@echo off

REM
REM Setup environment
REM

call setenv.bat


REM
REM Run QMake on unit test .pro files
REM

echo ...libAlg
cd %SOURCEDIR%\libAlg
%QMAKE% alg.pro

echo ...libAtlas
cd %SOURCEDIR%\libAtlas
%QMAKE% libAtlas.pro

echo ...libBlt
cd %SOURCEDIR%\libBlt
%QMAKE% libblt.pro

echo ...libCapthist
cd %SOURCEDIR%\libCapthist
%QMAKE% libCapthist.pro

echo ...libCbrDate
cd %SOURCEDIR%\libCbrDate
%QMAKE% libCbrDate.pro

echo ...libCbrPlot
cd %SOURCEDIR%\libCbrPlot
%QMAKE% cbrPlot.pro

echo ...libcbrqt4
cd %SOURCEDIR%\libcbrqt4
%QMAKE% libcbrqt4.pro

echo ...libcbrstd
cd %SOURCEDIR%\libcbrstd
%QMAKE% libcbrstd.pro

echo ...libCbrThread
cd %SOURCEDIR%\libCbrThread
%QMAKE% libCbrThread.pro 

echo ...libCbrTypes
cd %SOURCEDIR%\libCbrTypes
%QMAKE% cbrTypes.pro 

echo ...libCbrUi
cd %SOURCEDIR%\libCbrUi
%QMAKE% libCbrUi.pro

echo ...libCjs
cd %SOURCEDIR%\libCjs
%QMAKE% cjs.pro

echo ...libCoordinate
cd %SOURCEDIR%\libCoordinate
%QMAKE% coordinate.pro

echo ...libEquation
cd %SOURCEDIR%\libEquation
%QMAKE% equation.pro 

echo ...libEstimate
cd %SOURCEDIR%\libEstimate
%QMAKE% estimate.pro

echo ...libNavPanel
cd %SOURCEDIR%\libNavPanel
%QMAKE% navPanel.pro

echo ...libNumericalRecipes3
cd %SOURCEDIR%\libNumericalRecipes3
%QMAKE% numericalRecipes3.pro

echo ...libParser
cd %SOURCEDIR%\libParser
%QMAKE% parser.pro 

echo ...libPassageTiming
cd %SOURCEDIR%\libPassageTiming
%QMAKE% libPassageTiming.pro

echo ...libPitObs
cd %SOURCEDIR%\libPitObs
%QMAKE% libPitObs.pro

echo ...libProfileLikelihoods
cd %SOURCEDIR%\libProfileLikelihoods
%QMAKE% profileLikelihoods.pro

echo ...libpp
cd %SOURCEDIR%\libpp
%QMAKE% libpp.pro

echo ...libQtReport
cd %SOURCEDIR%\libQtReport
%QMAKE% qtreport.pro 

echo ...libQtSqlite
cd %SOURCEDIR%\libQtSqlite
%QMAKE% qtsqlite.pro 

echo ...libroster
cd %SOURCEDIR%\libroster
%QMAKE% libroster.pro

echo ...libSqliteBrowser
cd %SOURCEDIR%\libSqliteBrowser
%QMAKE% sqliteBrowser.pro 

echo ...libSitesConfig
cd %SOURCEDIR%\libSitesConfig
%QMAKE% libSitesConfig.pro 

echo ...libSqlite
cd %SOURCEDIR%\libSqlite
%QMAKE% sqlite.pro 

echo ...libStringUtilities
cd %SOURCEDIR%\libStringUtilities
%QMAKE% libStringUtilities.pro

echo ...libStatistics
cd %SOURCEDIR%\libStatistics
%QMAKE% statistics.pro

echo ...libsurph
cd %SOURCEDIR%\libsurph
%QMAKE% libsurph.pro

echo ...libTribPit
cd %SOURCEDIR%\libTribPit
%QMAKE% libTribPit.pro

echo ...libTribPitAuxiliary
cd %SOURCEDIR%\libTribPitAuxiliary
%QMAKE% libTribPitAuxiliary.pro

echo ...libTribPitGenExpCounts
cd %SOURCEDIR%\libTribPitGenExpCounts
%QMAKE% libTribPitGenExpCounts.pro

echo ...libTribPitEstimateFromCounts
cd %SOURCEDIR%\libTribPitEstimateFromCounts
%QMAKE% libTribPitEstimateFromCounts.pro

echo ...libTribPitSim
cd %SOURCEDIR%\libTribPitSim
%QMAKE% libTribPitSim.pro

echo ...libuser
cd %SOURCEDIR%\libuser
%QMAKE% user.pro

echo ...libxmlutils
cd %SOURCEDIR%\libxmlutils
%QMAKE% libxmlutils.pro

cd %WORKING_DIRECTORY%
