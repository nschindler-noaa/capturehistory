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

void Detector::setStage( CbrPit::Stage st ) {
	stage = st;
}

void Detector::setStage (char stage) 
{
	switch ( stage ) 
	{
	case 'J': case 'j' :
		setStage( CbrPit::ST_Juvenile );
		break;
	case 'A': case 'a' :
		setStage( CbrPit::ST_Adult );
		break;
	default:
		setStage( CbrPit::ST_Unknown );
	}
}

void Detector::setDetectorName( const string& detectorName ) {
	detector = detectorName;
}

void Detector::addCoil( const string& coil ) {
	coils.push_back( coil );
	string hexCoil = "0x" + coil;
	int intCoil;
	if (hex2dec( hexCoil.c_str(), intCoil ) )
		icoils.push_back( intCoil );
}

void Detector::setOutcome( CbrPit::Outcome oc ) { 
	outcome = oc; 
}

void Detector::setOutcome( char oc ) { 
	switch ( oc ) {
	case 'H':
		setOutcome( CbrPit::Hold );
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
		setOutcome( CbrPit::Returned );
		break;
	case 'S':
		setOutcome( CbrPit::Sampled );
		break;
	case 'T':
		setOutcome( CbrPit::Transported );
		break;
	case 'B':
		setOutcome( CbrPit::Bypass );
        break;
    case 'P':
        setOutcome( CbrPit::Spillway );
        break;
    case 'W':
        setOutcome( CbrPit::Weir );
        break;
    case 'A':
        setOutcome( CbrPit::AdultDetect);
        break;
	case 'U':
        setOutcome(CbrPit::Unknown);
        break;
    case 'V':
        setOutcome(CbrPit::AvianColony);
        break;
	default:
		setOutcome( CbrPit::Invalid );
		break;
	}
}


/*
* Return true if the input string matches either the
* detector name or one of the coil names
*/
bool Detector::isMatch( const string& s) const {
	string detectorName = getDetectorName();
	if ( !detectorName.compare( 0, s.size(), s ) )
		return true;
	replace_if(detectorName.begin(), detectorName.end(), bind2nd(equal_to<char>(), ','), ' ');
	if ( !detectorName.compare( 0, s.size(), s ) )
		return true;

	return isCoilMatch( s );
}

bool Detector::hex2dec(const char* hexNum, int& num) const
{ 
    char* pStopString; 
    num = strtol (hexNum, &pStopString, 16);
    return (bool)(strlen(pStopString) == 0);
}


bool Detector::isCoilMatch( const string& scoil ) const {

	// check as string
	const StringVector& coils = getCoils();
	if ( find( coils.begin(), coils.end(), scoil ) != coils.end() )
		return true;

	// check as numbers
	string hcoil = "0x" + scoil;
	int icoil;
	if (hex2dec( hcoil.c_str(), icoil ) ) {
		if ( find( icoils.begin(), icoils.end(), icoil ) != icoils.end() )
			return true;
	}

	return false;
}


/**
*/
ostream& operator<< ( ostream& os, const Detector& det ) 
{

	switch ( det.outcome ) {
  case CbrPit::Hold:
      os << 'H';
	  break;
  case CbrPit::Returned:
      os << 'R';
	  break;
  case CbrPit::Sampled:
      os << 'S';
	  break;
  case CbrPit::Transported:
      os << 'T';
	  break;
  case CbrPit::Unknown:
      os <<' U';
	  break;
  case CbrPit::Invalid:
      os << 'I';
	  break;
  case CbrPit::Bypass:
      os << 'B';
      break;
  case CbrPit::Spillway:
      os << 'P';
      break;
  case CbrPit::Weir:
      os << 'W';
      break;
  case CbrPit::AvianColony:
      os << 'V';
      break;
  case CbrPit::AdultDetect:
      os << 'A';
      break;
  case CbrPit::BonnLadder:
      os << 'W';
      break;
  case CbrPit::PileDike:
      os << 'D';
      break;
  case CbrPit::PitBarge:
      os << 'G';
      break;
  case CbrPit::AMBridge:
      os << 'M';
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


	return os;
}
