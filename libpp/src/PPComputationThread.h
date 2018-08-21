/*
 * PPComputationThread.h
 */

#ifndef PPComputationThread_h 
#define PPComputationThread_h

#include <string>
#include <vector>
#include <utility>

#include "ComputationThread.h"
#include "PPOutputMaker.h"

class TextWindowImpl;

class PPComputationThread : public ComputationThread, public PPOutputMaker
{
    Q_OBJECT

public:
	PPComputationThread (QObject* p, const QString& name);
	virtual ~PPComputationThread();

	void compute();

	void setStatus( RunStatus runStatus );

	/* PPOutputMaker virtual methods */

	void setBytesExpected (int num);
	void setCurrentBytes (int num);
	void setNumSteps (int num);
	void setCurrentStep (int step);
	void setProgressMessage (const std::string& msg);
	void write (const std::string& msg, OutputType type = Message);

private:
	bool isCanceled;
	int getTotalBytes() const;
	int currentStep;
};

#endif // PPComputationThread_h
