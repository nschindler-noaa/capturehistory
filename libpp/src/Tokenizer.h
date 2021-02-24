#ifndef Tokenizer_H
#define Tokenizer_H


#include <QStringList>
#include <string>
#include <vector>
#include "Token.h"
#include "TokenizerIterator.h"

/** Break a string into tokens based on the delimiters.
\param keepDelimiters Characters that delimit tokens and are returned
as tokens themselves (defaults to null)
\param dropDelimiters Characters that delimit tokens and are discarded (defaults to
white space characters)
\param startingColumn Starting column count, defaults to 1, nonzero if the tokenizer is set to a
subset of a line.  The boost::tokenizer was not used because
it doesn't provide the column information.
*/
class Tokenizer
{
public:
    Tokenizer(const QString theString, const QString commentIndicator = "#", const QString keepDelimiters = "",
        const QString dropDelimiters = " \n\t", int lineNumber = 0, int startingColumn = 0);
    ~Tokenizer() {}
    int numTokens() const {return tokens_.size();}
    const Token& token(int i) const { return tokens_[i]; }
    Token& token(int i) { return tokens_[i]; }
    const TokenizerIterator begin() const {return TokenizerIterator(this,0);}
    const TokenizerIterator end() const {return TokenizerIterator(this, tokens_.size()); }
    TokenizerIterator begin() { return TokenizerIterator(this, 0); }
    TokenizerIterator end() { return TokenizerIterator(this, tokens_.size()); }
    bool operator==(const Tokenizer& rhs) const;
private:
    QString theString_;
    QString commentIndicator_;
    QString keepDelimiters_;
    QString dropDelimiters_;
    QList<Token> tokens_;
};
#endif
