/*
 * ComputationThread.cpp
 */
 

#include <math.h>

#include <qapplication.h>

#include "ComputationThread.h"
#include "ComputationEvent.h"

void ComputationThread::run() {
    setStatus(Running);
	current = 0;
	prevStep = 0;
	compute();
}

void ComputationThread::sendStatusMessage(const QString& msg) {
	ComputationEvent* ce = new ComputationEvent(ComputationEvent::Status, runName);
	ce->setMessage(msg);
	QApplication::postEvent(object, ce);
}

void ComputationThread::sendProgressMessage(const QString& msg) {
	ComputationEvent* ce = new ComputationEvent(ComputationEvent::Progress, runName);
	ce->setMessage(msg);
	QApplication::postEvent(object, ce);
}

void ComputationThread::sendErrorMessage(const QString& msg) {
	ComputationEvent* ce = new ComputationEvent(ComputationEvent::Error, runName);
	ce->setMessage(msg);
	QApplication::postEvent(object, ce);
}

void ComputationThread::sendCompletedSignal() {
	status = Ok;
	ComputationEvent* ce = new ComputationEvent(ComputationEvent::Completed, runName);
	QApplication::postEvent(object, ce);
}


void ComputationThread::sendCanceledSignal() {
	status = Cancel;
	ComputationEvent* ce = new ComputationEvent(ComputationEvent::Canceled, runName);
	QApplication::postEvent(object, ce);
}

void ComputationThread::sendNumSteps(int nmStps) {
	ComputationEvent* ce = new ComputationEvent(ComputationEvent::NumSteps, runName);
	ce->setNumSteps(nmStps);
	QApplication::postEvent(object, ce); 
	numSteps = nmStps;
	setStepSize();
}

void ComputationThread::sendCurrentStep(int step) {
	if (current == 0 || step >= numSteps) {
		try {
			ComputationEvent* ce = new ComputationEvent(ComputationEvent::CurrentStep, runName);
			ce->setCurrentStep(step);
			QApplication::postEvent(object, ce); 
		}
		catch (std::bad_alloc&)
		{
			// todo: something
		}
	}

	if (current < stepSize)
		++current;
	else
		current = 0;
}

void ComputationThread::setStepIncr(int incr) { 
	stepIncr = incr; 
	setStepSize();
}

void ComputationThread::setStepSize() {
	stepSize = (stepIncr >= numSteps) ? 1 : numSteps / stepIncr;
	current = 0;
	prevStep = 0;
}

