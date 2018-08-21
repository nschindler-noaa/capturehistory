/*
*/

#include "RangeLineEditPlugin.h"
#include "RangeLineEdit.h"

#include <QtPlugin>

RangeLineEditPlugin::RangeLineEditPlugin(QObject *parent)
: QObject(parent)
{
	initialized = false;
}

void RangeLineEditPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
	if (initialized)
		return;

	initialized = true;
}

bool RangeLineEditPlugin::isInitialized() const
{
	return initialized;
}

QWidget *RangeLineEditPlugin::createWidget(QWidget *parent)
{
	return new RangeLineEdit(parent);
}

QString RangeLineEditPlugin::name() const
{
	return "RangeLineEdit";
}

QString RangeLineEditPlugin::group() const
{
	return "CBR Widgets";
}

QIcon RangeLineEditPlugin::icon() const
{
	return QIcon();
}

QString RangeLineEditPlugin::toolTip() const
{
	return "";
}

QString RangeLineEditPlugin::whatsThis() const
{
	return "";
}

bool RangeLineEditPlugin::isContainer() const
{
	return false;
}

QString RangeLineEditPlugin::domXml() const
{
	return "<widget class=\"RangeLineEdit\" name=\"rangeLineEdit\">\n"
		" <property name=\"geometry\">\n"
		"  <rect>\n"
		"   <x>0</x>\n"
		"   <y>0</y>\n"
		"   <width>100</width>\n"
		"   <height>40</height>\n"
		"  </rect>\n"
		" </property>\n"
		" <property name=\"toolTip\" >\n"
		"  <string>QLineEdit for ranges</string>\n"
		" </property>\n"
		" <property name=\"whatsThis\" >\n"
		"  <string>Allows the input of a range of numbers using the n0:n1 format.</string>\n"
		" </property>\n"
		"</widget>\n";
}

QString RangeLineEditPlugin::includeFile() const
{
	return "RangeLineEdit.h";
}


Q_EXPORT_PLUGIN2(cbrplugins, RangeLineEditPlugin)