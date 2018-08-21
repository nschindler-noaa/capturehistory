#include "Tokenizer.h"
using namespace std;

Tokenizer::Tokenizer(const string& theString, const string& commentIndicator, const string& keepDelimiters,
        const string& dropDelimiters, int lineNumber, int startingColumn) : theString_(theString),
commentIndicator_(commentIndicator),
keepDelimiters_(keepDelimiters), dropDelimiters_(dropDelimiters) 
{
    int currentPosition = startingColumn;
    string currentToken;
    bool parsingToken = false; // Indicates if in the middle of parsing a token
    int commentPos = theString_.find(commentIndicator_);
    if (commentPos != static_cast<int>(string::npos))
        theString_ = theString_.substr(0, commentPos);


    for (unsigned int i = 0; i < theString_.size(); ++i) {
        if (keepDelimiters_.find_first_of(theString_[i]) != string::npos) {
            if (parsingToken) {
                tokens_.push_back(Token(currentToken, lineNumber, currentPosition + 1));
                parsingToken = false;
            }
            tokens_.push_back(Token(string(theString_, i, 1), lineNumber, i + startingColumn + 1));
            currentToken = string();
        } else if (dropDelimiters_.find_first_of(string(theString_, i, 1)) != string::npos) {
            if (!parsingToken)
                continue;
            else {
                tokens_.push_back(Token(currentToken, lineNumber, currentPosition + 1));
                currentToken = string();
                currentPosition = i + startingColumn;
                parsingToken = false;
            }
        } else {
            currentToken += string(theString_, i, 1);
            if (!parsingToken) {
                currentPosition = i + startingColumn;
                parsingToken = true;
            }
        }
    }
    if (parsingToken)
        tokens_.push_back(Token(currentToken, lineNumber, currentPosition + 1));
}

bool Tokenizer::operator==(const Tokenizer& rhs) const {
    bool returnValue = (keepDelimiters_ == rhs.keepDelimiters_) && (dropDelimiters_ == rhs.dropDelimiters_) &&
            (tokens_.size() == rhs.tokens_.size());
    if (!returnValue)
        return returnValue;
    else {
        for (unsigned int i = 0; i < tokens_.size(); ++i)
            if (tokens_[i].name != rhs.tokens_[i].name) {
                returnValue = false;
                break;
            }
    }
    return returnValue;
}
