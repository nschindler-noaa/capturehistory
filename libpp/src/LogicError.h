#ifndef LogicError_H
#define LogicError_H

// A class for programming logic exceptions

#include <string>
#include <iostream>
#include "ErrorObject.h"

class LogicError : public ErrorObject
{
public:
    LogicError(const QString message) : message_("*** Logic Error --- " + message) {}
    ~LogicError() {}
    const QString& message() const {return message_;}
private:
    QString message_;
};

#endif
