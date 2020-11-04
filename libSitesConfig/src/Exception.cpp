/*
 * Exception
 *
 * Exceptions to the rule. These are times when the usual dam ops
 * is changed so that the configuration provided by the standard
 * site configuration is temporarily incorrect.
 *
 */

#include <string.h>
#include <QStringList>

#include <StringTok.h>
#include <StringUtil.h>

#include <ArrayDefs.h>
#include <DateConverter.h>

#include "Exception.h"

using std::vector;
using std::string;
using std::ostream;
using std::endl;


using namespace cbr;

const double Exception::presentJd = 100000000;

// dates are in one of two formats: a format
// that doesn't include the time ( yyyy.mm.dd )
// or ones that do ( yyyy.mm.dd+hh:mm:ss )
Exception::Exception( const QString& d1, const QString& d2, const Detector& d ) : det( d ) {
    QString date1;
    QString date2;
    QString time1;
    QString time2;

    QStringList d1Toks;
    QStringList d2Toks;
//    StringVector d1Toks;
//    StringVector d2Toks;
    stringTok( d1Toks, d1, "+" );
    stringTok( d2Toks, d2, "+" );

    if ( d1Toks.size() > 0 && d2Toks.size() > 0 ) {
        date1 = d1Toks[ 0 ];
        date2 = d2Toks[ 0 ];

        if ( d1Toks.size() == 2 ) 
            time1 = d1Toks[ 1 ];
        else
            time1 = "00:00:00";

        const std::string date = date1.toStdString();
        const std::string time = time1.toStdString();
//        DateConverter dc();
        DateConverter dc (date.c_str(), time.c_str());
//        dc.reset(date.c_str(), time.c_str());
        jd1 = dc.getTime();
    
        QString lowerDate2 = date2;
        lowerDate2 = lowerDate2.toLower();//( lowerDate2 );
        if (lowerDate2.contains(QString("present"))) {// !lowerDate2.compare( 0, 7, "present" ) ) {
            jd2 = presentJd;
        }
        else {
            if ( d2Toks.size() == 2 ) 
                time2 = d2Toks[ 1 ];
            else
                time2 = "00:00:00";

            dc.reset(date2.toUtf8().data(), time2.toUtf8().data());// date2.c_str(), time2.c_str() );
            jd2 = dc.getTime();
        }
    }
}

/*
 */
const char *Exception::getDetectorString() const { 
    string detString = det.getDetectorName();
    return detString.c_str();
 }

/*
 */
CbrPit::Outcome Exception::getOutcome() const {
    return det.getOutcome();
}

/*
 */
const StringVector& Exception::getCoils() const {
    return det.getCoils();
}

/*
 */
ostream& operator <<( ostream& os, const Exception& ex ) {
    DateConverter dc1 (ex.jd1);
    dc1.setDateFormat( DateConverter::B );
    dc1.setOutputFormat( DateConverter::DatePlusTime );
    os << "  exception: " << dc1 << " ";
    if ( ex.jd2 == Exception::presentJd ) 
        os << "Present";
    else {
        DateConverter dc2 (ex.jd2);
        dc2.setDateFormat( DateConverter::B );
        dc2.setOutputFormat( DateConverter::DatePlusTime );
        os << dc2;
    }
    os << "  { " << ex.det << " }" << endl;

    return os;
}
