/*
* DateConverter.h
*
*/

#ifndef DateConverter_h
#define DateConverter_h

#include <iostream>
#include <string>

#include <QString>

namespace cbr
{

class DateConverter
{
public:
    enum OutputFormat {
        DateTime,     // format: date time
        DatePlusTime, // format: date+time
        DateOnly,     // format: date
        TimeOnly      // format: time (hh:mm:ss)
    };
    enum DateFormat {
        A, // format: mm/dd/yyyy
        B, // format: dd-mm-yy
        C  // format: yyyy-mm-dd
    };
    enum Adjuster { // julian days before 1/1/1900
        Adj_None = 0,
        Adj_Lotek = 2415020
    };
    static DateConverter base;

    // constructors
    DateConverter (void);
    DateConverter (const DateConverter& date);
    DateConverter (double jd, Adjuster adj = Adj_None);
    DateConverter (int year, int month, int day);
    DateConverter (int doy, int year);
    DateConverter (const char *date, const char *time = nullptr);
    DateConverter (const QString &date, const QString &time);
    DateConverter (const QString& datetime);

    // mutator
    void jd (double jd) { jd_ = jd; }
    bool setDate (const QString &date);
    void setTime (int hr, int min, int sec);
    bool setTime (const QString& time);
    static bool isTime (const QString& s);

    // accessors/converters
    double jd () const { return jd_; }
    double getTime () const { return jd_ + time_; }
    int dayOfYear ();
    double timeOfYear ();
    void calendarDate (int *y, int *m, int *d) const;
    void calendarTime (int *h, int *m, int *s) const;
    void reset (const QString date, const QString time = QString(""));
    void reset (double jd);

    // convenience methods
    int year () const;
    int month () const;
    int monthToInt (const QString &strmon) const;// takes 3 char name and returns number
    const QString monthToString (int num) const; // takes number and returns 3 char month name
    int day () const;
    int hour () const;
    int minutes () const;
    int sec () const;

    int compare (const DateConverter& date) const;
    friend bool operator > (const DateConverter& date1, const DateConverter& date2)
    { return date1.compare(date2) > 0;}
    friend bool operator < (const DateConverter& date1, const DateConverter& date2)
    { return date1.compare(date2) < 0;}
    friend bool operator == (const DateConverter& date1, const DateConverter& date2)
    { return date1.compare(date2) == 0;}
    friend bool operator >= (const DateConverter& date1, const DateConverter& date2)
    { return date1.compare(date2) >= 0;}
    friend bool operator <= (const DateConverter& date1, const DateConverter& date2)
    { return date1.compare(date2) <= 0;}

    // io methods
    void setDateFormat (DateFormat format) { dateFormat = format; }
    void setOutputFormat (OutputFormat format) { outFormat = format; }
    QString outputDate() const;
    QString outputTime() const;
    QString output() const;
    friend std::ostream& operator << (std::ostream &os, const DateConverter &d){
        QString out(d.output()); os << out.toStdString(); return os; }
    friend std::istream& operator >> (std::istream &is, DateConverter &d);

    // conversion methods
    double julianDay (int year, int month, int day) const;
    double julianDay (int doy, int year);

private:
    double jd_;
    double time_;

    // parsing methods
    bool parseDate1 (const QString d, int *year, int *month, int *day);
    bool parseDate2 (const QString d, int *year, int *month, int *day);
    bool parseDate3 (const QString d, int *year, int *month, int *day);
    bool parseDate4 (const QString d, int *year, int *month, int *day);
    bool parseDate5 (const QString d, int *year, int *month, int *day);
    bool parseDate (const QString d, int *year, int *month, int *day);
    bool parseTime (const QString t, int *hr, int *min, int *sec);
    bool parseStrings (const QString y, const QString m, const QString d, int *year, int *month, int *day);

    // io vars
    DateFormat dateFormat;
    OutputFormat outFormat;

};

}

#endif

