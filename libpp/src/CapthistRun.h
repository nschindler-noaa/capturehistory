/*
 * CapthistRun.h
 */

#ifndef CapthistRun_h
#define CapthistRun_h

#include <vector>
#include <list>
//#include <string>
#include <iostream>
#include <fstream>

#include <ObsSequence.h>
#include <ArrayDefs.h>

#include <QStringList>

#include "PPDefs.h"
#include "PPTag.h"
#include "PPRel.h"
#include "PPRecap.h"
#include "PitProSettings.h"
#include "PPFishData.h"
#include "RunConfigVector.h"

class PPOutputMaker;
class PPSequenceOutput;
class PPSurphOutput;
class SitesMask;
class PPObs;
class PPSeqOutput;
class PPErrorsOutput;
class PPErrors;

typedef QList<PPSequenceOutput*> OutObjectPtrVector;

class CapthistRun
{

public:
    CapthistRun(PPOutputMaker& out);
    ~CapthistRun();

    void compute(const QString outPrefix, const RunConfigVector& runConfigVector);
    void setIsCanceledPtr(bool* bp) { isCanceledPtr = bp; }
    bool isCanceled() const;
    const QString getErrorMessage() const { return errorMessage; }
    bool hasError() const { return errorMessage.size() > 0; }
    bool isIcovMissing() const;

private:

    // data methods
    void readData(PPFishData& fishData, const RunConfigItem& runItem);
    void readTags(PPFishData& fishData, const QString file);
    void readRecaps(PPFishData& fishData, const QString file, FishSetEntry::RecapType);

    // error checking
    bool isOk (const PPObs& obs, const QList<PPTag>& tags);

    // processing
    void processObsRec(ObsSequence& seq, const PPObs& obs, int row);
    void initializeSequence(ObsSequence& seq);
    int processObsFile(std::ifstream& in, PPFishData& fishData, const SitesMask& mask);
    int handleUndetectedTags(PPFishData& fishData, const SitesMask& mask);
    void reset(ObsSequence& seq, const QString pitCode, PPFishData& fishData, PPErrors& errors);

    // output methods
    void openOutputStreams(const QString prefix);
    void closeOutputStreams();
    void outputHeaders(const SitesMask& mask);
    bool output(ObsSequence& seq, const SitesMask& mask, PPErrors& errors);
    void deleteOutput();

    // output members
    PPOutputMaker& out;
    OutObjectPtrVector outputObjects;
    PPSurphOutput* surphOutput;
    PPSeqOutput* seqOutput;
    PPErrorsOutput* errorsOutput;

    // status members
    QString errorMessage;
    void cancel();
    int bytesProcessed;
    void setFileBytes(std::ifstream& f);
    bool* isCanceledPtr; // for running in the gui environment

    bool icovMissing;
    int numICovs;

};

#endif // CapthistRun_h
