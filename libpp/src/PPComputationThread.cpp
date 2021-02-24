/*
* PPComputationThread
*
* This provides the main linkage between the old program
* capthist and the new program PitPro. To make this as
* painless as possible, we try to use the existing mechanisms
* in capthist rather than re-writting everything. This means
* create the Flag and Rc data structures from the ConfigWidget
* input to mimic a command line run.
*
*/

#include <string>
#include <vector>

#include <stdlib.h>
#include <stdio.h>

#include <qstringlist.h>
#include <qfileinfo.h>
#include <QMessageBox>

#include <ArrayDefs.h>
#include "PPComputationThread.h"
#include "PitProSettings.h"
#include "CapthistRun.h"

using std::string;
using std::vector;
using std::pair;

using namespace cbr;

PPComputationThread::PPComputationThread( QObject* p, const QString& name ) :
    ComputationThread( p, name ), isCanceled (false)
{}

PPComputationThread::~PPComputationThread()
{}

void PPComputationThread::compute()
{
    PitProSettings& settings = PitProSettings::getInstance();

    // detemine number of capthist runs to do
    QString outputFormat = settings.getValue(PitProSettings::OutputFormat);
    bool groupRuns = settings.isChecked( PitProSettings::GroupRuns ) && outputFormat.compare("ROSTER") != 0;
    int numGroups = settings.getNumGroups();
    int numRuns = ( groupRuns ) ? 1 : numGroups;

    CapthistRun chrun( *this );
    setBytesExpected( getTotalBytes() );

    isCanceled = false;
    chrun.setIsCanceledPtr( &isCanceled );
    for ( int run = 0; run < numRuns; run++ )
    {
        // get group name(s)
        QString outPrefix;
        if ( settings.isChecked( PitProSettings::GroupRuns) )
            outPrefix = settings.getValue (PitProSettings::OutPrefix);


        RunConfigVector runConfigVector;
        if (groupRuns && numGroups > 1)
        {
            settings.getAllRunConfigs(runConfigVector);

            if (outPrefix.isEmpty()) {
                outPrefix = "composite";
                settings.setValue(PitProSettings::OutPrefix, outPrefix);
            }
        }
        else {
            QString msg("Processing group ");
            settings.getRunConfig(runConfigVector, run);

            if (outPrefix.isEmpty()) {
                outPrefix = runConfigVector[0].name;
                settings.setValue(PitProSettings::OutPrefix, outPrefix);
            }
            msg.append(QString("\"%1\"...").arg(runConfigVector[0].name));
            write (msg.toStdString());
//			write (QString("Processing group \"%1\"...").arg(runConfigVector[0].name));
        }

        chrun.compute (outPrefix, runConfigVector);
        if (chrun.isCanceled())
            status = Cancel;
        if ( status == Cancel)
        {
            QString message = "Run canceled";
            if (chrun.hasError()) {
                message += ": " + chrun.getErrorMessage();
            }
            sendErrorMessage(message);
            sendCanceledSignal();
        }
    }
    write( "Done" );

    if (chrun.isIcovMissing()) {
        sendErrorMessage("Some individual covariates were missing, which is not compatible with SURPH."
            " Please re-run with <strong>Remove null valued covariates</strong> checked.");
        sendCanceledSignal();
    }
    else if ( status == Ok )
        sendCompletedSignal();
}

void PPComputationThread::setStatus( RunStatus runStatus )
{
    ComputationThread::setStatus (runStatus);
    if (runStatus == Cancel)
        isCanceled = true;
}


int PPComputationThread::getTotalBytes() const
{
    PitProSettings& settings = PitProSettings::getInstance();
    const QStringList obsFiles = settings.getObsFiles( -1 );
    int numBytes = 0;
    for (QStringList::const_iterator it = obsFiles.begin(); it!= obsFiles.end(); it++)
    {
        QFileInfo fi (settings.getDataFilePath(*it));
        if (fi.exists())
            numBytes += fi.size();
    }

    return numBytes;
}

void PPComputationThread::setBytesExpected (int num)
{
    PPOutputMaker::setBytesExpected(num);
    sendNumSteps(100);
    currentStep = 0;
}

void PPComputationThread::setCurrentBytes (int num)
{
    PPOutputMaker::setCurrentBytes (num);
    double stepSize = bytesExpected / 100.0;
    if ( currentStep * stepSize < bytesRead)
        sendCurrentStep(currentStep++);
}

void PPComputationThread::setNumSteps (int num)
{
    sendNumSteps(num);
}

void PPComputationThread::setCurrentStep (int step)
{
    sendCurrentStep(step);
}

void PPComputationThread::setProgressMessage( const std::string& msg )
{
    sendProgressMessage( msg.c_str() );
}

void PPComputationThread::write( const std::string& msg, OutputType type )
{
    PitProSettings& settings = PitProSettings::getInstance();

    if ( type != PPOutputMaker::Warning || settings.isChecked(PitProSettings::Warnings)) {
        string message;
        if (type == PPOutputMaker::Warning)
            message.append("Warning: ");
        else if ( type == PPOutputMaker::Error )
            message.append("Error: ");

        message.append(msg);
        sendStatusMessage(message.c_str());
    }
}

