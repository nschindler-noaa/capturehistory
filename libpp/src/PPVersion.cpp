/*
 *
 */

#include <sstream>
#include <QString>

#include "PPVersion.h"
#include "Sites.h"
#include "PPSystemSettings.h"

using std::string;
using std::stringstream;

string PPVersion::versionString() 
{   
	PPSystemSettings &settings = PPSystemSettings::getInstance();
	stringstream ss;
	ss << settings.get(PPSystemSettings::Version).toString().toStdString();
	return ss.str();
}

