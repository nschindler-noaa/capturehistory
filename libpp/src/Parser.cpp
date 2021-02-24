#include "Parser.h"
using namespace std;

Parser::Parser(istream& is, const QString& keepDelimiters, const QString& dropDelimiters) :
is_(is), commentString_("#"), keepDelimiters_(keepDelimiters), dropDelimiters_(dropDelimiters), tokenIndex_(-1), lineNumber_(0)

{
    tokenizer_ = new Tokenizer(line_);
    setupNextToken();
}

Token Parser::nextToken() {
    token_ = nextToken_;
    setupNextToken();
    return token_;
}

Token Parser::peekAtNextToken() const {
    return nextToken_;
}

void Parser::setupNextToken() {
    int numTokens = static_cast<int>(tokenizer_->numTokens());
    if (++tokenIndex_ >= numTokens) {
        tokenIndex_ = 0;
        do {
            std::string ln_;
            getline(is_, ln_);
            line_ = QString(ln_.data());
            ++lineNumber_;
            delete tokenizer_;
            tokenizer_ = new Tokenizer(line_, commentString_, keepDelimiters_, dropDelimiters_, lineNumber_);
        } while (tokenizer_->numTokens() == 0 && !is_.eof());
    }
    if (!is_.eof())
        nextToken_ = tokenizer_->token(tokenIndex_);
    else
        nextToken_.endOfFile = true;
    if (token_.line != nextToken_.line) {
        token_.lastInLine = true;
        nextToken_.firstInLine = true;
    }
}

void Parser::newLine() {
    if (!token_.firstInLine) {
        tokenIndex_ = tokenizer_->numTokens();
        setupNextToken();
    }
}
