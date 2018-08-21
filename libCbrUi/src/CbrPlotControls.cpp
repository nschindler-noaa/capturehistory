/*
*/

#include "CbrPlotControls.h"

using namespace cbr;

void CbrPlotControls::add(QWidget *control)
{
	drawControls_.append(control);
}

void CbrPlotControls::disconnectControls()
{
	QWidget *control;
	foreach(control, drawControls_)
	{
		control->disconnect(this);
	}
}

void CbrPlotControls::connectControls()
{
	QWidget *control;
	foreach(control, drawControls_)
	{
		QString class_name = control->metaObject()->className();    
		if (!class_name.compare("QComboBox")) {
			connect(control, SIGNAL(currentIndexChanged(int)), SIGNAL(currentChanged()));
		}
		else if (!class_name.compare("QCheckBox")) {
			connect(control, SIGNAL(toggled(bool)), SIGNAL(currentChanged()));
		}
		else if (!class_name.compare("QRadioButton")) {
			connect(control, SIGNAL(toggled(bool)), SIGNAL(currentChanged()));
		}
	}
}
