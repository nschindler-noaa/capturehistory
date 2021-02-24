/*
 *
 */

#ifndef PPBatchOutputMaker_h
#define PPBatchOutputMaker_h

#include <QString>
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

    void write (const QString& msg, OutputType type = Message);

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
