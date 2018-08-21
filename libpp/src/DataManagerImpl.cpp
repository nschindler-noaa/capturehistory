#include <q3textbrowser.h>
#include <qmime.h>

#include "DataManagerImpl.h"

#include "DirectoryView.h"
#include "PitProSettings.h"

/* 
 *  Constructs a DataManagerImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
DataManagerImpl::DataManagerImpl( QWidget* parent,  const char* name, Qt::WFlags fl )
    : DataManager( parent, name, fl )
{
	PitProSettings& settings = PitProSettings::getInstance();
	const QString& dataDir = settings.getValue( PitProSettings::DataDir ).c_str();

	// set up the data dir viewer
	dataDirView->addColumn( "Name" );
	dataDirView->addColumn( "Type" );
	Directory* dir = new Directory( dataDirView, dataDir );
	dir->setOpen( TRUE );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
DataManagerImpl::~DataManagerImpl()
{
    // no need to delete child widgets, Qt does it all for us
}


void DataManagerImpl::listItemClicked( Q3ListViewItem* fileItem ) {
    // the the file name that was double clicked on
    QString fileName = fileItem->text( 0 );

    // set the source of the browser to the file. The data dir
    // should have been set in the global mime source
    viewBrowser->setSource( fileName );

    //viewBrowser->setText( fileName );

}
