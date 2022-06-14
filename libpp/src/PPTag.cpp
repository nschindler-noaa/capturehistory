/*
*
*/

#include <vector>

#include <QStringList>

#include <ArrayDefs.h>
//#include <StringManip.h>
#include <DateConverter.h>
//#include <StringTok.h>

#include "PPTag.h"

using std::string;
using std::istream;
using std::ostream;
using std::vector;

//using cbr::fromString;
using cbr::StringVector;
using cbr::DateConverter;


PPTag::PPTag() : PPData( NFields )
{
    resetColumnOrder();
}

void PPTag::resetColumnOrder() {
    for ( int i = 1; i < NFields; ++i )
        setColumnOrder( i, i - 1 );
}


bool PPTag::read( istream& )
{
    species = 'A';
    run = 'A';
    rear_type = 'A';
    length = 0;
    relTime = -1;
    relSite.clear();
    icovs.clear();
    missingIcov = false;

    for ( size_t i = 0; i < columnData.size(); ++i ) {
        const string& data = columnData[i];
        //bool empty = (data.compare (NullString)) ? false : true;
        bool empty = data.empty();

        if ( i == columnOrder[ PitCode ] ) {
            pitCode = data;

            if ( !PPData::isValidPitTag( pitCode ) )
                return false;
        }
        else if ( i == columnOrder[ RelTime ] ) {
            if ( !empty )
            {
                relTime = PPData::getTimeFromDate(data.c_str());
                if (relTime == -1)
                    return false;
            }
        }
        else if ( i == columnOrder[ RelSite ] ) {
            if ( !empty )
                relSite = data;
        }
        else if ( i == columnOrder[ Species ] ) {
            if ( !empty )
                species = fromString<char>( data );
        }
        else if ( i == columnOrder[ Run ] ) {
            if ( !empty )
                run = fromString<char>( data );
        }
        else if ( i == columnOrder[ RearType ] ) {
            if ( !empty )
                rear_type = fromString<char>( data );
        }
        else if ( i >= columnOrder[ ICov1 ] ){
            if (!empty)
                icovs.push_back(data);
            else {
                missingIcov = true;
                icovs.push_back("");
            }
        }
        else if ( i == columnOrder[ TagGroup ] ) { // for use with data converter, normally not used
            if ( empty )
                return false;
            else
                tagGroup = data;
        }

    }

    return true;
}

void PPTag::write (ostream& os) const
{
    os << pitCode << ",";
    if ( relTime == -1 )
        os << DateConverter::base << ",";
    else {
        DateConverter dc (relTime);
        os << dc << ",";
    }
    os << relSite << ",";
    os << species << ",";
    os << run << ",";
    os << rear_type << ",";
    os << length;
}


short PPTag::getLength () const
{
    const string& length = getICov(0);
    if (length.empty())
        return 0;
    return cbr::fromString<int>(getICov(0));
}

const std::string& PPTag::getICov(int i) const
{
    return icovs[i];
}

int PPTag::numICovs() const
{
    return icovs.size();
}
