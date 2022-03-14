/*
*/

#ifndef PPFishData_h
#define PPFishData_h

#include <string>
#include <vector>

//#include <boost/multi_index_container.hpp>
//#include <boost/multi_index/member.hpp>
//#include <boost/multi_index/hashed_index.hpp>

#include "PitProSettings.h"

#include <QStringList>
#include <QMap>

class Site;

/*
 * A multi_index container for holding the non-obs data for each fish.
 */
struct FishSetEntry
{
    enum RecapType {Mort=0, Recap};
    FishSetEntry(const QString& pitCode, double relTime, const QString& relSite, const QStringList& icovs,
        const QString& riverkm = "") :
      pitCode(pitCode), relSite(relSite), relTime(relTime), icovs(icovs), recapTime(-1), recapSite(0),
      riverkm(riverkm) {}

    QString pitCode;
    QString relSite;
    double relTime;
    QStringList icovs;
    double recapTime;
    const Site* recapSite;
    QString riverkm;

};

/* tags for accessing the corresponding indices of fishdata_set */
struct PitCodeTag{};

/* fish set typedef */
//typedef boost::multi_index_container
//<
//    FishSetEntry,
//    boost::multi_index::indexed_by
//    <
//        boost::multi_index::hashed_unique
//        <
//            boost::multi_index::tag<PitCodeTag>,
//            boost::multi_index::member<FishSetEntry, QString, &FishSetEntry::pitCode>
//        >
//    >
//> FishSet;

//typedef FishSet::index<PitCodeTag>::type PitCodeIndexType;


class PPFishData
{
public:
    PPFishData();
    void addFish( const QString& pitTag, double relTime, const QString& relSite, const QStringList& icovs );
    void updateRecapData(const QString &pitTag, double recapTime, const Site* recapSite,
         const QString &riverKm );
    const FishSetEntry& get( const QString& pitTag ) const;

    void begin();
    bool next();

    bool setCurrent( const QString& pitTag );
    void deleteCurrent();
    const QString &getCurrentPitCode() const;
    const QString& getCurrentRelSite() const;
    const QString& getCurrentTagGroup() const;
    const QString& getCurrentRiverKm() const;
    const QStringList& getCurrentICovs() const;
    double getCurrentRelTime() const;
    double getCurrentRecapTime() const;
    const Site* getCurrentRecapSite() const;

    size_t size() const { return fishmap.size(); }
    int count() const {return fishmap.count();}

private:
    QMap <QString, FishSetEntry*> fishmap;
    QMap <QString, FishSetEntry*>::const_iterator currentMap;
    FishSetEntry *currentEntry;
    QString curPitCode;
//    FishSet fishes;
//    PitCodeIndexType::iterator current;
    void get();
};

#endif
