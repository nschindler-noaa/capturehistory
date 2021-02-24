/*
 * FileTableItem.h
 */


#ifndef FileTableItem_h
#define FileTableItem_h

#include <QTableWidget>
#include <qstring.h>

class FileTableItem : public QTableWidgetItem
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
