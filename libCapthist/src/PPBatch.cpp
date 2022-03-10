/*
 * PPBatchMain.cpp
 *
 * The main routine for the bar plot.
 */

#include <iostream>
#include <string>
#include <sstream>

#include <QFile>
#include <QString>

#include <portability.h>
#include <ArrayDefs.h>
#include <Sites.h>
#include <DateConverter.h>
#include <Dsplit.h>

#include <PPVersion.h>
#include <PPRunConfig.h>
#include <PPSystemSettings.h>
#include <PitProSettings.h>
#include <CapthistRun.h>
#include <RunConfigVector.h>
#include <Settings.h>
#include <StringUtil.h>

#include "PPBatch.h"
#include "PPBatchOutputMaker.h"
#include "PPGetOpts.h"

using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::stringstream;
using std::ends;

using namespace cbr;

int PPBatch::run(PPGetOpts& opts, PPBatchOutputMaker& out) 
{
    int retval = 0;

    // handle non-run modes: version, usage, new rc file
    if (opts.isChecked(PitProSettings::Version))
    {
        cout << "Capthist: Version " + PPVersion::versionString() << endl;
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

    out.write("Capthist ver. " + PPVersion::versionString(), PPBatchOutputMaker::Emphasis);

    PitProSettings& settings = PitProSettings::getInstance();
    settings.clear();
    string rcFileName = opts.getValue("rcFileName");
    if (!rcFileName.empty() && !settings.readFromXml(rcFileName))
    {
        stringstream ss;
        ss << "Unable to read run configuration file: " << rcFileName << ends;
        out.write(ss.str(), PPBatchOutputMaker::Warning);
    }
    settings.merge(opts, true);
    settings.setDefaults(); // fill in any missing parameters with defaults

    if (settings.getNumGroups() == 0)
        out.write("No data groups found.", PPBatchOutputMaker::Error);
    else
    {
        // read the sites configuration
        PPSystemSettings &systemSettings = PPSystemSettings::getInstance();
        systemSettings.resolveSitesConfig();
        QString configFile;
        if (settings.isSet(PitProSettings::AltSitesConfig)) // use alternate sites config
            configFile = QString(settings.getValue(PitProSettings::AltSitesConfig).c_str());
        else
            configFile = QString(systemSettings.get(PPSystemSettings::SitesConfigFile).toString());

        QFile file(configFile);
        if (!file.exists())
            out.write("Can't find sites configuration file \"" + configFile.toStdString() + "\"", PPOutputMaker::Error);
        else
        {
            Sites* sites = Sites::getInstance();

            out.write("Reading sites configuration file \"" + configFile.toStdString() + "\"...");
            sites->read(configFile.toStdString());

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
                out.write(msg, PPBatchOutputMaker::Error);
            } 
            catch (...) 
            {
                out.write("Internal error", PPBatchOutputMaker::Error);
            }
            delete sites;
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
    settings.merge(opts, true);
    string rcFileName = opts.getValue("rcFileName");
    settings.readFromXml(rcFileName);
    settings.setDefaults();
    Sites* sites = Sites::getInstance();
    string verNum = settings.getValue("version");

    QString configFile;

    PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
    try
    {
        if (opts.isSet("altSitesConfig'")) // use alternate sites config
            configFile = QString(opts.getValue("altSitesConfig").c_str());
        else
            configFile = systemSettings.get(PPSystemSettings::SitesConfigFile).toString();

        sites->read(configFile.toStdString());
    } 
    catch (string msg) 
    {
        configFile = systemSettings.getDefault(PPSystemSettings::SitesConfigFile).toString();
        sites->read(configFile.toStdString());
    }

    // now clear the settings so only defaults are set
    settings.clear();
    settings.setDefaults();
    settings.setConstants();

    // the usage
    stringstream ss;
    ss << "Capthist version " << verNum << " usage:" << endl << endl;

    ss << "The program is configured by use of program arguments given either on the" << endl;
    ss << "command line or in a run configuration file. Arguments on the command line" << endl;
    ss << "have precedence over those in the run configuration file. The run" << endl;
    ss << "configuration file by default is \"settings.xml\", but can be specified using" << endl;
    ss << "the \"rcFileName\" flag (see below)." << endl << endl;

    ss << "Program arguments are key words preceeded by two dashes ('-'). Arguments which" << endl;
    ss << "take a value are followed by an equals sign ('=') and the value. For instance:" << endl << endl;

    ss << "\tcapthist --rcFileName=example.xml" << endl << endl;

    ss << "Arguments that are either true or false can be specified without an argument," << endl;
    ss << "implying \"true\", or with the value stated explicitly:" << endl << endl;

    ss << "\tcapthist --warnings --removeJacks=false ..." << endl << endl;

    ss << "Following is a list of the program arguments and their usage:" << endl << endl;
    
    ss << settings.usage();
    
    cout << ss.str();

    return 0;
}

int PPBatch::newRcFile(PPBatchOutputMaker& out)
{
    PitProSettings& settings = PitProSettings::getInstance();
    settings.clear();
    settings.setDefaults();
    string fileName = settings.getValue(PitProSettings::RcFileName);
    out.write("Generating default run configuration file \"" + fileName + "\".");
    bool overwrite = true;
    if (access(fileName.c_str(), 0) != -1)
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

    // detemine number of capthist runs to do
    string outputFormat = settings.getValue(PitProSettings::OutputFormat);
    bool groupRuns = settings.isChecked(PitProSettings::GroupRuns) && outputFormat.compare("ROSTER") != 0;
    size_t numGroups = settings.getNumGroups();
    size_t numRuns = (groupRuns) ? 1 : numGroups;

    CapthistRun chrun(out);

    bool isCanceled = false;
    chrun.setIsCanceledPtr(&isCanceled);
    for (size_t run = 0; run < numRuns; run++) 
    {
        // get group name(s)
        string outPrefix;
        if (settings.isChecked(PitProSettings::GroupRuns))
            outPrefix = settings.getValue(PitProSettings::OutPrefix);


        RunConfigVector runConfigVector;
        if (groupRuns && numGroups > 1) 
        {
            settings.getAllRunConfigs(runConfigVector);

            if (outPrefix.empty()) 
            {
                outPrefix = "composite";
                settings.setValue(PitProSettings::OutPrefix, outPrefix);
            }
        }
        else 
        {
            settings.getRunConfig(runConfigVector, run);

            if (outPrefix.empty())
            {
                outPrefix = runConfigVector[0].name;
                settings.setValue(PitProSettings::OutPrefix, outPrefix);
            }
            out.write("Processing group \"" + runConfigVector[0].name + "\"...");
        }

        chrun.compute(outPrefix, runConfigVector);
        if (chrun.isCanceled())
        {
            string message = "Run canceled";
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
    size_t numGroups = settings.getNumGroups();
    if (numGroups > 1)
    {
        out.write("Too many groups. Max is 1!", PPBatchOutputMaker::Warning);
        return 0;
    }

    if (numGroups == 0) 
    {
        StringVector groups = settings.getValues(PitProSettings::GroupPrefix);
        for (StringVector::iterator it = groups.begin(); it != groups.end(); ++it) 
        {
            RunConfigItem item;
            string prefix = *it;
            item.name = prefix;
            item.tag = prefix + "." + settings.getSuffix(PitProSettings::TAG);
            item.obs = prefix + "." + settings.getSuffix(PitProSettings::OBS);
            item.recap = prefix + "." + settings.getSuffix(PitProSettings::RCP);
            item.mort = prefix + "." + settings.getSuffix(PitProSettings::MRT);
            runConfigVector.push_back(item);
        }
    }
    else 
    {
        settings.getRunConfig(runConfigVector, 0);
    }

    out.write("Dsplit \"" + runConfigVector[0].name + "\"...");
    Dsplit dsplit_(out);
    if (dsplit_.isTargetSiteValid())
        dsplit_.split(runConfigVector);

    return 0;
}

int PPBatch::batch1(PPBatchOutputMaker& out) 
{
    PitProSettings& settings = PitProSettings::getInstance();

    RunConfigVector runConfigVector;

    settings.getAllRunConfigs(runConfigVector);
    if (runConfigVector.size() == 0) 
    {
        StringVector groups = settings.getValues(PitProSettings::GroupPrefix);
        for (StringVector::iterator it = groups.begin(); it != groups.end(); ++it) {
            RunConfigItem item;
            string prefix = *it;
            item.name = prefix;
            item.tag = prefix + "." + settings.getSuffix(PitProSettings::TAG);
            item.obs = prefix + "." + settings.getSuffix(PitProSettings::OBS);
            item.recap = prefix + "." + settings.getSuffix(PitProSettings::RCP);
            item.mort = prefix + "." + settings.getSuffix(PitProSettings::MRT);
            runConfigVector.push_back(item);
        }
    }

    if (runConfigVector.size() == 0)
        out.write("No runs defined.", PPOutputMaker::Error);
    else
    {
        string outPrefix;
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
            string message = "Run canceled";
            if (chrun.hasError()) 
            {
                message += ": " + chrun.getErrorMessage();
            }
            out.write(message, PPOutputMaker::Error);
        }
    }

    return 0;
}
