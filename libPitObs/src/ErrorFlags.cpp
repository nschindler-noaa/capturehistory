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

#include <QStringList>

ErrorFlags::ErrorFlags (int num) //: errors(num, false)
{
    for (int s = 0; s < num; s++)
        errors.append(false);
}

ErrorFlags::~ErrorFlags()
{
}

void
ErrorFlags::setError(int index)
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
ErrorFlags::isSet(int index) const
{
    return errors[index];
}

void
ErrorFlags::write (ostream& os) const
{
    int col = 0;
    for (QList<bool>::const_iterator it = errors.begin(); it != errors.end(); ++it)
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
    int i = 0;
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
