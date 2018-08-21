#ifndef LogicError_H
#define LogicError_H

// A class for programming logic exceptions

#include <string>
#include <iostream>
#include "ErrorObject.h"

class LogicError : public ErrorObject
{
public:
	LogicError(const std::string& message) : message_("*** Logic Error --- " + message) {}
	~LogicError() {}
	const std::string& message() const {return message_;}
private:
	const std::string message_;
};

#endif
