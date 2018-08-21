/*
* DateConverter.h
*
*/

#ifndef DateConverter_h
#define DateConverter_h

#include <iostream>
#include <string>



namespace cbr
{

class DateConverter
{
public:
	enum OutputFormat {DateTime, DatePlusTime, DateOnly, TimeOnly};
	enum DateFormat {A, B, C};
	enum Adjuster {Adj_None = 0, Adj_Lotek = 2415020 }; // julian days before 1/1/1900
    static DateConverter base;

    DateConverter(void);
	DateConverter( const DateConverter& date );
	DateConverter( double jd, Adjuster adj = Adj_None );
	DateConverter( int year, int month, int day );
	DateConverter( int doy, int year );
    DateConverter( const char *date, const char *time = 0 );
	DateConverter( const std::string& date, const std::string& time );
	DateConverter( const std::string& datetime);

	// mutator
	void jd( double jd ) { jd_ = jd; }
	bool setDate( const std::string& date );
	void setTime( int hr, int min, int sec );
	bool setTime( const std::string& time );
	static bool isTime( const std::string& s );

	// accessors/converters
	double jd() const { return jd_; }
	double getTime() const { return jd_ + time_; } 
	int dayOfYear();
	double timeOfYear();
	void calendarDate( int *y, int *m, int *d ) const;
	void calendarTime( int *h, int *m, int *s ) const;
	void reset( const char *date, const char *time = 0);
	void reset( double jd );

	// convenience methods
	int year() const;
	int month() const;
	int day() const;
	int hour() const;
	int minutes() const;
	int sec() const;

	int compare( const DateConverter& date ) const;
	friend bool operator > ( const DateConverter& date1, const DateConverter& date2 );
	friend bool operator < ( const DateConverter& date1, const DateConverter& date2 );
	friend bool operator == ( const DateConverter& date1, const DateConverter& date2 );
	friend bool operator >= ( const DateConverter& date1, const DateConverter& date2 );
	friend bool operator <= ( const DateConverter& date1, const DateConverter& date2 );

	// io methods
	void setDateFormat( DateFormat format ) { dateFormat = format; }
	void setOutputFormat( OutputFormat format ) { outFormat = format; }
	friend std::ostream& operator <<( std::ostream &os, const DateConverter &d );
	friend std::istream& operator >>( std::istream &is, DateConverter &d );

    // conversion methods
    double julianDay( int year, int month, int day ) const;
    double julianDay( int doy, int year );

private:
	double jd_;
	double time_;

	// parsing methods
	bool parseDate1( const char *d, int *year, int *month, int *day );
	bool parseDate2( const char *d, int *year, int *month, int *day );
	bool parseDate3( const char *d, int *year, int *month, int *day );
	bool parseDate4( const char *d, int *year, int *month, int *day );
	bool parseDate5( const char *d, int *year, int *month, int *day );
	bool parseDate( const char *d, int *year, int *month, int *day );
	bool parseTime( const char *t, int *hr, int *min, int *sec );

	// io vars
	DateFormat dateFormat;
	OutputFormat outFormat;

};

}

#endif

