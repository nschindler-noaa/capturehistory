/*
*/

#include "PPRel.h"

#include <ArrayDefs.h>
#include <DateConverter.h>

using std::istream;
using std::ostream;
using std::string;
using std::getline;

using cbr::DateConverter;
//using cbr::StringVector;

PPRel::PPRel() : PPData(NFields)
{
}

bool PPRel::read (istream&)
{
    if (columnData.size() < 3)
        return false;

    if (columnData[Key] == NullString ||
        columnData[Date] == NullString ||
        columnData[Time] == NullString)
        return false;

    QString jnk = columnData[Key];
    key = columnData[Key];

    QString cdate = columnData[Date];
    QString ctime = columnData[Time];

    DateConverter dc (cdate, ctime);
    time = dc.getTime();

    return true;
}

bool PPRel::parseColumnData()
{
    bool okay = true;
    if (columnData.size() < 3) {
        okay = false;
    }
    else if (columnData[Key] == NullString ||
             columnData[Date] == NullString ||
             columnData[Time] == NullString) {
        okay = false;
    }
    else {
        QString jnk = columnData[Key];
        key = columnData[Key];

        QString cdate = columnData[Date];
        QString ctime = columnData[Time];

        DateConverter dc (cdate, ctime);
        time = dc.getTime();
    }

    return okay;
}

void PPRel::write(ostream& os) const
{
    os << key.toStdString();
    DateConverter dc (time);
    os << dc;
}
