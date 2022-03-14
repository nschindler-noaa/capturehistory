/*
 * CapthistRun
 *
 * This provides the main linkage between the old program
 * capthist and the new program PitPro. To make this as
 * painless as possible, we try to use the existing mechanisms
 * in capthist rather than re-writting everything. This means
 * create the Flag and Rc data structures from the ConfigWidget
 * input to mimic a command line run.
 *
 */

#include <vector>
//#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>

#include <CbrPit.h>
#include <StringManip.h>
#include <ObsSequence.h>
#include <Sites.h>
#include <SitesMask.h>
#include <DateConverter.h>

#include "CapthistRun.h"
#include "PitProSettings.h"
#include "PPOutputMaker.h"
#include "PPObs.h"
#include "PPSurphOutput.h"
#include "PPDdOutput.h"
#include "PPTtOutput.h"
#include "PPSeqOutput.h"
#include "PPErrors.h"
#include "PPErrorsOutput.h"
#include "PPFishData.h"
#include "PPVersion.h"
#include "PPRunInfo.h"

#include <QStringList>

using std::stringstream;
using std::ifstream;
using std::fstream;
using std::ofstream;
using std::endl;
using std::ios;

//using namespace cbr;
using cbr::IntVector;
using cbr::BoolVector;
using cbr::DateConverter;
using cbr::CbrPit;

CapthistRun::CapthistRun(PPOutputMaker& outputMaker) : out(outputMaker),
surphOutput(0), seqOutput(0), errorsOutput(0),
bytesProcessed(0), isCanceledPtr(0) {
    surphOutput = new PPSurphOutput();
    seqOutput = new PPSeqOutput();
    errorsOutput = new PPErrorsOutput();
    outputObjects.push_back(new PPDdOutput());
    outputObjects.push_back(new PPTtOutput());
}

CapthistRun::~CapthistRun() {
    OutObjectPtrVector::iterator it;
    for (it = outputObjects.begin(); it != outputObjects.end(); ++it) {
        delete *it;
    }

    delete surphOutput;
    delete seqOutput;
    delete errorsOutput;
}

bool CapthistRun::isCanceled() const {
    return isCanceledPtr && *isCanceledPtr == true;
}

void CapthistRun::cancel() {
    deleteOutput();
}

/*
 * Open output streams.
 */
void CapthistRun::openOutputStreams(const QString prefix) {
    OutObjectPtrVector::iterator it;
    for (it = outputObjects.begin(); it != outputObjects.end(); ++it) {
        (*it)->setPrefix(prefix);
    }
    seqOutput->setPrefix(prefix);
    errorsOutput->setPrefix(prefix);
}

void CapthistRun::closeOutputStreams() {
    OutObjectPtrVector::iterator it;
    for (it = outputObjects.begin(); it != outputObjects.end(); ++it) {
        (*it)->close();
    }
    seqOutput->close();
    errorsOutput->close();
}

/*
 * Delete output files
 */
void CapthistRun::deleteOutput() {
    OutObjectPtrVector::iterator it;
    for (it = outputObjects.begin(); it != outputObjects.end(); ++it) {
        (*it)->closeAndDelete();
    }
    seqOutput->closeAndDelete();
    surphOutput->closeAndDelete();
    errorsOutput->closeAndDelete();
}

/*
 * There will be one run for each group prefix generating output files for each
 * prefix but one surph file with the all of the capture histories grouped together.
 * Each group prefix will be matched with a release file and mort file if there is
 * the same number of entries in the groupPrefixes, relFiles, and mortFiles. If not,
 * only the first rel file and mort files is used (if any)
 */
void CapthistRun::compute(const QString outPrefix, const RunConfigVector& runConfigVector) {
    bytesProcessed = 0;
    icovMissing = false;

    PitProSettings& settings = PitProSettings::getInstance();
    bool rosterFormat = settings.getValue(PitProSettings::OutputFormat).compare("ROSTER") == 0;
    bool writeCovars = settings.isChecked(PitProSettings::ICovSwitch) && !rosterFormat;
    IntVector npops;

    QStringList juvenileSites = settings.getJuvenileSites();
    QStringList adultSites = settings.getAdultSites();

    // set the capture history symbols
//    CbrPit& cbrPit = CbrPit::getInstance();
    bool unknown = settings.isChecked(PitProSettings::UnknownSwitch);
/*    if (unknown)
        CbrPit::getInstance().setJuvenileSymbol(cbr::CbrPit::Unknown, "U");
    else
        CbrPit::getInstance().setJuvenileSymbol(cbr::CbrPit::Unknown); //default
*/
    QString histFormat = settings.getValue(PitProSettings::HistDetail);
    if (rosterFormat)
        CbrPit::getInstance().setOutputFormat(cbr::CbrPit::Roster, "Std", unknown);
    else
        CbrPit::getInstance().setOutputFormat(cbr::CbrPit::Surph, histFormat, unknown);

    SitesMask mask;
    for (QStringList::const_iterator it = juvenileSites.begin(); it != juvenileSites.end(); ++it)
        mask.addSite((*it));
    for (QStringList::const_iterator it = adultSites.begin(); it != adultSites.end(); ++it)
        mask.addSite((*it));
    mask.setNumJuvenileSites(juvenileSites.size());
    mask.setNumMainSites(settings.getIntValue(PitProSettings::NumMainSites));
    mask.setSiteRel(settings.isChecked(PitProSettings::SiteRel));

    surphOutput->setPrefix(outPrefix);

    for (RunConfigVector::const_iterator it = runConfigVector.begin(); it != runConfigVector.end(); ++it) {
        const RunConfigItem& runItem = *it;
        QString popName = runItem.name;
        QString msg(QString("Group \"%1\"").arg(popName));
        out.write(msg);
//        out.write("Group \"" + popName.data() + "\"");

        // initialize
        openOutputStreams(popName);
        outputHeaders(mask);

        // read data from files
        PPFishData fishData;
        readData(fishData, runItem);

        // process obs file
        QString obsfile = settings.getDataFilePath(runItem.obs);
        std::ifstream in(obsfile.toStdString().data());
        if (!in)
            out.write("Error. Unable to open file \"" + obsfile + "\".");
        else {
            setFileBytes(in);
            QString msg = "Processing obs data for \"" + popName + "\"...";
            out.write(msg);
            out.setProgressMessage(msg);

            int count = processObsFile(in, fishData, mask);
            if (isCanceled())
                return cancel();
            npops.push_back(count);
        }

        closeOutputStreams();
    }

    surphOutput->write(outPrefix, mask, runConfigVector, npops, writeCovars);
    surphOutput->close();

    PPRunInfo& info = PPRunInfo::instance();
    QString xml = info.serialize(outPrefix, runConfigVector);
    info.save(outPrefix, xml);
}

int
CapthistRun::processObsFile(ifstream& in, PPFishData& fishData, const SitesMask& mask) {
    PPErrors errors;
    PPObs obs;
    QString line;
    int row = 0;
    int count = 0;
    std::string ln;
    ObsSequence seq;
    initializeSequence(seq); // settings that don't change from fish to fish

    while (getline(in, ln)) {
        ++row;

        // check for cancellation
        if (isCanceledPtr && *isCanceledPtr == true)
            return false;
        line = QString(ln.data());

        // report progress
        out.setCurrentBytes(line.size() + 1);

        stringstream instream(ln);
        instream >> obs;
//        obs.read(line);

        if (!obs.isOk())
            out.write("Bad line: row " + QString::number(row), PPOutputMaker::Warning);
        else if (!obs.isHeader()) {
            // row is valid, non-header observation data
            const QString pitCode = obs.getPitCode();

            // do this the first time through or when we have changed to
            // a new pit code (new fish)
            if (!seq.isValid() || !seq.isMatch(pitCode)) {
                if (seq.isValid()) { // ie not the first one
                    // check for obs tag sorting
                    if (seq.compare(pitCode) >= 0) {
                        errorMessage = "Observation data must be sorted by tag id.";
                        errorMessage += "\n!! Pitcode " + pitCode + " is out of sequence.";
                        if (isCanceledPtr)
                            *isCanceledPtr = true;
                        return false;
                    }

                    if (output(seq, mask, errors))
                        ++count;
                    fishData.deleteCurrent(); // delete previous fish
                }


                reset(seq, obs.getPitCode(), fishData, errors);
            }

            if (seq.isValid()) {
                processObsRec(seq, obs, row);
            }
        }
    }

    //  output the final sequence
    if (seq.isValid()) {
        if (output(seq, mask, errors))
            ++count;
        fishData.deleteCurrent(); // delete previous fish
    }

    // output the undetected tags to the surph file with empty
    // capture histories
    count += handleUndetectedTags(fishData, mask);

    return count;
}

void
CapthistRun::initializeSequence(ObsSequence&) {
    PitProSettings& settings = PitProSettings::getInstance();

    // initial setup for the sequence object
    ObsSequence::setJuvenileCutoffDate(-1);
    ObsSequence::setMigrationYear(-1);
    ObsSequence::setUseSteelheadYear(settings.isChecked(PitProSettings::UseSteelheadYear));

    if (settings.isChecked(PitProSettings::AdultModeSwitch)) {
        if (settings.isChecked(PitProSettings::JuvenileCutoffSwitch)) {
            QString cutoff = settings.getValue(PitProSettings::JuvenileCutoffDate);
            if (!cutoff.isEmpty()) {
                DateConverter dc(cutoff);
                ObsSequence::setJuvenileCutoffDate(dc.getTime());
            }
        } else if (settings.isChecked(PitProSettings::MigrationYearSwitch)) {
            QString my = settings.getValue(PitProSettings::MigrationYear);
            if (my.size() == 4)
                ObsSequence::setMigrationYear(my.toInt());
        }
    }

    ObsSequence::setJacksPolicy(CbrPit::JP_Combined);

}

void
CapthistRun::processObsRec(ObsSequence& seq, const PPObs& obs, int row) {
    // stage
    const QString obsSite = obs.getObsSite();
    const QString coil = obs.getCoil();
    double time = obs.getTime();
    Sites* sites = Sites::getInstance();
    const Detector* det = sites->getDetector(obsSite, coil, time);

    if (!det) {
        DateConverter dc(time);
        QString sstr("Unable to find detector for observation (line ");
        sstr.append(QString::number(row));
        sstr.append(QString("): " + obsSite + ", " + coil + ", "));//%1, %2, %3").arg(obsSite).arg(coil).arg(dc)));
        sstr.append(dc.output());
//        stringstream ss;
//        ss << "Unable to find detector for observation (line " << row << "): ";
//        ss << obsSite.toStdString() << ", " << coil.toStdString() << ", " << dc;
        out.write(sstr, PPOutputMaker::Warning);
    } else {
        CbrPit::Stage stage = det->getStage();
        CbrPit::Outcome outcome = det->getOutcome();

        Site* site = sites->getSite(obsSite);
        if (!site)
            out.write("Unable to find site for \"" + obsSite + "\"", PPOutputMaker::Error);
        else {
            // The user can optionaly treat sampled fish as transported
            PitProSettings& settings = PitProSettings::getInstance();
            const QString obsSite = site->getSiteCode();
            if (outcome == CbrPit::Sampled && settings.isChecked(PitProSettings::SampTransSwitch)
                    && settings.isSet(PitProSettings::TransSite, obsSite)) {
                outcome = CbrPit::Transported;
            } else if (outcome == CbrPit::Transported && !settings.isSet(PitProSettings::TransSite, obsSite))
                outcome = CbrPit::Unknown;

            seq.addRecord(site, stage, outcome, time, time, 1);
        }
    }
}

/*
 * Reset the sequence data object with the new fish.
 */
void
CapthistRun::reset(ObsSequence& seq, const QString pitCode, PPFishData& fishData, PPErrors& errors) {
    PitProSettings& settings = PitProSettings::getInstance();

    // reset sequence and errors
    seq.reset(pitCode);
    errors.reset(pitCode);

    if (!fishData.setCurrent(pitCode)) { // pitCode not found in valid tag data
        if (PitProSettings::getInstance().isChecked(PitProSettings::TagCheck))
            errors.setError(PPErrors::NoTag);
        else {
            seq.clearICovs();
            if (settings.isChecked(PitProSettings::AltRelDate))
                seq.setReleaseDate(settings.getDoubleValue(PitProSettings::RelDate));
            else {
                seq.setReleaseDate(0);
            }
        }
    } else {
        bool rosterFormat = settings.getValue(PitProSettings::OutputFormat).compare("ROSTER") == 0;
        if (!settings.isChecked(PitProSettings::ICovSwitch) || rosterFormat) {
            seq.setOutputCovars(false);
        } else {
            seq.setOutputCovars(true);
            seq.setICovs(fishData.getCurrentICovs());
        }


        if (settings.isChecked(PitProSettings::AltRelDate))
            seq.setReleaseDate(settings.getDoubleValue(PitProSettings::RelDate));
        else {
            double relTime = fishData.getCurrentRelTime();
            if (relTime == DateConverter::base.getTime())
                relTime = -1;
            seq.setReleaseDate(relTime);
        }

        // add recap record, if recap data exists for this fish
        double recapTime = fishData.getCurrentRecapTime();
        const Site* recapSite = fishData.getCurrentRecapSite();
        const QString riverkm = fishData.getCurrentRiverKm();
        if (recapTime != -1 && recapSite)
            seq.addRecapRecord(recapSite, recapTime, riverkm);


    }
}

/*
 * write undetected pit code histories to the surph file (all zeros)
 */
int
CapthistRun::handleUndetectedTags(PPFishData& fishData, const SitesMask& mask) {
    int count = 0;
    int step = 0;

    if (fishData.size() > 0) {
        QString msg("Processing tags with no observations...");
        out.write(msg);
        out.setProgressMessage(msg);

        out.setNumSteps(fishData.size());
        fishData.begin();
        do {
            if (isCanceled())
                return count;

            out.setCurrentStep(++step);

            const QString pitCode = fishData.getCurrentPitCode();

            ObsSequence seq;
            seq.setPitCode(pitCode);
            PitProSettings& settings = PitProSettings::getInstance();
            bool rosterFormat = settings.getValue(PitProSettings::OutputFormat).compare("ROSTER") == 0;
            if (!settings.isChecked(PitProSettings::ICovSwitch) || rosterFormat) {
                seq.setOutputCovars(false);
            } else {
                seq.setOutputCovars(true);
                seq.setICovs(fishData.getCurrentICovs());
            }

            if (settings.isChecked(PitProSettings::AltRelDate))
                seq.setReleaseDate(settings.getDoubleValue(PitProSettings::RelDate));
            else {
                double relTime = fishData.getCurrentRelTime();
                if (relTime == DateConverter::base.getTime())
                    relTime = -1;
                seq.setReleaseDate(relTime);
            }

            double recapTime = fishData.getCurrentRecapTime();
            const Site* recapSite = fishData.getCurrentRecapSite();
            const QString riverkm = fishData.getCurrentRiverKm();
            if (recapTime != -1 && recapSite)
                seq.addRecapRecord(recapSite, recapTime, riverkm);

            // This tag was undetected. Check for errors, if none, print out empty surph
            // file capture history
            PPErrors errors;
            errors.setPitCode(pitCode);

            if (output(seq, mask, errors))
                ++count;
        } while (fishData.next());
    }

    return count;
}

bool
CapthistRun::isOk(const PPObs&, const QList<PPTag>&) {
    return true;
}

void
CapthistRun::outputHeaders(const SitesMask& mask) {
    OutObjectPtrVector::iterator it;
    for (it = outputObjects.begin(); it != outputObjects.end(); ++it) {
        (*it)->writeHeader(mask);
    }
    errorsOutput->writeHeader();
    seqOutput->writeHeader();
}

bool
CapthistRun::output(ObsSequence& seq, const SitesMask& mask, PPErrors& errors) {
    seqOutput->write(seq, "r");
    seq.sort();

    PitProSettings& settings = PitProSettings::getInstance();
    bool showAllCodes = (settings.getValue(PitProSettings::HistDetail) == "All");

    // remove all observations after the first recap, if any
    if (!showAllCodes)
        seq.truncateAtRecap();

    if (settings.isChecked(PitProSettings::AdultModeSwitch)) {
        // do this before stages are set. This should be based on the stage indicated by the
        // detector, if any.
        if (settings.isChecked(PitProSettings::RemoveResidualizers) && seq.isResidualized())
            errors.setError(PPErrors::AdultOnJuvenileDet);

        // check for fish observed in migration year +1 before the residualizing cutoff date. This attempts
        // to remove fish observed in spring of the year following migration. The cutoff date is set by user
        // and could be anything, but it should be a spring cutoff date.
        if (settings.isChecked(PitProSettings::UseSteelheadYear) || settings.isChecked(PitProSettings::ResCutoffSwitch)) {
            QString springCutoffDate;
//            stringstream ss;
            if (settings.isChecked(PitProSettings::UseSteelheadYear))
                springCutoffDate = QString("%1-07-01").arg(QString::number(settings.getIntValue(PitProSettings::MigrationYear) + 1));//ss <<settings.getIntValue(PitProSettings::MigrationYear) + 1 << "-07-01";
            else
                springCutoffDate = settings.getValue(PitProSettings::ResCutoffDate);//ss << settings.getValue(PitProSettings::ResCutoffDate);

            DateConverter dc(springCutoffDate);
            if (seq.isResidualized2(dc.getTime()))
                errors.setError(PPErrors::OneYearOldPreCutoff);
        }
    }

    if (!settings.isChecked(PitProSettings::AdultModeSwitch))
        seq.setStages(CbrPit::ST_Juvenile); // assume juvenile when not in adult mode
    else
        seq.setStages();

    if (!seq.isStagesSet())
        errors.setError(PPErrors::UnknownStage);

    // write s line
    seqOutput->write(seq, "s");

    if (showAllCodes)
        seq.compress(ObsSequence::ShowAllCodes);
    else if (settings.isChecked(PitProSettings::RemovalTrumpsSwitch))
        seq.compress(ObsSequence::RemovalTrumpsAll);
    else
        seq.compress(ObsSequence::LastOutcomeRules);

    // write c line
    seqOutput->write(seq, "c");

    if (!settings.isChecked(PitProSettings::SingleCoilSwitch))
        seq.removeSingleHits();

    // update any transported flags that are subsequently detected to unkown
    if (!showAllCodes) {
    if (seq.updateTransportedDetected()) {
        QString sstr("Censoring transported fish for detection downstream: ");
        sstr.append(seq.getPitCode());
        if (seq.isValidCursor()) {
            const ObsRecord curRec = seq.getCursorRecord();
            DateConverter dc(curRec.getLastDate());
            sstr.append(QString(" %1 %2").arg(curRec.getSite().getShortName(), dc.output()));
        }
        out.write(sstr, PPOutputMaker::Warning);
//        stringstream ss;
//        ss << "Censoring transported fish for detection downstream: ";
//        ss << seq.getPitCode().toStdString();
//        if (seq.isValidCursor()) {
//            const ObsRecord& curRec = seq.getCursorRecord();
//            DateConverter dc(curRec.getLastDate());
//            ss << " " << curRec.getSite().getShortName().toStdString() << " " << dc;
//        }
//        out.write(ss.str(), PPOutputMaker::Warning);
    }
    }

    if (settings.isChecked(PitProSettings::AdultModeSwitch)) {
        if (settings.isChecked(PitProSettings::AnyRouteSwitch))
            seq.transform(ObsSequence::AnyObs);
        else
            seq.transform(ObsSequence::LastRoute);

        // write t
        seqOutput->write(seq, "t");
    }

    if (seq.isPreRel())
        errors.setError(PPErrors::PreRel);

    if (seq.isOutOfSequence()) {
        errors.setError(PPErrors::OutOfSequence);
#if 0
        if (settings.isChecked(PitProSettings::CensorJuvUpstreamSwitch))
            errors.setError(PPErrors::OutOfSequence);
        else
            seq.truncateJuvenileUpstream(mask);
#endif
    }

    if (settings.isChecked(PitProSettings::SiteRel) && !seq.isFirstReturned(mask))
        errors.setError(PPErrors::NoSiteRel);

    const QStringList icovs = seq.getIcovs();
    for (QStringList::const_iterator it = icovs.begin(); it != icovs.end(); ++it) {
        const QString icov = *it;
        if (settings.isChecked(PitProSettings::NullCovariateSwitch) && icov.isEmpty())
            errors.setError(PPErrors::ZeroCovariate);
        if (settings.isChecked(PitProSettings::ZeroCovariateSwitch) && (icov.isEmpty() || icov.toInt() == 0))
            errors.setError(PPErrors::ZeroCovariate);
    }

    if (settings.isChecked(PitProSettings::ReleaseDataCheck) && seq.getReleaseDate() == -1)
        errors.setError(PPErrors::NoRelDate);

    if (seq.isPreRemoved(mask))
        errors.setError(PPErrors::PreRemoved);

    if (settings.isChecked(PitProSettings::RemoveJacks) && seq.hasMinijacks())
        errors.setError(PPErrors::Minijack);

#if 0
    if (seq.isTransportedDetected()) {
        if (settings.isChecked(PitProSettings::AdultModeSwitch))
            errors.setError(PPErrors::NotTransported);
        else
            seq.setTransportedToUnknown();
    }
#endif

    if (!errors.isOk()) {
        errorsOutput->write(errors);
        return false;
    }

    //seqOutput->write (seq, "p"); // pre-mask sequence

    // non-masked output
    OutObjectPtrVector::iterator it;
    for (it = outputObjects.begin(); it != outputObjects.end(); ++it) {
        (*it)->write(seq, mask, showAllCodes);
    }

    // masked output
    seq.applyMask(mask, showAllCodes);
    // write line
    seqOutput->write(seq, "m");

    if (seq.isMissingICov())
        icovMissing = true;
    surphOutput->writeHist(seq, mask, true);

    return true;
}

bool CapthistRun::isIcovMissing() const {
    PitProSettings& settings = PitProSettings::getInstance();
    bool rosterFormat = settings.getValue(PitProSettings::OutputFormat).compare("ROSTER") == 0;
    bool writeCovars = settings.isChecked(PitProSettings::ICovSwitch) && !rosterFormat;

    return writeCovars && icovMissing;
}

/*
 * Functions to read files and hash the data
 */

void CapthistRun::readData(PPFishData& fishData, const RunConfigItem& runItem) {
    PitProSettings& settings = PitProSettings::getInstance();

    QString popName = runItem.name;
    QString msg(QString("Reading tag data for \"%1\"").arg(popName));
    out.write(msg);
    out.setProgressMessage(msg);
    readTags(fishData, settings.getDataFilePath(runItem.tag));

    if (runItem.mort.compare("none") != 0) {
        msg = QString(QString("Reading mortality data for \"%1\"").arg(popName));
        out.write(msg);
        out.setProgressMessage(msg);

        readRecaps(fishData, settings.getDataFilePath(runItem.mort), FishSetEntry::Mort);
    }

    if (runItem.recap.compare("none") != 0) {
        msg = QString(QString("Reading recapture data for \"%1\"").arg(popName));
        out.write(msg);
        out.setProgressMessage(msg);
        readRecaps(fishData, settings.getDataFilePath(runItem.recap), FishSetEntry::Recap);
    }
}

/*
 * always read the tags first, this defines the set of fishes we are
 * interested in.
 */
void
CapthistRun::readTags(PPFishData& fishData, const QString file) {
    ifstream ifs(file.toStdString().data());
    if (!ifs.is_open())
        out.write("Error. Unable to open file \"" + file + "\"...", PPOutputMaker::Error);
    else {
        setFileBytes(ifs);
        std::string ln;
        QString line;
        PPTag tag;
        int row = 0;
        PitProSettings& settings = PitProSettings::getInstance();
        QString species_a = settings.getValue(PitProSettings::Species);
        QString run_a = settings.getValue(PitProSettings::Run);
        QString rt_a = settings.getValue(PitProSettings::RearType);

        numICovs = -1;
        while (getline(ifs, ln)) {
            if (isCanceled())
                return;
            ++row;
            line = QString(ln.data());

            out.setCurrentBytes(line.size() + 1);

            stringstream instream(line.toStdString());
            instream >> tag;

            PPErrors errors;
            errors.setPitCode(tag.getPitCode());

            if (tag.isOk() && !tag.isHeader()) {

                if (numICovs == -1) {
                    numICovs = tag.numICovs();
                    surphOutput->setNumICovs(numICovs);
                }

                QString species_b = QString(tag.getSpecies());
                if (species_a.compare("All") != 0 && species_b.compare("A") != 0 &&
                        species_a.compare(species_b) != 0)
                    errors.setError(PPErrors::WrongSpecies);

                QString run_b = QString(tag.getRun());
                if (run_a.compare("All") != 0 && run_b.compare("A") != 0 &&
                        run_a.compare(run_b) != 0)
                    errors.setError(PPErrors::WrongRun);

                QString rt_b = QString(tag.getRearType());
                if (rt_a.compare("All") != 0 && rt_b.compare("A") != 0 && rt_a.compare(rt_b) != 0)
                    errors.setError(PPErrors::WrongRearType);

                if (!errors.isOk())
                    errorsOutput->write(errors);
                else
                    fishData.addFish(tag.getPitCode(), tag.getRelTime(), tag.getRelSite(), tag.getICovs());
            }
        }
    }
}

void
CapthistRun::readRecaps(PPFishData& fishData, const QString file, FishSetEntry::RecapType type) {
    // open the file and parse it
    ifstream ifs(file.toStdString().data());
    if (!ifs.is_open())
        out.write("Unable to open file \"" + file + "\"...", PPOutputMaker::Warning);
    else {
        setFileBytes(ifs);

        PitProSettings& settings = PitProSettings::getInstance();
        std::string ln;
        QString line;
        PPRecap recap;
        int row = 0;
        Sites* sites = Sites::getInstance();
        while (getline(ifs, ln)) {
            if (isCanceled())
                return;
            ++row;
            line = QString(ln.data());

            out.setCurrentBytes(line.size() + 1);

            stringstream instream(line.toStdString());
            instream >> recap;

            if (recap.isOk() && !recap.isHeader() && !settings.ignoreRecap(recap.getSite())) {
                QString pitCode = recap.getPitCode();
                if (fishData.setCurrent(pitCode)) {
                    double recapTime = recap.getTime();
                    const QString recapSiteName = recap.getSite();
                    const QString recapRiverKm = recap.getRiverKM();
                    Site* recapSite = sites->getRelSite(recapSiteName);
                    if (!recapSite) {
                        out.write("Unable to find site information for \"" + recapSiteName + "\"", PPOutputMaker::Error);
                    }
                    else if (recapRiverKm.isEmpty() && !recapSite->validRiverkm()) {
                        out.write("Invalid river km data for \"" + recapSiteName + "\": " + recapSite->getRiverkDn().toString(),
                                PPOutputMaker::Warning);
                    } else {
                        bool ignoreReRecaps = settings.isChecked(PitProSettings::IgnoreReRecaps);
                        double relTime = fishData.getCurrentRelTime();
                        const QString relSite = fishData.getCurrentRelSite();
                        DateConverter recapDate(recapTime);
                        DateConverter relDate(relTime);

                        if (!ignoreReRecaps || relSite.isEmpty() || recapSiteName.isEmpty() ||
                                type == FishSetEntry::Mort || relSite.compare(recapSiteName) != 0 ||
                                recapDate.year() != relDate.year()) {
                            fishData.updateRecapData(pitCode, recapTime, recapSite, recapRiverKm);
                        }
                    }
                }
            }
        }
    }
}

void CapthistRun::setFileBytes(std::ifstream& f) {
    f.seekg(0, ios::end);
    int size = static_cast<int>(f.tellg()); // file must be under 2gb for this cast
    f.seekg(0, ios::beg);
    out.setBytesExpected(size);
}





