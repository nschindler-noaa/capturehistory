#ifndef Tokenizer_H
#define Tokenizer_H


#include <string>
#include <vector>
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
	Tokenizer(const std::string& theString, const std::string& commentIndicator = "#", const std::string& keepDelimiters = "",
		const std::string& dropDelimiters = " \n\t", int lineNumber = 0, int startingColumn = 0);
	~Tokenizer() {}
	size_t numTokens() const {return tokens_.size();}
	const Token& token(size_t i) const { return tokens_[i]; }
	Token& token(size_t i) { return tokens_[i]; }
	const TokenizerIterator begin() const {return TokenizerIterator(this,0);}
	const TokenizerIterator end() const {return TokenizerIterator(this,tokens_.size()); }
	TokenizerIterator begin() { return TokenizerIterator(this,0); }
	TokenizerIterator end() { return TokenizerIterator(this, tokens_.size()); }
	bool operator==(const Tokenizer& rhs) const;
private:
	std::string theString_;
	std::string commentIndicator_;
	std::string keepDelimiters_;
	std::string dropDelimiters_;
	std::vector<Token> tokens_;
};
#endif
