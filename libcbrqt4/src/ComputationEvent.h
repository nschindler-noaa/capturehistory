/*
 * ComputationEvent.h
 */

#ifndef ComputationEvent_h
#define ComputationEvent_h

#include <qevent.h>


class ComputationEvent : public QEvent {

private:
	QString message;
	QString runName;
	int numSteps;
	int step;
public:
	enum Type { Completed = QEvent::User + 1, Error, Status,
		Progress, NumSteps, CurrentStep, Canceled };

	ComputationEvent(Type type, const QString& name) :
	QEvent(static_cast<QEvent::Type>(type)), runName(name)
		{}

	const QString& getRunName() const { return runName; }

	void setMessage(const QString& msg) { message = msg; }
	const QString& getMessage() const { return message; }

	void setNumSteps(int nmStps) { numSteps = nmStps; }
	int getNumSteps() const { return numSteps; }

	void setCurrentStep(int stp) { step = stp; }
	int getCurrentStep() const { return step; }


};

#endif
