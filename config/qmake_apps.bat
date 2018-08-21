@echo off

REM
REM Setup environment
REM

call setenv.bat


REM
REM Run QMake on unit test .pro files
REM
echo ...atlas
cd %SOURCEDIR%\atlas
%QMAKE% atlasapp.pro

echo ...atlasParser
cd %SOURCEDIR%\atlasParser
%QMAKE% atlasParser.pro

echo ...attools
cd %SOURCEDIR%\attools
%QMAKE% attracker.pro
%QMAKE% locate.pro

echo ...blt
cd %SOURCEDIR%\blt
%QMAKE% blt.pro

echo ...capthist
cd %SOURCEDIR%\capthist
%QMAKE% capthist.pro

echo ...passageTiming
cd %SOURCEDIR%\passageTiming
%QMAKE% passageTimingApp.pro

echo ...pitpro
cd %SOURCEDIR%\pitpro
%QMAKE% pitpro.pro

echo ...surph
cd %SOURCEDIR%\surph
%QMAKE% surph.pro

echo ...samplesize
cd %SOURCEDIR%\samplesize
%QMAKE% samplesize.pro

echo ...tribPit
cd %SOURCEDIR%\tribPit
%QMAKE% tribPitApp.pro

echo ...tribPitNextDetections
cd %SOURCEDIR%\tribPitNextDetections
%QMAKE% tribPitNextDetections.pro

echo ...tribPitSim
cd %SOURCEDIR%\tribPitSim
%QMAKE% tribPitSimApp.pro

echo ...tribPitGenExpCounts
cd %SOURCEDIR%\tribPitGenExpCounts
%QMAKE% tribPitGenExpCountsApp.pro

echo ...tribPitEstimateFromCounts
cd %SOURCEDIR%\tribPitEstimateFromCounts
%QMAKE% tribPitEstimateFromCountsApp.pro

echo ...tribPitUserModelCreator
cd %SOURCEDIR%\tribPitUserModelCreator
%QMAKE% tribPitUserModelCreator.pro

echo ...user
cd %SOURCEDIR%\user
%QMAKE% userapp.pro

echo ...roster
cd %SOURCEDIR%\roster
%QMAKE% rosterapp.pro

cd %WORKING_DIRECTORY%