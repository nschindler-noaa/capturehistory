/*
 * This is the run configuration information written into the output directory for
 * later retrieval by the ResultsManager class.
 *
 * Design pattern: singleton
 */

#ifndef PPRunInfo_h
#define PPRunInfo_h

#include <string>
#include <sstream>

#include <QStringList>

#include <QDomDocument>

#include <ArrayDefs.h>

#include "RunConfigVector.h"

class SitesMask;

class PPRunInfo
{
public:
    static PPRunInfo& instance();

    static QString serialize( const QString& prefix, const RunConfigVector& runConfigVector );
    bool save( const QString& prefix, const QString& xml );

    QString getConfigFileName( const QString& prefix );
    QString read( const QString& inFile );
    bool parse( const QString& xml );
    bool load( const QString& prefix );

    // accessors
    RunConfigVector getRunConfig() const;

    QStringList &getRunNames() const;
    QStringList &getObsFiles() const;
    QStringList &getTagFiles() const;
    QStringList &getMortFiles() const;
    QStringList &getRecapFiles() const;
    QStringList &getJuvenileSites() const;
    QStringList &getAdultSites() const;
    QStringList &getAllSites() const;

    QString getDataDir() const;
    QString getOutputDir() const;
    QString getOutputFormat() const;

    bool isSiteRel() const;

    int getNumMainSites() const;

    bool isCombined();

    static QString protect(const QString& s);
    static QString unProtect(const QString& s);

private:
    PPRunInfo();
    ~PPRunInfo();

    QDomDocument doc;
    std::stringstream errorStream;
    QStringList &getValues( const char* tagName ) const;
    QString getValue( const char* tagName ) const;

    QStringList *allSites;
};

#endif
