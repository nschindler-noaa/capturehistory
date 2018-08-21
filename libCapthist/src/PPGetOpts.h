/*
*
*/

#ifndef PPGetOpts_h
#define PPGetOpts_h

#include <string>
#include <Settings.h>
#include "PPOutputMaker.h"

//class PPOutputMaker;

class PPGetOpts : public Settings
{
public:
	void get(int argc, char *argv[], PPOutputMaker& out);
	std::string usage();
};

#endif //PPGetOpts_h
