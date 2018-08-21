#ifndef FletchDialog_H
#define FletchDialog_H

#include <QDialog>
#include "ui_FletchDialog.h"
class QWidget;
class QIntValidator;
class QDoubleValidator;
class QString;

class FletchDialog : public QDialog, public Ui::FletchDialog
{
	Q_OBJECT
public:
	FletchDialog(QWidget* parent = 0, Qt::WFlags flags = 0);
	~FletchDialog ();
private slots:
	void doDefaultsButton ();
	void doOKButton ();
	void doCancelButton ();
	void doTextChanged (const QString&);
private:
	void cleanup();
	const double initialPrecision;
	const double initialStepSize;
	const int initialMaxIterations;
	QDoubleValidator* precisionValidator;
	QDoubleValidator* stepSizeValidator;
	QIntValidator* maxIterValidator;

};

#endif

