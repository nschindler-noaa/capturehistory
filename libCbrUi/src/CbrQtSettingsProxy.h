#ifndef CbrQtSettingsProxy_h
#define CbrQtSettingsProxy_h

#include "CbrSettingsProxy.h"

class QSettings;

//namespace cbr
//{
	class CbrQtSettingsProxy : public CbrSettingsProxy
	{
	public:
		CbrQtSettingsProxy();
		~CbrQtSettingsProxy();

		void setValue(const QString &key, const QVariant &value);
		QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;
		int beginReadArray(const QString & prefix);
		void beginWriteArray(const QString &prefix, int size = -1);
		void setArrayIndex(int i);
		void endArray();
		void remove(const QString &key);

	private:
		QSettings *settings_;
	};
//}


#endif
