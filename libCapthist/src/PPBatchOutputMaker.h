/*
 *
 */

#ifndef PPBatchOutputMaker_h
#define PPBatchOutputMaker_h

#include <string>
#include <iostream>

#include "PPOutputMaker.h"
#include <PitProSettings.h>

class PPBatchOutputMaker : public PPOutputMaker
{
public:
	static PPBatchOutputMaker& getInstance()
	{
		static PPBatchOutputMaker out;
		return out;
	}

	~PPBatchOutputMaker() {}

	void write (const std::string& msg, OutputType type = Message)
	{
        PitProSettings& settings = PitProSettings::getInstance();
        if (type != PPOutputMaker::Warning || settings.isChecked(PitProSettings::Warnings))
		    std::cerr << ppFormat(msg, type);
	}

#if 0
	void setCurrentStep(int num) 
	  {
	    PPOutputMaker::setCurrentStep (num);
	    std::cerr << "\f" << currentStep << "/" << numSteps << endl;
	  }
#endif


private:
	PPBatchOutputMaker() : PPOutputMaker() {}

};

#endif
