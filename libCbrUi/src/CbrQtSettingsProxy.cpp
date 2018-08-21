/*
*/

#include <QSettings>

#include "CbrQtSettingsProxy.h"

//using namespace cbr;

CbrQtSettingsProxy::CbrQtSettingsProxy() : settings_(0)
{
	//settings_ = new QSettings(QSettings::UserScope, organization, application);
	settings_ = new QSettings();
}

CbrQtSettingsProxy::~CbrQtSettingsProxy()
{
	delete settings_;
}

void CbrQtSettingsProxy::setValue(const QString &key, const QVariant &value)
{
	settings_->setValue(key, value);
}

QVariant CbrQtSettingsProxy::value(const QString &key, const QVariant &defaultValue) const
{
	return settings_->value(key, defaultValue);
}

int CbrQtSettingsProxy::beginReadArray(const QString & prefix)
{
	return settings_->beginReadArray(prefix);
}

void CbrQtSettingsProxy::beginWriteArray(const QString &prefix, int size)
{
	settings_->beginWriteArray(prefix, size);
}

void CbrQtSettingsProxy::setArrayIndex(int i)
{
	settings_->setArrayIndex(i);
}

void CbrQtSettingsProxy::endArray()
{
	settings_->endArray();
}

void CbrQtSettingsProxy::remove(const QString &key)
{
	settings_->remove(key);
}
