#ifndef StringManip_H
#define StringManip_H

// define some methods for string manipulation

#include <QString>

static QString result;

namespace cbr
{

    // strip white space from a string
    enum StripType { leading, trailing, both };
    QString & strip(const QString& str, StripType type = both);

    // convert value to a QString with specific decimal places,
    // total width, and fill character
    template <class T>
    QString & toString (const T& value, int d = 0, int w = -1, QChar fill = ' ');
    QString & toString (const int value, int w = -1, QChar fill = ' ');

}


#endif
