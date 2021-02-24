/*
 *
 */

#ifndef PPOutputMaker_h
#define PPOutputMaker_h

#include <QString>
#include <string>
#include <sstream>

class PPOutputMaker {
public:

    enum OutputType {
        None, Message, Error, Warning, Emphasis
    };

    PPOutputMaker();

    virtual ~PPOutputMaker();

    virtual void setNumSteps(int num);

    virtual void setCurrentStep(int num);

    virtual void setProgressMessage(const QString& msg);

    virtual void setBytesExpected(int num);

    virtual void setCurrentBytes(int num);

    virtual void write(const QString& msg, OutputType type = Message);
//    void write(const std::string& msg, OutputType type = Message);

    int getNumSteps() const;

    int getCurrentStep() const;

protected:
    std::string& ppFormat(const QString& msg, OutputType type);
    std::string out;

    int numSteps;
    int currentStep;
    int bytesExpected;
    int bytesRead;
    QString progressMsg;

};

#endif
