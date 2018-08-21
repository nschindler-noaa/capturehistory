#ifndef CjsUnformattedReport_H
#define CjsUnformattedReport_H
#include <iostream>

class CjsEstimates;
class TaggingData;
/** Write unformatted CJS estimates to output.  Write estimates in a way that can be read directly
by another program (e.g., S-Plus)
*/
class CjsUnformattedReport
{
public:
	CjsUnformattedReport(const TaggingData& data, const CjsEstimates& estimates);
	~CjsUnformattedReport() {}
	void writeObject(std::ostream& os) const;
private:
	unsigned int numPeriods_;
	const CjsEstimates& estimates_;
};

std::ostream& operator<<(std::ostream& os, const CjsUnformattedReport& report);

#endif