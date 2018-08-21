@echo off

REM 
REM Setup environment
REM


echo Setting Up Environment

call setenv.bat

echo -- Qt:     %QTDIR%
echo -- Boost:  %BOOSTDIR%
echo -- Xerces: %XERCESDIR%
echo -- Qwt:    %QWTDIR%
echo -- GTest:  %GTESTDIR%
echo -- GMock:  %GMOCKDIR%


REM
REM Call QMake on all .pro files
REM

echo QMakeing Project Files

SET QMAKE=%QTDIR%\bin\qmake

REM Libraries
REM ---------

echo .Libraries

call %WORKING_DIRECTORY%\qmake_libs.bat


REM Applications
REM ------------

echo .Applications

call %WORKING_DIRECTORY%\qmake_apps.bat
