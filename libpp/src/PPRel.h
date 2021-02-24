/*
*
*/

#ifndef PPRel_h
#define PPRel_h

#include <iostream>
#include <sstream>
#include <string>
#include <QString>

#include "PPData.h"

class PPRel : public PPData
{
public:
    enum RelFields {Key = 0, Date, Time, NFields };

    PPRel();
    bool read(std::istream& is);
    bool parseColumnData();
    void write(std::ostream& os) const;

    QString getKey() const { return key; }
    double getReleaseTime() const { return time; }

private:
    QString key;
    double time;

};

class PPRelEql
{
public:
    PPRelEql (const QString& s) : key(s) {}
    void setKey(const QString& s) { key = s; }
    bool operator() (const PPRel& rel)
    {
        return key.compare (rel.getKey()) == 0;
    }
private:
    QString key;
};



#endif
