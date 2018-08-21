/*
 * FileDirChooserImpl.cpp
 */

#include <q3listbox.h>

#include "FileDirChooserImpl.h"
#include "DirectoryView.h"

/* 
 *
 */
FileDirChooserImpl::FileDirChooserImpl( QWidget* parent,  const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, name, modal, fl )
{
	setupUi (this);
	dirView->addColumn( "Name" );
	dirView->addColumn( "Type" );
	Directory* dir = new Directory( dirView, "." );
	dir->setOpen( TRUE );
}

/*  
 *  
 */
FileDirChooserImpl::~FileDirChooserImpl()
{
    // no need to delete child widgets, Qt does it all for us
}

/*  
 *  Add the item selected in the directory view to the
 *  selected list.
 */
void FileDirChooserImpl::addSelectedItem() {
	QString file = dirView->selectedItem();
	selectedList->insertItem( file );
}
