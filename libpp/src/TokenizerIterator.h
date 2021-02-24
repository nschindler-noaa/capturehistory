#ifndef TokenizerIterator_H
#define TokenizerIterator_H

#include <QString>
#include "Token.h"

class Tokenizer;
/** Iterator for the Tokenizer class. */
class TokenizerIterator
{
public:
    TokenizerIterator(const Tokenizer* tokenizer, int index = 0);
    TokenizerIterator(Tokenizer* tokenizer, int index = 0);
    ~TokenizerIterator() {}
    const Token& operator*() const;
    Token& operator*();
    TokenizerIterator& operator++();
    bool operator==(const TokenizerIterator& rhs) const;
    bool operator!=(const TokenizerIterator& rhs) const;
private:
    const Tokenizer* const_tokenizer_;
    Tokenizer* tokenizer_;
    int currentIndex_;
};
#endif
