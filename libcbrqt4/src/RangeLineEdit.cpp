/*
 * RangeLineEdit.cpp
 */

#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QKeyEvent>

#include "RangeLineEdit.h"
#include "RangeLineEditMgr.h"

RangeLineEdit::RangeLineEdit(QWidget* parent, const char* name) :
QLineEdit(parent), editMgr_(0), name_(name),
rangeOk(true), editType(DOUBLE),
editMin(-2e10), editMax(2e10), rangeAllowed(true)
{}

RangeLineEdit::~RangeLineEdit() {
}

void RangeLineEdit::keyPressEvent(QKeyEvent* e) {
    if ((rangeAllowed && (e->key() == Qt::Key_Colon)) ||
            e->key() == Qt::Key_Backspace ||
            e->key() == Qt::Key_Enter ||
            e->key() == Qt::Key_Return ||
            e->key() == Qt::Key_Period ||
            e->key() == Qt::Key_Left ||
            e->key() == Qt::Key_Right ||
            (e->key() >= Qt::Key_0 && e->key() <= Qt::Key_9)) {
        // check for colon before text is updated, don't allow
        // colon if a range has already been defined
        if (e->key() == Qt::Key_Colon) {
            if (!rangeOk)
                emit rangeAlreadySet("Range not allowed for " + QString(name_));
            else if (hasRangeDefined()) {
                if (isRangePar(name_)) // current edit isn't range edit
                    emit rangeAlreadySet("Range already set for " + getRangePar());
            } else {
                setRangePar(name_);
                QLineEdit::keyPressEvent(e);
            }
        } else
            QLineEdit::keyPressEvent(e);

        // do this for the range par var, once the text has been updated
        if (isRangePar(name_)) {
            QString s = text();
            if (!s.contains(":"))
                resetRangePar();
            else
                parseRange(s);
        }
    }
}

bool RangeLineEdit::isRangeEdit() const {
    return isRangePar(name_);
}

bool RangeLineEdit::isRangePar(const QString& par) const {
    if (!editMgr_)
        return false;
    return editMgr_->isRangePar(par);
}

void RangeLineEdit::resetRangePar() {
    if (editMgr_)
        editMgr_->resetRangePar();
}

void RangeLineEdit::setRangePar(const QString &par) {
    if (editMgr_)
        editMgr_->setRangePar(par);
}

QString RangeLineEdit::getRangePar() const {
    if (!editMgr_)
        return QString::null;
    return editMgr_->getRangePar();
}

void RangeLineEdit::setRangeMin(double min) {
    if (editMgr_)
        editMgr_->setRangeMin(min);
}

void RangeLineEdit::setRangeMax(double max) {
    if (editMgr_)
        editMgr_->setRangeMax(max);
}

double RangeLineEdit::getRangeMin() const {
    if (!editMgr_)
        return -2e10;
    return editMgr_->getRangeMin();
}

double RangeLineEdit::getRangeMax() const {
    if (!editMgr_)
        return 2e10;
    return editMgr_->getRangeMax();
}

int RangeLineEdit::getNumSteps() const {
    if (!editMgr_)
        return 1;
    return editMgr_->getNumSteps();
}

double RangeLineEdit::getRangeValue(int i) const {
    if (!editMgr_)
        return -2e10;
    return editMgr_->getRangeValue(i);
}

bool RangeLineEdit::hasRangeDefined() {
    return editMgr_ && editMgr_->hasRangeDefined();
}

void RangeLineEdit::parseRange(const QString& s) {
    if (editMgr_)
        editMgr_->parseRange(s, name_, editType);
}

double RangeLineEdit::getDoubleValue(int i) {
    double retVal;
    if (!isRangeEdit())
        retVal = text().toDouble();
    else {
        double val = getRangeValue(i);
        retVal = val;
    }

    if (retVal < editMin || retVal >= editMax) {
        QString value = QString::number(retVal);
        throw QString("Out of range value in " + name_ + ": " + value);
    }

    return retVal;
}

int RangeLineEdit::getIntegerValue(int i) {
    return (int) getDoubleValue(i);
}

/* 
 * Only disable the range if no range 
 */
void RangeLineEdit::setRangeEnabled(bool rhs) {
    if (!rhs && hasRangeDefined()) {
        double f = getDoubleValue(0);
        QString val = QString::number(f);
        QMessageBox::information(this, "",
                "Disabling \"" + QString(name_) + "\" range. Re-setting to " + val + ".");
        setText(val);
        resetRangePar();
    }
    QLineEdit::setEnabled(rhs);
}

/* 
 * Don't allow ranges if this if false
 */
void RangeLineEdit::setRangeAllowed(bool rhs) {
    rangeAllowed = rhs;
}

bool RangeLineEdit::verify() {
    return verify(editMin, editMax);
}

bool RangeLineEdit::verify(double min) {
    if (isRangeEdit()) {
        if (editMin >= editMax)
            return false;
    } else {
        QString textVal = text();
        if (textVal.isEmpty())
            return false;

        bool ok;
        double val = textVal.toDouble(&ok);
        if (!ok)
            return false;

        if (val < min)
            return false;
    }
    return true;
}

bool RangeLineEdit::verify(double min, double max) {
    bool ok = true;
    if (isRangeEdit()) {
        if (editMin >= editMax)
            ok = false;
        else if (editMin < min)
            ok = false;
        else if (editMin > max)
            ok = false;
        else if (editMax < min)
            ok = false;
        else if (editMax > max)
            ok = false;
    }
    else {
        QString textVal = text();
        bool ok;
        double val = textVal.toDouble(&ok);
        if (!ok)
            ok = false;
        else if (val < min)
            ok = false;
        else if (val > max)
            ok = false;
    }

    return ok;
}

void RangeLineEdit::setName(const char* cs) {
    if (isRangeEdit())
        setRangePar(cs);
    name_ = cs;
}

void RangeLineEdit::setText(const QString& text) {
    QString s = text;

    if (isEnabled() && s.contains(":")) { // try to set a range 
        if (!hasRangeDefined() || isRangeEdit()) // this on is/will be the range
            parseRange(s);
        else if (hasRangeDefined()) { // range defined, but not this one
            s = "";
        }
    } else if (isRangeEdit())
        resetRangePar();

    QLineEdit::setText(s);
}
