/*
*
*/

#include "StringManip.h"

// define some methods for string manipulation


using namespace cbr;

QString &stripLeading(const QString & str)
{
    result = str;
    while (result.startsWith(' ') || result.startsWith('\t'))
        result.chop(1);
    return result;
}

QString &stripTrailing(const QString & str)
{
    result = str;
    while (result.endsWith(' ') || result.endsWith('\t'))
        result.remove(0, 1);
    return result;

}

QString & cbr::strip (const QString& str, StripType type)
{
    QString temp = str;

    switch (type) {
    case cbr::leading :
        temp = stripLeading(str);
        break;
    case cbr::trailing:
        temp = stripTrailing(str);
        break;
    case cbr::both:
        temp = stripLeading(str);
        temp = stripTrailing(temp);
        break;
    }
    result = temp;

    return result;
}

template <class T>
QString & toString (const T& value, int w, int d, QChar fill)
{
    bool isInt = (d == 0);
    int width = w < 0? 0: w;
    if (isInt) {
//        result = toString(value, width, fill);
        result = QString(QString("%1").arg(value, width, 10, fill));
    }
    else {
//        result = QString::number(value, 'g', d);
//        while (result.size() < width)
//            result.prepend(fill);
        result = QString(QString("%1").arg(value, width, 'g', d, fill));
    }

    return (result);
}

QString & toString (const int value, int w, QChar fill)
{
    QString num;
    int width = w < 0? 0: w;
    result = QString(QString("%1").arg(value, width, 10, fill));
//    result = QString::number(value);
//    while (result.size() < width)
//        result.prepend(fill);

    return (result);
}


