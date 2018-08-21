#include "CjsCaptureHistory.h"
using namespace std;

CjsCaptureHistory::CjsCaptureHistory(int numSites) : CaptureHistory(numSites),
captureHistory_(numSites + 1),
initialRelease_(0), lastCaptured_(0), removed_(0) {
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

string CjsCaptureHistory::label() const {
    string returnString;
    size_t num = static_cast<size_t>(captureHistory_.size()) - 1;
    for (size_t i = 1; i <= num; ++i)
    {
        if (captureHistory_[i])
        {
            if (removed_ == static_cast<int>(i))
                returnString += "2 ";
            else
                returnString += "1 ";
        } 
        else
            returnString += "0 ";
    }
    return returnString.substr(0, returnString.size() - 1);
}
