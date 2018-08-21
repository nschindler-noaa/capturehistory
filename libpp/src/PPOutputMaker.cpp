/*
 *
 */

#include "PPOutputMaker.h"

using std::string;
using std::endl;
using std::stringstream;

string PPOutputMaker::ppFormat(const string& msg, OutputType type) {
    stringstream ss;
    switch (type) {
        case Error:
            ss << "!! ";
            break;
        case Warning:
            ss << "?? ";
            break;
        case Message:
            ss << "** ";
            break;
        case Emphasis:
            ss << "***** ";
            break;
        case None :
            // do nothing
            break;
    }

    ss << msg;

    switch (type) {
        case Emphasis:
            ss << " *****";
            break;
        case None : case Warning : case Message : case Error :
            // do nothing
            break;
    }

    ss << endl;
    return ss.str();
}