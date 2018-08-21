#include "TokenizerIterator.h"
#include "Tokenizer.h"
using namespace std;

TokenizerIterator::TokenizerIterator(const Tokenizer* tokenizer, size_t index) :
const_tokenizer_(tokenizer), tokenizer_(0), currentIndex_(index)
{}

TokenizerIterator::TokenizerIterator(Tokenizer* tokenizer, size_t index) :
const_tokenizer_(tokenizer), tokenizer_(tokenizer), currentIndex_(index)
{}

const Token& TokenizerIterator::operator*() const
{
	return const_tokenizer_->token(currentIndex_);
}

Token& TokenizerIterator::operator *()
{
	return tokenizer_->token(currentIndex_);
}


TokenizerIterator& TokenizerIterator::operator++()
{
	++currentIndex_;
	return *this;
}

bool TokenizerIterator::operator==(const TokenizerIterator& rhs) const
{
	return currentIndex_ == rhs.currentIndex_;
}

bool TokenizerIterator::operator !=(const TokenizerIterator& rhs) const
{
	return !(*this == rhs);
}
