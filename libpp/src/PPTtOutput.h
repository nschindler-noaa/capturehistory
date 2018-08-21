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
	std::string getFileName (const std::string& prefix) const;
	void writeHeader (const SitesMask& mask);
	void write (ObsSequence& seq, const SitesMask& mask);
	bool active() const;
};

#endif
