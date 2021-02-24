/*
 *
 */

//#include <sstream>
#include <QString>

#include "PPVersion.h"
#include "Sites.h"
#include "PPSystemSettings.h"

//using std::string;
//using std::stringstream;
using namespace cbr;

static QString version;

QString &PPVersion::versionString()
{
    if (version.isEmpty()) {
        PPSystemSettings &settings = PPSystemSettings::getInstance();
        version = settings.get(PPSystemSettings::Version).toString();
    }
    return version;
}

