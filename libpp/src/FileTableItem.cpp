/*
 * FileTableItem.cpp: implementation of the FileTableItem class.
 */


#include "FileTableItem.h"

FileTableItem::FileTableItem (ItemType et,
                             const QString& file, const QString& dir) :
    QTableWidgetItem (file, et), fileName(file), dirName(dir)
{

}

FileTableItem::~FileTableItem()
{

}
