/*
 *
 */

#include <qfile.h>
#include <qstringlist.h>
#include <qtextstream.h>
#include <qregexp.h>
#include <qradiobutton.h>
#include <qcheckbox.h>

#include "CsvConverterDialogImpl.h"
#include "PitProSettings.h"

/* 
 *  Constructs a CsvConverterDialogImpl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
CsvConverterDialogImpl::CsvConverterDialogImpl( QWidget* parent,  Qt::WindowFlags fl )
    : QDialog( parent, fl )
{
}

/*  
 *  Destroys the object and frees any allocated resources
 */
CsvConverterDialogImpl::~CsvConverterDialogImpl()
{
    // no need to delete child widgets, Qt does it all for us
}


// re-implement these to do custom stuff
void CsvConverterDialogImpl::accept() {
    
    QDialog::accept();
}

void CsvConverterDialogImpl::reject() {
    QDialog::reject();
}

void CsvConverterDialogImpl::csvFileSelected( const QString& csvPath ) {
    // create a default out file name
    QString outPath = csvPath;

    // get proper suffix based on data type
    QString suffix = getDataSuffix();
    
    if ( outPath.endsWith( ".csv" ) )
        outPath.replace( ".csv", "." + suffix ); 
    else {
        QStringList toks = outPath.split ("/", QString::SkipEmptyParts);
        QString file = outPath.section('/', -1);
        QString newFileName = file;
        newFileName.replace( ".", "_" );
        newFileName.append( "." + suffix );
        outPath.replace( file, newFileName );
    }
    //outFileChooser->setFileName( outPath );

    updateTable();
}

QString CsvConverterDialogImpl::getDataSuffix() {
    CsvConverter::DataType type = getCsvType();

    PitProSettings& settings = PitProSettings::getInstance();
    if ( type == CsvConverter::Obs ) 
        return settings.getValue( "obsSuffix" ).c_str();
    else if ( type == CsvConverter::Tag ) 
        return settings.getValue( "tagSuffix" ).c_str();
    else if ( type == CsvConverter::Rel ) 
        return settings.getValue( "relSuffix" ).c_str();
    else if ( type == CsvConverter::Mort ) 
        return settings.getValue( "mrtSuffix" ).c_str();
    else
        return QString::null;
}

void CsvConverterDialogImpl::updateTable() {
#if 0
	QFile f( csvFileChooser->fileName() );
	if ( f.open( QIODevice::ReadOnly | QIODevice::Text ) ) {    // file opened successfully
		QTextStream t( &f );        // use a text stream	

        // convert the first several lines and display in
        // the table
        QString s;
        uint numRows = 100;
        uint numCols;
        uint line = 0;
        while ( !( s = t.readLine()).isNull() && line < numRows ) {
            s.replace( "\"", "" );
            QStringList fields = QStringList::split( ",", s, TRUE );
            if ( line == 0 ) { // resize the table based on the first row
                numCols = fields.count();
                dataTable->setNumRows( numRows );
                dataTable->setNumCols( numCols );
                
                // make the table columns fill all available space
                //for ( int col = 0; col < dataTable->numCols(); col++ )
		           // dataTable->setColumnStretchable( col, TRUE );

                // read the field name from the first row
                QStringList columnLabels;
                for ( uint i = 0; i < fields.count(); i++ )  {
                    if ( headerCheckBox->isChecked() ) 
                        columnLabels += fields[ i ];
                    else
                        columnLabels += QString::number( i + 1 );
                }
                dataTable->setColumnLabels( columnLabels );
            } 
            else if ( fields.count() != numCols ) {
                // error message 
            }
            
            if ( line > 0 || !headerCheckBox->isChecked() ) {
                // load the fields to the table
                for ( uint i = 0; i < fields.count(); i++ )  {
                    int row = line - ( headerCheckBox->isChecked()  ? 1 : 0 );
                    QString field = fields[ i ];
                    if ( field.isEmpty() )
                        field = "NA";
                    dataTable->setText( row, i, field );
                }
                            
            }

            // increment
            ++line;        
        }       
    }
#endif
}


// accessor functions
QString CsvConverterDialogImpl::getCsvFile() {
    //return csvFileChooser->fileName();
    return "";
}

QString CsvConverterDialogImpl::getOutFile() {
    //return outFileChooser->fileName();
    return "";
}

bool CsvConverterDialogImpl::getIsHeader() { 
    return headerCheckBox->isChecked(); 
}

CsvConverter::DataType CsvConverterDialogImpl::getCsvType() {
    if ( obsRadioButton->isChecked() )
        return CsvConverter::Obs;
    else if ( tagRadioButton->isChecked() )
        return CsvConverter::Tag;
    else if ( relRadioButton->isChecked() )
        return CsvConverter::Rel;
    else if ( mortRadioButton->isChecked() )
        return CsvConverter::Mort;
    else
        return CsvConverter::Error;
}

void setOutSuffix() {
}

void CsvConverterDialogImpl::doTypeToggled( bool  )
{
#if 0
    if ( rhs ) {
        QString outPath = outFileChooser->fileName();
        if ( !outPath.isEmpty() ) {
            QString suffix = "." + getDataSuffix();
            outPath.replace( QRegExp( "\\.\\D{3}$" ), suffix );
            outFileChooser->setFileName( outPath );
        }

    }
#endif
}

