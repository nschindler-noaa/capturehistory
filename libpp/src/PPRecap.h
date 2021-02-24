/*
*/

#ifndef PPRecap_h
#define PPRecap_h

#include <string>
#include <iostream>

#include "PPData.h"

class PPRecap : public PPData
{
public:
    enum ObsFields { PitCode = 0, RecapTime, Site, RiverKM, NFields };

    PPRecap();

    bool read(std::istream& is);
    bool parseColumnData();
    void write(std::ostream& os) const;

    const QString& getPitCode () const { return pitCode; }
    double getTime() const { return recapTime; }
    const QString& getSite () const { return site; }
    const QString& getRiverKM () const { return riverkm; }
    bool validRiverkm() const;

private:
    QString pitCode;
    double recapTime;
    QString site;
    QString riverkm;
};


#endif
