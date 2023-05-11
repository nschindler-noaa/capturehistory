/*
*/

#ifndef PPFishData_h
#define PPFishData_h

#include <string>
#include <vector>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>

#include "PitProSettings.h"

class Site;

/*
 * A multi_index container for holding the non-obs data for each fish.
 */
struct FishSetEntry
{
	enum RecapType {Mort=0, Recap};
    FishSetEntry( const std::string& pitCode, double relTime,
                  const std::string& relSite,
                  const std::vector<std::string>& icovs,
                  const std::string& riverkm = "") :
      pitCode( pitCode ), relSite( relSite ), relTime( relTime ), icovs(icovs),
      recapTime( -1 ), recapSite( 0 ), riverkm( riverkm) {}

	std::string pitCode;
	std::string relSite;
	double relTime;
	std::vector<std::string> icovs;
	double recapTime;
	const Site* recapSite;
    std::string riverkm;

};

/* tags for accessing the corresponding indices of fishdata_set */
struct PitCodeTag{};

/* fish set typedef */
typedef boost::multi_index_container<
	FishSetEntry,
	boost::multi_index::indexed_by<
		boost::multi_index::hashed_unique<
			boost::multi_index::tag<PitCodeTag>, 
			boost::multi_index::member<FishSetEntry, std::string, &FishSetEntry::pitCode>
		>
	>
> FishSet;
	
typedef FishSet::index<PitCodeTag>::type PitCodeIndexType;


class PPFishData
{
public:
	PPFishData();
	void addFish( const std::string& pitTag, double relTime, const std::string& relSite, const std::vector<std::string>& icovs );
	void updateRecapData( const std::string& pitTag, double recapTime, const Site* recapSite, 
         const std::string& riverKm );
	const FishSetEntry& get( const std::string& pitTag ) const;

	void begin();
	bool next();

	bool setCurrent( const std::string& pitTag );
	void deleteCurrent();
	const std::string& getCurrentPitCode() const;
	const std::string& getCurrentRelSite() const;
	const std::string& getCurrentTagGroup() const;
	const std::string& getCurrentRiverKm() const;
	const std::vector<std::string>& getCurrentICovs() const;
	double getCurrentRelTime() const;
	double getCurrentRecapTime() const;
	const Site* getCurrentRecapSite() const;

	size_t size() const { return fishes.size(); }
private:
	FishSet fishes;
	PitCodeIndexType::iterator current;
	void get();
};

#endif
