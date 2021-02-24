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

QString PPTtOutput::getFileName(const QString prefix) const
{
    PitProSettings& settings = PitProSettings::getInstance();
    QString suffix = settings.getValue (PitProSettings::TtSuffix);
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
                ofs << " " << site->getSiteCode().toStdString();
                ofs << " " << site->getSiteCode().toStdString();
            }
        }
        ofs << endl;
    }
}

void PPTtOutput::write (ObsSequence& seq, const SitesMask& mask, bool showAll)
{
    if ( ofs.is_open() && seq.numRecs() > 0 )
        ofs << seq.tt (mask, showAll).toStdString() << endl;
}

bool
PPTtOutput::active() const
{
    PitProSettings& settings = PitProSettings::getInstance();
    return settings.isChecked( PitProSettings::TtFileSwitch );
}

