/*
*
*/

#include "RangeLineEditMgr.h"


RangeLineEditMgr::RangeLineEditMgr() :
NumSteps(100),
rangeType_(RangeLineEdit::DOUBLE)
{
}

void RangeLineEditMgr::addLineEdit(RangeLineEdit *edit)
{
	edits.append(edit);
	edit->setManager(this);
}

bool RangeLineEditMgr::isRangePar(const QString& par) const
{
	return !rangePar_.isEmpty() && rangePar_.compare(par) == 0;
}

void RangeLineEditMgr::resetRangePar() 
{
	rangePar_ = QString::null;
}

void RangeLineEditMgr::setRangePar(const QString &par) 
{
	rangePar_ = par;
}

int RangeLineEditMgr::getNumSteps() const 
{
	int numSteps = 1;

    if (hasRangeDefined()) {
		if (rangeType_ == RangeLineEdit::DOUBLE)
			numSteps = NumSteps;
		else 
		{
			numSteps = static_cast<int>(rangeMax_ - rangeMin_);
			while (numSteps > NumSteps) {
				numSteps /= 10;
			}
		}
	}
    return numSteps;
}

double RangeLineEditMgr::getRangeValue(int i) const
{
	double retVal = 0;
    int numSteps = getNumSteps();
    if (i == 0)
        retVal = getRangeMin();
    else if (i == numSteps - 1) 
        retVal = getRangeMax();
    else  {
        double min = getRangeMin();
        double max = getRangeMax();
        retVal = min + i * ((max - min) / numSteps);
    }
	return retVal;
}

QList<double> RangeLineEditMgr::getRangeValues() const 
{
	QList<double> vals;
	for (int i = 0; i < getNumSteps(); ++i)
	{
		vals.append(getRangeValue(i));
	}
	return vals;
}

void RangeLineEditMgr::parseRange(const QString &s, const QString &name, RangeLineEdit::EditType type)
{
	QStringList range = s.split(":");
	setRangeType(type);
	if (range.count() == 1)
		setRangeMin(range[ 0 ].toDouble());
	else if (range.count() == 2) {
		setRangeMin(range[ 0 ].toDouble());
		setRangeMax(range[ 1 ].toDouble());
		setRangePar(name);
	}
}

QString RangeLineEditMgr::getRangeString(int format, int precision) const
{
	return QString::number(getRangeMin(), format, precision) + ":" + QString::number(getRangeMax(), format, precision);
}
