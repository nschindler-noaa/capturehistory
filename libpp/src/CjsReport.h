#ifndef CjsReport_H
#define CjsReport_H

#include <iostream>
#include <vector>
#include "ReportBuilder.h"

class TaggingData;
class CjsEstimates;
class CjsReport
{
public:
	CjsReport(const TaggingData& data, const std::vector<CjsEstimates*>& cjs);
	void writeObject(std::ostream& os) const;
private:
	void insertPopulationName(int row, int pop) const;
	void insertValues(int row, int col, double val, double se) const;

	const TaggingData& data_;
	const std::vector<CjsEstimates*>& cjs_;
	mutable ReportBuilder RB_;
	const int populationColumn_;
	const int populationColumnWidth_;
	const int precision_;
	const int columnWidth_;
	const int columnSpacing_;
	const int dataStartColumn_;
	const int overallColumn_;
};

std::ostream& operator<<(std::ostream& os, const CjsReport& report);

#endif
