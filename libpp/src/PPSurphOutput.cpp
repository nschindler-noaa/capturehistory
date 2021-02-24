/*
*
*/

#include <sstream>
#include <algorithm>
#include <fstream>

#include <QString>
#include <QStringList>
#include <QByteArray>

#include <DateConverter.h>
#include <ObsSequence.h>
#include <SitesMask.h>
#include <Site.h>
#include <Sites.h>

#include "PPSurphOutput.h"
#include "PPVersion.h"
#include "PitProSettings.h"

//using std::string;
using std::stringstream;
using std::endl;
using std::min;
using std::ifstream;

using namespace cbr;

void PPSurphOutput::close()
{
    tmpOut.close();
    PPFileOutput::close();
}

void PPSurphOutput::closeAndDelete()
{
    tmpOut.closeAndDelete();
    PPFileOutput::closeAndDelete();
}

void PPSurphOutput::setPrefix(const QString prefix)
{
    PPFileOutput::setPrefix( prefix );
    tmpOut.setPrefix( prefix );
}

QString PPTmpOutput::getFileName(const QString prefix) const
{
    PitProSettings& settings = PitProSettings::getInstance();
    QString suffix = settings.getValue (PitProSettings::SurphSuffix);
    return settings.getOutFilePath (prefix + "_tmp.txt");
}

QString PPSurphOutput::getFileName(const QString prefix) const
{
    PitProSettings& settings = PitProSettings::getInstance();
    QString suffix = settings.getValue (PitProSettings::SurphSuffix);
    return settings.getOutFilePath (prefix + "." + suffix);
}

void PPSurphOutput::writeHeader(const QString& outPrefix,
                                const SitesMask& mask,
                                const RunConfigVector& runConfigVector,
                                const IntVector& groupSizes,
                                bool writeICovs)
{
    if (!ofs.is_open())
        return;

    PitProSettings& settings = PitProSettings::getInstance();
    QString outputFormat = settings.getValue(PitProSettings::OutputFormat);

    /* print header */
    DateConverter currentTime;
    ofs << "#" << endl;
    ofs << "# Format: " << outputFormat.toStdString() << endl;
    ofs << "#" << endl;
    ofs << "# Generated by PitPro on " << currentTime << endl;
    ofs << "#     PitPro version:    " << PPVersion::versionString().toStdString() << endl;
    ofs << "#     Sites config date: " << Sites::getInstance()->getConfigDate().toStdString() << endl;
    ofs << "#" << endl;
    ofs << settings.writeLegend().toStdString();
    QStringList groupNames;
    for (RunConfigVector::const_iterator it = runConfigVector.begin(); it != runConfigVector.end(); ++it )
    {
        const RunConfigItem& runItem = *it;
        groupNames.push_back(runItem.name);
        ofs << "# Run config:" << endl;
        ofs << "#   name:  " << runItem.name.toStdString() << endl;
        ofs << "#   obs:   " << runItem.obs.toStdString() << endl;
        ofs << "#   tag:   " << runItem.tag.toStdString() << endl;
        ofs << "#   recap: " << runItem.recap.toStdString() << endl;
        ofs << "#   mort:  " << runItem.mort.toStdString() << endl;
        ofs << "#" << endl;
    }
    ofs << "#" << endl;

    /* print capture history fields as comments */
    ofs << getSurphFileLegend (mask, writeICovs, outputFormat).toStdString();

    if ( !outputFormat.compare( "SURPH1" ) )
        writeSurph1Header(outPrefix, mask, groupNames, groupSizes, writeICovs);
    else if ( !outputFormat.compare( "ROSTER" ) )
        writeRosterHeader();
    else
        writeSurph2Header(outPrefix, mask, groupNames, groupSizes, writeICovs);
}

void PPSurphOutput::writeRosterHeader()
{
}

void PPSurphOutput::writeSurph1Header( const QString& outPrefix,
                                      const SitesMask& mask,
                                      const QStringList& groupNames,
                                      const IntVector& groupSizes,
                                      bool writeICovs)

{
    ofs << "Data" << endl;
    ofs << outPrefix.toStdString() << endl << endl;
    SitesMaskVector maskVector = mask.getVector();
    ofs << "npop " << groupNames.size() << endl;
    ofs << "nper " << mask.numPeriods() << endl << endl;

    if (writeICovs && numICovs > 0) {
        for (int i = 1; i <= numICovs; ++i)
            ofs << "icov icov" << i << endl;
        ofs << endl;
    }

    /* print population names */
    ofs << "population_names" << endl;
    for (QStringList::const_iterator it = groupNames.begin(); it != groupNames.end(); ++it)
    {
        QString name = *it;
        if (name.size() > 15)
            name.resize(15);

        QString outname(name);
        outname.replace(QString(" "), QString("_"));

        ofs << outname.toStdString() << endl;
    }
    ofs << endl;

    /* print number of tagged fish per group */
    ofs << "ntag" << endl;
    for (IntVector::const_iterator it = groupSizes.begin(); it != groupSizes.end(); ++it)
    {
        ofs << *it;
        for (int i = 0; i < mask.numPeriods() - 1; ++i)
            ofs << " 0";
        ofs << endl;
    }
    ofs << endl << endl;

    ofs << "full_hist" << endl << endl;
    ofs << "idlen 14" << endl << endl;
    ofs << "data" << endl;
}

void PPSurphOutput::writeSurph2Header(const QString &outPrefix,
                                      const SitesMask& mask,
                                      const QStringList &groupNames,
                                      const IntVector& groupSizes,
                                      bool writeICovs)
{

    /* standard header info */
    SitesMaskVector maskVector = mask.getVector();
    ofs << "Surph2" << endl;
    ofs << outPrefix.toStdString() << endl << endl;
    ofs << "npop " << groupNames.size() << endl << endl;
    ofs << "nper " << mask.numPeriods() << endl << endl;

    if (writeICovs && numICovs > 0) {
        for (int i = 1; i <= numICovs; ++i)
            ofs << "individual_covariate icov" << i << endl;
        ofs << endl;
    }

    /* print population names */
    ofs << "population_names" << endl;
    for (QStringList::const_iterator it = groupNames.begin(); it != groupNames.end(); ++it)
    {
        QString outname((*it));
        outname.replace(QString(" "), QString("_"));

        ofs << outname.toStdString() << endl;
    }
    ofs << endl;

    /* print number of tagged fish per group */
    ofs << "ntag";
    for (IntVector::const_iterator it = groupSizes.begin(); it != groupSizes.end(); ++it)
    {
        ofs << " " << *it;
    }
    ofs << endl << endl;

    /* the rest */
    ofs << "full_hist" << endl << endl;
    ofs << "tagID present" << endl << endl;
    ofs << "captureHistories" << endl;
}

void PPSurphOutput::write (const QString& outPrefix,
                           const SitesMask& mask,
                           const RunConfigVector& runConfigVector,
                           const IntVector& groupSizes,
                           bool writeICovs)
{
    if (!ofs.is_open())
        return;

    QString outp(outPrefix);
    outp.replace(QString(" "), QString("_"));
    writeHeader(outp, mask, runConfigVector, groupSizes, writeICovs);
    tmpOut.close();
    QString tmpFile = tmpOut.getFileName(prefix);
    ifstream ifs(tmpFile.toStdString());
    if (ifs.is_open())
    {
        std::string line;
        while (getline(ifs, line))
        {
            ofs << line << endl;
        }
    }
    ifs.close();
    tmpOut.closeAndDelete();

    writeFooter();
}

void PPSurphOutput::writeHist (ObsSequence& seq, const SitesMask& mask, bool checkForErrors)
{
    PitProSettings& settings = PitProSettings::getInstance();
    QString outputFormat = settings.getValue(PitProSettings::OutputFormat);

    if (!checkForErrors || seq.getErrors().isOk())
    {
        QString strm(seq.getPitCode());
//        stringstream ss;
//        ss << seq.getPitCode();
        if (outputFormat.compare("ROSTER") != 0)
            strm.append(" 1");
        strm.append(seq.hist((mask)));
        strm.append('\n');
//            ss << " 1";
//        ss << seq.hist (mask) << endl;
        tmpOut.write(strm);//ss.str());
    }
}

void PPSurphOutput::writeFooter()
{
    if (!ofs.is_open())
        return;

    PitProSettings& settings = PitProSettings::getInstance();
    QString outputFormat = settings.getValue(PitProSettings::OutputFormat);
    if (!outputFormat.compare("SURPH1"))
        ofs << "enddata" << endl;
}


bool
PPSurphOutput::active() const
{
    PitProSettings& settings = PitProSettings::getInstance();
    return settings.isChecked( PitProSettings::SurphFileSwitch );
}

QString PPSurphOutput::getSurphFileLegend(const SitesMask& mask, bool lengthCovar, const QString& format) const
{
    QString outstr("#\n");
    stringstream ss;

    int i = 0;
    int col = 0;
    int field = 0;
    int numJuvSites = mask.getNumJuvenileSites();
    int numMainSites = mask.getNumMainSites();
    SitesMaskVector maskVector = mask.getVector();
    bool isSiteRel = mask.isSiteRel();
    const Site *siteptr;

    outstr.append("# Fields key\n");
    outstr.append("#\n");
    outstr.append(QString("#  %1: Pit Code").arg(QString::number(++col)));
    if (format.compare("ROSTER") != 0) {
        outstr.append(QString("#  %1: Release Site").arg(QString::number(++col)));
    }
    if (isSiteRel)
        i++;
    for (; i < maskVector.count(); i++) {
        siteptr = maskVector.at(i);
        if (field < numMainSites) {
            outstr.append(QString("#  %1: %2%3\n").arg(QString::number(++col), siteptr->getLongName(), getStageKey(numJuvSites)));
        }
        else if (field == numMainSites) {
            outstr.append(QString("#  %1: Combined\n").arg(QString::number(++col)));
            outstr.append(QString("#       %1%2\n").arg(siteptr->getLongName(), getStageKey(numJuvSites)));
        }
        else {
            outstr.append(QString("#       %1%2\n").arg(siteptr->getLongName(), getStageKey(numJuvSites)));
        }
        ++field;
    }
    if (lengthCovar)
        outstr.append(QString("#  %1: Length").arg(QString::number(++col)));
    outstr.append("#\n\n");

    return QString(outstr);

/*    ss << "#" << endl;
    ss << "# Fields key" << endl;
    ss << "#" << endl;
    ss << "#  " << ++col << ": Pit Code" << endl;
    if (format.compare("ROSTER") != 0)
        ss << "#  " << ++col << ": Release Site" << endl;
    SitesMaskVector::const_iterator it = maskVector.begin();
    if (isSiteRel && it != maskVector.end())
        ++it;
    for (; it != maskVector.end(); ++it) {
        if (field < numMainSites)
            ss << "#  " << ++col << ": " << (*it)->getLongName()<< getStageKey (numJuvSites) << endl;
        else if (field == numMainSites)  {
            ss << "#  " << ++col << ": Combined" << endl;
            ss << "#       " << (*it)->getLongName() << getStageKey (numJuvSites) << endl;
        }
        else
            ss << "#       " << (*it)->getLongName() << getStageKey (numJuvSites) << endl;

        ++field;
    }
    if (lengthCovar)
        ss << "#  " << ++col << ": Length" << endl;
    ss << "#" << endl << endl;

    return ss.str();*/
}

QString PPSurphOutput::getStageKey(int& numJuvSites) const
{
//    stringstream ss;
    QString outstr;
    if (numJuvSites == 0)
        outstr = QString(" (A)");
//        ss << " (A)";
    else if (numJuvSites > 0)
    {
        --numJuvSites;
        outstr = QString(" (J)");
//        ss << " (J)";
    }

    return QString(outstr);//ss.str();
}
