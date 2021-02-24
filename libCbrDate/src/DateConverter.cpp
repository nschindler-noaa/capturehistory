/*
 * DateConverter.cpp
 */

#include <string>
#include <list>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <time.h>

#include <ArrayDefs.h>
#include <StringTok.h>
#include <StringUtil.h>
#include <StringManip.h>
#include <StringTok.h>

#include "DateConverter.h"

#include <QString>
#include <QStringList>
#include <QStringRef>

using namespace std;
using namespace cbr;

//namespace cbr {

#define IGREG (15+31L*(10+12L*1582))
static const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};


DateConverter DateConverter::base("01-Jan-1970", "00:00:00");

const int Year2k = 80;

/**
 *  Contructor
 */

DateConverter::DateConverter(void) {
    jd_ = (0);
    time_ = (0);
    dateFormat = (A);
    outFormat = (DateTime);
    int year;
    int month;
    int day;
    int hour;
    int min ;
    int sec;

#ifdef WIN32
    time_t long_time;

    struct tm timeinfo;
    localtime_s(&timeinfo, &long_time);

    year = timeinfo.tm_year + 1900;
    month = timeinfo.tm_mon + 1;
    day = timeinfo.tm_mday;
    hour = timeinfo.tm_hour;
    min = timeinfo.tm_min;
    sec = timeinfo.tm_sec;

#else
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    year = timeinfo->tm_year + 1900;
    month = timeinfo->tm_mon + 1;
    day = timeinfo->tm_mday;
    hour = timeinfo->tm_hour;
    min = timeinfo->tm_min;
    sec = timeinfo->tm_sec;
#endif

    jd_ = julianDay(year, month, day);
    setTime(hour, min, sec);

}

/**
 *  Contructor
 */
DateConverter::DateConverter(double jd, Adjuster adj) {
    dateFormat = A;
    outFormat = DateTime;

    jd_ = static_cast<int> (jd + adj + 0.5) - 0.5;
    time_ = jd - jd_;
}

/**
 *  Contructor
 *
 *  year needs to be 4 digits
 */
DateConverter::DateConverter(int year, int month, int day) {
    time_ = 0;
    dateFormat = A;
    outFormat = DateTime;
    jd_ = julianDay(year, month, day);
}

/**
 *  Contructor
 */
DateConverter::DateConverter(int doy, int year) {
    time_ = (0);
    dateFormat = (A);
    outFormat = (DateTime);
    jd_ = julianDay(doy, year);
}

/**
 *  Constructor
 *
 *  Take a date in one of two formats ( see comments
 *  for parse_date) and a time and returns the julian day.
 *  Julian day is defined as the julian day of the given
 *  date plus the fractional day given by t.
 */
DateConverter::DateConverter(const char *date, const char *time) {
    dateFormat = (A);
    outFormat = (DateTime);
    reset(date, time);
}

DateConverter::DateConverter(const QString& date, const QString& time) {
    dateFormat = (A);
    outFormat = (DateTime);
    reset(date, time);
}

DateConverter::DateConverter(const QString &datetime) {
    dateFormat = (A);
    outFormat = (DateTime);
    // tokenize the data
    QStringList toks;
    stringTok(toks, datetime, " ");
    if (toks.size() == 2)
        reset (toks.at(0), toks.at(1));
    else if (datetime.length() == 8) { // yyyymmdd
        QString date;
        date.resize(10);
        date[0] = datetime[0];
        date[1] = datetime[1];
        date[2] = '-';
        date[3] = datetime[2];
        date[4] = datetime[3];
        date[5] = '-';
        date[6] = datetime[4];
        date[7] = datetime[5];
        date[8] = datetime[6];
        date[9] = datetime[7];
        reset(date);
    }
    else {
        reset(datetime);
    }
}

/**
 *  Copy contructor
 */
DateConverter::DateConverter(const DateConverter& date) {
    jd_ = (date.jd_);
    time_ = (date.time_);
    dateFormat = (date.dateFormat);
    outFormat = (date.outFormat);
}

/**
 *  setDate
 */
bool DateConverter::setDate(const QString& date) {
    int year;
    int month;
    int day;

    if (!parseDate(date, &year, &month, &day))
        return false;
    else {
        jd(julianDay(year, month, day));
        return true;
    }
}

/**
 * setTime
 */
void DateConverter::setTime(int hr, int min, int sec) {
    time_ = static_cast<double> (hr) / 24.0;
    time_ += static_cast<double> (min) / (24.0 * 60.0);
    time_ += static_cast<double> (sec) / (24.0 * 60.0 * 60.0);
}

/**
 *  setTime
 */
bool DateConverter::setTime(const QString &time) {
    int hr;
    int min;
    int sec;

    if (!parseTime(time, &hr, &min, &sec))
        return false;
    else {
        setTime(hr, min, sec);
        return true;
    }
}

/*
 *  reset - Reset the time based on the input
 */
void DateConverter::reset(double jd) {
    jd_ = jd;
}

/**
 *  reset - Reset the time based on the input
 */
void DateConverter::reset(const QString date, const QString time) {
    int yr, mo, day;
    int hr, min, sec;

    parseDate(date, &yr, &mo, &day);
    jd_ = julianDay(yr, mo, day);
    if (time.isEmpty())
        time_ = 0;
    else {
        parseTime(time, &hr, &min, &sec);
        setTime(hr, min, sec);
    }
}

/**
 *  year - return the year as an integer
 */
int DateConverter::year() const {
    int y;
    int m;
    int d;
    calendarDate(&y, &m, &d);
    return y;
}

/**
 *  month - return the month as an integer
 */
int DateConverter::month() const {
    int y;
    int m;
    int d;
    calendarDate(&y, &m, &d);
    return m;
}

int DateConverter::monthToInt(const QString &strmon) const
{
    QString lwrmon(strmon.toLower());
    int month = 0;

    if      (lwrmon.compare("jan") == 0)
        month = 1;
    else if (lwrmon.compare("feb") == 0)
        month = 2;
    else if (lwrmon.compare("mar") == 0)
        month = 3;
    else if (lwrmon.compare("apr") == 0)
        month = 4;
    else if (lwrmon.compare("may") == 0)
        month = 5;
    else if (lwrmon.compare("jun") == 0)
        month = 6;
    else if (lwrmon.compare("jul") == 0)
        month = 7;
    else if (lwrmon.compare("aug") == 0)
        month = 8;
    else if (lwrmon.compare("sep") == 0)
        month = 9;
    else if (lwrmon.compare("oct") == 0)
        month = 10;
    else if (lwrmon.compare("nov") == 0)
        month = 11;
    else if (lwrmon.compare("dec") == 0)
        month = 12;
    return month;
}

const char *monthToString(int num)
{
    return months[num];
}

/**
 *  day - return the day as an integer
 */
int DateConverter::day() const {
    int y;
    int m;
    int d;
    calendarDate(&y, &m, &d);
    return d;
}

/**
 *  hour - return the hour as an integer
 */
int DateConverter::hour() const {
    int h;
    int m;
    int s;
    calendarTime(&h, &m, &s);
    return h;
}

/**
 *  min - return the minute as an integer
 */
int DateConverter::minutes() const {
    int h;
    int m;
    int s;
    calendarTime(&h, &m, &s);
    return m;
}

/**
 *  sec - return the second as an integer
 */
int DateConverter::sec() const {
    int h;
    int m;
    int s;
    calendarTime(&h, &m, &s);
    return s;
}

/*
 * Return the julian day given day of year and
 * year.
 */
double DateConverter::julianDay(int doy, int year) {
    return doy + julianDay(year - 1, 12, 31);
}

/* convert year, month, day to julian day */
double DateConverter::julianDay(int year, int month, int day) const {
    int jd;
    int ja;
    int jy = year;
    int jm;

    if (jy < 0) ++jy;
    if (month > 2)
        jm = month + 1;
    else {
        --jy;
        jm = month + 13;
    }

    jd = static_cast<int> (365.25 * jy) + static_cast<int> (30.6001 * jm) + day + 1720995;
    if (day + 31L * (month + 12L * year) >= IGREG) {
        ja = static_cast<int> (0.01 * jy);
        jd += 2 - ja + static_cast<int> (0.25 * ja);
    }

    return jd - 0.5; // calculated date is at noon, so subtract 1/2 a day
}

/* convert julian day to calendar day */
void DateConverter::calendarDate(int *year, int *month, int *day) const {
    int jul = static_cast<int> (jd_ + 0.5);
    long ja;
    long jalpha;
    long jb;
    long jc;
    long jd;
    long je;

    if (jul < IGREG)
        ja = jul;
    else {
        jalpha = static_cast<long> ((static_cast<double> (jul - 1867216) - 0.25) / 36524.25);
        ja = jul + 1 + jalpha - static_cast<long> (0.25 * jalpha);
    }

    jb = ja + 1524;
    jc = static_cast<long> (6680.0 + (static_cast<double> (jb - 2439870) - 122.1) / 365.25);
    jd = static_cast<long> (365 * jc + (0.25 * jc));
    je = static_cast<long> ((jb - jd) / 30.6001);
    *day = jb - jd - static_cast<int> (30.6001 * je);
    *month = je - 1;
    if (*month > 12) * month -= 12;
    *year = jc - 4715;
    if (*month > 2) --(*year);
    if (*year <= 0) --(*year);
}

void DateConverter::calendarTime(int *h, int *m, int *s) const {
    if (time_ < .0000001)
        *h = *m = *s = 0;
    else {
        // hour
        double fh = 24.0 * time_;
        int ih = static_cast<int> (fh);

        // min
        double fm = (fh - static_cast<double> (ih)) * 60.0;
        int im = static_cast<int> (fm);

        // sec
        double delta = fm - static_cast<double> (im);
        double fs = delta * 60.0;
        int is = static_cast<int> (fs);

        double remainder = fs - is;

        if (remainder > 0.5)
            ++is;
        if (is == 60) {
            is = 0;
            ++im;
        }
        if (im == 60) {
            im = 0;
        }

        *h = ih;
        *m = im;
        *s = is;
    }
}

/*
 * return the day of the year
 */
int DateConverter::dayOfYear() {
    int year;
    int month;
    int day;
    calendarDate(&year, &month, &day);
    double jd = julianDay(year - 1, 12, 31);
    return static_cast<int> (jd_ - jd);
}

/*
 * Return the day of year plus the fraction of the day
 * based on the time of day.
 */
double DateConverter::timeOfYear() {
    int doy = dayOfYear();
    return static_cast<double> (doy) + time_;
}

/**
 * parsing methods */

/* date of format dd-mmm-yyyy */
bool DateConverter::parseDate1(const QString d, int *year, int *month, int *day) {
    QString cm;
    QString cd;
    QString cy;
    *year = *month = *day = 0;
    bool okay = false;

    QStringList toks;
    stringTok(toks, d, "-");
    if (toks.size() == 3) {
        okay = true;
        cd = toks[ 0 ];
        cm = toks[ 1 ];
        cy = toks[ 2 ];

        *day = cd.toInt();
        *month = monthToInt(cm);
        *year = cy.toInt();

        /* good until 2080! */
        if (cy.length() == 2) {
            if (*year > Year2k)
                *year += 1900;
            else
                *year += 2000;
        }
        if (*day < 1 || *day > 31)
            okay = false;
        else if (*month == 0)
            okay= false;
        else if (*year < 1980 || *year > 2080) // good until 2080!
            okay = false;

/*        cm = cm.toLower();

        if (!cm.compare("jan"))
            *month = 1;
        else if (!cm.compare("feb"))
            *month = 2;
        else if (!cm.compare("mar"))
            *month = 3;
        else if (!cm.compare("apr"))
            *month = 4;
        else if (!cm.compare("may"))
            *month = 5;
        else if (!cm.compare("jun"))
            *month = 6;
        else if (!cm.compare("jul"))
            *month = 7;
        else if (!cm.compare("aug"))
            *month = 8;
        else if (!cm.compare("sep"))
            *month = 9;
        else if (!cm.compare("oct"))
            *month = 10;
        else if (!cm.compare("nov"))
            *month = 11;
        else if (!cm.compare("dec"))
            *month = 12;
        else
            okay = false;*/
    }

    return okay;
}

/* date of format yyyy.mm.dd */
bool DateConverter::parseDate2(const QString d, int *year, int *month, int *day) {
    QString cm;
    QString cd;
    QString cy;
    *year = *month = *day = 0;

    QStringList toks;
    bool okay = false;
    stringTok(toks, QString(d), ".");
    if (toks.size() == 3) {
        cy = toks[ 0 ];
        cm = toks[ 1 ];
        cd = toks[ 2 ];

        *year = cy.toInt();
        *month = cm.toInt();
        *day = cd.toInt();
        okay = true;
    }

    return okay;
}

/* date of format m/d/y with month and day being either 1 or 2 digits, and year being 2 or 4 */
bool DateConverter::parseDate3(const QString d, int *year, int *month, int *day) {
    QString cm;
    QString cd;
    QString cy;
    *year = *month = *day = 0;
    bool okay = false;

    QStringList toks;
    stringTok(toks, QString(d), "/");
    if (toks.size() == 3) {
        cm = toks[ 0 ];
        cd = toks[ 1 ];
        cy = toks[ 2 ];

        *year = cy.toInt();
        *month = cm.toInt();
        *day = cd.toInt();

        /* good until 2080! */
        if (cy.length() == 2) {
            if (*year > Year2k)
                *year += 1900;
            else
                *year += 2000;
        }
        okay = true;
    }

    return okay;
}

/* date of format yyyy-mm-dd */
bool DateConverter::parseDate4(const QString d, int *year, int *month, int *day) {
    *year = *month = *day = 0;
    bool okay = false;
    QStringList toks;
    stringTok(toks, QString(d), "-");
    if (toks.size() != 3) {
        *year = toks[0].toInt();
        *month = toks[1].toInt();
        *day = toks[2].toInt();

        okay = true;
    }
    return okay;
}

/* date of format yyyymmdd */
bool DateConverter::parseDate5(const QString d, int *year, int *month, int *day) {
    bool okay = false;
    *year = *month = *day = 0;
    QString date(d);

    if (date.count() == 8) {
        int i = 0;
        QString stryr, strmon, strday;
        for (;i < 4; i++)
            stryr.append(date.at(i));
        for (;i < 6; i++)
            strmon.append(date.at(i));
        for (;i < 8; i++)
            strday.append(date.at(i));

        *year = stryr.toInt();
        *month = strmon.toInt();
        *day = strday.toInt();

        okay = true;
    }
    else if (date.size() == 6) {
        int i = 0;
        QString stryr, strmon, strday;
        for (;i < 2; i++)
            stryr.append(date.at(i));
        for (;i < 4; i++)
            strmon.append(date.at(i));
        for (;i < 6; i++)
            strday.append(date.at(i));

        *year = stryr.toInt();
        *month = strmon.toInt();
        *day = strday.toInt();
        /* good until 2080! */
        if (*year > Year2k)
            *year += 1900;
        else
            *year += 2000;

        okay = true;
    }

    return okay;
}

/* Parses these types of dates: Date1 'dd-mmm-yyyy',
 *                              Date2 'yyyy.mm.dd',
 *                              Date3 'm/d/y' with 2 or 4 digits for year,
 *                              Date4 'yyyy-mm-dd',
 *                              Date5 'yyyymmdd'.
It distinguishes between them by
searching for the '-',  '.', or '/' character */
bool DateConverter::parseDate(const QString date, int *year, int *month, int *day) {
    bool okay = false;
    int ind = date.indexOf('-'); // if either yyyy-mm-dd or dd-mm-yyyy
    if (ind != -1) { // found '-'
        if (ind == 4)                // date is in form yyyy-mm-dd
            okay = parseDate4(date, year, month, day);
        else                         // date is in form dd-mmm-yyyy
            okay = parseDate1(date, year, month, day);
    } else if (date.contains('.')) { // date is in form yyyy.mm.dd
        okay = parseDate2(date, year, month, day);
    } else if (date.contains('/')) { // date is in form m/d/y
        okay = parseDate3(date, year, month, day);
    } else {                         // date is in form yyyymmdd
        okay = parseDate5(date, year, month, day);
    }
    return okay;
}

bool DateConverter::parseStrings(const QString y, const QString m, const QString d, int *year, int *month, int *day) {
    bool okay = true;
    *year = y.toInt(&okay);
    if (m.count() > 2) {
        *month = monthToInt(m);
        if (*month < 1 || *month > 12)
            okay = false;
    }
    else {
        *month = m.toInt(&okay);
    }
    *day = d.toInt(&okay);

    return okay;
}

/*
 * Simple check to distinguish a valid time string from a valid date
 * string. Return true if the string contains the colon (":") character.
 */
bool DateConverter::isTime(const QString& s) {
    return s.contains(':');
}

/* time of format h:m:s */
bool DateConverter::parseTime(const QString t, int *hr, int *min, int *sec) {
    bool okay = false;
    *hr = *min = *sec = 0;

    QString time(t);
    QStringList toks;
    stringTok(toks, time, ":");

    if (toks.size() == 0) {
        okay = false;
    } else {
        enum {
            Hour = 0, Min, Sec
        };
        for (int i = 0; i < toks.size(); ++i) {
            int val = toks.at(i).toInt();//fromString<int>(toks[i]);
            switch (i) {
                case Hour:
                    *hr = val;
                    break;
                case Min:
                    *min = val;
                    break;
                case Sec:
                    *sec = val;
                    break;
            }
        }
        okay = true;
    }

    return okay;
}

int DateConverter::compare(const DateConverter& date) const {
    int retval = 0;
    if (getTime() > date.getTime())
        retval =  1;
    else if (getTime() < date.getTime())
        retval =  -1;
    return retval;
}

/*
bool operator>(const DateConverter& date1, const DateConverter& date2) {
    return date1.compare(date2) > 0;
}

bool operator<(const DateConverter& date1, const DateConverter& date2) {
    return date1.compare(date2) < 0;
}

bool operator ==(const DateConverter& date1, const DateConverter& date2) {
    return date1.compare(date2) == 0;
}

bool operator >=(const DateConverter& date1, const DateConverter& date2) {
    return date1.compare(date2) >= 0;
}


bool operator <=(const DateConverter& date1, const DateConverter& date2) {
    return date1.compare(date2) <= 0;
}*/

/*
 * outputs:
 *   DateFormat:
 *     A: dd/mm/yy (default)
 *     B: dd-Mmm-yy
 *     C: yyyy-mm-dd
 *
 *   TimeFormat:
 *        mm:hh:ss
 *
 *   OutputFormat:
 *     DateTime:     date time (default)
 *     DatePlusTime: date+time
 *     DateOnly:     date
 *     TimeOnly:     time
 */
QString DateConverter::outputDate() const {
    QString date;
    QString dd(QString("%1").arg(day(), 4, 10, QChar('0')));// = toString(day(), 2, '0');
    QString mm(QString("%1").arg(month(), 4, 10, QChar('0')));// = toString(month(), 2, '0');
    QString yyyy(QString("%1").arg(year(), 4));// = toString(year(), 4);
    if (dateFormat == DateConverter::A) {       // format: mm/dd/yyyy
        date = QString(QString("%1/%2/%3").arg(mm, dd, yyyy));
    } else if (dateFormat == DateConverter::B) {// format: mm/dd/yy
        QStringRef yy(&yyyy, 2, 2);
        date = QString(QString("%1/%2/%3").arg(mm, dd, yy.toString()));
    } else {                                      // format: yyyy-mm-dd
        date = QString(QString("%1-%2-%3").arg(yyyy, mm, dd));
    }
    return QString(date);
}

QString DateConverter::outputTime() const {
    QString hr(QString("%1").arg(hour(), 2, 10, QChar('0')));// = toString(hour(), 2, '0');
    QString mn(QString("%1").arg(minutes(), 2, 10, QChar('0')));// = toString(minutes(), 2, '0');
    QString sc(QString("%1").arg(sec(), 2, 10, QChar('0')));// = toString(sec(), 2, '0');
    QString time(QString("%1:%2:%3").arg(hr, mn, sc)); // always this format hh:mm:ss
    return QString(time);
}

QString DateConverter::output() const {
    QString date(outputDate());
    QString time(outputTime());
    QString out;

    switch (outFormat) {
        case DateConverter::DatePlusTime: // "dateStr+timeStr"
            out = QString(date + "+" + time);
            break;
        case DateConverter::DateOnly:     // "dateStr"
            out = QString(date);
            break;
        case DateConverter::TimeOnly:     // "timeStr"
            out = QString(time);
            break;
        default:                          // "dateStr timeStr"
            out = QString(date + " " + time);
            break;
    }
    return QString(out);
}

/*ostream& operator<<(ostream &ostrm, const DateConverter &d) {
    QString out(d.output());
    ostrm << out.toStdString();

    return ostrm;
}*/

istream& operator >>(istream &is, DateConverter &d) {
    string s;
    QString str;
    is >> s;
    str = QString(s.data());


    if (DateConverter::isTime(str))
        d.setTime(str);
    else
        d.setDate(str);

    return is;
}

//}
