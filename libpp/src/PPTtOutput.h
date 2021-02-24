/*
 *
 */

#ifndef PPTtOutput_h
#define PPTtOutput_h

#include <string>

#include "PPSequenceOutput.h"

class PPTtOutput : public PPSequenceOutput
{
public:
    QString getFileName (const QString prefix) const;
    void writeHeader (const SitesMask& mask);
    void write (ObsSequence& seq, const SitesMask& mask, bool showAll = false);
    bool active() const;
};

#endif
