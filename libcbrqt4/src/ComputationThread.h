/*
 * ComputationThread.h
 */

#ifndef ComputationThread_h
#define ComputationThread_h

#include <qthread.h>
#include <qobject.h>
#include <qwidget.h>


class ComputationThread : public QThread {
	Q_OBJECT

public:
	enum RunStatus { Ok, Error, Cancel };

	ComputationThread(QObject* object, const QString& name = "Run") : 
	  object(object), runName(name), status(Ok), stepSize(0),
		  stepIncr(100), numSteps(0), current(0), prevStep(0)
		   {}
	virtual ~ComputationThread() {}

	void run();

	bool isCanceled() const { return status == Cancel; }
	RunStatus getStatus() const { return status; }
	void setRunName(const QString& s) { runName = s; }
	const QString& getRunName() const { return runName; }
	void setStepIncr(int incr);

	virtual void setStatus(RunStatus runStatus) { status = runStatus; }
	virtual void sendStatusMessage(const QString& msg);
	virtual void sendProgressMessage(const QString& msg);
	virtual void sendErrorMessage(const QString& msg);
	virtual void sendCompletedSignal();
    virtual void sendCanceledSignal();
	virtual void sendNumSteps(int numSteps);
	virtual void sendCurrentStep(int step);


protected:
	QObject* object;
	QString runName;
	RunStatus status;
	int stepSize;
	int stepIncr;
	int numSteps;
	int current;
	int prevStep;

	virtual void compute() = 0;
	void setStepSize();

signals:
	void cancelEnabled(bool rhs);

};


#endif

