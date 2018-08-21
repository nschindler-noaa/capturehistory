/*
*/

#include <string>
#include <sstream>

#include <DateConverter.h>

#include <gtest/gtest.h>

#include "DateConverterTest.h"

using std::string;
using std::stringstream;
using cbr::DateConverter;

DateConverterTest::DateConverterTest()
{
}
	
TEST_F(DateConverterTest, Constructor) 
{
	DateConverter dc1(2010, 5, 13);

	ASSERT_EQ(2010, dc1.year());
	ASSERT_EQ(5, dc1.month());
	ASSERT_EQ(13, dc1.day());
	ASSERT_EQ(2455329.5, dc1.jd());

	dc1.setTime(12, 0, 0);
	ASSERT_EQ(2455329.5, dc1.jd());
	ASSERT_EQ(2455330, dc1.getTime());

	
	DateConverter dc2(133, 2010);
	ASSERT_FALSE(dc1 == dc2);
	dc2.setTime(12, 0, 0);
	ASSERT_TRUE(dc1 == dc2);

	/*
	 * Lotek uses the Dublin julian dates which is the julian date beginning
	 * at noon prior to 1/1/1900, and is calculated like:
	 *   jd - 2415020
	 */
	DateConverter dc3(40309.5, DateConverter::Adj_Lotek);
	dc3.setTime(12, 0, 0);
	ASSERT_TRUE(dc1 == dc3);

	
	// string parsing tests
	DateConverter dc4("13-may-2010", "12:00:00");
	ASSERT_TRUE(dc1 == dc4);

	dc4.reset("2010-05-13", "12:00:00");
	ASSERT_TRUE(dc1 == dc4);

	dc4.reset("20100512", "12:00:00");
	ASSERT_FALSE(dc1 == dc4);

	dc4.reset("20100513", "12:00:00");
	ASSERT_TRUE(dc1 == dc4);

	DateConverter dc5(string("13-may-2010 12:00:00"));
	ASSERT_TRUE(dc1 == dc5);
}


TEST_F(DateConverterTest, Accessors) 
{
	DateConverter dc1("13-may-2010", "12:00:00");

	int year;
	int month;
	int day;
	dc1.calendarDate(&year, &month, &day);
	ASSERT_EQ(2010, year);
	ASSERT_EQ(5, month);
	ASSERT_EQ(13, day);

	int hour;
	int minute;
	int second;
	dc1.calendarTime(&hour, &minute, &second);
	ASSERT_EQ(12, hour);
	ASSERT_EQ(0, minute);
	ASSERT_EQ(0, second);

	ASSERT_EQ(133.5, dc1.timeOfYear());

	ASSERT_FALSE(DateConverter::isTime("13-may-2010"));
	ASSERT_FALSE(DateConverter::isTime("2010-05-13"));
	ASSERT_FALSE(DateConverter::isTime("20100513"));
	ASSERT_TRUE(DateConverter::isTime("12:00:00"));
}                                             


TEST_F(DateConverterTest, Output) 
{
	DateConverter dc1("13-may-2010", "12:05:05");
	stringstream ss;

	// output format A
	dc1.setDateFormat(DateConverter::A);

	dc1.setOutputFormat(DateConverter::DateTime);
	ss << dc1;
	ASSERT_EQ(string("05/13/2010 12:05:05"), ss.str());

	ss.str("");
	dc1.setOutputFormat(DateConverter::DatePlusTime);
	ss << dc1;
	ASSERT_EQ(string("05/13/2010+12:05:05"), ss.str());

	ss.str("");
	dc1.setOutputFormat(DateConverter::DateOnly);
	ss << dc1;
	ASSERT_EQ(string("05/13/2010"), ss.str());

	ss.str("");
	dc1.setOutputFormat(DateConverter::TimeOnly);
	ss << dc1;
	ASSERT_EQ(string("12:05:05"), ss.str());

	// output format B
	dc1.setDateFormat(DateConverter::B);
	ss.str("");
	dc1.setOutputFormat(DateConverter::DateTime);
	ss << dc1;
	ASSERT_EQ(string("13-May-10 12:05:05"), ss.str());

	// output format C
	dc1.setDateFormat(DateConverter::C);
	ss.str("");
	dc1.setOutputFormat(DateConverter::DateTime);
	ss << dc1;
	ASSERT_EQ(string("2010-05-13 12:05:05"), ss.str());



#if 0
	void setDateFormat( DateFormat format ) { dateFormat = format; }
	void setOutputFormat( OutputFormat format ) { outFormat = format; }
	friend std::ostream& operator <<( std::ostream &os, const DateConverter &d );
	friend std::istream& operator >>( std::istream &is, DateConverter &d );

#endif
}    