/*
*/

#ifndef PPObs_h
#define PPObs_h

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <QString>

#include "PPData.h"


class PPObs : public PPData
{
public:
    enum ObsFields { PitCode=0, ObsSite, ObsTime, Coil1, NFields };

    PPObs();
    bool read(std::istream& is);
    bool read(QString &istr);
    bool parseColumnData();
    void write(std::ostream& os) const;

    const QString& getPitCode () const { return pitCode; }
    const QString& getObsSite () const { return obsSite; }
    double getTime() const { return time; }
    QString getCoil() const { return coil1; }

private:
    QString pitCode;
    QString obsSite;
    double time;
    QString coil1;
};


struct ppobs_sort_bydate : public std::binary_function<const PPObs&, const PPObs&, bool>
{
    bool operator() (const PPObs& o1, const PPObs& o2)
    {
        return o1.getTime() < o2.getTime();
    }
};

#endif
