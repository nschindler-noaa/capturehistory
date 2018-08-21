#ifndef SettingsController_H
#define SettingsController_H

//#include <DbController.h>
#include <QtSql>
#include <CbrSettingsProxy.h>

namespace cbr {

    class SettingsController : public QSqlDriver, public cbr::CbrSettingsProxy {
//    class SettingsController : public cbr::DbController, public cbr::CbrSettingsProxy {
    public:
        SettingsController(QSqlDatabase *db, QSqlTableModel *settingModel);

        void setValue(const QString &key, const QVariant &value);
        QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;
        int beginReadArray(const QString & prefix);
        void beginWriteArray(const QString &prefix, int size = -1);
        void setArrayIndex(int i);
        void endArray();
        void remove(const QString &key);

    private:
        bool writingArray_;
        QString arrayPrefix_;
        bool readingArray_;
        int arrayPosition_;
    };
}

#endif
