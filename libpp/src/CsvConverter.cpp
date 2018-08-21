/* 
 * CsvConverter.cpp
 */

#include <qfile.h>
#include <qstringlist.h>
//Added by qt3to4:
#include <QTextStream>

#include "CsvConverter.h"

 /*
 * Basic constructor
*/
CsvConverter::CsvConverter (QObject* p, const QString& name) : ComputationThread (p, name),
    isHeader (true), dataType (Obs)
{}

/*
* This is called by the run method of ComputationThread
*/
void CsvConverter::compute() {
    sendStatusMessage( " " );
    sendStatusMessage( "***** PitPro *****" );
    sendStatusMessage( "** Converting csv file..." );
    
    
    if ( !csvFile.isEmpty() && !outFile.isEmpty() ) {
        QFile in( csvFile );
        QFile out( outFile );
        
        if ( in.open( QIODevice::ReadOnly | QIODevice::Text ) && 
            out.open( QIODevice::WriteOnly ) ) {    // files opened successfully
            QTextStream istream( &in );        // use a text stream	
            QTextStream ostream( &out );
            
            QString s;
            QStringList::iterator it;
            QString na;
            if ( dataType == Obs )
                na = "XX";
            else 
                na = "NA";
            int line = 0;
            while ( !( s = istream.readLine(1024)).isNull() ) {
                if ( line > 0 || !isHeader ) {
                    s.replace( "\"", "" );
                    QStringList fields = s.split (",", QString::KeepEmptyParts);
                    for ( it = fields.begin(); it != fields.end(); it++ )  {
                        if ( (*it).isEmpty() )
                            *it = na;
                    }       
                    ostream << fields.join( " " ) << endl;
                }
                ++line;
            }
        }
    }
    
    sendStatusMessage( "***** Done *****" );
    sendCompletedSignal();
}


// mutator methods

void CsvConverter::setCsvFile( const QString& s ) {
    csvFile = s;
}

void CsvConverter::setOutFile( const QString& s ) {
    outFile = s;
}

void CsvConverter::setIsHeader( bool rhs ) {
    isHeader = rhs;
}

void CsvConverter::setDataType( DataType type ) {
    dataType = type;
}
