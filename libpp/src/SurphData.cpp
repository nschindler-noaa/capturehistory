#include "SurphData.h"
#include "Parser.h"
#include "Token.h"
#include "CjsCaptureHistory.h"
#include "ParseError.h"
//#include <boost/lexical_cast.hpp>
using namespace std;

namespace surph
{
    SurphData::SurphData(istream& is, const QString fileName)   {
        Parser parser(is);

        Token token = parser.nextToken();
        fileName_ = QString(fileName);
        numPopulations_ = 0;
        numPeriods_ = 0;
        fullCaptureHistories_ = false;
        numIndividualCovariates_ = 0;
        numGroupCovariates_ = 0;
        tagIDPresent_ = false;

        if (token.name != "Surph2")
            throw ParseError("not a valid SURPH 2 file");
        description_ = parser.nextToken().name;
        token = parser.nextToken();
        while (!token.firstInLine)
        {
            description_ += " " + token.name;
            token = parser.nextToken();
        }

        for (;token.name != "captureHistories"; token = parser.nextToken())
        {
            if (token.name == "npop" || token.name == "num_populations")
            {
                numPopulations_ = token.name.toInt();//boost::lexical_cast<unsigned int, string>(parser.nextToken().name);
            }
            else if (token.name == "nper" || token.name == "num_periods")
            {
                numPeriods_ = parser.nextToken().name.toInt();//boost::lexical_cast<unsigned int, string>(parser.nextToken().name);
            }
            else if (token.name == "ntag" || token.name == "num_tagged")
            {
                numReleased_.clear();
//                numReleased_.reset(new vector<unsigned int>(numPopulations_));
                for (int i=0; i < numPopulations_; ++i)
                    numReleased_.append(parser.nextToken().name.toInt());
//                    (*numReleased_)[i] = boost::lexical_cast<unsigned int, string>(parser.nextToken().name);
            }
            else if (token.name == "population_names")
            {
                populationNames_.clear();
//                populationNames_.reset(new vector<string>(numPopulations_));
                for (int i=0; i < numPopulations_; ++i) {
                    populationNames_.append(parser.nextToken().name);
                }
//                    (*populationNames_)[i] = parser.nextToken().name;
            }
            else if (token.name == "icov" || token.name == "individual_covariate")
            {
                ++numIndividualCovariates_;
            }
            else if (token.name == "gcov" || token.name == "group_covariate")
            {
                ++numGroupCovariates_;
            }
            else if (token.name == "tagIDPresent")
            {
                tagIDPresent_ = true;
            }
            else if (token.name == "tagID")
            {
                token = parser.nextToken();
                if (token.name == "present") {
                    tagIDPresent_ = true;
                }
            }
            else if (token.name == "full_hist")
            {
                fullCaptureHistories_ = true;
            }
        }

        // Set up default population names if none specified
        if (populationNames_.isEmpty())
        {
//            populationNames_.reset(new vector<string>(numPopulations_));
            for (int i=0; i < numPopulations_; ++i) {
                populationNames_.append(QString::number(i+1));
            }
//                (*populationNames_)[i] = boost::lexical_cast<string,unsigned int>(i+1);
        }

        captureHistoryMaps_.clear();
//        captureHistoryMaps_.reset(new vector<CaptureHistoryMap>(numPopulations_));

        // Parse the capture histories
        for (int pop=0; pop < numPopulations_; ++pop)
        {
//            captureHistoryMaps_.append()
            for (int i=0; i < numReleased_.at(pop); ++i)
            {
                if (tagIDPresent_)
                    Token tagID = parser.nextToken();
                CjsCaptureHistory *captureHistory = new CjsCaptureHistory(numPeriods_+1);
//                auto_ptr<CjsCaptureHistory> captureHistory(new CjsCaptureHistory(numPeriods_+1));
                int count = 1;

                for (int j=1; j <= numPeriods_+1; ++j)
                {
                        token = parser.nextToken();
                        //if (token.name.isEmpty())
                        //    throw unexpectedEndOfLine(token);
                        if (token.name == "1")
                            captureHistory->capture(j);
                        else if (token.name == "2")
                        {
                            captureHistory->remove(j);
                            if (!fullCaptureHistories_)
                                break;
                        }
                }
                if (parser.peekAtNextToken().name == ":")
                {
                    parser.nextToken();
                    token = parser.nextToken();
                    count = token.name.toInt();//boost::lexical_cast<int,string>(token.name);
                }

                for (int j=0; j < numIndividualCovariates_; ++j)
                    parser.nextToken();

                CaptureHistoryMap::iterator iter = (captureHistoryMaps_)[pop].find(captureHistory);
                if (iter == (captureHistoryMaps_)[pop].end())
                    (captureHistoryMaps_)[pop].insert(CaptureHistoryMap::value_type(captureHistory, count));
                else
                    iter->second += count;
            }
        }
    }

    const CaptureHistoryMap& SurphData::captureHistoryMap(int pop) const
    {
        return (captureHistoryMaps_)[pop];
    }
};

