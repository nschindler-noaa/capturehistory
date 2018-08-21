/*
 * FileTableItem.h
 */


#ifndef FileTableItem_h
#define FileTableItem_h

#include <QTableWidget>
//#include <q3table.h>
#include <qstring.h>

class FileTableItem : public QTableWidgetItem
//class FileTableItem : public Q3TableItem
{
private:
    QString fileName;
    QString dirName;

public:
    FileTableItem(QTableWidget* table, ItemType et, const QString& file, const QString& dir );
//    FileTableItem( Q3Table* table, EditType et, const QString& file, const QString& dir );
    virtual ~FileTableItem();

};

#endif // !FileTableItem_h
