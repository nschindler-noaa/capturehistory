/*
*
*/

#include <iostream>
#include <sstream>

#include <ObsSequence.h>
#include <SitesMask.h>
#include <Site.h>

#include "PPTtOutput.h"
#include "PitProSettings.h"

using namespace std;

string PPTtOutput::getFileName (const string& prefix) const
{
	PitProSettings& settings = PitProSettings::getInstance();
	string suffix = settings.getValue (PitProSettings::TtSuffix);
	return settings.getOutFilePath (prefix + "." + suffix);
}

void 
PPTtOutput::writeHeader (const SitesMask& mask)
{
	if ( ofs.is_open()) 
	{
		ofs << "pitcode";
		const SitesMaskVector& sitesVector = mask.getVector();
		for (SitesMaskVector::const_iterator it = sitesVector.begin(); it != sitesVector.end(); ++it) {
			const Site* site = *it;
			if (site)
			{
				ofs << " " << site->getSiteCode();
				ofs << " " << site->getSiteCode();
			}
		}
		ofs << endl;
	}
}

void PPTtOutput::write (ObsSequence& seq, const SitesMask& mask)
{
	if ( ofs.is_open() && seq.numRecs() > 0 )
		ofs << seq.tt (mask) << endl;
}

bool
PPTtOutput::active() const
{
	PitProSettings& settings = PitProSettings::getInstance();
	return settings.isChecked( PitProSettings::TtFileSwitch );
}

