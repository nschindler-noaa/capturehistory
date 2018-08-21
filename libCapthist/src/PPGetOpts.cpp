/*
 */

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstring>

#include "PPGetOpts.h"
#include "PitProSettings.h"
#include "PPOutputMaker.h"


using std::string;
using std::cout;
using std::endl;
using std::ends;
using std::stringstream;

void PPGetOpts::get(int argC, char *argV[], PPOutputMaker& out)
{
    PitProSettings& settings = PitProSettings::getInstance();

    int argInd;
    for (argInd = 1; argInd < argC; argInd++) 
    {
        // Break out on first parm not starting with a dash
        if (argV[argInd][0] != '-')
            break;

        char* keyName;
        if (!strncmp(argV[argInd], "--", 2)) 
        {
            keyName = argV[argInd] + 2;
        }
        else
        {
            keyName = argV[argInd] + 1;
        }

        char* value = strchr(argV[argInd], '=');
        if (value)
        {
            char *c = value;
            ++value; // skip the =
            *c = 0;
        }

        int keyNum = settings.getKeyNum(keyName);
        if (keyNum == -1)
        {
            stringstream ss;
            ss << "Unable to find command line parameter: " << keyName << ends;
            out.write(ss.str(), PPOutputMaker::Warning);
        } 
        else 
        {
            addKeyName(keyName, keyNum);

            if (!value)
                addParamDef(keyName, "1");
            else if (!strcmp(value, "true"))
                addParamDef(keyName, "1");
            else if (!strcmp(value, "false"))
                addParamDef(keyName, "0");
            else
                addParamDef(keyName, value);

            if (!strcmp(keyName, "relDate")) 
            {
                addParamDef(PitProSettings::AltRelDate, "1");
            }
            else if (!strcmp(keyName, "juvenileCutoffDate"))
            {
                addParamDef(PitProSettings::JuvenileCutoffSwitch, "1");
            }
            else if (!strcmp(keyName, "migrationYear"))
            {
                addParamDef(PitProSettings::MigrationYearSwitch, "1");
            }
            else if (!strcmp(keyName, "resCutoffDate"))
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

string PPGetOpts::usage() 
{
    string s;


    return s;
}