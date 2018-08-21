/*
 *
 */

#include <q3listbox.h>
//Added by qt3to4:
#include <Q3ValueList>

#include "ListChooser.h"

/* 
 *  Constructs a ListChooser which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
ListChooser::ListChooser( QWidget* parent,  const char* name, Qt::WFlags fl )
    : ListChooserUIC( parent, name, fl ), dataType( String )
{
    setSorted( TRUE );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
ListChooser::~ListChooser()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 * public slot
 */
void ListChooser::doSelectOne()
{
    QStringList list = getSelectedListItems( availableList );
    selectedList->insertStringList( list );
    removeSelectedItems( availableList );
    sort();

    emit itemsSelected( list );
}

/*
 * public slot
 */
void ListChooser::doDeSelectOne()
{
    QStringList list = getSelectedListItems( selectedList );
    availableList->insertStringList( list );
    removeSelectedItems( selectedList );
    sort();

    emit itemsDeSelected( list );
}

/*
 * public slot
 */
void ListChooser::doSelectAll()
{
    QStringList list = getAllListItems( availableList );
    selectedList->insertStringList( list );
    availableList->clear();
    sort();

    emit itemsSelected( list );

}

/*
 * public slot
 */
void ListChooser::doDeSelectAll()
{
    QStringList list = getAllListItems( selectedList );
    availableList->insertStringList( list );
    selectedList->clear();
    sort();

    emit itemsDeSelected( list );
}

/*
 * public slot
 */
void ListChooser::setAvailable( const QStringList& list )
{
    availableList->clear();
    availableList->insertStringList( list );
    sort();

}

/*
 * public slot
 */
void ListChooser::setSelected( const QStringList& list )
{
    selectedList->clear();
    selectedList->insertStringList( list );
    sort();
}


void ListChooser::sort() {
    if ( sorted ) {
        if ( dataType == String ) {
            availableList->sort();
            selectedList->sort();
        }
        else {
            sortNumeric( availableList );
            sortNumeric( selectedList );
        }
    }
}


/* 
 * Helpful QListBox functions
 */

/* 
 * Get a QStringList with all selected items from the list
 */
QStringList ListChooser::getSelectedListItems( Q3ListBox* listBox ) {
    QStringList stringList;
    for ( uint i = 0; i < listBox->count(); i++ ) {
        if ( listBox->isSelected( i ) )
            stringList += listBox->text( i );
    }

    return stringList;
}

/* 
 * Sort a QListBox in numeric order
 */
void ListChooser::sortNumeric( Q3ListBox* listBox ) {
    // make numeric list from list box
    Q3ValueList<double> values;
    for ( uint i = 0; i < listBox->count(); i++ ) 
        values += listBox->text( i ).toDouble();

    // sort the list numerically
    qHeapSort( values );

    // add the values back to the list box
    listBox->clear();
    Q3ValueList<double>::iterator it;
    QStringList sl;
    for ( it = values.begin(); it != values.end(); it++ )
        sl += QString::number( *it );
    listBox->insertStringList( sl );

}


/* 
 * Get a QStringList with all items from the list
 */
QStringList ListChooser::getAllListItems( Q3ListBox* listBox ) {
    QStringList stringList;
    for ( uint i = 0; i < listBox->count(); i++ ) {
        stringList += listBox->text( i );
    }

    return stringList;
}


/*
 * Remove all selected items.
 */
void ListChooser::removeSelectedItems( Q3ListBox* listBox ) {
    Q3ValueList<int> selected;

    // make a list of the selected indices
    for ( uint i = 0; i < listBox->count(); i++ ) {
        if ( listBox->isSelected( i ) )
            selected += i;
    }

    // clear the selection
    listBox->clearSelection();

    for ( int j = selected.count() - 1; j >= 0; j-- ) 
        listBox->removeItem( selected[ j ] );
    
}

/*
 * Set whether the availableList and selectedList
 * are sorted or not.
 */
void ListChooser::setSorted( bool rhs ) { 
    sorted = rhs; 
    sort();
}


void ListChooser::clearSelected() {
    selectedList->clear();
}

void ListChooser::clearAvailable() {
    availableList->clear();
}

void ListChooser::clearAll() {
    clearSelected();
    clearAvailable();
}

