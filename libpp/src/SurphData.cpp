#include "SurphData.h"
#include "Parser.h"
#include "Token.h"
#include "CjsCaptureHistory.h"
#include "ParseError.h"
#include <boost/lexical_cast.hpp>
using namespace std;

namespace surph
{
    SurphData::SurphData(istream& is, const string fileName) : fileName_(fileName), numPopulations_(0), numPeriods_(0),
		fullCaptureHistories_(false), numIndividualCovariates_(0), numGroupCovariates_(0), tagIDPresent_(false)
    {
        Parser parser(is);

        Token token = parser.nextToken();
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
                numPopulations_ = boost::lexical_cast<unsigned int, string>(parser.nextToken().name);
            else if (token.name == "nper" || token.name == "num_periods")
            {
                numPeriods_ = boost::lexical_cast<unsigned int, string>(parser.nextToken().name);
            }
            else if (token.name == "ntag" || token.name == "num_tagged")
            {
                numReleased_.reset(new vector<unsigned int>(numPopulations_));
                for (unsigned int i=0; i < numPopulations_; ++i)
                    (*numReleased_)[i] = boost::lexical_cast<unsigned int, string>(parser.nextToken().name);
            }
            else if (token.name == "population_names")
            {
                populationNames_.reset(new vector<string>(numPopulations_));
                for (unsigned int i=0; i < numPopulations_; ++i)
                    (*populationNames_)[i] = parser.nextToken().name;
            }
			else if (token.name == "icov" || token.name == "individual_covariate")
				++numIndividualCovariates_;
			else if (token.name == "gcov" || token.name == "group_covariate")
				++numGroupCovariates_;
			else if (token.name == "tagIDPresent")
				tagIDPresent_ = true;
			else if (token.name == "tagID")
			{
				token = parser.nextToken();
				if (token.name == "present")
					tagIDPresent_ = true;
			}
			else if (token.name == "full_hist")
				fullCaptureHistories_ = true;
        }

		// Set up default population names if none specified
		if (populationNames_.get() == 0)
		{
			populationNames_.reset(new vector<string>(numPopulations_));
			for (unsigned int i=0; i < numPopulations_; ++i)
				(*populationNames_)[i] = boost::lexical_cast<string,unsigned int>(i+1);
		}

        captureHistoryMaps_.reset(new vector<CaptureHistoryMap>(numPopulations_));

		// Parse the capture histories
        for (unsigned int pop=0; pop < numPopulations_; ++pop)
        {
            for (unsigned int i=0; i < (*numReleased_)[pop]; ++i)
            {
				if (tagIDPresent_)
					Token tagID = parser.nextToken();
                auto_ptr<CjsCaptureHistory> captureHistory(new CjsCaptureHistory(numPeriods_+1));
                int count = 1;

                for (unsigned int j=1; j <= numPeriods_+1; ++j)
                {
                        token = parser.nextToken();
						//if (token.name == string())
						//throw unexpectedEndOfLine(token);
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
                    count = boost::lexical_cast<int,string>(token.name);
                }

				for (unsigned int j=0; j < numIndividualCovariates_; ++j)
					parser.nextToken();
                
                CaptureHistoryMap::iterator iter = (*captureHistoryMaps_)[pop].find(captureHistory.get());
                if (iter == (*captureHistoryMaps_)[pop].end())
                    (*captureHistoryMaps_)[pop].insert(CaptureHistoryMap::value_type(captureHistory.release(), count));
                else
                    iter->second += count;
            }
        }
    }

    const CaptureHistoryMap& SurphData::captureHistoryMap(unsigned int pop) const
    {
        return (*captureHistoryMaps_)[pop];
    }
};

