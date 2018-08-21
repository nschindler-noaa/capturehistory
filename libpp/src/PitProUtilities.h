/*
 * PitProUtilities.h
 */

#ifndef PitProUtilities_h
#define PitProUtilities_h

#include <string>

#include <qdir.h>
#include <qstringlist.h>
#include <qstring.h>


#include "Utilities.h"

class PitProUtilities {
  public:
    static QStringList getDataGroups( const QString& dataDir, 
				      const QString& obsSuffix, 
				      const QString& tagSuffix );

    static QStringList getResultsGroups( const QString& outDir, const QStringList& suffixes );

	static std::string usage();

};

#endif
