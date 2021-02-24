/*
 *
 */

#include "PPOutputMaker.h"
#include <PitProSettings.h>

using std::string;
using std::endl;
using std::stringstream;

PPOutputMaker::PPOutputMaker() {
     numSteps = (0);
     currentStep = (0);
     progressMsg = QString("");
}

PPOutputMaker::~PPOutputMaker() {
}

void PPOutputMaker::setNumSteps(int num) {
    numSteps = num;
}

void PPOutputMaker::setCurrentStep(int num) {
    currentStep = num;
}

void PPOutputMaker::setProgressMessage(const QString& msg) {
    progressMsg = msg;
}

void PPOutputMaker::setBytesExpected(int num) {
    bytesExpected = num;
    bytesRead = 0;
}

void PPOutputMaker::setCurrentBytes(int num) {
    bytesRead += num;
}

int PPOutputMaker::getNumSteps() const {
    return numSteps;
}

int PPOutputMaker::getCurrentStep() const {
    return currentStep;
}

//void PPOutputMaker::write(const std::string &msg, OutputType type) {
//    QString messg(msg.data());
//    write(messg, type);
//}

void PPOutputMaker::write(const QString &msg, OutputType type) {
    PitProSettings& settings = PitProSettings::getInstance();
    switch (type) { //   None, Message, Error, Warning, Emphasis
    case Warning:
        if (settings.isChecked(PitProSettings::Warnings)) {
            std::cerr << ppFormat(msg,type);
        }
        break;
    case Error:
        std::cerr << ppFormat(msg,type);
        break;
    default:
        std::cout << ppFormat(msg, type);
    }
    if (type != PPOutputMaker::Warning || settings.isChecked(PitProSettings::Warnings))
        std::cerr << ppFormat(msg, type);
}

string& PPOutputMaker::ppFormat(const QString& msg, OutputType type) {
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

    ss << msg.toUtf8().data();

    switch (type) {
        case Emphasis:
            ss << " *****";
            break;
        case None : case Warning : case Message : case Error :
            // do nothing
            break;
    }

    ss << endl;
    out = ss.str();
    return out;
}
