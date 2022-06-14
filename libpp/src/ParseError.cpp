#include "ParseError.h"
#include "LogicError.h"
#include "Token.h"
#include </boost/lexical_cast.hpp>
using namespace std;

ParseError::ParseError(const string& message, const string& fileName)
{
    setupMessage(message, fileName);
}

ParseError::ParseError(const string& message, const Token& token,
    const string& fileName)
{
    setupMessage(message, fileName);
    message_ += ", token \"" + token.name + "\", line " +
        boost::lexical_cast<string,unsigned int>(token.line) +
        ", column " + boost::lexical_cast<string,unsigned int>(token.column);
}

void ParseError::setFileName(const string& fileName)
{
    if (fileNameSet_)
        throw LogicError("ParseError::setFileName - tried to set fileName twice");
    else
    {
        fileNameSet_ = true;
        message_ = "File \"" + fileName + "\", " + message_;
    }
}

void ParseError::setupMessage(const string& message, const string& fileName)
{
    fileNameSet_ = fileName != string();
    if (fileNameSet_)
        message_ = "File \"" + fileName + "\", ";
    message_ += message;
}
