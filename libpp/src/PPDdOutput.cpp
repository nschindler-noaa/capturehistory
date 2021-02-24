/*
*
*/

#include <sstream>

#include <ObsSequence.h>
#include <SitesMask.h>
#include <Site.h>

#include "PPDdOutput.h"
#include "PitProSettings.h"

#include <QStringList>

//using std::string;
//using std::stringstream;
using std::endl;

QString PPDdOutput::getFileName(const QString prefix) const
{
    PitProSettings& settings = PitProSettings::getInstance();
    QString suffix = settings.getValue (PitProSettings::DdSuffix);
    return settings.getOutFilePath (prefix + "." + suffix);
}



void PPDdOutput::writeHeader (const SitesMask& mask)
{
    if ( ofs.is_open())
    {
      ofs << "pitcode rel";
      const SitesMaskVector& sitesVector = mask.getVector();
      for (SitesMaskVector::const_iterator it = sitesVector.begin(); it != sitesVector.end(); ++it) {
        const Site* site = *it;
        if (site)
          ofs << " " << site->getSiteCode().toStdString() << " " << site->getSiteCode().toStdString();
      }
      ofs << endl;
    }
}

void PPDdOutput::write (ObsSequence& seq, const SitesMask& mask, bool showAll)
{
    PitProSettings& settings = PitProSettings::getInstance();
    bool julianDates = settings.isChecked (PitProSettings::JulianDates);
    if ( ofs.is_open() && seq.numRecs() > 0 )
        ofs << seq.dd (mask, julianDates, showAll).toStdString() << endl;
}

bool PPDdOutput::active() const
{
    PitProSettings& settings = PitProSettings::getInstance();
    return settings.isChecked( PitProSettings::DdFileSwitch );
}

