/*
* Detector.cpp
*/

#include <algorithm>
#include <functional>

#include "Detector.h"
#include "StringManip.h"

using std::string;
using std::ostream;
using std::endl;
using std::cout;
using std::replace_if;
using std::equal_to;
using std::bind2nd;

using namespace cbr;

/*
Detector::Detector( const Detector& det ) :
detector( det.detector ), coils( det.coils ),
outcome( det.outcome ), stage( det.stage ),
order( det.order )
{}
*/

void Detector::setStage(CbrPit::Stage st) {
    stage = st;
}

void Detector::setStage (char stage)
{
    switch (stage)
    {
    case 'J': case 'j' :
        setStage(CbrPit::ST_Juvenile);
        break;
    case 'A': case 'a' :
        setStage(CbrPit::ST_Adult);
        break;
    default:
        setStage(CbrPit::ST_Unknown);
    }
}

void Detector::setDetectorName(const QString detectorName ) {
    detector = detectorName;
}

void Detector::addCoil(const QString &coil) {
    coils.push_back(coil);
    QString hexCoil = "0x" + coil;
    int intCoil;
    if (hex2dec(hexCoil.toStdString().c_str(), intCoil))
        icoils.push_back(intCoil);
}

void Detector::setOutcome(CbrPit::Outcome oc) {
    outcome = oc;
}

void Detector::setOutcome(char oc) {
    switch (oc) {
    case 'H':
        setOutcome(CbrPit::Hold);
        break;
    case 'D':
        setOutcome(CbrPit::PileDike);
        break;
    case 'M':
        setOutcome(CbrPit::AMBridge);
        break;
    case 'G':
        setOutcome(CbrPit::PitBarge);
        break;
    case 'R':
        setOutcome(CbrPit::Returned);
        break;
    case 'S':
        setOutcome(CbrPit::Sampled);
        break;
    case 'T':
        setOutcome(CbrPit::Transported);
        break;
    case 'B':
        setOutcome(CbrPit::Bypass);
        break;
    case 'P':
        setOutcome(CbrPit::Spillway);
        break;
    case 'W':
        setOutcome(CbrPit::Weir);
        break;
    case 'A':
        setOutcome(CbrPit::AdultDetect);
        break;
    case 'U':
        setOutcome(CbrPit::Unknown);
        break;
    case 'V':
        setOutcome(CbrPit::AvianColony);
        break;
    default:
        setOutcome(CbrPit::Invalid);
        break;
    }
}


/*
* Return true if the input string matches either the
* detector name or one of the coil names
*/
bool Detector::isMatch(const QString& s) const {
//    bool equal = false;
    QString detectorName = getDetectorName();
//    if (detectorName.compare(s, Qt::CaseInsensitive) == 0)
//        equal = true;
//    return equal;

    if (!detectorName.compare(s))// 0, s.size(), s ) )
        return true;
    detectorName.replace(',', ' ');
//    replace_if(detectorName.begin(), detectorName.end(), bind2nd(equal_to<char>(), ','), ' ');
    if (!detectorName.compare(s)) // 0, s.size(), s ) )
        return true;

    return isCoilMatch(s);
}

bool Detector::hex2dec(const char* hexNum, int& num) const
{
    char* pStopString;
    num = strtol (hexNum, &pStopString, 16);
    return (strlen(pStopString) == 0);
}


bool Detector::isCoilMatch(const QString& scoil) const {

    // check as string
    if (validCoil(scoil))
//    if ( find( coils.begin(), coils.end(), scoil ) != coils.end() )
        return true;

    // check as numbers
    QString hcoil = "0x" + scoil;
    int icoil;
    if (hex2dec( hcoil.toStdString().c_str(), icoil ) ) {
        if (validICoil(icoil))
//        if ( find( icoils.begin(), icoils.end(), icoil ) != icoils.end() )
            return true;
    }

    return false;
}


/**
*/
ostream& operator<< (ostream& os, const Detector& det)
{
    os << det.output().toStdString();
    return os;
}

bool Detector::validCoil(const QString& scoil) const {
    bool found = false;
    for (int i = 0; i < coils.count(); i++) {
        if (coils.at(i).compare(scoil, Qt::CaseInsensitive) == 0) {
            found = true;
            break;
        }
    }
    return found;
}

bool Detector::validICoil(const int icoil) const {
    bool found = false;
    for (unsigned i = 0; i < icoils.size(); i++) {
        if (icoils.at(i) == icoil) {
            found = true;
            break;
        }
    }
    return found;
}

QString Detector::output() const {
    QString out;
    switch (outcome) {
    case CbrPit::Hold:
        out.append('H');
        break;
    case CbrPit::Returned:
        out.append('R');
        break;
    case CbrPit::Sampled:
        out.append('S');
        break;
    case CbrPit::Transported:
        out.append('T');
        break;
    case CbrPit::Unknown:
        out.append('U');
        break;
    case CbrPit::Invalid:
        out.append('I');
        break;
    case CbrPit::Bypass:
        out.append('B');
        break;
    case CbrPit::Spillway:
        out.append('P');
        break;
    case CbrPit::Weir:
        out.append('W');
        break;
    case CbrPit::AvianColony:
        out.append('V');
        break;
    case CbrPit::AdultDetect:
        out.append('A');
        break;
    case CbrPit::BonnLadder:
        out.append('W');
        break;
    case CbrPit::PileDike:
        out.append('D');
        break;
    case CbrPit::PitBarge:
        out.append('G');
        break;
    case CbrPit::AMBridge:
        out.append('M');
        break;
    default:
        out.append('I');
    }

    out.append(": ");

    switch (stage) {
    case CbrPit::ST_Juvenile :
        out.append('J');
        break;
    case CbrPit::ST_Adult :
        out.append('A');
        break;
    case CbrPit::ST_Unknown :
        out.append('U');
        break;
    default :
        out.append('?');
    }

    out.append(" : " + QString::number(order));

    out.append(" : " + detector + " :");

    for (int i = 0; i < coils.count(); i++)
        out.append(" " + coils.at(i));


    return QString(out);

/*
    switch ( det.outcome ) {
  case CbrPit::Hold:
      os <<'H';
      break;
  case CbrPit::Returned:
      os <<'R';
      break;
  case CbrPit::Sampled:
      os <<'S';
      break;
  case CbrPit::Transported:
      os <<'T';
      break;
  case CbrPit::Unknown:
      os <<'U';
      break;
  case CbrPit::Invalid:
      os <<'I';
      break;
  case CbrPit::Bypass:
      os <<'B';
      break;
  case CbrPit::Spillway:
      os <<'P';
      break;
  case CbrPit::Weir:
      os <<'W';
      break;
  case CbrPit::AvianColony:
      os <<'V';
      break;
  case CbrPit::AdultDetect:
      os <<'A';
      break;
  case CbrPit::BonnLadder:
      os <<'W';
      break;
  case CbrPit::PileDike:
      os <<'D';
      break;
  case CbrPit::PitBarge:
      os <<'G';
      break;
  case CbrPit::AMBridge:
      os <<'M';
      break;
  default:
      os << 'I';
    }

    os << ": ";

    switch ( det.stage ) {
  case CbrPit::ST_Juvenile :
      os << 'J';
      break;
  case CbrPit::ST_Adult :
      os << 'A';
      break;
  case CbrPit::ST_Unknown :
      os << 'U';
      break;
  default :
      os << '?';
    }

    os << " : " << det.order;

    os << " : " << det.detector << " :";

    for ( StringVector::const_iterator it = det.coils.begin(); it != det.coils.end(); it++ )
        os << " " << *it;


    return os;*/
}
