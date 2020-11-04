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
    FileTableItem(ItemType et, const QString& file, const QString& dir );
    virtual ~FileTableItem();

};

#endif // !FileTableItem_h
