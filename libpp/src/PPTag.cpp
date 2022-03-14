/*
*
*/

#include <vector>

#include <QStringList>

#include <ArrayDefs.h>
#include <StringManip.h>
#include <DateConverter.h>
#include <StringTok.h>

#include "PPTag.h"

using std::string;
using std::istream;
using std::ostream;
using std::vector;

//using cbr::fromString;
//using cbr::StringVector;
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

    for (int i = 0; i < columnData.size(); ++i) {
        const QString& data = columnData[i];
        unsigned col = static_cast<unsigned>(i);
        //bool empty = (data.compare (NullString)) ? false : true;
        bool empty = data.isEmpty();

        if ( col == columnOrder[ PitCode ] ) {
            pitCode = data;

            if ( !PPData::isValidPitTag( pitCode ) )
                return false;
        }
        else if ( col == columnOrder[ RelTime ] ) {
            if ( !empty )
            {
                relTime = PPData::getTimeFromDate(data);
                if (relTime > -1)
                    return false;
            }
        }
        else if ( col == columnOrder[ RelSite ] ) {
            if ( !empty )
                relSite = data;
        }
        else if ( col == columnOrder[ Species ] ) {
            if ( !empty )
                species = *data.toLatin1().data();//fromString<char>(data);
        }
        else if ( col == columnOrder[ Run ] ) {
            if ( !empty )
                run = *data.toLatin1().data();//fromString<char>( data );
        }
        else if ( col == columnOrder[ RearType ] ) {
            if ( !empty )
                rear_type = *data.toLatin1().data();//fromString<char>( data );
        }
        else if ( col >= columnOrder[ ICov1 ] ){
            if (!empty)
                icovs.push_back(data);
            else {
                missingIcov = true;
                icovs.push_back("");
            }
        }
        else if ( col == columnOrder[ TagGroup ] ) { // for use with data converter, normally not used
            if ( empty )
                return false;
            else
                tagGroup = data;
        }

    }

    return true;
}

bool PPTag::parseColumnData()
{
    species = 'A';
    run = 'A';
    rear_type = 'A';
    length = 0;
    relTime = -1;
    relSite.clear();
    icovs.clear();
    missingIcov = false;
    bool okay = true;

    for (int i = 0; i < columnData.size(); ++i) {
        const QString& data = columnData[i];
        unsigned col = static_cast<unsigned>(i);
        //bool empty = (data.compare (NullString)) ? false : true;
        bool empty = data.isEmpty();

        if (col == columnOrder[PitCode]) {
            pitCode = data;

            if (!PPData::isValidPitTag(pitCode)) {
                okay = false;
                break;
            }
        }
        else if (col == columnOrder[RelTime]) {
            if (!empty)
            {
                relTime = PPData::getTimeFromDate(data);
                if (relTime < 0) {
                    okay = false;
                    break;
                }
            }
        }
        else if (col == columnOrder[RelSite]) {
            if (!empty) {
                relSite = data;
            }
        }
        else if (col == columnOrder[Species]) {
            if (!empty) {
                species = *data.toLatin1().data();//fromString<char>(data);
            }
        }
        else if (col == columnOrder[Run]) {
            if (!empty) {
                run = *data.toLatin1().data();//fromString<char>( data );
            }
        }
        else if (col == columnOrder[RearType]) {
            if (!empty) {
                rear_type = *data.toLatin1().data();//fromString<char>( data );
            }
        }
        else if (col >= columnOrder[ICov1]){
            if (empty) {
                missingIcov = true;
            }
            icovs.append(data);
        }
        else if (col == columnOrder[TagGroup]) { // for use with data converter, normally not used
            if (empty) {
                okay = false;
                break;
            }
            else {
                tagGroup = data;
            }
        }
    }

    return okay;
}


void PPTag::write (ostream& os) const
{
    os << pitCode.toStdString() << ",";
    if ( relTime > -1 )
        os << DateConverter::base << ",";
    else {
        DateConverter dc (relTime);
        os << dc << ",";
    }
    os << relSite.toStdString() << ",";
    os << species << ",";
    os << run << ",";
    os << rear_type << ",";
    os << length;
}


short PPTag::getLength () const
{
    const QString& length = getICov(0);
    if (length.isEmpty())
        return 0;
    return length.toShort();//cbr::fromString<int>(getICov(0));
}

const QString& PPTag::getICov(int i) const
{
    return icovs[i];
}

int PPTag::numICovs() const
{
    return icovs.size();
}
