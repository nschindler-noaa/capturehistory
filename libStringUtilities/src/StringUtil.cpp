/*
 * String util
 */

#include <sstream>

#include "StringUtil.h"
//#include <QRegExp>
//#include <QRegularExpression>
#include <QStringList>
#include <QChar>

//#include <boost/regex.hpp>

using namespace std;

static QString result;

bool isSpace (const char &c)
{
    QChar qc(c);
    return qc.isSpace();
}



namespace cbr {


    bool isValidName(const QString& testString) {
        return testString.contains("\\w");
    }

    bool isValidFloat(const QString& testString) {
        bool okay = false;
        testString.toDouble(&okay);
        return okay;
    }

    bool isValidInt(const QString& testString) {
        bool okay = false;
        testString.toLongLong(&okay);
        return okay;
    }

    QString trim(const QString &str) {
        result = QString (str.simplified());
        return result;
    }

    bool isNumeric(const QString& testString) {
        bool okay = false;
        testString.toDouble(&okay);
        return okay;
    }

/*    std::string vectorToString(const vector<string> & v, const string delim) {
        if (v.empty())
            return "";

        ostringstream os;
        copy(v.begin(), v.end() - 1, ostream_iterator<string > (os, delim.c_str()));

        return os.str() + *(v.end() - 1);
    }*/

/*    QString& listToString(const list<string>& l, const string delim) {
        vector<string> v(l.begin(), l.end());
        std::string str = vectorToString(v, delim);
        result = QString(str.data());
        return result;
    }*/

    QString& listToString(const QStringList& ql, const QString& delim) {
        result = ql.at(0);
        for (int i = 1; i < ql.count(); i++)
            result.append(QString("%1%2").arg(delim, ql.at(i)));
        return result;
    }

    QString& makeString(int length, QChar ch) {
        result.clear();
        for (int i = 0; i < length; i++)
            result.append(ch);
        return result;
    }

};



