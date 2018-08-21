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

#include <QDomDocument>

#include <ArrayDefs.h>

#include "RunConfigVector.h"

class SitesMask;

class PPRunInfo
{
public:
	static PPRunInfo& instance();

	static std::string serialize( const std::string& prefix, const RunConfigVector& runConfigVector );
	bool save( const std::string& prefix, const std::string& xml );

	std::string getConfigFileName( const std::string& prefix );
	std::string read( const std::string& inFile );
	bool parse( const std::string& xml );
	bool load( const std::string& prefix );

	// accessors
	RunConfigVector getRunConfig() const;

	cbr::StringVector getRunNames() const;
	cbr::StringVector getObsFiles() const;
	cbr::StringVector getTagFiles() const;
	cbr::StringVector getMortFiles() const;
	cbr::StringVector getRecapFiles() const;
    cbr::StringVector getJuvenileSites() const;
    cbr::StringVector getAdultSites() const;
	cbr::StringVector getAllSites() const;

    std::string getDataDir() const;
    std::string getOutputDir() const;
    std::string getOutputFormat() const;

	bool isSiteRel() const;

    int getNumMainSites() const;

	bool isCombined();

	static std::string protect(const std::string& s);
	static std::string unProtect(const std::string& s);

private:
	PPRunInfo();
	~PPRunInfo();

	QDomDocument doc;
	std::stringstream errorStream;
	cbr::StringVector getValues( const char* tagName ) const;
    std::string getValue( const char* tagName ) const;

};

#endif
