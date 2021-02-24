/*
 *
 */

#ifndef PPFileOutput_h
#define PPFileOutput_h

#include <iostream>
#include <fstream>

#include <QStringList>

class ObsSequence;
class SitesMask;

class PPFileOutput
{
public:
    PPFileOutput() : fw(15) {}
    virtual ~PPFileOutput();
    virtual void setPrefix (const QString prefix);
    virtual QString getFileName(const QString prefix) const = 0;
    virtual bool active() const { return true; }
    virtual void closeAndDelete ();
    void setFieldWidth(int rhs) { fw = rhs; }
    void close();

protected:
    std::ofstream ofs;
    QString prefix;
    int fw; // field width
};

#endif
