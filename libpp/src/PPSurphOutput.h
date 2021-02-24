/*
 *
 */

#ifndef PPSurphOutput_h
#define PPSurphOutput_h

#include <string>
#include <ArrayDefs.h>
#include <SitesMask.h>

#include <QStringList>

#include "PPFileOutput.h"
#include "RunConfigVector.h"

class PPTmpOutput : public PPFileOutput
{
public:
    QString getFileName(const QString prefix) const;
    void write (const QString &text)
    {
        if (ofs.is_open())
            ofs << text.toStdString();
    }
    void write ( const std::string& text )
    {
        if (ofs.is_open())
            ofs << text;
    }
};


class PPSurphOutput : public PPFileOutput
{
public:
    QString getFileName (const QString prefix) const;
    void write (const QString &outPrefix, const SitesMask& fieldNames,
         const RunConfigVector& runConfigVector,
        const cbr::IntVector& groupSizes, bool writeICovs);
    void writeHist (ObsSequence& seq, const SitesMask& mask, bool checkForErrors);
    void writeFooter ();
    bool active() const;
    void close();
    void closeAndDelete();
    void setPrefix(const QString prefix );
    void setNumICovs(int n) { numICovs = n; }

private:
    PPTmpOutput tmpOut;

    int numICovs;

    QString getSurphFileLegend (const SitesMask& mask, bool lengthCovar, const QString &format) const;
    QString getStageKey(int& numJuvSites) const;
    void writeHeader (const QString &outPrefix, const SitesMask& fieldNames,
                 const RunConfigVector& runConfigVector,
        const cbr::IntVector& groupSizes, bool writeICovs);
    void writeSurph1Header (const QString& outPrefix, const SitesMask& fieldNames,
        const QStringList& groupNames, const cbr::IntVector& groupSizes, bool writeICovs);
    void writeSurph2Header (const QString& outPrefix, const SitesMask& fieldNames,
        const QStringList& groupNames, const cbr::IntVector& groupSizes, bool writeICovs);
    void writeRosterHeader();

    QString outstr;

};

#endif
