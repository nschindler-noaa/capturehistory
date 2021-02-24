/*
*
*/

#include <vector>

#include <DateConverter.h>
#include <ArrayDefs.h>
#include <StringManip.h>
#include <StringTok.h>

#include "PPRecap.h"

#include <QStringList>

using std::string;
using std::istream;
using std::ostream;
using std::vector;

using cbr::DateConverter;
//using cbr::StringVector;
//using cbr::fromString;

PPRecap::PPRecap() : PPData( NFields ) {}

bool PPRecap::read( istream& )
{
    int numFields = columnData.size();
    bool okay = true;

    for (int i = 0; i < numFields; ++i)
    {
        ObsFields field = static_cast<ObsFields>(i);
        const QString& data = columnData[i];
        if (data.isEmpty()) {
            okay = false;
            break;
        }
        else {
            if (field == columnOrder[PitCode]) {
                if (!PPData::isValidPitTag(data)) {
                    okay = false;
                    break;
                }
                pitCode = data;
            }
            else if (field == columnOrder[RecapTime]) {
                recapTime = PPData::getTimeFromDate(data);
                if (recapTime < -.9) {
                    okay = false;
                    break;
                }
            }
            else if (field == columnOrder[Site]) {
                site = data;
            }
            else if (field == columnOrder[RiverKM]) {
                riverkm = data;
            }
        }
    }

    return okay;
}

bool PPRecap::parseColumnData()
{
    int numFields = columnData.size();
    bool okay = true;

    for (int i = 0; i < numFields; ++i)
    {
        ObsFields field = static_cast<ObsFields>(i);
        const QString& data = columnData[i];
        if (data.isEmpty()) {
            okay = false;
            break;
        }
        else {
            if (field == columnOrder[PitCode]) {
                if (!PPData::isValidPitTag(data)) {
                    okay = false;
                    break;
                }
                pitCode = data;
            }
            else if (field == columnOrder[RecapTime]) {
                recapTime = PPData::getTimeFromDate(data);
                if (recapTime < -.9) {
                    okay = false;
                    break;
                }
            }
            else if (field == columnOrder[Site]) {
                site = data;
            }
            else if (field == columnOrder[RiverKM]) {
                riverkm = data;
            }
        }
    }

    return okay;
}



void PPRecap::write (ostream& os) const
{
    DateConverter dc (recapTime);

    os << pitCode.toStdString() << " ";
    os << dc << " ";
    os << site.toStdString() << " ";
    os << riverkm.toStdString();
}
