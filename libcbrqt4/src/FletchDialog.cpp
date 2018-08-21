#include "FletchDialog.h"
#include <FletchDefs.h>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QString>
#include <QMessageBox>
#include <QWidget>
#include <FletchDefs.h>

FletchDialog::FletchDialog (QWidget* parent, Qt::WFlags flags) : QDialog (parent, flags), 
initialPrecision(cbr::FletchDefs::instance()->precision()),
initialStepSize(cbr::FletchDefs::instance()->stepSize()),
initialMaxIterations(cbr::FletchDefs::instance()->maxIterations()),
precisionValidator (new QDoubleValidator (this)),
stepSizeValidator (new QDoubleValidator (this)), 
maxIterValidator (new QIntValidator (this))
{
	try {
		setupUi (this);

		disconnect (cancelButton, 0, 0, 0);
		connect (defaultsButton, SIGNAL (clicked(bool)), this, SLOT (doDefaultsButton()));
		connect (okButton, SIGNAL (clicked(bool)), this, SLOT (doOKButton()));
		connect (cancelButton, SIGNAL (clicked(bool)), this, SLOT (doCancelButton()));
		connect (lineEditPrecision, SIGNAL (textChanged (const QString&)), SLOT (doTextChanged (const QString&)));
		connect (lineEditStepSize, SIGNAL (textChanged (const QString&)), SLOT (doTextChanged (const QString&)));
		connect (lineEditMaxIter, SIGNAL (textChanged (const QString&)), SLOT (doTextChanged (const QString&)));
	
		lineEditPrecision->setText(QString::number(initialPrecision));
		lineEditStepSize->setText(QString::number(initialStepSize));
		lineEditMaxIter->setText(QString::number(initialMaxIterations));

		lineEditPrecision->setValidator (precisionValidator);
		lineEditStepSize->setValidator (stepSizeValidator);
		lineEditMaxIter->setValidator (maxIterValidator);

		lineEditPrecision->setReadOnly (false);
		lineEditStepSize->setReadOnly (false);
		lineEditMaxIter->setReadOnly (false);
		doTextChanged(QString());
	}
	catch (...)
	{
		cleanup();
	}
}

FletchDialog::~FletchDialog()
{
	cleanup();
}

void FletchDialog::cleanup()
{
	delete precisionValidator;
	delete stepSizeValidator;
	delete maxIterValidator;
}

void FletchDialog::doDefaultsButton ()
{
	int status = QMessageBox::warning (this, "Fletch Configuration", 
		"Discard current values and replace with the defaults?", QMessageBox::Ok, QMessageBox::Cancel);
	if (status == QMessageBox::Ok)
	{
		lineEditPrecision->setText (QString::number (cbr::FletchDefs::defaultPrecision));
		lineEditStepSize->setText (QString::number (cbr::FletchDefs::defaultStepSize));
		lineEditMaxIter->setText (QString::number (cbr::FletchDefs::defaultMaxIterations));
		defaultsButton->setEnabled (false);
	}
}

void FletchDialog::doCancelButton ()
{
	if (okButton->isEnabled ())
	{
		int status = QMessageBox::warning (this, "Cancel Changes",
			"Discard changes and quit?", QMessageBox::Ok, QMessageBox::Cancel);
		if (status == QMessageBox::Ok)
			close();
	}
	else
		close();
}

void FletchDialog::doOKButton ()
{
	cbr::FletchDefs *fletchDefs = cbr::FletchDefs::instance();
	fletchDefs->setPrecision (lineEditPrecision->text().toDouble());
	fletchDefs->setStepSize (lineEditStepSize->text().toDouble());
	fletchDefs->setMaxIterations (lineEditMaxIter->text().toDouble());
}

void FletchDialog::doTextChanged (const QString&)
{
	const double precision = lineEditPrecision->text().toDouble();
	const double stepSize = lineEditStepSize->text().toDouble();
	const int maxIter = lineEditMaxIter->text().toInt();
	okButton->setEnabled (!(precision == initialPrecision && stepSize == initialStepSize && maxIter == initialMaxIterations));
	const cbr::FletchDefs* fletchDefs = cbr::FletchDefs::instance();
	defaultsButton->setEnabled (!(precision == fletchDefs->defaultPrecision && stepSize == fletchDefs->defaultStepSize &&
		maxIter == fletchDefs->defaultMaxIterations));
}
