#ifndef ParseError_H
#define ParseError_H

#include <string>
#include "ErrorObject.h"

struct Token;
/** Parsing error to be thrown at an exception. */
class ParseError : public ErrorObject
{
public:
	ParseError(const std::string& message,
		const std::string& fileName = std::string());
	ParseError(const std::string& message, const Token& token,
		const std::string& fileName = std::string());
	~ParseError() {}
	void setFileName(const std::string& fileName);
	const std::string& message() const {return message_;}
private:
	void setupMessage(const std::string& message, const std::string& fileName);
	std::string message_;
	bool fileNameSet_;
};

#endif
