#ifndef CjsReport_H
#define CjsReport_H

#include <iostream>
#include "ReportBuilder.h"

#include <QStringList>

class TaggingData;
class CjsEstimates;
class CjsReport
{
public:
    CjsReport(const TaggingData& data, const QList<CjsEstimates*>& cjs);
    void writeObject(std::ostream& os) const;
private:
    void insertPopulationName(int row, int pop) const;
    void insertValues(int row, int col, double val, double se) const;

    const TaggingData& data_;
    const QList<CjsEstimates*>& cjs_;
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
