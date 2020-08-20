/*
* Represent the sequence of observations for one fish. Each
* record in the sequence contains the location, outcome,
* and detection time information.
*
*/

#ifndef ObsSequence_h
#define ObsSequence_h 

#include <string>
#include <vector>
#include <iostream>
#include <functional>

#include "CbrPit.h"
#include "ObsErrors.h"

class Site;
class SitesMask;

#define PP_NULL_RELEASE_DATE -1
#define PP_NULL_MIGRATION_YEAR -1
#define PP_NULL_CUTOFF_DATE -1

class ObsRecord
{
public:
	ObsRecord();
	ObsRecord (const Site* site, cbr::CbrPit::Stage stage, cbr::CbrPit::Outcome outcome,
		double firstDate, double lastDate, int hits );
	ObsRecord (const Site* site, cbr::CbrPit::Stage stage, cbr::CbrPit::Outcome outcome);
	~ObsRecord () {}
	//ObsRecord (const ObsRecord&);
	//ObsRecord& operator= (const ObsRecord& rec);

	void setSite (const Site* s) { site = s; }
	void setStage (cbr::CbrPit::Stage st) { stage = st; }
	void setOutcome (cbr::CbrPit::Outcome oc) { outcome = oc;}
	void setFirstDate (double date) { firstDate = date; }
	void setLastDate (double date) { lastDate = date; }
	void setIsRecap (bool rhs ) { recap = rhs; }
	void addCoilHits (int hits) { coilHits += hits; }
    void setRiverKm( const std::string& rkm) { riverkm = rkm; }
	cbr::CbrPit::Outcome getOutcome () const { return outcome; }
    cbr::CbrPit::Stage getStage () const { return stage; }
	double getFirstDate() const { return firstDate; }
	double getLastDate () const { return lastDate; }
	const Site& getSite () const { return *site; }
	const Site* getSitePointer() const { return site; }
	bool isDownstream (const ObsRecord& rec) const;
	bool isRecap() const { return recap; }
	int getAge() const;
    void setAge(int migrationYear, double date, bool useSteelheadYear = false);
	int getCoilHits() const { return coilHits; }
    const std::string& getRiverKm() const { return riverkm; }

	static const ObsRecord null;

	friend bool operator== (const ObsRecord& or1, const ObsRecord& or2 );
	friend bool operator!= (const ObsRecord& or1, const ObsRecord& or2 );
	friend std::ostream& operator<< (std::ostream& os, const ObsRecord& seq);

private:
	const Site* site;
	cbr::CbrPit::Stage stage;
	cbr::CbrPit::Outcome outcome;
	double firstDate;
	double lastDate;
	int coilHits;
	bool recap;
    int age;
    std::string riverkm; // supplied by rel/mort file, may be empty 
};

class ObsRecPrinter  
{
public:
	ObsRecPrinter (std::ostream& rhs) : os(rhs) {}
	virtual void operator() (const ObsRecord& rec) = 0;
protected:
	std::ostream& os;
};


typedef std::vector<ObsRecord> ObsRecordVector;

class ObsSequence 
{
public:
    enum CompressionMethod { LastOutcomeRules, RemovalTrumpsAll, ShowAllCodes };
	enum TransformMethod { LastRoute, FirstRoute, AnyObs };

	ObsSequence ();
	~ObsSequence () {}
	//ObsSequence (const ObsSequence&);
	//ObsSequence& operator= (const ObsSequence& seq);

    static void setJuvenileCutoffDate (double jcd);// { juvCutoffDate = jcd; }
    static void setMigrationYear (int year);// { migrationYear = year; }
    static void setJacksPolicy( cbr::CbrPit::JacksPolicy jp );// { jacksPolicy = jp; }
	static double getCutoffDate();
	static int getMigrationYear();
    static void setUseSteelheadYear(bool rhs);// { useSteelheadYear = rhs; }


	size_t numRecs() const { return sequence.size(); }

	bool isMatch (const std::string& pitCode) const; 
	int compare(const std::string& pitCode) const;
	bool isValid () const { return !pitCode.empty (); }
	bool isOutOfSequence() const;
	bool isTransportedDetected() const;
	bool isFirstReturned(const SitesMask& mask) const;
	bool hasMinijacks() const;
	bool isStagesSet() const;
	bool isPreRecap( const SitesMask& mask );
	bool isPreRemoved( const SitesMask& mask );
	bool isPreRel();
	bool isResidualized() const;
	bool isResidualized2( double springCutoffDate ) const;

	void clear();
	void reset( const std::string& pitCode );
	void setPitCode (const std::string& rhs) { pitCode = rhs; }
	void setReleaseDate (double rd) { releaseDate = rd; }
	void setICovs(const std::vector<std::string>& icv) { icovs = icv; }
	bool isMissingICov() const;
	void clearICovs() { icovs.clear(); }
	void setTransportedToUnknown();
	void addRecord (const Site* site, cbr::CbrPit::Stage stage, cbr::CbrPit::Outcome outcome,
		double firstDate, double lastDate, int hits);	
    void addRecapRecord (const Site* site, double date, const std::string& riverkm);
	const Site* getLastSite() const;
	void setStages(cbr::CbrPit::Stage stage = cbr::CbrPit::ST_Unknown);
	void setOutputCovars(bool rhs) { outputCovars = rhs; }

	double getReleaseDate() const { return releaseDate; }
	const std::string& getPitCode() const { return pitCode; }
	const ObsErrors& getErrors() const { return errors; }
	const ObsRecordVector& getSequence() const { return sequence; }
	const ObsRecord& getRecord (const Site& site, cbr::CbrPit::Stage stage) const;
	const ObsRecord& getFirstRecord () const;
	const ObsRecord& getNextRecord (const ObsRecord& rec ) const;

	const std::vector<std::string>& getIcovs() const { return icovs; }

	void sort();
	void sortJuvenileRecap();
    ObsRecordVector applyMaskSimple(const SitesMask& mask, bool showAll) const;
    void applyMask(const SitesMask& mask, bool showAll);
	bool removeStrays (const Site& lastAdultSite); 
	bool removeSingleHits ();
	const ObsSequence& compress (CompressionMethod method );
	const ObsSequence& transform (TransformMethod method );
    bool truncateAtRecap();
    bool truncateJuvenileUpstream(const SitesMask& mask);
    bool updateTransportedDetected();
    bool isValidCursor() const { return it_seq != sequence.end(); }
    const ObsRecord& getCursorRecord() const { return *it_seq; }


	// output
    std::string hist (const SitesMask& mask) const;
    std::string dd (const SitesMask& mask, bool julianDates = true, bool showAll=false) const;
    std::string tt (const SitesMask& mask, bool showAll) const;

	friend std::ostream& operator<< (std::ostream& os, const ObsSequence& seq);

	static const int FW;
	static const int P;

private:
	static double juvCutoffDate;
	static int migrationYear;
	static cbr::CbrPit::JacksPolicy jacksPolicy;
	static bool useSteelheadYear;

	std::string pitCode;
	double releaseDate;
	std::vector<std::string> icovs;
	bool outputCovars;
	bool recap;

	ObsErrors errors;

	ObsRecordVector sequence;
    ObsRecordVector::iterator it_seq; // multi-use cursor

	void traverseHist (const SitesMask& mask, ObsRecPrinter& printer) const;
	cbr::CbrPit::JacksPolicy getJacksPolicy() const { return jacksPolicy; }

    int getJuvenileYear();
    bool rangeCheckStage( cbr::CbrPit::Stage a, cbr::CbrPit::Stage b, cbr::CbrPit::Stage current) const;
    bool rangeCheckSequence(const Site* siteA, cbr::CbrPit::Stage stageA,
        const Site* siteB, cbr::CbrPit::Stage stageB, 
        const ObsRecord& currentRec, const ObsRecord* prevRec) const;
    void buildRangeRecord(ObsRecord& maskRec, const Site* nextSite, cbr::CbrPit::Stage nextStage , bool keepAll);

    void transform_last_route ();
    void transform_any_obs ();
    void compress_removal_trumps_all();
    void compress_show_all_codes();
	void compress_last_outcome_rules();



};


#endif // !ObsSequence_h 
