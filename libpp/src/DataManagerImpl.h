/*
 * DataManagerImpl_h
 */

#ifndef DataManagerImpl_h
#define DataManagerImpl_h

#include "ui_DataManager.h"

class Q3ListViewItem;

class DataManagerImpl : public QDialog, public Ui::DataManager
{ 
    Q_OBJECT

public:
    DataManagerImpl( QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );
    ~DataManagerImpl();

public slots:
    void listItemClicked( Q3ListViewItem* );

};

#endif // DataManagerImpl_h
