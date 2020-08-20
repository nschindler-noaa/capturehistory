/*
 *
 */

#ifndef PPDdOutput_h
#define PPDdOutput_h

#include <string>

#include "PPSequenceOutput.h"

class PPDdOutput : public PPSequenceOutput
{
public:
	std::string getFileName (const std::string& prefix) const;
	void writeHeader (const SitesMask& mask);
    void write (ObsSequence& seq, const SitesMask& mask, bool showAll);
	bool active() const;
};

#endif
