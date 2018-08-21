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
using cbr::StringVector;

PPRel::PPRel() : PPData( NFields)
{
}

bool PPRel::read ( istream& )
{
	if (columnData.size() < 3)
		return false;

	if (columnData[Key] == NullString ||
		columnData[Date] == NullString ||
		columnData[Time] == NullString)
		return false;

	string jnk = columnData[Key];
	key = columnData[Key];

	string cdate = columnData[Date];
	string ctime = columnData[Time];

	DateConverter dc (cdate, ctime);
	time = dc.getTime();

	return true;
}

void PPRel::write(ostream& os) const
{
	os << key;
	DateConverter dc (time);
	os << dc;
}
