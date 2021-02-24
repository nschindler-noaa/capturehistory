/*
 *
 */

#ifndef PPSeqOutput_h
#define PPSeqOutput_h

#include <ArrayDefs.h>
#include <SitesMask.h>

#include "PPFileOutput.h"

class PPSeqOutput : public PPFileOutput
{
public:
    QString getFileName (const QString prefix) const;
    void writeHeader ();
    void write (ObsSequence& seq, const QString& type);
    bool active() const;
};

#endif
