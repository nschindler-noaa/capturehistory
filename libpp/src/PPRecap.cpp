/*
*
*/

#include <vector>

#include <QStringList>

#include <DateConverter.h>
#include <ArrayDefs.h>
//#include <StringManip.h>
//#include <StringTok.h>

#include "PPRecap.h"

using std::string;
using std::istream;
using std::ostream;
using std::vector;

using cbr::DateConverter;
using cbr::StringVector;
//using cbr::fromString;

PPRecap::PPRecap() : PPData( NFields ) {}

bool PPRecap::read( istream& )
{
    size_t numFields = columnData.size();

    for (size_t i = 0; i < numFields; ++i)
    {
        const string& data = columnData[i];
        if ( data.empty() )
            return false;

        if ( i == columnOrder[ PitCode ] ) {
            if ( !PPData::isValidPitTag( data ) )
                return false;
            pitCode = data;
        }
        else if ( i == columnOrder[ RecapTime ] ) {
            recapTime = PPData::getTimeFromDate(data.c_str());
            if (recapTime == -1)
                return false;
        }
        else if ( i == columnOrder[ Site ] )
            site = data;
        else if ( i == columnOrder[ RiverKM ] )
            riverkm = data;
    }

    return true;
}



void PPRecap::write (ostream& os) const
{
    DateConverter dc (recapTime);

    os << pitCode << " ";
    os << dc << " ";
    os << site << " ";
    os << riverkm;
}
