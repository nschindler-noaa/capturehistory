/*
 * StringUtil.h
 */

#ifndef StringUtil_h
#define StringUtil_h

#include <string>
#include <list>
#include <cctype>
#include <vector>
#include <limits.h>

#include <QString>

/** Remove all White space characters from the left hand side
        of a string.
 */
std::string chopWSLeft(const std::string &s);

/** Remove all White space characters from the right hand side
        of a string
 */
std::string chopWSRight(const std::string &s);

namespace cbr {

    void toLower(std::string& s);
    void toUpper(std::string& s);

    /** Test if a string is a valid name.  That is, start with a alpha character
            followed by alphanumeric and "_" characters.
     */
    bool isValidName(const std::string& testString);

    /** Test if a string is a valid floating point number. */
    bool isValidFloat(const std::string& testString);
    /** Or an int. */
    bool isValidInt(const std::string& testString);

    /** Remove control characters from front end and back end of string. */
    std::string trim(const std::string& str);
    std::string trim(const QString& str);

    /** Check if string is all numeric */
    bool isNumeric(const std::string& s);

    // like join or concat
    std::string vectorToString(const std::vector<std::string>& v, const std::string delim = " ");
    std::string listToString(const std::list<std::string>& v, const std::string delim = " ");
    std::string listToString(const QStringList &ql, const std::string delim = " ");
    
    // format a block of text to fit 80 col display (standard terminal line)
    // firstline is whether to have hanging indent (1) or normal (2) or none (0)
    // bodyIndent is the total tabs to indent body of text
    std::string formatBlock(std::string block, int firstline, int bodyIndent);
    void addIndent(QString &text, int number);
}

#endif

