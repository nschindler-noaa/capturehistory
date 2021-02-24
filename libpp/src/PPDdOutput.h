/*
 *
 */

#ifndef PPDdOutput_h
#define PPDdOutput_h

//#include <string>
#include <QStringList>

#include "PPSequenceOutput.h"

class PPDdOutput : public PPSequenceOutput
{
public:
    QString getFileName (const QString prefix) const;
    void writeHeader (const SitesMask& mask);
    void write (ObsSequence& seq, const SitesMask& mask, bool showAll);
    bool active() const;
};

#endif
