#ifndef SurphData_H
#define SurphData_H

#include <istream>
#include <iostream>
#include <QStringList>
//#include <memory>

#include <TaggingData.h>
#include <CaptureHistoryMap.h>

namespace surph {

    /** Surph data object. Represents the contents of the SURPH data file. */
    class SurphData : public TaggingData {
    public:
        SurphData(std::istream &is, const QString fileName = QString());
        SurphData(const SurphData& surphData);

        virtual ~SurphData() {
        }

        const QString fileName() const {
            return fileName_;
        }

        const QString dataDescription() const {
            return description_;
        }

        const QString populationName(int i) const {
            return (populationNames_)[i];
        }

        int numPopulations() const {
            return numPopulations_;
        }

        int numPeriods() const {
            return numPeriods_;
        }

        int numReleased(int i) const {
            return (numReleased_)[i];
        }
        const CaptureHistoryMap& captureHistoryMap(int pop) const;
    private:
        QString fileName_;
        QString description_;
        int numPopulations_;
        int numPeriods_;
        QStringList populationNames_;
        QList<int> numReleased_;
        QList<CaptureHistoryMap> captureHistoryMaps_;
        bool fullCaptureHistories_;
        int numIndividualCovariates_;
        int numGroupCovariates_;
        bool tagIDPresent_;
    };
};

#endif



