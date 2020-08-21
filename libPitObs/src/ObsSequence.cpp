/*
*
*/

#include <algorithm>
#include <sstream>

#include <DateConverter.h>
#include <Site.h>
#include <RiverKm.h>

#include "ObsSequence.h"
#include "SitesMask.h"


using std::string;
using std::vector;
using std::ostream;
using std::endl;
using std::cout;
using std::reverse;
using std::binary_function;
using std::unary_function;
using std::stringstream;
using std::for_each;
using namespace cbr;

// static vars
const int ObsSequence::FW = 15;
const int ObsSequence::P  =  6;
CbrPit::JacksPolicy ObsSequence::jacksPolicy = CbrPit::JP_Seperate;
int ObsSequence::migrationYear = PP_NULL_MIGRATION_YEAR;
double ObsSequence::juvCutoffDate = -1;
bool ObsSequence::useSteelheadYear = false;

ObsRecord::ObsRecord ()
{
    site = 0;
    stage = CbrPit::ST_Unknown;
    outcome = CbrPit::NoDetect;
    firstDate = 0;
    lastDate = 0;
    coilHits = 0;
    recap = false;
    age = 0;
}

ObsRecord::ObsRecord (const Site* s, CbrPit::Stage st, CbrPit::Outcome oc, 
                      double fd, double ld, int hits )
{
    site = s;
    stage = st;
    outcome = oc;
    firstDate = fd;
    lastDate = ld;
    coilHits = hits;
    recap = false;
    age = 0;
}

ObsRecord::ObsRecord (const Site* s, CbrPit::Stage st, CbrPit::Outcome oc )
{
    site = s;
    stage = st;
    outcome = oc;
    firstDate = 0;
    lastDate = 0;
    coilHits = 0;
    recap = false;
    age = 0;
}

const ObsRecord ObsRecord::null;


int ObsRecord::getAge() const
{ return age; }

/*
* Age is defined to be the number of winters a fish
* has experienced since release. Jacks and juveniles
* will have the same age
*/
void ObsRecord::setAge( int migrYear, double date, bool useSteelheadYear ) {
    if ( migrYear != PP_NULL_MIGRATION_YEAR) {
	    DateConverter dc (date);
	    age = dc.year() - migrYear;
		//int month = dc.month();
		if (useSteelheadYear && dc.month() <= 6) 
			age -= 1;
    }
}


/*
* Remove true if the sites for the record is
* downstream of the given site. Return false
* if the riverk for either site is null. This
* determination is made irregardless of stage.
*/
bool ObsRecord::isDownstream (const ObsRecord& target) const
{
	const Site& thisSite = getSite();
	const Site& targetSite = target.getSite();
	return thisSite.isDownstream(&targetSite);
}


bool operator== ( const ObsRecord& or1, const ObsRecord& or2 )
{
	if ( or1.site != or2.site )
		return false;
	if ( or1.stage != or2.stage )
		return false;
	if ( or1.outcome != or2.outcome )
		return false;
	if ( or1.firstDate != or2.firstDate )
		return false;
	if ( or1.lastDate != or2.lastDate )
		return false;
	if ( or1.coilHits != or2.coilHits )
		return false;

	return true;
}

bool operator!= ( const ObsRecord& or1, const ObsRecord& or2 )
{ return !( or1 == or2 ); }


ostream& operator<< (ostream& os, const ObsRecord& rec)
{
	if (rec == ObsRecord::null )
		os << "NULL";
	else {
		if ( rec.site )
			os << rec.site->getSiteCode ();
		else 
			os << "lf"; // null site implies last field

		os << ".";
		switch (rec.stage) 
		{
		case CbrPit::ST_Adult :
			os << "A";
			break;
		case CbrPit::ST_Juvenile :
			os << "J";
			break;
		default:
			os << "U";
		}

		os << ".";
		switch (rec.outcome) 
		{
		case CbrPit::Hold :
			os << "H";
			break;
		case CbrPit::Returned :
			os << "R";
			break;
		case CbrPit::Sampled :
			os << "S";
			break;
		case CbrPit::Transported :
			os << "T";
			break;
		case CbrPit::Unknown :
			os << "U";
			break;
		case CbrPit::Bypass :
			os << "B";
			break;
		case CbrPit::Invalid :
			os << "I";
			break;
		case CbrPit::NoDetect :
			os << "N";
            break;
        case CbrPit::Weir:
            os << "W";
            break;
        case CbrPit::AMBridge:
            os <<"M";
            break;
        case CbrPit::PileDike:
            os <<"D";
            break;
        case CbrPit::PitBarge:
            os <<"G";
            break;
        case CbrPit::AvianColony:
            os <<"V";
            break;
        case CbrPit::Spillway:
            os <<"P";
            break;
        case CbrPit::BonnLadder:
            os <<"W";
            break;
        case CbrPit::PitTrawl:
            os <<"R";
            break;
        case CbrPit::AdultDetect:
            os <<"A";
            break;
		default:
			os << "?";
		}
	}

	return os;
}


ObsSequence::ObsSequence () /*:
releaseDate(PP_NULL_RELEASE_DATE), outputCovars(false), recap(false),
it_seq(sequence.end())*/
{
    releaseDate = PP_NULL_RELEASE_DATE;
    outputCovars= false;
    recap = false;
    it_seq = (sequence.end());
}

void ObsSequence::setJuvenileCutoffDate (double jcd)
{
    juvCutoffDate = jcd;
}

void ObsSequence::setMigrationYear (int year)
{
    migrationYear = year;
}

void ObsSequence::setJacksPolicy( cbr::CbrPit::JacksPolicy jp )
{
    jacksPolicy = jp;
}

void ObsSequence::setUseSteelheadYear(bool rhs)
{
    useSteelheadYear = rhs;
}


bool ObsSequence::isMatch( const string& pc) const
{
	return !pitCode.compare(pc);
}

int ObsSequence::compare( const string& pc) const
{
	return pitCode.compare(pc);
}

/* 
* Check sequence based on riverk. If a site has a riverk span, assume it's
* ok. Check adult upriver migration too, fallbacks should have been dealt with.
*/
bool ObsSequence::isOutOfSequence() const {
	const Site* prev = 0;
	bool prevJuvenile = true;
	vector<ObsRecord>::const_iterator it;
	for (it = sequence.begin(); it != sequence.end(); ++it) 
	{
		const ObsRecord& rec = *it;
        if (rec != ObsRecord::null && !rec.isRecap()) {
			const Site* current = rec.getSitePointer();
			if (current) {
				if (prev) {
					if (rec.getStage() == CbrPit::ST_Juvenile) {
						if (prev->isDownstream(current, Site::RK_Up))
							return true;
					}
					else {
						if (!prevJuvenile && current->isDownstream(prev, Site::RK_Down))
							return true;

						if (prevJuvenile)
							prevJuvenile = false;
					}
				}

				prev = current;
			}
		}
	}

	return false;
}

/* 
* Return true if their is an obs record with
* a return to river for the first site in the
* mask.
* 
* pre: sequence should be sorted, stages set, and compressed prior to calling this.
*
*/
bool ObsSequence::isFirstReturned(const SitesMask& mask) const 
{
	const SitesMaskVector& maskVector = mask.getVector();

	if (maskVector.size() > 0) {
		int numJuvenileSites = mask.getNumJuvenileSites();
		CbrPit::Stage stage = (numJuvenileSites > 0) ? CbrPit::ST_Juvenile : CbrPit::ST_Adult;
		SitesMaskVector::const_iterator it = maskVector.begin();
		const Site* site = *it;
		const ObsRecord& firstRec = getRecord (*site, stage);

		// for fish detected at first mask site
		if ( firstRec != ObsRecord::null ) {
			CbrPit::Outcome oc = firstRec.getOutcome();

			if (oc == CbrPit::Returned || oc == CbrPit::Bypass)  
				return true;
		} 
	}

	return false;
}

/*
 * Return true if a fish supposed juvenile observation happens outside of the migration
 * year. This check should be run based on the only the detectors where the stage is known,
 * before migration year is used to determine the stage, since this check is based on comparing 
 * the stage to the migration year.
 */

bool ObsSequence::isResidualized() const {
	if (migrationYear != -1) {
		vector<ObsRecord>::const_iterator it;
		for (it = sequence.begin(); it !=sequence.end(); ++it) {
			const ObsRecord& rec = *it;
			DateConverter dc( rec.getFirstDate() );
			if (rec.getStage() == CbrPit::ST_Juvenile && dc.year() > migrationYear)
				return true;
		}
	}
	return false;
}

/*
 * Check for fish observed in the sprint of year following the migration year. This should
 * indicate a residualized fish. 
 */

bool ObsSequence::isResidualized2(double springCutoffDate) const {

	if (migrationYear != -1) {
		DateConverter dcc(springCutoffDate);
		vector<ObsRecord>::const_iterator it;
			for (it = sequence.begin(); it !=sequence.end(); ++it) {
			const ObsRecord& rec = *it;
			DateConverter dc( rec.getFirstDate() );
			if (dc.year() == migrationYear + 1 && dc < dcc) 
				return true;
		}
	}
	return false;
}



/*
* Return true if any of the records in the sequence do
* not have their stage set.
*/
bool ObsSequence::isStagesSet() const {
	vector<ObsRecord>::const_iterator it;
	for (it = sequence.begin(); it !=sequence.end(); ++it) 
	{
		if ((*it).getStage() == CbrPit::ST_Unknown)
			return false;
	}
	return true;
}

void ObsSequence::addRecord (const Site* site, CbrPit::Stage stage, 
							 CbrPit::Outcome outcome, double firstDate, double lastDate,
							 int hits)
{
	ObsRecord rec (site, stage, outcome, firstDate, lastDate, hits);
    rec.setAge(getMigrationYear(), firstDate, useSteelheadYear);
	sequence.push_back (rec);
}

void ObsSequence::addRecapRecord (const Site* site, double date, const string& riverkm)
{
	ObsRecord rec;
	rec.setSite( site );
	rec.setFirstDate( date );
	rec.setLastDate( date );
	rec.setOutcome( CbrPit::Sampled );
	rec.setStage( CbrPit::ST_Unknown );
	rec.setIsRecap( true );
	rec.addCoilHits(1);
    rec.setAge(getMigrationYear(), date, useSteelheadYear);
	rec.setRiverKm(riverkm);


	sequence.push_back(rec);
	recap = true;
}

/*
* Check for unkown stages and attempt to
* set the correct stage
*/
void ObsSequence::setStages(CbrPit::Stage stage)
{
	// and the sites
	vector<ObsRecord>::iterator it;
	for ( it = sequence.begin(); it !=sequence.end(); ++it ) 
	{
		ObsRecord& rec = (*it);
		if ( stage != CbrPit::ST_Unknown )
			rec.setStage (stage);
		else if (rec.getStage() == CbrPit::ST_Unknown) 
		{
			double cutoff = getCutoffDate();

			if ( cutoff != -1 )
			{			
				double lastDate = rec.getLastDate();
				if (lastDate > cutoff)
					rec.setStage( CbrPit::ST_Adult );
				else
					rec.setStage( CbrPit::ST_Juvenile );
			}
		}
	}
}


const Site* ObsSequence::getLastSite() const 
{
	if ( sequence.size() == 0 )
		return 0;
	else
		return sequence.back().getSitePointer();
}

/* 
* If there are any known juvenile detections,
* return the year of that/those detections
*/
int ObsSequence::getJuvenileYear()
{
	vector<ObsRecord>::iterator it;
	for (it = sequence.begin(); it !=sequence.end(); ++it) 
	{
		ObsRecord& rec = (*it);
		if (rec.getStage() == CbrPit::ST_Juvenile)
		{
			DateConverter dc (rec.getLastDate());
			return dc.year();

		}
	}

	return -1;
}

/*
* Determine the juvenile cutoff date based on 
* a juvCutoffDate if available, followed by migration year
* on 12/31 followed by release year on 12/31
*/
double ObsSequence::getCutoffDate()
{
	if (juvCutoffDate != PP_NULL_CUTOFF_DATE)
		return juvCutoffDate;
	else if (migrationYear != PP_NULL_MIGRATION_YEAR)
	{
		DateConverter dc(migrationYear, 12, 31);
		return dc.getTime();
	}
	return PP_NULL_CUTOFF_DATE;
}


/*
* Determine the migration year. If migration year
* is set, use that. Othewise use release year. Otherwise,
* return -1;
*/
int ObsSequence::getMigrationYear()
{
	if ( migrationYear != -1 )
		return migrationYear;
	if ( juvCutoffDate != -1 ) {
		DateConverter dc( juvCutoffDate );
		return dc.year();
	}

	return -1;
}


/*
* Remove any adult sites that are not in the same
* river system as the lastAdulSite which should be
* the most upstream adult site in the capture history.
* Remove true if any records are removed.
*/
bool ObsSequence::removeStrays (const Site& lastAdultSite) 
{
	if ( !lastAdultSite.validRiverkm())
		return false;

	size_t initialSize = sequence.size();
	vector<ObsRecord>::iterator it;
	for (it = sequence.begin(); it != sequence.end();)
	{
		const ObsRecord& rec = *it;
		const Site& currentSite = rec.getSite();
		if (rec.getStage() == CbrPit::ST_Adult && !currentSite.isDownstream(&lastAdultSite)) 
			it = sequence.erase(it);
		else
			++it;
	}

	return sequence.size() != initialSize;

}

/*
* Remove any record that has only 1 coil hit
*/
bool ObsSequence::removeSingleHits()
{
	size_t initialSize = sequence.size();
	vector<ObsRecord>::iterator it;
	for (it = sequence.begin(); it != sequence.end();)
	{
		const ObsRecord& rec = *it;
		if (!rec.isRecap() && rec.getCoilHits() == 1)
			it = sequence.erase(it);
		else
			++it;
	}

	return sequence.size() != initialSize;

}

/* 
 * If a fish is flagged as transported and then detected downstream,
 * change the flag to unkown. This will change only the first record
 * flagged as trnsport.
 * 
 * pre: sequence should be sorted, stages set, and compressed
 *
 * Return true if transported and detected downstream
 */
bool ObsSequence::updateTransportedDetected() 
{
    it_seq = sequence.end();

	vector<ObsRecord>::iterator it;
	for (it = sequence.begin(); it != sequence.end(); ++it) 
	{
		ObsRecord& rec = *it;
		const Site& site = rec.getSite();
		string siteCode( site.getSiteCode() );
		bool isTwx = siteCode.compare( "tw" ) == 0; // tranpsorted fish can normally be detected at twx
        if (isValidCursor() && rec.getStage() == CbrPit::ST_Juvenile && !isTwx ) {
            (*it_seq).setOutcome(CbrPit::Unknown);
            return true;
        }
        else if (!isValidCursor() && rec.getOutcome() == CbrPit::Transported) {
            it_seq = it;
        }
    }
    return false;
}

/*
* Truncate sequence at first recap. Keep the recap
*/
bool ObsSequence::truncateAtRecap() {
	vector<ObsRecord>::iterator it = sequence.begin();
    while (it != sequence.end() && !(*it).isRecap()) { ++it; }

    if (it == sequence.end() || ++it == sequence.end()) 
        return false;
    else {
        sequence.erase(it, sequence.end());
	    return true;
    }
}


/*
* Truncate sequence at first upstream (out of sequence for juveniles detection)
*/
bool ObsSequence::truncateJuvenileUpstream(const SitesMask& /*mask*/) {
	const Site* prev = 0;
	vector<ObsRecord>::iterator it;
	for (it = sequence.begin(); it != sequence.end(); ++it) 
	{
		const ObsRecord& rec = *it;
        if (rec != ObsRecord::null && !rec.isRecap()) {
			const Site* current = rec.getSitePointer();
			if (current) {
				if (prev) {
					if (rec.getStage() == CbrPit::ST_Juvenile) {
						if (prev->isDownstream(current, Site::RK_Up)) {
							sequence.erase(it, sequence.end());
							return true;
						}
					}
				}

				prev = current;
			}
		}
	}

	return false;
}


/*
* Sort by first observation time
*/
struct obs_record_less_time : public binary_function<const ObsRecord&, const ObsRecord&, bool> {
    bool operator()(const ObsRecord& x, const ObsRecord& y) 
    { 
        return x.getFirstDate() < y.getFirstDate();
    }
};
/*
 * Stages must be set before sort is called
 */
void ObsSequence::sort()
{
     // sort by time
	std::sort (sequence.begin(), sequence.end(), obs_record_less_time());
	sortJuvenileRecap();
}


void ObsSequence::sortJuvenileRecap() {
    // if there is a juvenile recap, put that in order based on riverk
    if (recap && sequence.size() > 1) {

        vector<ObsRecord>::iterator it_recap;
        for ( it_recap = sequence.begin(); it_recap != sequence.end(); ++it_recap) {
            ObsRecord& rec = *it_recap;
            if (rec.isRecap()) 
                break;
        }


        if (it_recap != sequence.end() && (*it_recap).getStage() == CbrPit::ST_Juvenile) {

            ObsRecord recap = *it_recap;

            // remove the recap from it's current position
            it_recap = sequence.erase(it_recap);

            // get the riverk
            RiverKm recapKm = recap.getRiverKm();
            if (!recapKm.isValid())
                recapKm = recap.getSite().getRiverKm(Site::RK_Up);

            // find the place where the recap should be based on riverk
            RiverKm currKm;
            reverse(sequence.begin(), sequence.end());
            vector<ObsRecord>::iterator it = sequence.begin();
            while (it != sequence.end()) {
                ObsRecord& rec = *it;

                if (rec.getStage() == CbrPit::ST_Juvenile) {
                    currKm = rec.getSite().getRiverKm();

                    if (recapKm.isColocated(currKm) || recapKm.isDownstream(currKm))
                        break;
                }

                ++it;
            }

            // insert the recap in the correct position based on riverk

            if (it == sequence.end()) {
                if (currKm.isDownstream(recapKm)) 
                    sequence.push_back(recap);
                else
                    sequence.insert(it_recap, recap);
            }
            else if (it == sequence.begin())
                sequence.insert(sequence.begin(), recap);
            else 
                sequence.insert(it, recap);

            reverse(sequence.begin(), sequence.end());

        }

    }
}


const ObsSequence& ObsSequence::transform (TransformMethod method)
{
	if (method == ObsSequence::LastRoute)
		transform_last_route();
	else if (method == ObsSequence::AnyObs)
		transform_any_obs();
	return *this;
}


/*
*
* Take into account the issue of fallback. Here the sequence
* of observations matter. In this case we only take the 
* last route of the fish past a dam. Any prior ascents above
* the dam and above an other upstream dams with a subsequent 
* fallback prior to the last ascent are removed.
*
* Notes: what percent of fallback fish go undetected
*
*/
void ObsSequence::transform_last_route ()
{
	setStages (); // attempt to set any unknown stages
	if (!isStagesSet ()) // only transform if all stages have been set
		return;
	if (sequence.size() < 2)
		return;

	// reverse the sequence
	reverse (sequence.begin(), sequence.end());

	// retain only the last upward path, if any
	vector<ObsRecord>::iterator it0 = sequence.begin();
	vector<ObsRecord>::iterator it1 = it0 + 1;
	ObsRecord rec0 = *it0;
	ObsRecord rec1 = *it1;
    int firstAdultAge = -1;
	while (it1 != sequence.end() && (*it1).getStage() == CbrPit::ST_Adult)
	{
        if (firstAdultAge == -1) 
            firstAdultAge = (*it1).getAge();
        else if (firstAdultAge < (*it1).getAge()) 
            it1 = sequence.end();
        else {

		    const Site& site0 = (*it0).getSite();
		    const Site& site1 = (*it1).getSite();
		    if (site0.isColocated(&site1) || site0.isDownstream(&site1))
			    ++it1;
		    else if (it1 - it0 > 1) 
		    {
			    it0 = sequence.erase (++it0, it1);
			    it1 = it0 + 1;
		    }
		    else
		    {
			    ++it0;
			    ++it1;
		    }
        }
	}

	if (it1 - it0 > 1)
		sequence.erase (++it0, it1);

	reverse (sequence.begin(), sequence.end());

}

/*
* 
* In this case we are only concerned with whether a fish
* was detected at a given site, order and sequence do not
* matter. Here we don't need to transform at all.
*
*/
void ObsSequence::transform_any_obs ()
{
}

/*
* Compress multiple records at the same site with the
* same stage into one record. The way that outcome is
* determined when combining multiple observation records
* with perhaps multiple outcomes is determined by the
* CompressionMethod
*/
const ObsSequence& 
ObsSequence::compress (CompressionMethod method)
{
	switch (method)
	{
	case RemovalTrumpsAll:
		compress_removal_trumps_all();
        break;
    case ShowAllCodes:
        compress_show_all_codes();
        break;
	default:
		compress_last_outcome_rules();
	}

	return *this;
}


/*
* Compress the records so that if any observation
* is considered a removal then the final outcome
* will be removal. Also, samples and holds trump
* transports, which all trump returned.
* if (current is hold or sampled) keep current
* else if (current is returned and (next is hold or sampled)) set to next // hold and sampled trump returned
* else if (current is bypass and (next is not invalid)) set to next  // everything trumps bypass
* else if (current is transport and (new is sampled, hold, or returned) set to next // transport trumps all but sampled, hold, and return
* else if (next is not invalid) set to next
*/
void
ObsSequence::compress_removal_trumps_all()
{
	if (sequence.size() < 2)
		return;

	// retain only the last upward path, if any
	vector<ObsRecord>::iterator it0 = sequence.begin();
	vector<ObsRecord>::iterator it1 = it0 + 1;
	while (it1 != sequence.end())
	{
		ObsRecord& rec0 = *it0;
		ObsRecord& rec1 = *it1;
		const Site& rec0Site = rec0.getSite();
		const Site& rec1Site = rec1.getSite();

		//if (rec0.getSite() != rec1.getSite() || rec0.getStage() != rec1.getStage() )
		if (!rec0Site.isColocated(&rec1Site) || rec0.getStage() != rec1.getStage() )
		{
			if (it1 - it0 > 1) 
				it0 = sequence.erase (it0 + 1, it1); 
			else 
				it0 = it1;

			it1 = it0 + 1;
		}
		else 
		{
			CbrPit::Outcome oc0 = rec0.getOutcome();
			CbrPit::Outcome oc1 = rec1.getOutcome();

			if (oc0 != CbrPit::Sampled && oc0 != CbrPit::Hold ) // sampled and hold trump all
			{
				if (oc0 == CbrPit::Returned) // sampled, hold trump ret, bypass
				{
					if (oc1 == CbrPit::Sampled || oc1 == CbrPit::Hold)
						rec0.setOutcome (oc1);
				}
                else if (oc0 == CbrPit::Bypass) // anything trumps bypass
                {
                    if (oc1 != CbrPit::Invalid)
                        rec0.setOutcome (oc1);
                }
				else if (oc0 == CbrPit::Transported) // sampled, hold, returned trump transported (not bypass)
				{
					if (oc1 == CbrPit::Sampled || oc1 == CbrPit::Hold || oc1 == CbrPit::Returned)
						rec0.setOutcome (oc1);
				}
                else if (oc1 != CbrPit::Invalid)
                {
                    rec0.setOutcome (oc1);
                }
			}			

			// carry over last date
			rec0.setLastDate (rec1.getLastDate ());
			rec0.addCoilHits (rec1.getCoilHits ());

			++it1;
		}
	}

	if (it1 - it0 > 1) 
		sequence.erase (it0 + 1, it1);
}

/*
* Similar to compress_removal_trumps_all without
* losing codes to Unknown or NoDetect.
* Rules:
* if (current is hold or sampled or spillway or weir or avianColony) keep current
* else if (current is returned and (next is hold or sampled)) set to next // hold and sampled trump returned
* else if (current is bypass and (next is not invalid or nodetect)) set to next  // everything trumps bypass
* else if (current is transport and (next is sampled, hold, or returned) set to next // transport trumps all but sampled, hold, and return
* else if (next is not nodetect or invalid) set to next
*/
void
ObsSequence::compress_show_all_codes()
{
    if (sequence.size() < 2)
        return;

    // retain only the last upward path, if any
    vector<ObsRecord>::iterator it0 = sequence.begin();
    vector<ObsRecord>::iterator it1 = it0 + 1;
    while (it1 != sequence.end())
    {
        ObsRecord& rec0 = *it0;
        ObsRecord& rec1 = *it1;
        const Site& rec0Site = rec0.getSite();
        const Site& rec1Site = rec1.getSite();

        if (!rec0Site.isColocated(&rec1Site) || rec0.getStage() != rec1.getStage() )
        {
            if (it1 - it0 > 1)
                it0 = sequence.erase (it0 + 1, it1);
            else
                it0 = it1;

            it1 = it0 + 1;
        }
        else
        {
            CbrPit::Outcome oc0 = rec0.getOutcome();
            CbrPit::Outcome oc1 = rec1.getOutcome();

            switch(oc0) {
            case CbrPit::Hold:
            case CbrPit::Sampled:
            case CbrPit::Spillway:
            case CbrPit::Weir:
            case CbrPit::BonnLadder:
            case CbrPit::AvianColony:
            case CbrPit::AMBridge:
                break;
//            case CbrPit::Transported:
//                if (oc1 == CbrPit::Hold || oc1 == CbrPit::Sampled || oc1 == CbrPit::Returned)
//                    rec0.setOutcome(oc1);
//                break;
//            case CbrPit::Returned:
//                if (oc1 == CbrPit::Hold || oc1 == CbrPit::Sampled)
//                    rec0.setOutcome(oc1);
//                break;
//            case CbrPit::Bypass:
//                if (oc1 != CbrPit::Invalid && oc1 != CbrPit::NoDetect && oc1 != CbrPit::Unknown)
//                    rec0.setOutcome(oc1);
//                break;
//            case CbrPit::NoDetect:
//            case CbrPit::Invalid:
//            case CbrPit::Unknown:
            default:
                if (oc1 > oc0)
                    rec0.setOutcome(oc1);
//                if (oc1 != CbrPit::Invalid && oc1 != CbrPit::NoDetect)
//                    rec0.setOutcome(oc1);
                break;
            }

            // carry over last date
            rec0.setLastDate (rec1.getLastDate ());
            rec0.addCoilHits (rec1.getCoilHits ());

            ++it1;
        }
    }

    if (it1 - it0 > 1)
        sequence.erase (it0 + 1, it1);
}


void 
ObsSequence::compress_last_outcome_rules()
{
	if (sequence.size() < 2)
		return;

	// retain only the last upward path, if any
	vector<ObsRecord>::iterator it0 = sequence.begin();
	vector<ObsRecord>::iterator it1 = it0 + 1;
	while (it1 != sequence.end())
	{
		ObsRecord& rec0 = *it0;
		ObsRecord& rec1 = *it1;

		if (rec0.getSite() == rec1.getSite() && rec0.getStage() == rec1.getStage())
		{
			// carry over first date, coil hits
			rec1.setFirstDate (rec1.getFirstDate ());
			rec1.addCoilHits (rec0.getCoilHits ());

			++it1;
		}
		else
		{
			if (it1 - it0 > 1)
				it0 = sequence.erase (it0, it1 - 1);
			else
				it0 = it1;
			it1 = it0 + 1;
		}
	}

	if (it1 - it0 > 1) 
		sequence.erase (it0, it1 - 1);
}

/*
 * Return true for stage configurations that are possible for an inrange record
 */
bool ObsSequence::rangeCheckStage(CbrPit::Stage a, CbrPit::Stage b, CbrPit::Stage current) const {
    if (current == a && current == b)
        return true;
    if (current == CbrPit::ST_Juvenile && a == CbrPit::ST_Juvenile && b == CbrPit::ST_Adult)
        return true;
    if (current == CbrPit::ST_Adult && a== CbrPit::ST_Juvenile && b == CbrPit::ST_Adult)
        return true;
    return false;
}

/*
 * Check to see if record is in sequence betwee [a,b)
 *
 * Situations:
 *
 *      SiteA       SiteB       Current    LastField        InRange?
 *     ------------------------------------------------------------------
 *  1)    J           J           J           T               SiteA >= Current
 *  2)    J           J           J           F               SiteA >= Current && Current < SiteB
 *  3)    J           A           J           T               SiteA >= Current
 *  4)    J           A           J           F               SiteA >= Current
 *  5)    J           A           A           T               TRUE
 *  6)    J           A           A           F               SiteB > Current
 *  7)    A           A           A           T               Current >= SiteA
 *  8)    A           A           A           F               Current >= SiteA && Current < SiteB
 *

 */
bool ObsSequence::rangeCheckSequence(const Site* siteA, CbrPit::Stage stageA,
                                     const Site* siteB, CbrPit::Stage stageB, 
                                     const ObsRecord& currentRec, const ObsRecord* prevRec) const 
{
    // determine a riverkm for the current record
    const Site* currentSite = currentRec.getSitePointer();
    const Site* prevSite = 0;
    // NOTE: Use this for something.
    if (prevRec)
        prevSite = prevRec->getSitePointer();
    Q_UNUSED(prevSite);

    // How to get riverkm for the current rec.
    //  1) If the riverkm was provided in the input data then use it (recaps/morts)
    //  2) If the riverkm is not a range, use the riverk down value 
    //  3) If the riverkm is a range:
    //      a) If there is a non-riverkm range previous site, we use that one.
    //      b) We use the upstream riverkm for Juvenile stage, downstream for Adult stage
    //  note: when there is no range, getRiverkUp and getRiverkDn are equivalent
    RiverKm rkCurrent;
    if (!currentRec.getRiverKm().empty())
        rkCurrent.setRiverKm(currentRec.getRiverKm());
    if (!rkCurrent.isValid()) {
        if (!currentSite->isRiverkRange()) 
            rkCurrent = currentSite->getRiverkDn();
        else {
            if (currentRec.getStage() == CbrPit::ST_Adult) 
                rkCurrent = currentSite->getRiverkDn();
            else 
                rkCurrent = currentSite->getRiverkUp();
        }
    }

    const RiverKm& rkA = siteA->getRiverKm();
    CbrPit::Stage currentStage = currentRec.getStage();

    bool lastSite = !siteB;
    RiverKm rkB;
    if (!lastSite)
        rkB = siteB->getRiverKm();
    if (stageA == CbrPit::ST_Juvenile) {
        if (stageB == CbrPit::ST_Juvenile) {
            if (currentStage == CbrPit::ST_Juvenile) {
                if (lastSite) {
                    // Situation 1
                    return rkCurrent.isColocated(rkA) || rkCurrent.isDownstream(rkA); 
                }
                else {
                    // Situation 2
                    return (rkCurrent.isColocated(rkA) || rkCurrent.isDownstream(rkA)) &&
                        rkCurrent.isUpstream(rkB);
                }
            }
        }
        else if (stageB == CbrPit::ST_Adult) {
            if (currentStage == CbrPit::ST_Juvenile) {
                // Situation 3 & 4
                return rkCurrent.isColocated(rkA) || rkCurrent.isDownstream(rkA); 
            }
            else if (currentStage == CbrPit::ST_Adult) {
                if (lastSite) {
                    // Situation 5
                    return true;
                }
                else {
                    // Situation 6
                    return rkCurrent.isDownstream(rkB);
                }
            }
        }
    }
    else if (stageA == CbrPit::ST_Adult) {
        if (stageB == CbrPit::ST_Adult) {
            if (currentStage == CbrPit::ST_Adult) {
                if (lastSite) {
                    // Situation 7
                    return rkCurrent.isColocated(rkA) || rkCurrent.isUpstream(rkA);
                }
                else {
                    // Situation 8
                    return (rkCurrent.isColocated(rkA) || rkCurrent.isUpstream(rkA)) && 
                        rkCurrent.isDownstream(rkB);
                }
            }
        }
    }
    
    return false;
                                    
}

/*
 * Get the outcome for a range of obs records. The range is from one mask site, including
 * the mask site, to the next mask site in the sequence, non-inclusive. If the second 
 * site is null, any subsequent obs records are used.
 */
void ObsSequence::buildRangeRecord (ObsRecord& maskRec, const Site* nextSite, CbrPit::Stage nextStage, bool keepAll)
{
    const ObsRecord* prevRec = 0;
	const Site* maskSite    = maskRec.getSitePointer();
	CbrPit::Stage maskStage = maskRec.getStage();

    // iterate through observation sequence
    bool any = false; // true once an in range record is found
	vector<ObsRecord>::const_iterator it;
	for (it = sequence.begin(); it != sequence.end(); ++it) {
		const ObsRecord& rec = *it;

        // for any valid record (obs, recap, mort)
		if ( rec != ObsRecord::null && rec.getSitePointer() != 0 ) {
			const Site* currentSite = rec.getSitePointer();
			CbrPit::Stage currentStage = rec.getStage();

            // check to see if record is in range
            bool inRange = rangeCheckStage(maskStage, nextStage, currentStage) &&
                rangeCheckSequence(maskSite, maskStage, nextSite, nextStage, rec, prevRec);

            // merge record into the mask record
            if (inRange) {
                any = true;
				CbrPit::Outcome currentOutcome = rec.getOutcome();
				bool lastSite = !nextSite;

				if (!maskRec.getAge())
					maskRec.setAge(getMigrationYear(), rec.getFirstDate(), useSteelheadYear);

				// When the record is colocated with the mask site, the mask site gets the 
				// outcome of the record. 
				if ( maskSite->isColocated( currentSite ) && currentStage == maskStage) {
					if ( maskRec.getFirstDate() == 0 )
						maskRec.setFirstDate(rec.getFirstDate() );
					if ( rec.getLastDate() > maskRec.getLastDate() )
						maskRec.setLastDate( rec.getLastDate() );

					// the downstream detection trumps the upstream one if the downstream disposition is not unkown,
					// and if it is it still trumps everything except Returned
					if (currentOutcome != CbrPit::Unknown || maskRec.getOutcome() != CbrPit::Returned) 
						maskRec.setOutcome(currentOutcome);		
                }

				// if this is the last site, we only are concerned with detected/not detected
                if (lastSite) {
                    if (keepAll)
                        maskRec.setOutcome (currentOutcome);
                    else if (currentOutcome != CbrPit::Invalid && currentOutcome != CbrPit::NoDetect)
                        maskRec.setOutcome (CbrPit::Returned);
					return;
				}

				// if we have any censored or returned records in the range, we are done
                if (currentOutcome == CbrPit::Sampled  || currentOutcome == CbrPit::Hold) {
                    maskRec.setOutcome (currentOutcome);
                    if (!keepAll)
                        return;
				}

			} 
			else if (any) {
				return;
			}

			if (!currentSite->isRiverkRange())
				prevRec = &rec;
		}
    }
}

#if 0
/*
 * Get the outcome for a range of obs records. The range is from one mask site, including
 * the mask site, to the next mask site in the sequence, non-inclusive. If the second 
 * site is null, any subsequent obs records are used.
 */
void ObsSequence::buildRangeRecord( ObsRecord& maskRec, const Site* nextSite, CbrPit::Stage nextStage )
{
	bool inRange = false;
	const Site* maskSite = maskRec.getSitePointer();
	CbrPit::Stage maskStage = maskRec.getStage();
	bool brk = !pitCode.compare("505536616B");
	bool lastSite =  !nextSite;
	vector<ObsRecord>::const_iterator it;
	for (it = sequence.begin(); it != sequence.end(); ++it)
	{
		const ObsRecord& rec = *it;


		// check whether or not obs record is in range
		if ( rec != ObsRecord::null && rec.getSitePointer() != 0 ) {
			const Site* currentSite = rec.getSitePointer();
			CbrPit::Stage currentStage = rec.getStage();
			CbrPit::Outcome currentOutcome = rec.getOutcome();

            if (!rec.isRecap() || !currentSite->isRiverkRange()) {
			    // in range conditions
			    if ( currentStage == maskStage && currentSite->isColocated( maskSite ) ) {
				    if ( lastSite && currentOutcome != CbrPit::Invalid && currentOutcome != CbrPit::NoDetect ) {
					    maskRec.setOutcome( CbrPit::Returned );
					    return;
				    }

				    maskRec.setOutcome( currentOutcome );
				    if ( currentOutcome == CbrPit::Sampled || currentOutcome == CbrPit::Hold ) 
					    return;
				    inRange = true;
			    }
			    else if ( currentStage == CbrPit::ST_Juvenile && maskStage == CbrPit::ST_Juvenile ) {
				    if ( lastSite || nextStage == CbrPit::ST_Adult) {
					    if ( currentSite->isDownstream(maskSite) ) 
						    inRange = true;
				    }
				    else if ( nextStage == CbrPit::ST_Juvenile ) {
					    if ( currentSite->isDownstream(maskSite) && nextSite->isDownstream(currentSite) )
						    inRange = true;
					    else if ( inRange ) 
						    return;
				    }
			    }
			    else if ( currentStage == CbrPit::ST_Adult && ( lastSite || nextStage == CbrPit::ST_Adult ) ) {
				    if ( maskStage == CbrPit::ST_Juvenile ) {
					    if ( lastSite || currentSite->isDownstream( nextSite ) )
						    inRange = true;
					    else if ( inRange )
						    return;
				    }
				    else if ( maskStage == CbrPit::ST_Adult ) {
					    if ( maskSite->isDownstream(currentSite) && ( lastSite || currentSite->isDownstream(nextSite)))
						    inRange = true;
					    else if ( inRange )
						    return;
				    }
			    }
            }

			// we only get here with inRange == true when the current record is not colocated
			// with sitea
			if ( inRange ) {
				if ( maskRec.getFirstDate() == 0 )
					maskRec.setFirstDate(rec.getFirstDate() );
				if ( rec.getLastDate() > maskRec.getLastDate() )
					maskRec.setLastDate( rec.getLastDate() );


				if ( lastSite && currentOutcome != CbrPit::Invalid && currentOutcome != CbrPit::NoDetect ) {
					maskRec.setOutcome( CbrPit::Returned );
					return;
				}

				if ( currentOutcome == CbrPit::Sampled  || currentOutcome == CbrPit::Hold ) {
					maskRec.setOutcome( currentOutcome );
					return;
				}	
			}
		}
	}
}

#endif

/*
* Return the obs record that matches the site and stage. If there are more than
* one record that matches the first one is returned. This shouldn't happen if
* the sequence has been transformed/compressed properly
*/
const ObsRecord& ObsSequence::getRecord (const Site& site, CbrPit::Stage stage) const
{
	vector<ObsRecord>::const_iterator it;
	for (it = sequence.begin(); it != sequence.end(); ++it)
	{
		const ObsRecord& rec = *it;
		if ( rec != ObsRecord::null && rec.getSitePointer() != 0 ) {
			if (site.isColocated(&rec.getSite()) && rec.getStage() == stage)
				return rec;
		}
	}

	return ObsRecord::null;
}

const ObsRecord& ObsSequence::getFirstRecord () const 
{
  vector<ObsRecord>::const_iterator it = sequence.begin();
  if ( it == sequence.end() )
    return ObsRecord::null;
  else 
    return *it;
}

const ObsRecord& ObsSequence::getNextRecord ( const ObsRecord& rec ) const 
{
	vector<ObsRecord>::const_iterator it = find( sequence.begin(), sequence.end(), rec );
	if ( it == sequence.end() || ++it == sequence.end() )
		return ObsRecord::null;
	else 
		return *it;
}


/*
* Set any transported outcomes to unkown. This is called when a fish marked
* as transported is then detected downstream during the juvenile life stage.
* 
*/
void ObsSequence::setTransportedToUnknown()
{
	vector<ObsRecord>::iterator it;
	for (it = sequence.begin(); it != sequence.end(); ++it)
	{
		ObsRecord& rec = *it;
		if (rec.getOutcome() == CbrPit::Transported)
			rec.setOutcome( CbrPit::Unknown );
	}
}

void ObsSequence::reset( const string& pitCode ) {
	clear();
	setPitCode( pitCode );
}

void ObsSequence::clear() {
	pitCode.clear();
	releaseDate = PP_NULL_RELEASE_DATE;
	icovs.clear();
	recap = false;

	sequence.clear();
	errors.clear();

	it_seq = sequence.end();
}


/*
* Traverse the observation records, formatted using mask,
* to generate the capture history
*/
void ObsSequence::traverseHist (const SitesMask& mask, ObsRecPrinter& printer) const
{
	const SitesMaskVector& maskVector = mask.getVector();
	SitesMaskVector::const_iterator it;
	int field = 0;
	int numJuvenileSites = mask.getNumJuvenileSites();
	int numMainSites = mask.getNumMainSites();
	for (it = maskVector.begin(); it != maskVector.end() ;it++)
	{
		CbrPit::Stage stage = 
			(field++ < numJuvenileSites) ? CbrPit::ST_Juvenile : CbrPit::ST_Adult;
		const Site& site = **it;
		const ObsRecord& rec = getRecord (site, stage);	


		if ( field <= numMainSites )
			printer( rec );
		else if ( rec != ObsRecord::null ) // any detections
		{
			ObsRecord obs = rec;
			obs.setOutcome( CbrPit::Returned );
			printer( obs );
			return;
		}
	}

	// last field was empty
	if (field > numMainSites)
	{
		ObsRecord obs;
		obs.setOutcome (CbrPit::NoDetect);
		obs.setStage (CbrPit::ST_Juvenile);
		printer (obs);
	}
}

bool ObsSequence::isTransportedDetected() const 
{
	bool transported = false;
	const Site* transSite = 0;

	vector<ObsRecord>::const_iterator it;
	for (it = sequence.begin(); it != sequence.end(); ++it) 
	{
		const ObsRecord& rec = *it;
		const Site& site = rec.getSite();
		if (!transSite || !site.isColocated(transSite)) {
			string siteCode( site.getSiteCode() );
			bool isTwx = siteCode.compare( "tw" ) == 0; // tranpsorted fish can normally be detected at twx
			if (transported && rec.getStage() == CbrPit::ST_Juvenile && !isTwx )
				return true;
			else if (!transported && rec.getOutcome() == CbrPit::Transported) {
				transported = true;
				transSite = &site;
			}
		}
	}

	return false;
}





bool ObsSequence::hasMinijacks() const
{
	vector<ObsRecord>::const_iterator it;
	for (it = sequence.begin(); it != sequence.end(); ++it) 
	{
		const ObsRecord& rec = *it;
		CbrPit::Stage stage = rec.getStage();
		if ( stage == CbrPit::ST_Adult && rec.getAge() == 0 )
			return true;

	}

	return false;
}

/*
 * Return true if this fish is recaped before the first mask site
 */
bool ObsSequence::isPreRecap( const SitesMask& mask ) {
	if ( mask.getNumSites() == 0 )
		return false;
	vector<ObsRecord>::const_iterator it;
	for (it = sequence.begin(); it != sequence.end(); ++it) 
	{
		const ObsRecord& rec = *it;

		if ( rec.isRecap() && rec.getStage() == CbrPit::ST_Juvenile) {
			const Site* firstMaskSite = mask.getSite( 0 );
			const Site* recapSite = rec.getSitePointer();
			return firstMaskSite->isDownstream( recapSite, Site::RK_Up );
		}
	}

	return false;
}

/*
 * Return true if this fish is sampled/transported/held
 * before the first mask site
 */
bool ObsSequence::isPreRemoved( const SitesMask& mask ) {
	if ( mask.getNumSites() == 0 )
		return false;

	const CbrPit& cbrPit = CbrPit::getInstance();
	const Site* firstMaskSite = mask.getSite( 0 );
	vector<ObsRecord>::const_iterator it;
	for (it = sequence.begin(); it != sequence.end(); ++it) 
	{
		const ObsRecord& currentRec = *it;
		if (currentRec.getStage() == CbrPit::ST_Juvenile) {
			const Site* currentSite = currentRec.getSitePointer();

			if ( firstMaskSite->isDownstream( currentSite, Site::RK_Up ) && 
                cbrPit.isRemoved( currentRec.getOutcome() ) )
				return true;
		}
	}

	return false;
}

bool ObsSequence::isMissingICov() const {
	for (vector<string>::const_iterator it = icovs.begin(); it != icovs.end(); ++it) {
		if ((*it).empty())
			return true;
	}
	return false;
}

/* 
 * Return true if any obsrvation in the sequence (including recaptures
 * and mortalites) occurs before the release date day (ignore time).
 */
bool ObsSequence::isPreRel() {
	if (releaseDate == PP_NULL_RELEASE_DATE) {
		return false;
	}
    DateConverter rd(releaseDate);
    double rd_jd = rd.jd(); // date, no time
	vector<ObsRecord>::const_iterator it;
	for (it = sequence.begin(); it != sequence.end(); ++it) {
		const ObsRecord& rec = *it;
		if (rd_jd > rec.getFirstDate())
			return true;
	}

	return false;
}


/*
* return an ObsRecordVector that has only entries matching the mask
* This is used for the non-capture histories output.
*/
ObsRecordVector ObsSequence::applyMaskSimple(const SitesMask& mask, bool showAll) const {
	ObsRecordVector masked;

	// get sites vector from the mask, return an empty vector 
	// if the sites vector is empty
	const SitesMaskVector& maskVector = mask.getVector();
	if (maskVector.size() == 0)
		return masked;

	int numJuvenileSites = mask.getNumJuvenileSites();

	SitesMaskVector::const_iterator it = maskVector.begin();
	int field = 0;
	bool censored = false;
	bool transported = false;
	for ( ; it != maskVector.end(); ++field, ++it ) {
		// get the correct obs record for this site and stage
		CbrPit::Stage stage = (field < numJuvenileSites) ? CbrPit::ST_Juvenile : CbrPit::ST_Adult;
		const Site& site = **it;
        const ObsRecord& rec = getRecord (site, stage);

        if (showAll) {
            masked.push_back (rec);
        }
        else {
            if ( censored || ( transported && stage == CbrPit::ST_Juvenile ) )
                masked.push_back (ObsRecord::null);
            else
                masked.push_back (rec);
        }

		CbrPit::Outcome oc = rec.getOutcome();
		if ( oc == CbrPit::Unknown || oc == CbrPit::Hold || oc == CbrPit::Sampled )
			censored = true;
		else if ( oc == CbrPit::Transported )
			transported = true;
	}

	return masked;
}


/*
* Return the sequence of obs records transformed by mask. 
* Any observations at non-mask sites apply to the previous
* mask site in the sequence.
*/
void ObsSequence::applyMask(const SitesMask& mask, bool keepAll)
{
	ObsRecordVector masked;

	// get sites vector from the mask, return an empty vector 
	// if the sites vector is empty
	const SitesMaskVector& maskVector = mask.getVector();
	if (maskVector.size() == 0)
		return;

	int numSites = mask.getNumSites();
	int numJuvenileSites = mask.getNumJuvenileSites();
	int numMainSites = mask.getNumMainSites();
	if (numMainSites < 0 || numMainSites > numSites)
		numMainSites = numSites;
	int numFields = ( numMainSites == numSites ) ? numSites : numMainSites + 1;

	// start at beginning of mask unless this is a site release,
	// in that case skip the first site
	int offset = (mask.isSiteRel()) ? 1 : 0;

	bool censored = false;
	bool transported = false;
	for (int field = 0 ; field < numFields; ++field ) {
		int currentFieldIndex = field + offset;
		// get the correct obs record for this site and stage			
		const Site* maskSite = maskVector.at(currentFieldIndex);
		CbrPit::Stage stage = (field < numJuvenileSites) ? CbrPit::ST_Juvenile : CbrPit::ST_Adult;
		bool lastField = ( field == numFields - 1 );

		// get outcome
        ObsRecord maskRec( maskSite, stage, CbrPit::NoDetect );
        if (keepAll || (!censored  && (!transported || stage == CbrPit::ST_Adult))) {
			// get the outcome based on the observations in the range
			// that includes the first site and evertying up till the second.
			const Site* nextSite = ( lastField ) ? 0 :  maskVector.at( currentFieldIndex + 1 );
			CbrPit::Stage nextStage = (currentFieldIndex + 1 < numJuvenileSites) ? CbrPit::ST_Juvenile : CbrPit::ST_Adult;
            buildRangeRecord (maskRec, nextSite, nextStage, keepAll);
			CbrPit::Outcome oc = maskRec.getOutcome();

			if ( oc == CbrPit::Unknown || oc == CbrPit::Hold || oc == CbrPit::Sampled )
				censored = true;
			else if ( oc == CbrPit::Transported )
				transported = true;
		}

		// add the site to the masked list
		masked.push_back( maskRec );
	}

	sequence.clear();
    sequence.insert(sequence.begin(), masked.begin(), masked.end());
}


struct print_hist : public unary_function<const ObsRecord&, void>
{
	print_hist(ostream& out, int y, CbrPit::JacksPolicy jp) : os(out), migrYear(y), jacksPolicy(jp) {}
	void operator() (const ObsRecord& rec) 
	{ 
		os << " " ;
		if ( rec == ObsRecord::null )
			os << "0";
		else {
			CbrPit::Outcome oc = rec.getOutcome();
			CbrPit::Stage  stage = rec.getStage();
			//stage = CbrPit::ST_Juvenile;
			int age = rec.getAge();

			CbrPit& cbrPit = CbrPit::getInstance();
			if ( stage == CbrPit::ST_Juvenile )
				os << cbrPit.stringFromJuvenileOutcome( oc );
			else if ( stage == CbrPit::ST_Adult )
				os << cbrPit.stringFromAdultOutcome( oc, age, jacksPolicy );
			else
				os << "U";

		}
	}
	ostream& os;
	int migrYear;
	CbrPit::JacksPolicy jacksPolicy;
};

string ObsSequence::hist (const SitesMask& /*mask*/) const
{
	stringstream ss;

	//ObsRecordVector seq = applyMask( mask );
	const ObsRecordVector& seq = sequence;
	for_each( seq.begin(), seq.end(), print_hist (ss, getMigrationYear(), getJacksPolicy() ) );
	if (outputCovars) {
		for (vector<string>::const_iterator it = icovs.begin(); it != icovs.end(); ++it)
		{
			ss << " ";
			if ((*it).empty())
				ss << "NA";
			else
				ss << *it;
		}
	}
	return ss.str();
}

/*
*/
struct print_dd : public unary_function<const ObsRecord&, void>
{
	print_dd(ostream& out, int /*fieldWidth*/, bool julianDates = true) : os(out), julian(julianDates) 
	{}

	void operator() (const ObsRecord& rec) 
	{ 
		double fdd;
		double ldd;

		if ( rec == ObsRecord::null ) 
			fdd = ldd = 0;
		else {
			DateConverter first (rec.getFirstDate());
			DateConverter last (rec.getLastDate());
			if (julian)
			{
				fdd = first.getTime();
				ldd = last.getTime();
			}
			else 
			{
				fdd = first.timeOfYear();
				ldd = last.timeOfYear();
			}
		}


		os << std::fixed;
		os << " ";
		os.precision(ObsSequence::P);
		os << fdd;
		os << " ";
		os.precision(ObsSequence::P);
		os << ldd;
	}
	ostream& os;

	bool julian;
};

string ObsSequence::dd (const SitesMask& mask, bool julianDates, bool showAll) const
{
	stringstream ss;
	ss << pitCode;
	double relTime;
	if (releaseDate == PP_NULL_RELEASE_DATE)
		relTime = 0;
	else
	{
		DateConverter rd(releaseDate);
		if (julianDates)
			relTime = rd.getTime();
		else
			relTime = rd.timeOfYear();
	}

	ss << std::fixed;
	ss.precision(ObsSequence::P);
	ss << " " << relTime;

    ObsRecordVector seq = applyMaskSimple(mask, showAll);
	for_each(seq.begin(), seq.end(), print_dd(ss, julianDates));

	return ss.str();
}

struct print_tt : public unary_function<const ObsRecord&, void>
{
	print_tt(ostream& out, double f ) : os(out), releaseDate(f) {}
	void operator() (const ObsRecord& rec) 
	{ 
		double ftt;
		double ltt;

		if ( rec == ObsRecord::null )
			ftt = ltt = 0;
		else if (releaseDate == PP_NULL_RELEASE_DATE)
			ftt = ltt = -999;
		else
		{
			ftt = rec.getFirstDate() - releaseDate;
			ltt = rec.getLastDate() - releaseDate;
		}

		os << std::fixed;
		os << " ";
		os.precision(ObsSequence::P);
		os << ftt;
		os << " ";
		os.precision(ObsSequence::P);
		os << ltt;
	}
	ostream& os;
	double releaseDate;
};
string ObsSequence::tt (const SitesMask& mask, bool showAll = false) const
{
	stringstream ss;
	ss << pitCode;
    ObsRecordVector seq = applyMaskSimple(mask, showAll);
	for_each(seq.begin(), seq.end(), print_tt(ss, releaseDate ));
	return ss.str();
}

ostream& operator<< (ostream& os, const ObsSequence& seq) 
{
	// the pitcode
	os << seq.pitCode;

	// and the sites
	vector<ObsRecord>::const_iterator it;
	for (it = seq.sequence.begin(); it != seq.sequence.end(); ++it) 
	{
		os << " " << *it;
	}

	return os;
}
