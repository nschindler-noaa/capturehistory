/*
*
*/

#include "StringManip.h"

// define some methods for string manipulation

using std::string;
using std::ostringstream;
using std::istringstream;

using namespace cbr;


string cbr::strip (const string& str, StripType type)
{
	int startPos = 0;
	int endPos = str.end()-str.end();
	size_t pos;

	switch (type) {
	case cbr::leading :
		pos = str.find_first_not_of(" \t");
		if (pos != std::string::npos)
			startPos = pos;
		break;
	case cbr::trailing:
		pos = str.find_last_not_of(" \t");
		if (pos != std::string::npos)
			endPos = pos+1;
		break;
	case cbr::both:
		pos = str.find_first_not_of(" \t");
		if (pos != std::string::npos)
			startPos = pos;
		pos = str.find_last_not_of(" \t");
		if (pos != std::string::npos)
			endPos = pos+1;
		break;
	}

	return str.substr(startPos,endPos-startPos);
}

