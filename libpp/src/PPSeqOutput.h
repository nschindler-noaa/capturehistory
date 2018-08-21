/*
 *
 */

#ifndef PPSeqOutput_h
#define PPSeqOutput_h

#include <string>
#include <ArrayDefs.h>
#include <SitesMask.h>

#include "PPFileOutput.h"

class PPSeqOutput : public PPFileOutput
{
public:
	std::string getFileName (const std::string& prefix) const;
	void writeHeader ();
	void write (ObsSequence& seq, const std::string& type);
	bool active() const;
};

#endif
