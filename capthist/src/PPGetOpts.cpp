/*
 */

#include <cstdio>
#include <iostream>
#include <sstream>
#include <cstring>
#include <QStringList>

#include "PPGetOpts.h"
#include "PitProSettings.h"
#include "PPOutputMaker.h"


using std::string;
//using std::cout;
//using std::endl;


using namespace cbr;

void PPGetOpts::get(int argC, char *argV[], PPOutputMaker& out)
{
    PitProSettings& settings = PitProSettings::getInstance();
    QStringList pair;
    QString argument, keyName, value;
//    char* value;
//    char* keyName;

    int argInd;
    for (argInd = 1; argInd < argC; argInd++)
    {
        argument = QString(argV[argInd]);
        pair = argument.split('=', QString::KeepEmptyParts);
        if (pair.count() > 2)
            break;
        // Break out on first parm not starting with a dash
        if (!pair.at(0).startsWith('-'))//argV[argInd][0] != '-')
            break;

        while (pair.at(0).startsWith('-'))
            pair[0].remove(0,1);

        keyName = pair.at(0);
        if (pair.count() == 2) {
            value = pair.at(1);
        }
        else {
            value = QString("1");
        }

/*        if (!strncmp(argV[argInd], "--", 2))
        {
            keyName = argV[argInd] + 2;
        }
        else
        {
            keyName = argV[argInd] + 1;
        }

        value = strchr(argV[argInd], '=');
        if (value)
        {
            char *c = value;
            ++value; // skip the =
            *c = 0;
        }*/

        int keyNum = settings.getKeyNum(keyName);
        if (keyNum == -1)
        {
            QString sstr (QString("Unable to find command line parameter: %1\n").arg(keyName));
//            stringstream ss;
//            ss << "Unable to find command line parameter: " << keyName << ends;
            out.write(sstr, PPOutputMaker::Warning);//QString(ss.str().data()), PPOutputMaker::Warning);
        }
        else
        {
            addKeyName(keyName, keyNum);

            if (value.isEmpty())
                addParamDef(keyName, "1");
            else if (value.compare("true") == 0)
                addParamDef(keyName, "1");
            else if (value.compare("false") == 0)
                addParamDef(keyName, "0");
            else
                addParamDef(keyName, value);

            if (keyName.compare("relDate") == 0)
            {
                addParamDef(PitProSettings::AltRelDate, "1");
            }
            else if (keyName.compare("juvenileCutoffDate") == 0)//!strcmp(keyName, "juvenileCutoffDate"))
            {
                addParamDef(PitProSettings::JuvenileCutoffSwitch, "1");
            }
            else if (keyName.compare("migrationYear") == 0)//!strcmp(keyName, "migrationYear"))
            {
                addParamDef(PitProSettings::MigrationYearSwitch, "1");
            }
            else if (keyName.compare("resCutoffDate") == 0)//!strcmp(keyName, "resCutoffDate"))
            {
                addParamDef(PitProSettings::ResCutoffSwitch, "1");
            }
        }
    }

    //
    //  There should be only one and only one parameter left, and that
    //  should be the file name.
    //
    if (argInd != argC - 1)
    {
        usage();
    }
}

QString PPGetOpts::usage()
{
    QString s;


    return use;
}
