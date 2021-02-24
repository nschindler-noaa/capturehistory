/*
*
*/


#include <string>
#include <sstream>
#include <vector>

#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QStringList>
#include <QRegExpValidator>


//#include <boost/regex.hpp>
//#include <boost/algorithm/string/trim.hpp>
//#include <boost/date_time/gregorian/gregorian.hpp>
//#include <boost/algorithm/combination.hpp>
//#include <boost/tokenizer.hpp>

#include "PPData.h"

#include <ArrayDefs.h>
#include <StringTok.h>
#include <StringManip.h>
#include <DateConverter.h>
#include <Tokenizer.h>

using std::string;
using std::istream;
using std::ostream;
using std::stringstream;
using std::vector;

using namespace cbr;
//using namespace boost::gregorian;

//typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

QString PPData::NullString = "XX";
bool PPData::firstDate = true;


PPData::PPData(int numFields)  : numFields(numFields), header (false), indata (false), ok (true)
{
    resetColumnOrder();

    validTimeFormats << "hh:mm:ss";
    validTimeFormats << "hh:mm";
    validTimeFormats << "h:mm";
    validTimeFormats << "h:m:ss";
    validTimeFormats << "AP";
    validTimeFormats << "h:m:ss AP";

    validDateFormats << "yyyy-MM-dd";
    validDateFormats << "dd-MMM-yyyy";
    validDateFormats << "yyyy.MM.dd";
    validDateFormats << "MM/dd/yy";
    validDateFormats << "NN.dd.yyyy";
    validDateFormats << "M/d/yy";
    validDateFormats << "M/d/yyyy";
    validDateFormats << "m/d/yy";

}

bool PPData::isValidPitTag(const QString pitCode)
{
//   static const boost::regex e("[\\.0-9A-F]+");
//   return regex_match(pitCode, e);
    int pos = 0;
    QString check(pitCode);
    QRegExp e("[\\.0-9A-F]+");
    QRegExpValidator v(e, nullptr);
    return v.validate(check, pos) == QRegExpValidator::Acceptable;
}

bool PPData::isValidDate(const QString s)
{
    QDate date;
    foreach (QString format, validDateFormats) {
        date = QDate::fromString(s, format);
        if (date.isValid())
        {
            if (firstDate)
            {
                validDateFormats.removeOne(format);
                validDateFormats.push_front(format);
                // put this date format as first in formats list
                firstDate = false;
            }
            return true;
        }
    }

    return false;
}

bool PPData::isValidTime( const QString s) {
    QTime time;
    foreach (QString format, validTimeFormats) {
        time = QTime::fromString(s, format);
        if (time.isValid())
            return true;
    }

    return false;
}

bool PPData::isValidDateTime(const QString s) {
    QDateTime dt = getDateTime(s);
    return dt.isValid();
}

QDateTime PPData::getDateTime(const QString s)
{
    int pos = s.indexOf(' ');

    QString dateString = pos == -1 ? s : s.mid(0, pos);

    QDate date;
    foreach (QString format, validDateFormats) {
        date = QDate::fromString(dateString, format);
        if (date.isValid())
            break;
    }

    if (!date.isValid())
        return QDateTime(); // invalid

    if (date.year() < 1980)
        date = date.addYears(100);

    if (pos == -1)
        return QDateTime(date);

    QString timeString = s.mid(pos + 1);
    QTime time;
    foreach (QString format, validTimeFormats) {
        time = QTime::fromString(timeString, format);
        if (time.isValid())
            break;
    }

    if (!time.isValid())
        return QDateTime();
    else
    {
        QDateTime dt(date, time);
        QString ds = date.toString();
        QString ts = time.toString();
        QString dateTimeString = dt.toString();
        return QDateTime(date, time);
    }
}

double PPData::getTimeFromDate( const QString s)
{
    QDateTime time = getDateTime(s);
    QString timeString = time.toString();
    time.setTimeSpec(Qt::UTC);
    unsigned utime = time.toTime_t();
    double daysSinceEpoch = utime / 86400.0;
    const double epochJd = 2440587.5;
    double jd = daysSinceEpoch + epochJd;
    return jd;
}


/*
* If the data is csv and has missing fields, insert
* the NullString
*/
void PPData::replaceMissingFields (QString s)
{
    s.replace(QString("\"\""), QString(NullString));
//	QString find = "\"\"";
//	int length = find.length();
//	string::size_type pos = 0;
//	while((pos = s.indexOf(find)) < s.count()) {// find, pos )) != string::npos ) {
//		s.replace(pos, length, NullString );
//	}
}

void PPData::resetColumnOrder() {
    for ( int i = 0; i < numFields; ++i )
        setColumnOrder( i, i );
}


istream& operator>> (istream& is, PPData& d)
{
    // reset
    d.header = false;
    d.ok = true;
    d.columnData.clear();

    // read line of data
    std::string line;
    getline (is, line);
    QString line_(line.data());

    if (line_.isEmpty()) {//.length() == 0) {
        d.ok = false;
    }
    else {

        // parse the data
//        d.read(line_);

#if 0
        // replace empty fields with NullString (for csv data)
        string target = ",\"\",";
        int len = target.length();
        string::size_type pos = 0;
        while( (pos = line.find( target, pos )) != string::npos ) {
            line.replace( pos, len, ",\"" + d.NullString + "\"," );
        }
        target = ",,";
        len = target.length();
        pos = 0;
        while( (pos = line.find( target, pos )) != string::npos ) {
            line.replace( pos, len, "," + d.NullString + "," );
        }
        if (line.find_first_of(',') == 0)
            line.replace( 0, 1, d.NullString + "," );
        if (line.find_last_of(',') == line.size() - 1)
            line.replace( line.size() - 1, 1, "," + d.NullString);
#endif

        // tokenize the data

        // remove quotes;
        line_.replace(QRegExp("[\"]"), "");
//        static const boost::regex e("[\"]");
//        line = regex_replace(line, e, "");

        // check whether we have commma separated data or not
        if (line_.contains(',') || line_.contains('\t')) {
//        if (line.find(',') != string::npos || line.find('\t') != string::npos)  { // csv or tab delimited
//            boost::char_separator<char> sep(",\t\n", "|", boost::keep_empty_tokens);
            Tokenizer tk(line_, "#", "", ",\t");
            for (int i = 0; i < tk.numTokens(); i++)
                d.columnData.append(tk.token(i).name);
//            tokenizer toks(line, sep);
//            for (tokenizer::iterator it = toks.begin() = toks.begin(); it != toks.end(); ++it) {
//                d.columnData.push_back(*it);
//            }
        }
        else { // space delimited?
//            boost::char_separator<char> sep(" \t\n", "|", boost::keep_empty_tokens);
            Tokenizer tk(line_, "#", "", " \n");
            QString dtime;
//            tokenizer toks(line, sep);
//            string tok;
//            stringstream ss;
            bool datePending = false;
            for (int i = 0; i < tk.numTokens(); i++) {
//            for (tokenizer::iterator it = toks.begin() = toks.begin(); it != toks.end(); ++it) {
//                tok = *it;
                if (d.isValidDate(tk.token(i).name)) {
                    dtime = QString(tk.token(i).name);
//                    ss.str("");
//                    ss << tok;
                    datePending = true;
                }
                else if (datePending) {
                    if (d.isValidTime(tk.token(i).name)) {
                        dtime.append(' ');
                        dtime.append(tk.token(i).name);
//                        ss << " " << tok;
                    }
                    else {
                        d.columnData.append(dtime);
//                        d.columnData.push_back(ss.str()); // push completed date string
                        datePending = false;
                    }
                }

                if (!datePending)
                    d.columnData.append(tk.token(i).name);
            }
        }


//        bool ok  = d.read (is);
        bool ok = d.parseColumnData();
        if (ok) {
            d.indata = true;
            d.ok = true;
        }
        else {
            if (d.indata) {
                d.ok = false;
            }
            else {
                d.ok = true;
                d.header = true;
            }

        }
    }

    return is;
}



ostream& operator<< (ostream& os, const PPData& d)
{
  d.write (os);
  return os;
}


