/*
 *
 */

#ifndef PPSequenceOutput_h
#define PPSequenceOutput_h

#include "PPFileOutput.h"

class PPSequenceOutput : public PPFileOutput
{
public:
	PPSequenceOutput() : PPFileOutput() {}
	virtual ~PPSequenceOutput() {}
	virtual void writeHeader (const SitesMask&) {}
	virtual void write (ObsSequence& seq, const SitesMask& mask) = 0;

};

#endif
