/*
*/

#include "SettingModel.h"

using namespace cbr;

/*const std::string SettingModel::names[] = {
	"id",
	"key",
	"position",
	"value"
};

const std::string SettingModel::types[] = {
	"INTEGER PRIMARY KEY AUTOINCREMENT",
	"TEXT",
	"INTEGER",
	"TEXT"
};*/

SettingModel::SettingModel() : QSqlTableModel() // cbr::DbModel("settings", NUM_FIELDS)
{
    names << "id" << "key" << "position" << "value";
    types << "INTEGER PRIMARY KEY AUTOINCREMENT" << "TEXT" << "INTEGER" << "TEXT";

    setEditStrategy(QSqlTableModel::OnFieldChange);
    setObjectName("Settings");
    for (int i = 0; i < NUM_FIELDS; i++)
        setHeaderData(i, Qt::Horizontal, names.at(i), Qt::DisplayRole);
//    setup(NUM_FIELDS, names, types);
}

