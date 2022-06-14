/*
 *
 */

#include <vector>
#include <string>
#include <QStringList>

#include <boost/regex.hpp>

#include <DateConverter.h>
#include <ArrayDefs.h>
//#include <StringManip.h>
//#include <StringTok.h>

#include "PPObs.h"

using std::string;
using std::istream;
using std::ostream;
using std::vector;

using cbr::DateConverter;
using cbr::StringVector;
//using cbr::fromString;
//using stringTok;

PPObs::PPObs() : PPData(NFields) {
}

bool PPObs::read(istream&) {
    size_t numFields = columnData.size();

    for (size_t i = 0; i < numFields; ++i) {
        const string& data = columnData[i];
        //bool empty = (data.compare (NullString)) ? false : true;
        bool empty = data.empty();

        if (i == columnOrder[ PitCode ]) {
            pitCode = data;
            if (empty || !PPData::isValidPitTag(pitCode))
                return false;
        } else if (i == columnOrder[ ObsSite ]) {
            if (empty)
                return false;
            else
                obsSite = data;
        } else if (i == columnOrder[ ObsTime ]) {
            if (empty)
                return false;
            time = PPData::getTimeFromDate(data.c_str());
            if (time == -1)
                return false;
        } else if (i == columnOrder[ Coil1 ]) {
            if (empty)
                return false;
            else {
                QStringList toks;
                QString dataqs(data.data());
//				vector<string> toks;
                stringTok(toks, dataqs);
                coil1.clear();
                for (int i = 0; i < toks.count(); i++)
                {
                    if (i != 0)
                        coil1.append(" ");
                    coil1.append(toks.at(i).toStdString());
                }
/*				for (vector<string>::iterator it = toks.begin(); it != toks.end(); ++it) {
                    if (it != toks.begin())
                        coil1.append(" ");
                    coil1.append(*it);
                }*/
            }
        }
    }

    return true;
}

void PPObs::write(ostream& os) const {
    DateConverter dc(time);

    os << pitCode << ",";
    os << obsSite << ",";
    os << dc << ",";
    os << coil1;
}
