#ifndef TokenizerIterator_H
#define TokenizerIterator_H

#include <string>
#include "Token.h"

class Tokenizer;
/** Iterator for the Tokenizer class. */
class TokenizerIterator
{
public:
	TokenizerIterator(const Tokenizer* tokenizer, size_t index = 0);
	TokenizerIterator(Tokenizer* tokenizer, size_t index = 0);
	~TokenizerIterator() {}
	const Token& operator*() const;
	Token& operator*();
	TokenizerIterator& operator++();
	bool operator==(const TokenizerIterator& rhs) const;
	bool operator!=(const TokenizerIterator& rhs) const;
private:
	const Tokenizer* const_tokenizer_;
	Tokenizer* tokenizer_;
	size_t currentIndex_;
};
#endif
