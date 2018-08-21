#ifndef Parser_H
#define Parser_H

#include <iostream>
#include <string>
#include <memory>
#include "Token.h"
#include "Tokenizer.h"
#include "TokenizerIterator.h"

/** Parse an input file.
The Parser class provides the functionality for parsing a generic input text
file token by token.  The <b>Parser</b> can be customized with the
<i>dropDelimiters</i> and <i>keepDelimiters</i> described below.
*/

class Parser
{
public:
	/** Parser constructor.
	\param is The input stream
	\param dropDelimiters Characters that separate tokens and are discarded,
	and not returned as a token or as part of a token.
	It defaults to white space.
	\param keepDelimiters Charaters that separate tokens, but are returned as
	tokens of length 1 as they are encountered.  The default is no
	keepDelimiters.
	\param commentCharacter A single character indicating that the rest of
	the line is ignored and discarded.
	*/
	Parser(std::istream& is, const std::string& keepDelimiters = "",
		const std::string& dropDelimiters = " \n\t");
	~Parser() {}
	/** Return the next token in the input stream.  Returns the null string
	if at the end of line. */
	Token nextToken();

	/*! Look at next token in input stream without
	affecting the position in the input stream
	*/
	Token peekAtNextToken() const;
	/** Ensure at beginning of a line.  If not, advance to the beginning of the next line. */
	void newLine();
	const std::string& keepDelimiters() const {return keepDelimiters_;}
	const std::string& dropDelimiters() const {return dropDelimiters_;}
private:
	void setupNextToken();

	std::istream& is_;
	std::string commentString_;
	std::string keepDelimiters_;
	std::string dropDelimiters_;
	int tokenIndex_;
	int lineNumber_;
	std::string line_;
	std::string workingLine_;
    std::auto_ptr<Tokenizer> tokenizer_;
	Token nextToken_;
	Token token_;
};
#endif
