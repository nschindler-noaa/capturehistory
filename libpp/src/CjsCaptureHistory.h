#ifndef CjsCaptureHistory_H
#define CjsCaptureHistory_H

#include <vector>
#include <string>
#include "CaptureHistory.h"

#include <QStringList>

/*! Basic capture history for generating the Cormack-Jolly-Seber estimates.

Provides the minimal requirements for the CJsStatistics and CJS template classes.
*/
class CjsCaptureHistory : public CaptureHistory
{
public:
    CjsCaptureHistory(int numSites);
    ~CjsCaptureHistory() {}
    void capture(int i);	//!< Set status to "captured" at site i (i = 1,...,numSites).
    void remove(int i);		//!< Set status to "removed" (censored) at site i (i = 2,...,numSites)
    int lastCaptured() const {return lastCaptured_;}	//!< Returns site of last capture
    bool captured(int i) const { return captureHistory_[i];} //!< Indicates if captured at site i
    bool removed(int i) const {return removed_ == i;}	//!< Indicates if removed at site i
    QString label() const;		//!< Returns a string representation of the capture history.
    int released() const {return initialRelease_;}
private:
    QList<bool> captureHistory_;
    int initialRelease_;
    int lastCaptured_;
    int removed_;
};

#endif

