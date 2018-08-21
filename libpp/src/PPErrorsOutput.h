/*
 *
 */

#ifndef PPErrorsOutput_h
#define PPErrorsOutput_h

#include <string>

#include "PPFileOutput.h"

class PPErrors;

class PPErrorsOutput : public PPFileOutput
{
public:
	std::string getFileName (const std::string& prefix) const;
	void writeHeader ();
	void write (const PPErrors& errors);
	bool active() const;
};

#endif
