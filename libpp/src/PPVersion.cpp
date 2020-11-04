/*
 *
 */

#include <sstream>
#include <QStringList>

#include "PPVersion.h"
#include "Sites.h"
#include "PPSystemSettings.h"

using std::string;
using std::stringstream;

string PPVersion::versionString() 
{   
	PPSystemSettings &settings = PPSystemSettings::getInstance();
	stringstream ss;
    QString ver(settings.get(PPSystemSettings::Version).toString());
    ss << ver.toStdString();
	return ss.str();
}

