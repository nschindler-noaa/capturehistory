@echo off


REM
REM Setup environment
REM

call setenv.bat


REM
REM Run QMake on unit test .pro files
REM

cd %SOURCEDIR%\libAtlas\test
%QMAKE% atlasTest.pro

cd %SOURCEDIR%\libCbrTypes\test
%QMAKE% cbrTypesTest.pro

cd %SOURCEDIR%\libCjs\test
%QMAKE% cjsTest.pro

cd %SOURCEDIR%\libEquation\test
%QMAKE% equationTest.pro

cd %SOURCEDIR%\libpp\test
%QMAKE% pitProTest.pro

cd %SOURCEDIR%\libSitesConfig\test
%QMAKE% sitesConfigTest.pro

cd %SOURCEDIR%\libStatistics\test
%QMAKE% statisticsTest.pro

cd %SOURCEDIR%\libTribPit\test
%QMAKE% tribPitTest.pro

cd %SOURCEDIR%\libCbrDate\test
%QMAKE% cbrDateTest.pro

cd %WORKING_DIRECTORY%
