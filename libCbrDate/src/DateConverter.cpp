/* 
 * DateConverter.cpp
 */

#include <string>
#include <list>
#include <iostream>
#include <cmath>
#include <time.h>
#include <QStringList>

#include <ArrayDefs.h>
#include <StringTok.h>
#include <StringUtil.h>
#include <StringManip.h>
#include <StringTok.h>

#include "DateConverter.h"

using namespace std;

namespace cbr {
    
#define IGREG (15+31L*(10+12L*1582))
const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
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
//    __time64_t long_time;
//    _time64(&long_time);
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

DateConverter::DateConverter(const string& date, const string& time) {
    dateFormat = (A);
    outFormat = (DateTime);
    reset(date.c_str(), time.c_str());
}

DateConverter::DateConverter(const string& datetime) {
    dateFormat = (A);
    outFormat = (DateTime);
    // tokenize the data
    QStringList toks;
    QString dtstr(datetime.data());
//    vector<string> toks;
    stringTok(toks, dtstr, " ");
    if (toks.size() == 2)
        reset (toks.at(0).toStdString().data(), toks.at(1).toStdString().data());
//        reset(toks[0].c_str(), toks[1].c_str());
	else if (datetime.length() == 8) { // yyyymmdd
		stringstream ss;
		ss << datetime.substr(0, 4) << "-" << datetime.substr(4, 2) << "-" << datetime.substr(6, 2);
		string date = ss.str();
		reset(date.c_str());
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
bool DateConverter::setDate(const string& date) {
    int year;
    int month;
    int day;

    if (!parseDate(date.c_str(), &year, &month, &day))
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
bool DateConverter::setTime(const string& time) {
    int hr;
    int min;
    int sec;

    if (!parseTime(time.c_str(), &hr, &min, &sec))
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
void DateConverter::reset(const char *date, const char *time) {
    int yr, mo, day;
    int hr, min, sec;

    parseDate(date, &yr, &mo, &day);
    jd_ = julianDay(yr, mo, day);
    if (!time)
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

    jd = (int) (365.25 * jy) + (int) (30.6001 * jm) + day + 1720995;
    if (day + 31L * (month + 12L * year) >= IGREG) {
        ja = (int) (0.01 * jy);
        jd += 2 - ja + (int) (0.25 * ja);
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
        jalpha = (long) (((float) (jul - 1867216) - 0.25) / 36524.25);
        ja = jul + 1 + jalpha - (long) (0.25 * jalpha);
    }

    jb = ja + 1524;
    jc = (long) (6680.0 + ((float) (jb - 2439870) - 122.1) / 365.25);
    jd = (long) (365 * jc + (0.25 * jc));
    je = (long) ((jb - jd) / 30.6001);
    *day = jb - jd - (int) (30.6001 * je);
    *month = je - 1;
    if (*month > 12) * month -= 12;
    *year = jc - 4715;
    if (*month > 2) --(*year);
    if (*year <= 0) --(*year);
}

void DateConverter::calendarTime(int *h, int *m, int *s) const {
    if (time_ == 0)
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
bool DateConverter::parseDate1(const char *d, int *year, int *month, int *day) {
    QString cm;
    QString cd;
    QString cy;
    *year = *month = *day = 0;

    QStringList toks;
    QString dee(d);
//    cbr::StringVector toks;
    stringTok(toks, dee, "-");
    if (toks.size() != 3)
        return false;
    else {
        cd = toks[ 0 ];
        cm = toks[ 1 ];
        cy = toks[ 2 ];

        *day = cd.toInt();//atoi(cd.c_str());
        *year = cy.toInt();//atoi(cy.c_str());

        /* good until 2080! */
        if (cy.length() == 2) {
            if (*year > Year2k)
                *year += 1900;
            else
                *year += 2000;
        }

        cm = cm.toLower();//toLower(cm);

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
            return false;
    }

    return true;
}

/* date of format yyyy.mm.dd */
bool DateConverter::parseDate2(const char *d, int *year, int *month, int *day) {
    QString cm;
    QString cd;
    QString cy;
    *year = *month = *day = 0;

    QStringList toks;
    QString dee(d);
//    cbr::StringVector toks;
    stringTok(toks, dee, ".");
    if (toks.size() != 3)
        return false;
    else {
        cy = toks[ 0 ];
        cm = toks[ 1 ];
        cd = toks[ 2 ];

        *year = cy.toInt();//atoi(cy.c_str());
        *month = cm.toInt();//atoi(cm.c_str());
        *day = cd.toInt();//atoi(cd.c_str());
    }

    return true;
}

/* date of format m/d/y with month and day being either 1 or 2 digits, and year begin 2 or 4 */
bool DateConverter::parseDate3(const char *d, int *year, int *month, int *day) {
    QString cm;
    QString cd;
    QString cy;
    *year = *month = *day = 0;

    QStringList toks;
    QString dee(d);
//    cbr::StringVector toks;
    stringTok(toks, dee, "/");
    if (toks.size() != 3)
        return false;
    else {
        cm = toks[ 0 ];
        cd = toks[ 1 ];
        cy = toks[ 2 ];

        *year = cy.toInt();//atoi(cy.c_str());
        *month = cm.toInt();//atoi(cm.c_str());
        *day = cd.toInt();//atoi(cd.c_str());

        /* good until 2080! */
        if (cy.length() == 2) {
            if (*year > Year2k)
                *year += 1900;
            else
                *year += 2000;
        }
    }

    return true;
}

/* date of format yyyy-mm-dd */
bool DateConverter::parseDate4(const char *d, int *year, int *month, int *day) {
    *year = *month = *day = 0;

    QStringList toks;
    QString dee(d);
//    cbr::StringVector toks;
    stringTok(toks, dee, "-");
    if (toks.size() != 3)
        return false;
    else {
        *year = toks[0].toInt();//fromString<int>(toks[0]);
        *month = toks[1].toInt();//fromString<int>(toks[1]);
        *day = toks[2].toInt();//fromString<int>(toks[2]);

        return true;
    }
}

/* date of format yyyymmdd */
bool DateConverter::parseDate5(const char *d, int *year, int *month, int *day) {

    *year = *month = *day = 0;

    if (strlen(d) != 8)
        return false;
    else {
        string date(d);
        string cy = date.substr(0, 4);
        string cm = date.substr(4, 2);
        string cd = date.substr(6, 2);

        *year = atoi(cy.c_str());
        *month = atoi(cm.c_str());
        *day = atoi(cd.c_str());

        /* good until 2080! */
        if (cy.length() == 2) {
            if (*year > Year2k)
                *year += 1900;
            else
                *year += 2000;
        }
    }

    return true;
}

/* Parses thre types of dates: mm-ddd-yyyy, yyyy.mm.dd,  and
mm/dd/yy. It distinguishes between the two by
searching for the '-',  '.', or '/' character */
bool DateConverter::parseDate(const char *date, int *year, int *month, int *day) {
    if (strchr(date, '-')) {
        string sdate(date);
        if (sdate.find_first_of('-') == 4) /* if date is in form 1997-04-30 */
            return parseDate4(date, year, month, day);
        else /* if date is in form 30-apr-1997 */
            return parseDate1(date, year, month, day);
    } else if (strchr(date, '.'))
        return parseDate2(date, year, month, day);
    else if (strchr(date, '/'))
        return parseDate3(date, year, month, day);
    else
        return parseDate5(date, year, month, day);
}

/*
 * Simple check to distinguish a valid time string from a valid date
 * string. Return true if the string contains the colon (":") character.
 */
bool DateConverter::isTime(const string& s) {
    return s.find(':') != string::npos;
}

/* time of format h:m:s */
bool DateConverter::parseTime(const char *t, int *hr, int *min, int *sec) {
    *hr = *min = *sec = 0;

//    string time(t);
    QStringList toks;
    QString time(t);
//    vector<string> toks;
    stringTok(toks, time, ":");

    if (toks.size() == 0)
        return false;

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

    return true;
}

int DateConverter::compare(const DateConverter& date) const {
    if (getTime() > date.getTime())
        return 1;
    else if (getTime() == date.getTime())
        return 0;
    else
        return -1;
}


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
}

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
ostream& operator<<(ostream &ostrm, const DateConverter &d) {
    stringstream date;
    date << setfill('0');

    if (d.dateFormat == DateConverter::A) {
        date << setw(2) << d.month() << "/" << setw(2) << d.day() << "/" << d.year();
    } else if (d.dateFormat == DateConverter::B) {
        string sy = toString<int>(d.year()).substr(2);
        date << setw(2) << d.day() << "-" << months[d.month() - 1] << "-" << sy;
    } else {
        date << d.year() << "-" << setw(2) << d.month() << "-" << setw(2) << d.day();
    }

    stringstream time;
    time << setfill('0');
    time << setw(2) << d.hour() << ":" << setw(2) << d.minutes() << ":" << setw(2) << d.sec();


    switch (d.outFormat) {
        case DateConverter::DatePlusTime:
            ostrm << date.str() << "+" << time.str();
            break;
        case DateConverter::DateOnly:
            ostrm << date.str();
            break;
        case DateConverter::TimeOnly:
            ostrm << time.str();
            break;
        default: // DateTime
            ostrm << date.str() << " " << time.str();
            break;
    }

    return ostrm;
}

istream& operator >>(istream &is, DateConverter &d) {
    string s;
    is >> s;


    if (DateConverter::isTime(s))
        d.setTime(s);
    else
        d.setDate(s);

    return is;
}

}
