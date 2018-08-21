/*
 *
 */

#include <algorithm>

#include "PPErrors.h"
#include "PPData.h"

using std::string;
using std::istream;
using std::ostream;
using std::fill;
using std::find;
using namespace cbr;

PPErrors::PPErrors() : ErrorFlags (NumErrorTypes), valid(true)
{
}

PPErrors::~PPErrors()
{
}

string
PPErrors::getText(int type)
{
	return getText( static_cast<ErrorType>( type ) );
}

string
PPErrors::getText(ErrorType type)
{
	switch (type)
	{
	case AdultOnJuvenileDet:
		return "Observation on known juvenile detector after migration year";
	case Minijack:
		return "Fish removed as minijack";
	case NoRelDate:
		return "No release data found";
	case NoSiteRel:
		return "Fish released at dam (site release) not returned to river";
	case NoTag:
		return "PIT tag not found in list of valid tags or tag not loaded";
	case OneYearOldPreCutoff:
		return "Fish observed before residualization cutoff date in year following migration year";
	case OutOfSequence:
		return "Observations  out of sequence";
	case PreRel:
		return "Fish observed before release date";
	case PreRemoved:
		return "Fish removed before first capture history site";
	case UnknownStage:
		return "Stage unknown";
	case WrongSpecies:
		return "Wrong species";
	case WrongRun:
		return "Wrong run";
	case WrongRearType:
		return "Wrong rearing type";
	case ZeroCovariate:
		return "Individual covariate has zero or null value";
	default:
		return "Unknown";
	}
}

void
PPErrors::write (ostream& os) const
{
	os << pitCode;
	if (errors.size() > 0)
		os << " ";
	ErrorFlags::write (os);
}

void
PPErrors::read (istream& is)
{
	is >> pitCode;
    if (!PPData::isValidPitTag(pitCode))
        valid = false;
    else
	    ErrorFlags::read (is);
}

void
PPErrors::reset( const string& pitCode )
{
	clear();
	setPitCode( pitCode );
}