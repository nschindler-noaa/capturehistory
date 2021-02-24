/*
*
*/

#ifndef PPGetOpts_h
#define PPGetOpts_h

#include <string>
#include <QString>
#include <Settings.h>
#include "PPOutputMaker.h"

//class PPOutputMaker;

class PPGetOpts : public Settings
{
public:
    void get(int argc, char *argv[], PPOutputMaker& out);
    QString usage();

private:
    QString use;
};

#endif //PPGetOpts_h
