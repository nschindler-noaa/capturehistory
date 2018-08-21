/*
 */

#include <sstream>

#include <QStringList>

#include <QtSql>
//#include <SqliteDb.h>
//#include <SqliteStmt.h>

#include "SettingsController.h"
#include "SettingModel.h"

using namespace std;
using namespace cbr;

SettingsController::SettingsController(QSqlDatabase *db, QSqlTableModel *settingModel) : QSqlDriver(db) //, settingModel),
//writingArray_(false), readingArray_(false), arrayPosition_(0)
{
    writingArray_ = false;
    readingArray_ = false;
    arrayPosition_ = 0;
    model_ = settingModel;
}
/*SettingsController::SettingsController(SqliteDb *db, DbModel *settingModel) : DbController(db, settingModel),
writingArray_(false), readingArray_(false), arrayPosition_(0) {
}*/

void SettingsController::setValue(const QString &key, const QVariant &value) {
    QString fullKey;
    if (!writingArray_)
        fullKey = key;
    else
        fullKey = arrayPrefix_ + "_" + key;

    stringstream ss;
    ss << "DELETE FROM " << model_->getTableName() << " WHERE ";
    ss << model_->qualifiedFieldName(SettingModel::KEY) << " = \"" << fullKey.toStdString() << "\" AND ";
    ss << model_->qualifiedFieldName(SettingModel::POSITION) << " = " << arrayPosition_ << "";
    const string sql = ss.str();
    db_->exec(sql);

    ss.str("");
    ss << "INSERT INTO " << model_->getTableName() << " (";
    ss << model_->qualifiedFieldName(SettingModel::KEY) << ", ";
    ss << model_->qualifiedFieldName(SettingModel::VALUE) << ") ";
    ss << " VALUES (?, ?)";

    SqliteStmt stmt;
    int rc = db_->prepare_insert_stmt(*model_, stmt);
    if (rc != SQLITE_OK) {
        return;
    }

    const string skey = fullKey.toStdString();
    stmt.bind_string(SettingModel::KEY, skey);

    stmt.bind_int(SettingModel::POSITION, arrayPosition_);

    string svalue;
    if (value.type() == QVariant::ByteArray) {
        QByteArray barray = value.toByteArray();
        const char *cvalue = barray.constData();
        stmt.bind_text(SettingModel::VALUE, cvalue);
    } else {
        svalue = value.toString().toStdString();
        stmt.bind_string(SettingModel::VALUE, svalue);
    }

    stmt.exec();
}

QVariant SettingsController::value(const QString &key, const QVariant &defaultValue) const {
    QString fullKey;
    if (!readingArray_)
        fullKey = key;
    else
        fullKey = arrayPrefix_ + "_" + key;

    stringstream ss;
    ss << "SELECT " << model_->qualifiedFieldName(SettingModel::VALUE) << " ";
    ss << "FROM " << model_->getTableName() << " WHERE ";
    ss << model_->qualifiedFieldName(SettingModel::KEY) << " = \"" << fullKey.toStdString() << "\" AND ";
    ss << model_->qualifiedFieldName(SettingModel::POSITION) << " = " << arrayPosition_ << "";
    const string sql = ss.str();
    TableData data;
    db_->get_query_data(data, sql);
    if (data.getNumRows() > 0) {
        return data.column(0, 0);
    }
    db_->free_data_table(data);
    return defaultValue;
}

int SettingsController::beginReadArray(const QString &prefix) {
    arrayPrefix_ = prefix;
    readingArray_ = true;

    stringstream ss;
    ss << "SELECT COUNT (DISTINCT " << model_->qualifiedFieldName(SettingModel::POSITION) << ") ";
    ss << "FROM " << model_->getTableName() << " WHERE ";
    ss << model_->qualifiedFieldName(SettingModel::KEY) << " LIKE \"" << prefix.toStdString() << "_%\" ";
    const string sql = ss.str();
    TableData data(sql);
    int retVal = 0;
    if (data.getNumRows() > 0)
        retVal = data.column_int(0, 0);
    db_->free_data_table(data);
    return retVal;
}

void SettingsController::beginWriteArray(const QString &prefix, int /*size*/) {
    arrayPrefix_ = prefix;
    writingArray_ = true;
}

void SettingsController::setArrayIndex(int i) {
    arrayPosition_ = i;
}

void SettingsController::endArray() {
    readingArray_ = false;
    writingArray_ = false;
    arrayPosition_ = 0;
}

void SettingsController::remove(const QString &key) {
    stringstream ss;
    ss << "DELETE FROM " << model_->getTableName() << " WHERE ";
    ss << model_->qualifiedFieldName(SettingModel::KEY) << " LIKE \"" << key.toStdString() << "\"";
    const string sql = ss.str();
    db_->exec(sql);
}
