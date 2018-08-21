/*
 * String util
 */

#include <sstream>

#include "StringUtil.h"
//#include <QRegExp>
//#include <QRegularExpression>
#include <QStringList>

//#include <boost/regex.hpp>

using namespace std;


bool isSpace (const char &c)
{
    bool ans = false;
    if (c == '\t' ||
        c == '\n' ||
        c == '\v' ||
        c == '\f' ||
        c == '\r' ||
        c == ' ')
        ans = true;
    return ans;
}

/*
 * Remove all White space characters from the left hand side
 * of a string.
 */
string chopWSLeft(const string &s) {
    QString qstr;
    unsigned i;
    for (i = 0; i < s.size(); i++)
    {
        if (!isSpace(s.at(i)))
            break;
    }
    for ( ; i < s.size(); i++)
        qstr.append(s.at(i));

    return qstr.toStdString();
/*    string str = s;
    size_t firstCh = str.find_first_not_of("\x20\x09\x0A\x0B\x0C\x0D");
    if ((firstCh != 0))
        str.erase(0, firstCh);
    return str;*/
}

/*
 * Remove all White space characters from the right hand side
 * of a string.
 */
string chopWSRight(const string &s) {
    string str = s;
    size_t lastCh = str.find_last_not_of("\x20\x09\x0A\x0B\x0C\x0D");
    if (lastCh != str.npos)
        str.resize(lastCh + 1);
    else {
        size_t firstCh = str.find_first_not_of("\x20\x09\x0A\x0B\x0C\x0D");
        if (firstCh == str.npos)
            str.erase(str.begin(), str.end());
    }

    return str;
}

namespace cbr {

    void toLower(string &s) {
        string::iterator it;
        for (it = s.begin(); it != s.end(); it++)
            *it = tolower(*it);
    }

    void toUpper(string &s) {
        string::iterator it;
        for (it = s.begin(); it != s.end(); it++)
            *it = toupper(*it);
    }

    bool isValidName(const string& testString) {
        QString qstr(testString.data());
        return qstr.contains("\\w");
//        QRegularExpression nameExpr("\\w*");
//        boost::regex nameExpr("\\w*");
//        QRegularExpressionMatch rem = nameExpr.match(qstr);
//        return rem.captured().count() > 0;
//        return boost::regex_match(testString, nameExpr, boost::match_default);
    }

    bool isValidFloat(const string& testString) {
        bool okay = false;
        QString qstr(testString.data());
        qstr.toFloat(&okay);
        return okay;
//        boost::regex floatExpr("[+-]?\\d+\\.?\\d*(?:[eE]?[+-]?\\d+)?|[+-]?\\d+(?:[eE][+-]?\\d+)?");
//        return boost::regex_match(testString, floatExpr, boost::match_default | boost::format_all);
    }

    bool isValidInt(const string& testString) {
        bool okay = false;
        QString qstr(testString.data());
        qstr.toInt(&okay);
        return okay;
//        boost::regex intExpr("[+-]?\\d+");
//        return boost::regex_match(testString, intExpr, boost::match_default | boost::format_all);
    }

    string trim(const std::string& str) {
//        QRegularExpression matchExpr("^([\\s\\n]*)(.*?)([\\s\\n]*)$");
        QString qstr(str.data());
        return qstr.simplified().toStdString();
//        QString replaceExpr("\\2");
//        qstr = qstr.replace(matchExpr, replaceExpr);
//        return str;
//        const boost::regex matchExpr("^([\\s\\n]*)(.*?)([\\s\\n]*)$");
//        const string replaceExpr("\\2");
//        return boost::regex_replace(str, matchExpr, replaceExpr, boost::match_default | boost::format_sed);
    }

    string trim(const QString& str) {
//        QRegularExpression matchExpr("^([\\s\\n]*)(.*?)([\\s\\n]*)$");
        QString qstr(str.simplified());
//        QString replaceExpr("\\2");
//        qstr = qstr.replace(matchExpr, replaceExpr);
        return qstr.toStdString();
    }

    bool isNumeric(const std::string& s) {
        return (s.find_first_not_of("0123456789.-+eE") == string::npos);
    }

    string vectorToString(const vector<string> & v, const string delim) {
        if (v.empty())
            return "";

        ostringstream os;
        copy(v.begin(), v.end() - 1, ostream_iterator<string > (os, delim.c_str()));

        return os.str() + *(v.end() - 1);
    }

    string listToString(const list<string>& l, const string delim) {
        vector<string> v(l.begin(), l.end());
        return vectorToString(v, delim);
    }

    string listToString(const QStringList& ql, const string delim) {
        vector<string> v;
        for (int i = 0; i < ql.count(); i++)
        {
            v.push_back(ql.at(i).toStdString());
        }
        return vectorToString(v, delim);
    }

};



