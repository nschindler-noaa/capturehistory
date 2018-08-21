/*
 *
 */

#include <algorithm>

#include "ErrorFlags.h"

using std::string;
using std::istream;
using std::ostream;
using std::fill;
using std::find;
using namespace cbr;

ErrorFlags::ErrorFlags (size_t num) : errors(num, false)
{
}

ErrorFlags::~ErrorFlags()
{
}

void 
ErrorFlags::setError(size_t index)
{
	errors[index] = true;
}

void
ErrorFlags::clear()
{
	fill (errors.begin(), errors.end(), false);
}


bool
ErrorFlags::isOk() const
{
	return find(errors.begin(), errors.end(), true) == errors.end();
}

bool
ErrorFlags::isSet(size_t index) const
{
	return errors[index];
}

void 
ErrorFlags::write (ostream& os) const
{
	int col = 0;
	for (BoolVector::const_iterator it = errors.begin(); it != errors.end(); ++it)
	{
		os << (col++ ? " " : "" ) << ((*it) ? "1" : "0");
	}
}

ostream& operator<< (ostream& os, const ErrorFlags& e)
{
	e.write (os);

	return os;
}

void
ErrorFlags::read (istream& is)
{
	size_t i = 0;
	while (!is.eof() && i < errors.size())
	{
		bool rhs;
		is >> rhs;
		errors[i++] = rhs;
	}
}


istream& operator>> (istream& is, ErrorFlags& e)
{
	e.read (is);
	return is;
}
