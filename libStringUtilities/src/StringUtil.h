/*
 * StringUtil.h
 */

#ifndef StringUtil_h
#define StringUtil_h

#include <string>
#include <list>
#include <vector>

#include <QStringList>


namespace cbr {

    /** Test if a string is a valid name.  That is, start with a alpha character
            followed by alphanumeric and "_" characters.
     */
    bool isValidName(const QString& testString);

    /** Test if a string is a valid floating point number. */
    bool isValidFloat(const QString& testString);
    /** Test if a string is a valid integer. */
    bool isValidInt(const QString& testString);

    /** Remove control characters from front end and back end of string. */
    QString trim(const QString &str);

    /** Check if string is all numeric */
    bool isNumeric(const QString& testString);

    // like join or concat
//    std::string vectorToString(const std::vector<std::string>& v, const std::string delim = " ");
//    QString& listToString(const std::list<std::string>& v, const std::string delim = " ");
    QString& listToString(const QStringList &ql, const QString &delim = " ");
    QString& makeString(int length, QChar ch = ' ');

}

#endif

