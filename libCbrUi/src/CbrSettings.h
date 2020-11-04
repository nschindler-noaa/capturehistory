/*
 * CbrSettings.h
 */

#ifndef CbrSettings_h
#define CbrSettings_h

#include <QObject>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QVector>
#include <QSignalMapper>


//namespace cbr {
    class CbrSettingsProxy;

    class CbrSettings : public QObject {
        Q_OBJECT

    public:
        CbrSettings();
        ~CbrSettings();

        virtual void init() {
        }
        virtual void setDefaults();
        virtual void clear(bool force = false);

        bool keyExists(int key) const;

        QVariant get(int key) const;
        QVariant get(int key, int index);
        QVariant getDefault(int key) const;

        bool isChecked(int key) const {
            return get(key).toBool();
        }
        void set(int key, const QVariant &val);
        void set(int key, int index, const QVariant &val);

        void removeSetting(int key);

        void saveDir(int key, const QString& path);
        QString getDir(int key) const;

        virtual void mapArrayObject(QObject* obj, int key, int index, bool clear = true);
        virtual void mapObject(QObject* obj, int key, bool clear = false);
        virtual void mapObject(QObject *obj, int key, const QVariant &val, bool clear = false);
        virtual void unmapObject(QObject *obj);

        void makePersist(int ikey) {
            persistent.push_back(ikey);
        } // not cleared

        QList<QVariant> readArray(int key);
        void writeArray(int key, const QList<QVariant>& values);
        QVariant readArrayValue(int key, int position);
        void writeArrayValue(int key, int position, QVariant value);
        void appendArrayValue(int key, QVariant value);
        void removeArrayValue(int key, QVariant value);

        const QString &lastError() const {
            return lastError_;
        }

        void setLastError(const QString &error) {
            lastError_ = error;
        }

    public slots:
        virtual void settingChanged(int);
	signals:
		void statusMessage(const QString &msg);

    protected:

        QMap<int, QString> keys;
        QMap<int, QVariant> defaults;
        QVector<int> persistent;

        /* Associate an integer key with it's name. The most recently added
           settings proxy is associated with this key */
        virtual void addKey(int ikey, const QString &skey, QVariant defaultValue = QVariant());

        /* Add a proxy. CbrSettings takes over ownership of the proxy and deletes it. */
        void addProxy(CbrSettingsProxy *proxy);

        CbrSettingsProxy *proxy(int ikey);
        const CbrSettingsProxy *proxy(int ikey) const;
        CbrSettingsProxy *proxy();
        const CbrSettingsProxy *proxy() const;

        QString getHomePath(QString programName = QString::null) const;
        QString getAppDataPath(QString programName = QString::null);
        QString getUserLocalDataPath(QString programName = QString::null);

    private:
        QSignalMapper* signalMapper;

        QString getKeyNameWithIndex(const QString &keyName, int index) const;
        const int arrayKeyMult_;

        QString lastError_;

        QMap<int, CbrSettingsProxy*> proxyMap_;
        QList<CbrSettingsProxy*> proxies_;

        QString getEnv(const char* varname) const;
        QString getMyDocumentsPath() const;

    };
//}

#endif 
