/*
*
* The number of juvenile sites can be set to help
* the program determine the stage of each site. The
* number of main fields will be the number of fields
* that have their own field in the capture history. If
* the mask has more sites then the difference between
* the the number of main sites and the number of total
* sites are all combined in a final field.
*/

#ifndef SitesMask_h
#define SitesMask_h

#include <vector>

#include <ArrayDefs.h>

class Site;

typedef std::vector<const Site*> SitesMaskVector;

class SitesMask 
{
public:
	enum HistMode {Juvenile, Adult};
	SitesMask() : numJuvenileSites(-1), numMainSites(-1), siteRel(false) {}
	void init( const cbr::StringVector& juvSites, const cbr::StringVector& adultSites, int numMainSites );
	void addSite (const Site* site);
	void addSite (const char* code);
	void autoConfigure (const Site* firstSite);
	void setNumJuvenileSites (int num) { numJuvenileSites = num; }
	void setNumMainSites (int num) { numMainSites = num; }
	void setSiteRel (bool rhs) { siteRel = rhs; }
	void setHistMode (HistMode hm) { mode = hm; }

	const SitesMaskVector& getVector() const { return mask; }
	const Site* getSite( size_t i ) const;
	size_t getNumJuvenileSites() const { return numJuvenileSites; }
	size_t getNumMainSites() const { return numMainSites; }
	size_t getNumSites() const { return mask.size(); }
	bool isSiteRel() const { return siteRel; }
	HistMode getHistMode() const { return mode; }
	size_t numPeriods() const;

private:
	SitesMaskVector mask;
	int numJuvenileSites;
	int numMainSites;
	bool siteRel;
	HistMode mode;
};

#endif
