/*
 * Code.cpp
 */

#include <stdlib.h>

#include "Code.h"
#include "CbrPit.h"

using namespace std;
using namespace cbr;

Code::~Code() {
    for ( int i = 0; i < ranges.size(); i++ )
        delete ranges[ i ];
    ranges.clear();
}

void Code::addRange (Range* range) {
    ranges.push_back (range);
}

void Code::addException (Exception* ex) {
    exceptions.push_back (ex);
}


/*
 * This return the outcome for the detector given either as
 * the detector name or as one of the coils associated with
 * the detector.
 */
CbrPit::Outcome Code::getOutcome (const QString detector, double jd) const {
    CbrPit::Outcome oc = CbrPit::Invalid;
    const Detector* det = getDetector (detector, jd);
    if (allReturned) {
        oc = CbrPit::Returned;
    } else if (det) {
        oc = det->getOutcome();
    } else (
        oc = CbrPit::Invalid;
    }
    return oc;
}

QStringList Code::getCoils (const QString detector, double jd) const
{
  QStringList coils; // this will be empty if we don't find a detector

  const Detector* det = getDetector (detector, jd);
  if (det)
    {
      QStringList c = det->getCoils();
      for (int i = 0; i < c.count(); i++)
          coils.prepend (c.at(i));
//      coils.insert (coils.begin(), c.begin(), c.end());
    }

  return coils;
}

const Range* Code::getRange (double jd) const
{
    Range *range = nullptr;
    for (int i = 0; i < ranges.size(); i++)
    {
        range = ranges[ i ];
        if (jd >= range->getJd1() && jd <= range->getJd2())
            break;
    }
    return range;
}

const QList<Exception *> Code::getExceptions (double jd) const
{
    QList<Exception*> matches;
    QList<Exception*>::const_iterator it_ex;
    for (it_ex = exceptions.begin(); it_ex != exceptions.end(); ++it_ex)
    {
        Exception* ex = *it_ex;

        if (jd >= ex->getJd1() && jd <= ex->getJd2())
          matches.push_back (ex);
    }

    return matches;
}


/*
 * Find the detector for the give coil and julian date. The coil can
 * be either a coil code or a detector name. The coil code is compare
 * both as a string, and as a converted integer (from hex)
 */
const Detector* Code::getDetector(const QString coil, double jd) const
{
    Exception* ex = nullptr;
    const Detector *detect = nullptr;
    const Detector *det = nullptr;
    // get any exceptions for the julian date
    QList<Exception*> exs = getExceptions (jd);

    // check the exceptions first
    QList<Exception*>::const_iterator it_ex;

    // check coils before detectors to
    // allow different outcomes for
    // different coils for the same detector
    for (it_ex = exs.begin(); it_ex != exs.end(); ++it_ex)
    {
        ex = *it_ex;
        det = ex->getDetector();

        if (det->isCoilMatch (coil)) {
            detect = det;
            break;
        }
    }
    if (detect == nullptr) {
    // now check for matches on the detector name
    for (it_ex = exs.begin(); it_ex != exs.end(); ++it_ex)
    {
        ex = *it_ex;
        det = ex->getDetector();

        if (det->isMatch (coil)) {
            detect = det;
            break;
        }
    }
    }

    // now check the normal ranges
    if (detect == nullptr) {
    const Range* range = getRange(jd);
    if (range != nullptr)
        detect = range->getDetector (coil);
    }
    }
    return detect;
}

/**
*/
ostream &operator <<( ostream &o, const Code &code ) {
    o << "code: " << code.name.toStdString() << endl;
    o << "{" << endl;
    int i;
    for ( i = 0; i < code.ranges.size(); i++ ) {
        Range* range = code.ranges[ i ];
        o << *range;
    }

    for ( i = 0; i < code.exceptions.size(); i++ ) {
        Exception* ex = code.exceptions[ i ];
        o << *ex;
    }
    o << "}" << endl;

    return o;
}
