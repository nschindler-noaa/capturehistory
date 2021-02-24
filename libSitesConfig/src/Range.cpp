/**
 *  Range.cpp
*/

#include <string.h>

#include <StringTok.h>
#include <StringUtil.h>
#include <QStringList>

#include "ArrayDefs.h"
#include "DateConverter.h"
#include "Range.h"

using std::vector;
using std::string;
using std::ostream;
using std::endl;
using std::cout;

using namespace cbr;

const double Range::presentJd = 100000000;

// dates are in one of two formats: a format
// that doesn't include the time ( dd-Mmm-yy )
// or ones that do ( dd-Mmm-yy+hh:mm:ss )
Range::Range(const QString &d1, const QString &d2) {
    string date1;
    string date2;
    string time1;
    string time2;

    QStringList d1Toks;
    QStringList d2Toks;
//    StringVector d1Toks;
//    StringVector d2Toks;
    stringTok(d1Toks, d1, "+");
    stringTok(d2Toks, d2, "+");

    if (d1Toks.size() > 0 && d2Toks.size() > 0) {
        date1 = d1Toks[0].toStdString();
        date2 = d2Toks[0].toStdString();

        if (d1Toks.size() == 2)
            time1 = d1Toks[1].toStdString();
        else
            time1 = "00:00:00";

        DateConverter dc(date1.c_str(), time1.c_str());
        jd1 = dc.getTime();

        QString lowerDate2 = QString(date2.data()).toLower();
        if (!lowerDate2.compare("present")) {
            jd2 = presentJd;
        }
        else {
            if (d2Toks.size() == 2)
                time2 = d2Toks[1].toStdString();
            else
                time2 = "23:59:50";

            dc.reset(date2.c_str(), time2.c_str());
            jd2 = dc.getTime();
        }
    }
}

QString Range::getDetectorString(int i) const {
//    const Detector& det = detectors[i];
//    QString detString = det.getDetectorName();
//    return detString.toStdString().c_str();
    return detectors[i].getDetectorName();
 }

/*
 * Return the outcome for the target detector. The target detector can
 * be either the detector name or the string representing on of the
 * associated coils.
 */
CbrPit::Outcome Range::getOutcome(const QString targetDetector) const {
    for (int i = 0; i < detectors.size(); i++) {
        const Detector& detector = detectors[i];
        if (detector.isMatch(targetDetector))
            return detector.getOutcome();
    }
    return CbrPit::Invalid;
}

void Range::addDetector(const Detector& det) {
  detectors.push_back(det);
}

/*
 * Return the coils for the given detector name
 */
QStringList Range::getCoils(const QString targetDetector) const {
  QStringList coils;
  for (int i = 0; i < detectors.size(); i++) {
    const Detector& detector = detectors[i];
    if (detector.isMatch( targetDetector)) {
      QStringList c = detector.getCoils();
      coils = QStringList(c);//.insert( coils.begin(), c.begin(), c.end() );
    }
  }
  return coils;
}

/*
 * Get the detector for the target. In this case the coil can
 * be either the code for a particular coil or a detector name
 */
const Detector* Range::getDetector(const QString coil) const {
    const Detector *detector = nullptr;
    for (int i = 0; i < detectors.size(); i++) {
        detector = &detectors[i];
        if (detector->isMatch(coil))
            break;
    }
    return detector;
}

/*
 */
ostream& operator <<(ostream& os, const Range& range) {
    DateConverter dc1(range.jd1);
    dc1.setDateFormat(DateConverter::B);
    dc1.setOutputFormat(DateConverter::DateOnly);

    os << "  range: " << dc1 << " ";
    if (range.jd2 == Range::presentJd)
        os << "Present";
    else {
        DateConverter dc2(static_cast<int>(range.jd2));
        dc2.setDateFormat(DateConverter::B);
        dc2.setOutputFormat(DateConverter::DateOnly);
        os << dc2;
    }
    os << endl;
    os << "  {" << endl;
    for (int i = 0; i < range.detectors.size(); i++) {
        const Detector& det = range.detectors[i];
        os << "    " << det << endl;
    }
    os << "  }" << endl;

    return os;
}
