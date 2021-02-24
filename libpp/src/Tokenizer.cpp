#include "Tokenizer.h"
using namespace std;

Tokenizer::Tokenizer(const QString theString, const QString commentIndicator, const QString keepDelimiters,
        const QString dropDelimiters, int lineNumber, int startingColumn) : theString_(theString),
commentIndicator_(commentIndicator),
keepDelimiters_(keepDelimiters), dropDelimiters_(dropDelimiters)
{
    int currentPosition = startingColumn;
    QString currentToken;
//    bool parsingToken = false; // Indicates if in the middle of parsing a token
    int commentPos = theString_.indexOf(commentIndicator_);
    if (commentPos < 0)
        commentPos = theString_.count();
    if (commentPos < theString_.count())// != static_cast<int>(string::npos))
        theString_.truncate(commentPos);//theString_ = theString_.substr(0, commentPos);

    currentPosition = 0;
    for (int i = 0; i < commentPos; i++)
    {
        QChar ch_(theString_.at(i));
        if (keepDelimiters_.contains(ch_))
        {
            if (!currentToken.isEmpty()) {
                tokens_.append(Token(currentToken, lineNumber, currentPosition));
                currentToken.clear();
            }
            tokens_.append(Token(QString(ch_), lineNumber, i));
            currentPosition = i + 1;
        }
        else if (dropDelimiters_.contains(ch_))
        {
            if (!currentToken.isEmpty()) {
                tokens_.append(Token(currentToken, lineNumber, currentPosition));
                currentToken.clear();
            }
            currentPosition = i + 1;
        }
        else
        {
            currentToken.append(ch_);
        }
    }
    if (!currentToken.isEmpty())
    {
        tokens_.append(Token(currentToken, lineNumber, currentPosition));
    }
/*
    for (int i = 0; i < theString_.size(); ++i) {
        if (keepDelimiters_.indexOf(theString_[i]) != theString_.count()) {//string::npos) {
            if (parsingToken) {
                tokens_.push_back(Token(currentToken, lineNumber, currentPosition + 1));
                parsingToken = false;
            }
            tokens_.push_back(Token(QString(theString_, i, 1), lineNumber, i + startingColumn + 1));
            currentToken = QString();
        } else if (dropDelimiters_.indexOf(QString(theString_, i, 1)) != string::npos) {
            if (!parsingToken)
                continue;
            else {
                tokens_.push_back(Token(currentToken, lineNumber, currentPosition + 1));
                currentToken = QString();
                currentPosition = i + startingColumn;
                parsingToken = false;
            }
        } else {
            currentToken += QString(theString_, i, 1);
            if (!parsingToken) {
                currentPosition = i + startingColumn;
                parsingToken = true;
            }
        }
    }
    if (parsingToken)
        tokens_.push_back(Token(currentToken, lineNumber, currentPosition + 1));*/
}

bool Tokenizer::operator==(const Tokenizer& rhs) const {
    bool returnValue = (keepDelimiters_ == rhs.keepDelimiters_) && (dropDelimiters_ == rhs.dropDelimiters_) &&
            (tokens_.size() == rhs.tokens_.size());
    if (!returnValue)
        return returnValue;
    else {
        for (int i = 0; i < tokens_.size(); ++i)
            if (tokens_[i].name != rhs.tokens_[i].name) {
                returnValue = false;
                break;
            }
    }
    return returnValue;
}
