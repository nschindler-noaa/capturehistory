/*
*/

#ifndef PPTag_h
#define PPTag_h

#include <iostream>
#include <sstream>
#include <string>


#include "PPData.h"

class PPTag : public PPData
{
public:
    enum TagFields {TagGroup=0, PitCode, RelTime, RelSite, Species, Run, RearType, ICov1, NFields };

    PPTag();
    bool read(std::istream& is);
    bool parseColumnData();
    void write(std::ostream& os) const;

    const QString& getPitCode () const { return pitCode; }
    const QString& getRelSite() const { return relSite; }
    char getSpecies () const { return species; }
    char getRun () const { return run; }
    char getRearType () const { return rear_type; }
    short getLength () const;
    const QString& getICov(int i) const;
    const QStringList& getICovs() const { return icovs; }
    int numICovs() const;
    double getRelTime() const { return relTime; }
    const QString& getTagGroup() const { return tagGroup; } // only used for data converter

    void setRelTime( double time ) { relTime = time; }

private:
    QString pitCode;
    QString relSite;
    double relTime;
    char species;
    char run;
    char rear_type;
    QStringList icovs;
    bool missingIcov;

    short length;

    QString tagGroup; // not normally used, for use in data converter

    virtual void resetColumnOrder();

};


#endif
