#include "ParseError.h"
#include "LogicError.h"
#include "Token.h"
//#include <boost/lexical_cast.hpp>
//using namespace std;

ParseError::ParseError(const QString& message, const QString& fileName)
{
    setupMessage(message, fileName);
}

ParseError::ParseError(const QString& message, const Token& token,
    const QString &fileName)
{
    setupMessage(message, fileName);
    message_ += ", token \"" + token.name +
        "\", line " + QString::number(token.line) +
        ", column " + QString::number(token.column);
}

void ParseError::setFileName(const QString& fileName)
{
    if (fileNameSet_)
        throw LogicError("ParseError::setFileName - tried to set fileName twice");
    else
    {
        fileNameSet_ = true;
        message_ = "File \"" + fileName + "\", " + message_;
    }
}

void ParseError::setupMessage(const QString& message, const QString& fileName)
{
    fileNameSet_ = !fileName.isEmpty();// != QString();
    if (fileNameSet_)
        message_ = "File \"" + fileName + "\", ";
    message_ += message;
}
