#ifndef RangeLineEditMgr_h
#define RangeLineEditMgr_h

#include <QString>
#include <QList>

#include "RangeLineEdit.h"

class RangeLineEditMgr 
{
public:
	RangeLineEditMgr();

	void addLineEdit(RangeLineEdit *edit);

	const QString &getRangePar() const { return rangePar_; }
	RangeLineEdit::EditType getRangeType() const { return rangeType_; }
	double getRangeMin() const { return rangeMin_; }
	double getRangeMax() const { return rangeMax_; }
	QString getRangeString(int format = 'g', int precision = 6) const;
	int getNumSteps() const;
    double getRangeValue(int i) const; // return the value of the ith value
	bool hasRangeDefined() const { return rangePar_ != QString::null; }
	QList<double> getRangeValues() const;

	void parseRange(const QString &s, const QString &name, RangeLineEdit::EditType type);

	bool isRangePar(const QString& par) const;
	void setRangePar(const QString &par);
	void setRangeMin(double min) { rangeMin_ = min; }
	void setRangeMax(double max) { rangeMax_ = max; }
	void resetRangePar();
	void setRangeType(RangeLineEdit::EditType type) { rangeType_ = type; }

private:
	const int NumSteps;
	QList<QLineEdit*> edits;

    QString rangePar_;
	RangeLineEdit::EditType rangeType_; 
    double rangeMin_;
    double rangeMax_;
};

#endif