/*
*/

#include <Site.h>
#include <DateConverter.h>

#include "PPFishData.h"

using std::string;
using std::vector;

using boost::multi_index_container;
using namespace boost::multi_index;

using cbr::DateConverter;

/*
 * Unary functions for calls to modify
 */

struct change_recap_data
{
	change_recap_data( double time, const Site* recapSite, const string& rkm ) : 
    time( time ), recapSite( recapSite ), riverkm(rkm) {}

	void operator()( FishSetEntry& f ) {
		f.recapTime = time;
		f.recapSite = recapSite;
        f.riverkm = riverkm;
	}

private:
	double time;
	const Site* recapSite;
    string riverkm;
};

PPFishData::PPFishData() 
{
	current = fishes.end();
}

/*
 * Mutator methods
 */

void PPFishData::addFish( const string& pitTag, double relTime, const string& relSite, const vector<string>& icovs) {
	FishSetEntry entry( pitTag, relTime, relSite, icovs );
	fishes.insert( entry );
}

void PPFishData::updateRecapData( const string& pitCode, double recapTime, 
								 const Site* recapSite, const string& rkm)
{
	// update the record
    if ( setCurrent( pitCode ) ) {
        double currentRecapTime = getCurrentRecapTime();
        PitCodeIndexType& index = fishes.get<PitCodeTag>();
        if ( currentRecapTime == -1 || recapTime < currentRecapTime )  // keep the first recap
            index.modify( current, change_recap_data( recapTime, recapSite, rkm ) );
    }
}

void  PPFishData::begin() {
	PitCodeIndexType& index = fishes.get<PitCodeTag>();
	current = index.begin();
}

bool PPFishData::next() {
	PitCodeIndexType& index = fishes.get<PitCodeTag>();
	if ( current == index.end() || ++current == index.end() )
		return false;
	return true;
}


bool PPFishData::setCurrent( const string& pitCode ) {
	// get the pittag index into fishes
	PitCodeIndexType& index = fishes.get<PitCodeTag>();

	if ( current != index.end() && !pitCode.compare( current->pitCode ) )
		return true;

	// update the record
	current = index.find( pitCode );

	return current != index.end();
}

void PPFishData::deleteCurrent() {
	// get the pittag index into fishes
	PitCodeIndexType& index = fishes.get<PitCodeTag>();

	if ( current != index.end() ) {
		index.erase( current );
		current = index.end();
	}
}

/*
 * Assume current is pointing to a valid record
 */
const string& PPFishData::getCurrentPitCode() const {
	return current->pitCode;
}

const string& PPFishData::getCurrentRelSite() const {
	return current->relSite;
}

double PPFishData::getCurrentRelTime() const {
	return current->relTime;
}

const vector<string>& PPFishData::getCurrentICovs() const {
	return current->icovs;
}

double PPFishData::getCurrentRecapTime() const {
	return current->recapTime;
}

const Site* PPFishData::getCurrentRecapSite() const {
	return current->recapSite;
}

const string& PPFishData::getCurrentRiverKm() const {
	return current->riverkm;
}

