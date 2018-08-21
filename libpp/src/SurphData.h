#ifndef SurphData_H
#define SurphData_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <TaggingData.h>
#include <CaptureHistoryMap.h>

namespace surph {

    /** Surph data object. Represents the contents of the SURPH data file. */
    class SurphData : public TaggingData {
    public:
        SurphData(std::istream& is, const std::string fileName = std::string());
        SurphData(const SurphData& surphData);

        virtual ~SurphData() {
        }

        const std::string& fileName() const {
            return fileName_;
        }

        const std::string& dataDescription() const {
            return description_;
        }

        const std::string& populationName(unsigned int i) const {
            return (*populationNames_)[i];
        }

        unsigned int numPopulations() const {
            return numPopulations_;
        }

        unsigned int numPeriods() const {
            return numPeriods_;
        }

        unsigned int numReleased(unsigned int i) const {
            return (*numReleased_)[i];
        }
        const CaptureHistoryMap& captureHistoryMap(unsigned int pop) const;
    private:
        const std::string fileName_;
        std::string description_;
        unsigned int numPopulations_;
        unsigned int numPeriods_;
        std::auto_ptr<std::vector<std::string> > populationNames_;
        std::auto_ptr<std::vector<unsigned int> > numReleased_;
        std::auto_ptr<std::vector<CaptureHistoryMap> > captureHistoryMaps_;
        bool fullCaptureHistories_;
        unsigned int numIndividualCovariates_;
        unsigned int numGroupCovariates_;
        bool tagIDPresent_;
    };
};

#endif



