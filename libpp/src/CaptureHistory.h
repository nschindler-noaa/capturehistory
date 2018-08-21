#ifndef CaptureHistory_H
#define CaptureHistory_H


/** \brief All CBR standard utilities. */
/**	Abstract base class for a capture history.
Specifies the minimum requirements for the Cormack-Jolly-Seber estimates, thus
allowing the estimation of the CJS parameters from any derived class.
*/
class CaptureHistory
{
public:
	CaptureHistory(int numSites) : numSites_(numSites) {}
	virtual ~CaptureHistory() {}
	virtual void capture(int i) = 0;
	virtual void remove(int i) = 0;
	virtual bool removed(int i) const = 0;		//!< Removed at site i?
	virtual bool captured(int i) const = 0;		//!< Captured (or detected) at site i?
	virtual int lastCaptured() const = 0;		//!< Site of last capture/detection
	virtual int released() const = 0;			//!< Site of initial release
	virtual std::string label() const = 0;
	unsigned int numSites() const {return numSites_;}
private:
	const int numSites_;
};
#endif
