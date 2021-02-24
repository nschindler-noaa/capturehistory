#include "CjsCaptureHistory.h"
using namespace std;

CjsCaptureHistory::CjsCaptureHistory(int numSites) : CaptureHistory(numSites),
initialRelease_(0), lastCaptured_(0), removed_(0) {
    for (int i = 0; i <= numSites; i++)
        captureHistory_.append(false);
}

void CjsCaptureHistory::capture(int i) {
    captureHistory_[i] = true;
    if (i > lastCaptured_)
        lastCaptured_ = i;
    if (initialRelease_ == 0)
        initialRelease_ = i;
}

void CjsCaptureHistory::remove(int i) {
    captureHistory_[i] = true;
    lastCaptured_ = i;
    removed_ = i;
}

QString CjsCaptureHistory::label() const {
    QString returnString;
    size_t num = static_cast<size_t>(captureHistory_.size()) - 1;
    for (size_t i = 1; i <= num; ++i)
    {
        if (captureHistory_[i])
        {
            if (removed_ == static_cast<int>(i))
                returnString.append("2 ");
            else
                returnString.append("1 ");
        }
        else
            returnString.append("0 ");
    }
    returnString.chop(1);
    return returnString;
}
