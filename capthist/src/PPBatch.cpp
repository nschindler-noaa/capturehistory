/*
 * PPBatchMain.cpp
 *
 * The main routine for the bar plot.
 */

#include <iostream>
#include <string>
#include <sstream>

#include <QFile>
#include <QStringList>

#include <portability.h>
#include <ArrayDefs.h>
#include <Sites.h>
#include <DateConverter.h>
#include <Dsplit.h>

#include <PPVersion.h>
#include <PPRunConfig.h>
#include <CbrSettings.h>
#include <PPSystemSettings.h>
#include <PitProSettings.h>
#include <CapthistRun.h>
#include <RunConfigVector.h>
#include <Settings.h>

#include "PPBatch.h"
#include "PPBatchOutputMaker.h"
#include "PPGetOpts.h"

using std::string;
using std::cout;
using std::cerr;
using std::cin;
//using std::endl;
//using std::stringstream;
//using std::ends;

using namespace cbr;

int PPBatch::run (PPGetOpts& opts, PPBatchOutputMaker& out)
{
    int retval = 0;

    // handle non-run modes: version, usage, new rc file
    if (opts.isChecked(PitProSettings::Version))
    {
        QString ver(PPSystemSettings::getInstance().get(PPSystemSettings::Version).toString());//PPVersion::versionString());
        QString text(QString("Capthist: Version %1\n").arg(ver));
        cout << text.toStdString();//<< "Capthist: Version " + PPVersion::versionString().toStdString() << endl;
    }
    else if (opts.isChecked(PitProSettings::Usage))
    {
        retval = usage(opts);
    }
    else if (opts.isChecked(PitProSettings::NewRcFile))
    {
        retval = newRcFile(out);
    }
    else
    {
        retval = runBatch(opts, out);
    }

    out.write("Done.", PPBatchOutputMaker::Emphasis);

    return retval;
}

int PPBatch::runBatch(PPGetOpts& opts, PPBatchOutputMaker& out)
{
    int retval = 0;
    QString ver (PPVersion::versionString());
    QString text(QString("Capthist v.%1").arg(ver));
    out.write(text, PPBatchOutputMaker::Emphasis);

    PitProSettings& settings = PitProSettings::getInstance();
    settings.clear();
    QString rcFileName (opts.getValue(QString("rcFileName")));
    if (!rcFileName.isEmpty() && !settings.readFromXml(rcFileName))
    {
        QString sstr ("Unable to read run configuration file: ");
        sstr.append(rcFileName);
        out.write(sstr, PPBatchOutputMaker::Warning);
    }
    settings.merge(opts, true);
    settings.setDefaults(); // fill in any missing parameters with defaults

    if (settings.getNumGroups() == 0)
        out.write("No data groups found.", PPBatchOutputMaker::Error);
    else
    {
        // read the sites configuration
        cbr::PPSystemSettings &systemSettings = cbr::PPSystemSettings::getInstance();
        systemSettings.resolveSitesConfig();
        QString configFile;
        if (settings.isSet(PitProSettings::AltSitesConfig)) // use alternate sites config
            configFile = settings.getValue(PitProSettings::AltSitesConfig);
        else
            configFile = systemSettings.get(cbr::PPSystemSettings::SitesConfigFile).toString();

        QFile file(configFile);
        if (!file.exists()) {
            QString msg(QString("Can't find sites configuration file \"%1\"").arg(configFile));
            out.write(msg, PPOutputMaker::Error);
        }
        else
        {
            Sites* sites = Sites::getInstance();
            QString msg(QString("Reading sites configuration file \"%1\". . .").arg(configFile.toStdString().data()));
            out.write(msg);
            sites->read(configFile);

            // run the batch program
            try
            {
                if (settings.isSet(PitProSettings::Dsplit))
                {
                    retval = dsplit(out);
                }
                else
                {
                    retval = batch(out);
                }
            }
            catch (string& msg)
            {
                out.write(msg.data(), PPBatchOutputMaker::Error);
            }
            catch (...)
            {
                out.write("Internal error", PPBatchOutputMaker::Error);
            }
        }
    }


    return retval;
}

int PPBatch::usage(PPGetOpts& opts)
{
    PitProSettings& settings = PitProSettings::getInstance();

    // read the users sites configuration file so that
    // usage information will contain the info
    settings.clear();
    QString rcFileName = opts.getValue("rcFileName");
    QString vernum = opts.getValue("Version");
    settings.readFromXml(rcFileName);
    settings.merge(opts, true);
    settings.setDefaults();
    Sites* sites = Sites::getInstance();

    QString configFile;

    cbr::PPSystemSettings& systemSettings = cbr::PPSystemSettings::getInstance();
    try
    {
        if (opts.isSet("altSitesConfig'")) // use alternate sites config
            configFile = opts.getValue("altSitesConfig");
        else
            configFile = systemSettings.get(cbr::PPSystemSettings::SitesConfigFile).toString();

        sites->read(configFile);
    }
    catch (string msg)
    {
        configFile = systemSettings.getDefault(cbr::PPSystemSettings::SitesConfigFile).toString();
        sites->read(configFile);
    }

    // now clear the settings so only defaults are set
    settings.clear();
    settings.setDefaults();
    settings.setConstants();

    // the usage
    QString sstr("Capthist version ");
//    stringstream ss;
    sstr.append(QString("%1 usage:\n\n").arg(vernum));
//    ss << "Capthist version " << vernum.toStdString() << " usage:" << endl << endl;
    sstr.append("The program is configured by use of program arguments given either on the\n");
//    ss << "The program is configured by use of program arguments given either on the" << endl;
    sstr.append("command line or in a run configuration file. Arguments on the command line\n");
//    ss << "command line or in a run configuration file. Arguments on the command line" << endl;
    sstr.append("have precedence over those in the run configuration file. The run\n");
//    ss << "have precedence over those in the run configuration file. The run" << endl;
    sstr.append("configuration file by default is \"settings.xml\", but can be specified using\n");
//    ss << "configuration file by default is \"settings.xml\", but can be specified using" << endl;
    sstr.append("the \"rcFileName\" flag (see below).\n\n");
//    ss << "the \"rcFileName\" flag (see below)." << endl << endl;
    sstr.append("Program arguments are key words preceeded by two dashes ('-'). Arguments which\n");
//    ss << "Program arguments are key words preceeded by two dashes ('-'). Arguments which" << endl;
    sstr.append("take a value are followed by an equals sign ('=') and the value. For instance:\n\n");
//    ss << "take a value are followed by an equals sign ('=') and the value. For instance:" << endl << endl;
    sstr.append("\tcapthist --rcFileName=example.xml\n\n");
//    ss << "\tcapthist --rcFileName=example.xml" << endl << endl;
    sstr.append("Arguments that are either true or false can be specified without an argument,\n");
//    ss << "Arguments that are either true or false can be specified without an argument," << endl;
    sstr.append("implying \"true\", or with the value stated explicitly:\n\n");
//    ss << "implying \"true\", or with the value stated explicitly:" << endl << endl;
    sstr.append("\tcapthist --warnings --removeJacks=false ...\n\n");
//    ss << "\tcapthist --warnings --removeJacks=false ..." << endl << endl;
    sstr.append("Following is a list of the program arguments and their usage:\n\n");
//    ss << "Following is a list of the program arguments and their usage:" << endl << endl;

    sstr.append(settings.usage());
//    ss << settings.usage().toStdString();

    cout << sstr.toStdString();//ss.str();

    return 0;
}

int PPBatch::newRcFile(PPBatchOutputMaker& out)
{
    PitProSettings& settings = PitProSettings::getInstance();
    settings.clear();
    settings.setDefaults();
    QString fileName = QString(settings.getValue(PitProSettings::RcFileName).data());
    out.write("Generating default run configuration file \"" + fileName + "\".");
    bool overwrite = true;
//    if (access(fileName.c_str(), 0) != -1)
    if (access(fileName.toStdString().c_str(), 0) != -1)
    {
        cerr << "?? File exists. Overwrite? (y/n) ";
        char answer;
        cin >> answer;
        if (answer != 'y')
            overwrite = false;
    }
    if (!overwrite)
        out.write("Canceled.", PPBatchOutputMaker::Error);
    else
    {
        settings.clear();
        settings.setDefaults();
        settings.writeXml(fileName);
    }

    return 0;
}

int PPBatch::batch(PPBatchOutputMaker& out)
{
    PitProSettings& settings = PitProSettings::getInstance();
    int PPoutFormat = PitProSettings::OutputFormat;
    int PPgroupRuns = PitProSettings::GroupRuns;
    int PPoutPrefix = PitProSettings::OutPrefix;

    // detemine number of capthist runs to do
    QString outputFormat = settings.getValue(PPoutFormat);//PitProSettings::OutputFormat);
    bool groupRuns = settings.isChecked(PPgroupRuns) && outputFormat.compare("ROSTER") != 0;//PitProSettings::GroupRuns) && outputFormat.compare("ROSTER") != 0;
    int numGroups = settings.getNumGroups();
    int numRuns = (groupRuns) ? 1 : numGroups;

    CapthistRun chrun(out);

    bool isCanceled = false;
    chrun.setIsCanceledPtr(&isCanceled);
    for (int run = 0; run < numRuns; run++)
    {
        // get group name(s)
        QString outPrefix;
        if (settings.isChecked(PPgroupRuns))//PitProSettings::GroupRuns))
            outPrefix = settings.getValue(PPoutPrefix);//PitProSettings::OutPrefix);


        RunConfigVector runConfigVector;
        if (groupRuns && numGroups > 1)
        {
            settings.getAllRunConfigs(runConfigVector);

            if (outPrefix.isEmpty())
            {
                outPrefix = "composite";
                settings.setValue(PPoutPrefix, outPrefix);//PitProSettings::OutPrefix, outPrefix);
            }
        }
        else
        {
            settings.getRunConfig(runConfigVector, run);

            if (outPrefix.isEmpty())
            {
                outPrefix = runConfigVector[0].name;
                settings.setValue(PPoutPrefix, outPrefix);//PitProSettings::OutPrefix, outPrefix);
            }
            out.write("Processing group \"" + runConfigVector[0].name + "\"...");
        }

        chrun.compute(outPrefix, runConfigVector);
        if (chrun.isCanceled())
        {
            QString message = "Run canceled";
            if (chrun.hasError())
            {
                message += ": " + chrun.getErrorMessage();
            }
            out.write(message, PPOutputMaker::Error);
        }
    }
    out.write("Done");

    return 0;
}

int PPBatch::dsplit(PPBatchOutputMaker& out)
{
    PitProSettings& settings = PitProSettings::getInstance();
    RunConfigVector runConfigVector;
    int numGroups = settings.getNumGroups();
    if (numGroups > 1)
    {
        out.write("Too many groups. Max is 1!", PPBatchOutputMaker::Warning);
        return 0;
    }

    if (numGroups == 0)
    {
      QStringList groups = settings.getValues(PitProSettings::GroupPrefix);
        for (int i = 0; i < groups.count(); i++) //QStringList::iterator it = groups.begin(); it != groups.end(); ++it)
        {
            RunConfigItem item;
            QString prefix = groups[i];
            item.name = prefix;
            item.tag = prefix + "." + settings.getSuffix(PitProSettings::TAG);
            item.obs = prefix + "." + settings.getSuffix(PitProSettings::OBS);
            item.recap = prefix + "." + settings.getSuffix(PitProSettings::RCP);
            item.mort = prefix + "." + settings.getSuffix(PitProSettings::MRT);
            runConfigVector.append(item);
        }
    }
    else
    {
        settings.getRunConfig(runConfigVector, 0);
    }

    out.write("Dsplit \"" + QString(runConfigVector[0].name.data()) + "\"...");
    Dsplit dsplit(out);
    if (dsplit.isTargetSiteValid())
        dsplit.split(runConfigVector);

    return 0;
}

int PPBatch::batch1(PPBatchOutputMaker& out)
{
    PitProSettings& settings = PitProSettings::getInstance();

    RunConfigVector runConfigVector;

    settings.getAllRunConfigs(runConfigVector);
    if (runConfigVector.isEmpty())
    {
        QStringList groups = settings.getValues(PitProSettings::GroupPrefix);
        for (int i = 0; i < groups.count(); i++){ //QStringList::iterator it = groups.begin(); it != groups.end(); ++it) {
            RunConfigItem item;
            QString prefix = groups[i];//*it;
            item.name = prefix;
            item.tag = prefix + "." + settings.getSuffix(PitProSettings::TAG);
            item.obs = prefix + "." + settings.getSuffix(PitProSettings::OBS);
            item.recap = prefix + "." + settings.getSuffix(PitProSettings::RCP);
            item.mort = prefix + "." + settings.getSuffix(PitProSettings::MRT);
            runConfigVector.append(item);
        }
    }

    if (runConfigVector.isEmpty())
        out.write("No runs defined.", PPOutputMaker::Error);
    else
    {
        QString outPrefix;
        if (runConfigVector.size() == 1)
        {
            outPrefix = runConfigVector[0].name;
            settings.setValue(PitProSettings::OutPrefix, outPrefix);
        }
        else
        {
            outPrefix = settings.getValue(PitProSettings::OutPrefix);
        }

        CapthistRun chrun(out);
        bool isCanceled = false;
        chrun.setIsCanceledPtr(&isCanceled);
        chrun.compute(outPrefix, runConfigVector);
        if (chrun.isCanceled())
        {
            QString message = "Run canceled";
            if (chrun.hasError())
            {
                message += ": " + chrun.getErrorMessage();
            }
            out.write(message, PPOutputMaker::Error);
        }
    }

    return 0;
}
