/*
*
*/

#ifndef ObsReader_h
#define ObsReader_h

#include <iostream>
#include <string>
#include <vector>

#include "CSVReader.h"
#include "Pars.h"
#include "ObsSequence.h"
#include "CbrPit.h"
#include "ObsDataRow.h"
#include "ObsProcessor.h"
#include "DateConverter.h"
#include <Sites.h>

template <class T>
class ObsReader
{
public:
    ObsReader( const std::string& infile );
    void readHeader();
    void readData( std::vector<ObsProcessor*>& processors );
    Pars& getHeaderPars() const;
    void reset() { reader.reset(); }
    void setMigrationYear( int year ) { migrationYear = year; }

private:
    CSVReader<T> reader;
    int migrationYear;
};

template <class T>
ObsReader<T>::ObsReader( const std::string& infile ) : reader( infile.c_str() )
{
}

template <class T>
void ObsReader<T>::readHeader()
{
    reader.parseHeader();
}

//template <class T>
//Pars& ObsReader<T>::getHeaderPars() const
//{
//    return ObsDataRow::getHeaderPars();
//}

template <class T>
void ObsReader<T>::readData(std::vector<ObsProcessor*>& processors )
{

    for (std::vector<ObsProcessor*>::iterator it = processors.begin(); it != processors.end(); ++it )
        (*it)->pre();

    ObsSequence seq;
    const Sites* sites = Sites::getInstance();
    int rowNum = 0;
    while ( reader.getNext() )
    {
        const T& row = reader.getRow();
        if ( row.isValid() )
        {
            ++rowNum;
            const Site* site = sites->getSite ( row.obsSite() );
            if (site)
            {
                if (!seq.isValid() || !seq.isMatch( row.pitCode() ) )
                {
                    if ( seq.isValid() )
                    {
                        seq.sort();
                        seq.setStages();
                        for (std::vector<ObsProcessor*>::iterator it = processors.begin(); it != processors.end(); ++it )
                            (*it)->processSequence( seq );
                    }

                    seq.clear();
                    seq.setMigrationYear( migrationYear );
                    seq.setReleaseDate( row.relDate() );
                    seq.setPitCode( row.pitCode() );
                }


                double obsTime = row.lastDate();
                const Detector* det =  sites->getDetector( row.obsSite(), row.coil(), obsTime );
                if ( !det ) {
                    cbr::DateConverter dc( obsTime );
                    std::cout  << "Unable to find detector for observation (line " << rowNum << "): ";
                    std::cout  << row.obsSite() << ", " << row.coil() << ", " << dc << std::endl;
                }
                else {
                    cbr::CbrPit::Outcome outcome =
                        sites->getOutcome ( row.obsSite(), row.lastDet(), row.lastDate() );

                    seq.addRecord (site, row.stage(), outcome, row.firstDate(), row.lastDate(), 1 );
                }
            }
        }
    }

    // last fish
    if ( seq.isValid() )
    {
        seq.sort();
        seq.setStages();
        for (std::vector<ObsProcessor*>::iterator it = processors.begin(); it != processors.end(); ++it )
            (*it)->processSequence( seq );
    }

    for (std::vector<ObsProcessor*>::iterator it = processors.begin(); it != processors.end(); ++it ) {
        (*it)->post();
    }


}


#endif
