/*
*/

#include <Site.h>
#include <DateConverter.h>

#include "PPFishData.h"

using std::string;
using std::vector;

//using boost::multi_index_container;
//using namespace boost::multi_index;

using cbr::DateConverter;
#include <QStringList>
#include <QMap>

/*
 * Unary functions for calls to modify
 */

struct change_recap_data
{
    change_recap_data( double time_, const Site* recapSite_, const QString& rkm_ ) :
    time( time_ ), recapSite( recapSite_ ), riverkm(rkm_) {}

    void operator()( FishSetEntry& f ) {
        f.recapTime = time;
        f.recapSite = recapSite;
        f.riverkm = riverkm;
    }

private:
    double time;
    const Site* recapSite;
    QString riverkm;
};

PPFishData::PPFishData()
{
    currentMap = fishmap.end();
//    current = fishes.end();
}

/*
 * Mutator methods
 */

void PPFishData::addFish( const QString& pitTag, double relTime, const QString& relSite, const QStringList& icovs) {
    FishSetEntry entry( pitTag, relTime, relSite, icovs );
    fishmap.insert(pitTag, new FishSetEntry(entry));
//    fishes.insert( entry );
}

void PPFishData::updateRecapData( const QString& pitCode, double recapTime,
                                 const Site* recapSite, const QString& rkm)
{
    // update the record
    if (setCurrent(pitCode)) {
        double currentRecapTime = getCurrentRecapTime();
        // keep the first recap
        if (currentRecapTime < 0 || recapTime < currentRecapTime) {
            currentMap.value()->recapTime = recapTime;
            currentMap.value()->recapSite = recapSite;
            currentMap.value()->riverkm = rkm;
        }
    }
//    if ( setCurrent( pitCode ) ) {
//        double currentRecapTime = getCurrentRecapTime();
//        PitCodeIndexType& index = fishes.get<PitCodeTag>();
//        if ( currentRecapTime == -1 || recapTime < currentRecapTime )  // keep the first recap
//            index.modify( current, change_recap_data( recapTime, recapSite, rkm ) );
//    }
}

void  PPFishData::begin() {
//    PitCodeIndexType& index = fishes.get<PitCodeTag>();
//    current = index.begin();
    currentMap = fishmap.begin();
}

bool PPFishData::next() {
    bool end = false;
    if (currentMap == fishmap.end() || ++currentMap == fishmap.end())
        end = true;
    return !end;
//    PitCodeIndexType& index = fishes.get<PitCodeTag>();
//    if ( current == index.end() || ++current == index.end() )
//        return false;
//    return true;
}


bool PPFishData::setCurrent(const QString &pitCode ) {
    curPitCode = pitCode;
    currentEntry = fishmap[curPitCode];
    currentMap = fishmap.find(curPitCode);
    // get the pittag index into fishes
//    PitCodeIndexType& index = fishes.get<PitCodeTag>();

//    if ( current != index.end() && !pitCode.compare( current->pitCode ) )
//        return true;

    // update the record
//    current = index.find( pitCode );
    return currentMap != fishmap.end();
//    return current != index.end();
}

void PPFishData::deleteCurrent() {
    // get the pittag index into fishes
//    PitCodeIndexType& index = fishes.get<PitCodeTag>();
    if (!fishmap.isEmpty() && currentMap != fishmap.end()) {
        QString pcode (currentMap.value()->pitCode);
        QString begin (fishmap.begin().value()->pitCode);
        setCurrent(begin);
        fishmap.remove(pcode);
    }

//    if ( current != index.end() ) {
//        index.erase( current );
//        current = index.end();
//    }
}

/*
 * Assume current is pointing to a valid record
 */
const QString& PPFishData::getCurrentPitCode() const {
    return currentMap.value()->pitCode;
//    return current->pitCode;
}

const QString& PPFishData::getCurrentRelSite() const {
    return currentMap.value()->relSite;
//    return current->relSite;
}

double PPFishData::getCurrentRelTime() const {
    return currentMap.value()->relTime;
//    return current->relTime;
}

const QStringList& PPFishData::getCurrentICovs() const {
    return currentMap.value()->icovs;
//    return current->icovs;
}

double PPFishData::getCurrentRecapTime() const {
    return currentMap.value()->recapTime;
//    return current->recapTime;
}

const Site* PPFishData::getCurrentRecapSite() const {
    return currentMap.value()->recapSite;
//    return current->recapSite;
}

const QString& PPFishData::getCurrentRiverKm() const {
    return currentMap.value()->riverkm;
//    return current->riverkm;
}

