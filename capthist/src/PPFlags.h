/*
 *
 */

#ifndef _PPFLAGS_H_
#define _PPFLAGS_H_

#include <string>

class PPOutputMaker;

class PPFlags {
public:
    void readArgs(int argc, char *argv[], PPOutputMaker& out);
    std::string usage();

};

#endif //_PPFLAGS_H_
