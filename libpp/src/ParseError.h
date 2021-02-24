#ifndef ParseError_H
#define ParseError_H

#include <string>
#include "ErrorObject.h"

#include <QString>

struct Token;
/** Parsing error to be thrown at an exception. */
class ParseError : public ErrorObject
{
public:
    ParseError(const QString &message,
        const QString &fileName = QString(""));
    ParseError(const QString& message, const Token& token,
        const QString& fileName = QString());
    ~ParseError() {}
    void setFileName(const QString& fileName);
    const QString& message() const {return message_;}
private:
    void setupMessage(const QString& message, const QString& fileName);
    QString message_;
    bool fileNameSet_;
};

#endif
