#ifndef CbrSettingsProxy_h
#define CbrSettingsProxy_h

#include <QVariant>
#include <QString>

namespace cbr
{
    class CbrSettingsProxy
    {
    public:
        CbrSettingsProxy() {}
        virtual ~CbrSettingsProxy() {}

        virtual void setValue(const QString &key, const QVariant &value) = 0;
        virtual QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const = 0;
        virtual int beginReadArray(const QString & prefix) = 0;
        virtual void beginWriteArray(const QString &prefix, int size = -1) = 0;
        virtual void setArrayIndex(int i) = 0;
        virtual void endArray() = 0;
        virtual void remove(const QString &key) = 0;
    };
}

#endif
