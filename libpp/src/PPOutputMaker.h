/*
 *
 */

#ifndef PPOutputMaker_h
#define PPOutputMaker_h

#include <string>
#include <sstream>

class PPOutputMaker {
public:

    enum OutputType {
        None, Message, Error, Warning, Emphasis
    };

    PPOutputMaker() : numSteps(0), currentStep(0) {
    }

    virtual ~PPOutputMaker() {
    }

    virtual void setNumSteps(int num) {
        numSteps = num;
    }

    virtual void setCurrentStep(int num) {
        currentStep = num;
    }

    virtual void setProgressMessage(const std::string& msg) {
        progressMsg = msg;
    }

    virtual void setBytesExpected(int num) {
        bytesExpected = num;
        bytesRead = 0;
    }

    virtual void setCurrentBytes(int num) {
        bytesRead += num;
    }

    virtual void write(const std::string& msg, OutputType type = Message) = 0;

    int getNumSteps() const {
        return numSteps;
    }

    int getCurrentStep() const {
        return currentStep;
    }

protected:
    std::string ppFormat(const std::string& msg, OutputType type);

    int numSteps;
    int currentStep;
    int bytesExpected;
    int bytesRead;
    std::string progressMsg;

};

#endif
