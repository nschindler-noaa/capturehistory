#ifndef Code_h
#define Code_h

//#include <vector>
//#include <string>

#include "CbrPit.h"
#include "Range.h"
#include "Exception.h"

#include <QStringList>

class Code
{
  public:
      Code(const QString& siteCode) : allReturned(false) { name = QString(siteCode); }
    ~Code();

    // insert the returned object at the end of the list,
    // returned rules defined earlier in the config file
    // have higher precedence
    void addRange(Range* oc);

    // insert the exception at the end of the list,
    // exceptions defined earlier in the config file
    // have higher precedence
    void addException(Exception* ex);

    void setAllReturned() { allReturned = true; }

    int entries() { return ranges.size(); }
    const QString getName() { return name; }
    cbr::CbrPit::Outcome getOutcome(const QString detector, double jd) const;
    QStringList getCoils(const QString detector, double jd) const;
    const Detector* getDetector(const QString coil, double jd) const;
    const Range* getRange(double jd) const;
    const QList<Exception*> getExceptions (double jd) const;

    friend std::ostream &operator <<(std::ostream &o, const Code &code);

private:
    QString name;
    QList<Range*> ranges;
    QList<Exception*> exceptions;
    bool allReturned;

};

#endif
