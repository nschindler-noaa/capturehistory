/*
 *
 */

#include "PPObs.h"

#include <vector>
#include <string>
#include <QStringList>

//#include <boost/regex.hpp>

#include <DateConverter.h>
#include <ArrayDefs.h>
#include <StringManip.h>
#include <StringTok.h>


using std::string;
using std::istream;
using std::ostream;
using std::vector;

//using cbr::DateConverter;

PPObs::PPObs() : PPData(NFields) {
}

bool PPObs::read(istream&) {
    bool okay = true;
    size_t numFields = static_cast<size_t>(columnData.size());

    for (size_t i = 0; okay && i < numFields; ++i) {
        const QString& data = columnData[static_cast<int>(i)];
        //bool empty = (data.compare (NullString)) ? false : true;
        okay = !data.isEmpty();

        if (okay) {
            if (i == columnOrder[ PitCode ]) {
                pitCode = data;
                if (!PPData::isValidPitTag(pitCode))
                    okay = false;
            } else if (i == columnOrder[ ObsSite ]) {
                obsSite = data;
            } else if (i == columnOrder[ ObsTime ]) {
                time = PPData::getTimeFromDate(data);
                if (time > -1)
                    okay = false;
            } else if (i == columnOrder[ Coil1 ]) {
                QStringList toks;
                stringTok(toks, QString(data.data()));
                coil1.clear();
                for (int i = 0; i < toks.count(); i++)
                {
                    if (i != 0)
                        coil1.append(" ");
                    coil1.append(toks.at(i));
                }
            }
        }
    }

    return okay;
}

bool PPObs::read(QString &istr) {
    bool okay = true;
    size_t numFields = static_cast<size_t>(columnData.size());

    for (size_t i = 0; okay && i < numFields; ++i) {
        const QString& data = columnData[static_cast<int>(i)];
        //bool empty = (data.compare (NullString)) ? false : true;
        okay = !data.isEmpty();

        if (okay) {
            if (i == columnOrder[ PitCode ]) {
                pitCode = data;
                if (!PPData::isValidPitTag(pitCode))
                    okay = false;
            } else if (i == columnOrder[ ObsSite ]) {
                obsSite = data;
            } else if (i == columnOrder[ ObsTime ]) {
                time = PPData::getTimeFromDate(data);
                if (time > -1)
                    okay = false;
            } else if (i == columnOrder[ Coil1 ]) {
                QStringList toks;
                stringTok(toks, QString(data.data()));
                coil1.clear();
                for (int i = 0; i < toks.count(); i++)
                {
                    if (i != 0)
                        coil1.append(" ");
                    coil1.append(toks.at(i));
                }
            }
        }
    }

    return okay;
}

bool PPObs::parseColumnData() {
    bool okay = true;
    size_t numFields = static_cast<size_t>(columnData.size());

    for (size_t i = 0; okay && i < numFields; ++i) {
        const QString& data = columnData[static_cast<int>(i)];
        //bool empty = (data.compare (NullString)) ? false : true;
        okay = !data.isEmpty();

        if (okay) {
            if (i == columnOrder[ PitCode ]) {
                pitCode = data;
                if (!PPData::isValidPitTag(pitCode))
                    okay = false;
            } else if (i == columnOrder[ ObsSite ]) {
                obsSite = data;
            } else if (i == columnOrder[ ObsTime ]) {
                time = PPData::getTimeFromDate(data);
                if (time < 0)
                    okay = false;
            } else if (i == columnOrder[ Coil1 ]) {
                QStringList toks;
                stringTok(toks, QString(data.data()));
                coil1.clear();
                for (int i = 0; i < toks.count(); i++)
                {
                    if (i != 0)
                        coil1.append(" ");
                    coil1.append(toks.at(i));
                }
            }
        }
    }

    return okay;
}


void PPObs::write(ostream& os) const {
    cbr::DateConverter dc(time);

    os << pitCode.toStdString() << ",";
    os << obsSite.toStdString() << ",";
    os << dc << ",";
    os << coil1.toStdString();
}
