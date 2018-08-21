/*
 * RangeLineEdit.h: interface for the RangeLineEdit class.
 *
 */

#ifndef RangeLineEdit_h
#define RangeLineEdit_h

class RangeLineEditMgr;

#include <qlineedit.h>

/*
 * The range line edit allows for one (and only one) range to be
 * defined among all RangeLineEdit widgets. The range is specified by
 * two numbers seperated by a colon (":").
 */
class RangeLineEdit : public QLineEdit {

    Q_OBJECT

public:
    enum EditType {
        INTEGER, DOUBLE
    };

    // These vars keep track of the range variable info. They
    // are made static so that the whole program can have easy
    // access to them

    RangeLineEdit(QWidget* parent, const char* name = 0);
    virtual ~RangeLineEdit();

    EditType getEditType() const {
        return editType;
    }

    double getEditMin() const {
        return editMin;
    }

    double getEditMax() const {
        return editMax;
    }

    const QString& name() const {
        return name_;
    }

    double getDoubleValue(int i = 0);
    int getIntegerValue(int i = 0);

    bool hasRangeDefined();
    bool verify();
    bool verify(double min);
    bool verify(double min, double max);

    virtual void setName(const char* name);

    void setManager(RangeLineEditMgr *mgr) {
        editMgr_ = mgr;
    }

public slots:
    void setText(const QString & text);

    void setRangeOk(bool rhs) {
        rangeOk = rhs;
    }

    void setEditType(EditType type) {
        editType = type;
    }

    void setEditMin(double min) {
        editMin = min;
    } // >=

    void setEditMax(double max) {
        editMax = max;
    } // <
    void setRangeEnabled(bool);
    void setRangeAllowed(bool); // sometimes we don't want a range, just an ordinary number

signals:
    void rangeAlreadySet(const QString&);

protected:
    void keyPressEvent(QKeyEvent* e);

private:
    RangeLineEditMgr *editMgr_;
    QString name_;

    QString getRangePar() const;
    double getRangeMin() const;
    double getRangeMax() const;
    int getNumSteps() const;
    double getRangeValue(int i) const;
    void parseRange(const QString &s);

    bool isRangeEdit() const;
    bool isRangePar(const QString& par = QString::null) const;
    void resetRangePar();
    void setRangeMin(double min);
    void setRangeMax(double max);
    void setRangePar(const QString &par);
    bool hasRangeDefined() const;

    bool rangeOk; // is a range def allowed for this editline
    EditType editType; // what is the type (int, double) of this editline
    double editMin; // not used yet, will be used to enforce bounds on input
    double editMax; //
    bool rangeAllowed;
};

#endif // RangeLineEdit_h
