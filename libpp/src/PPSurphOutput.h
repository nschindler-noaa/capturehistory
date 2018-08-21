/*
 *
 */

#ifndef PPSurphOutput_h
#define PPSurphOutput_h

#include <string>
#include <ArrayDefs.h>
#include <SitesMask.h>

#include "PPFileOutput.h"
#include "RunConfigVector.h"

class PPTmpOutput : public PPFileOutput
{
public:
	std::string getFileName(const std::string& prefix) const;
	void write ( const std::string& text ) 
	{ 
		if (ofs.is_open())
			ofs << text;
	}
};


class PPSurphOutput : public PPFileOutput
{
public:
	std::string getFileName (const std::string& prefix) const;
	void write (const std::string& outPrefix, const SitesMask& fieldNames,
		 const RunConfigVector& runConfigVector,
		const cbr::IntVector& groupSizes, bool writeICovs);
	void writeHist (ObsSequence& seq, const SitesMask& mask, bool checkForErrors);
	void writeFooter ();
	bool active() const;
	void close();
	void closeAndDelete();
	void setPrefix( const std::string& prefix );
	void setNumICovs(int n) { numICovs = n; }

private:
	PPTmpOutput tmpOut;

	int numICovs;

	std::string getSurphFileLegend (const SitesMask& mask, bool lengthCovar, const std::string& format) const;
	std::string getStageKey(int& numJuvSites) const;
	void writeHeader (const std::string& outPrefix, const SitesMask& fieldNames,
				 const RunConfigVector& runConfigVector,
		const cbr::IntVector& groupSizes, bool writeICovs);
	void writeSurph1Header (const std::string& outPrefix, const SitesMask& fieldNames,
		const cbr::StringVector& groupNames, const cbr::IntVector& groupSizes, bool writeICovs);
	void writeSurph2Header (const std::string& outPrefix, const SitesMask& fieldNames,
		const cbr::StringVector& groupNames, const cbr::IntVector& groupSizes, bool writeICovs);
	void writeRosterHeader();

};

#endif
