/*
 * CbrPit
*/

#ifndef CbrPit_h
#define CbrPit_h

//#include <string>
#include <QStringList>

#include <ArrayDefs.h>

namespace cbr
{
    class CbrPit
    {
    public:
        enum Outcome
        {
            Invalid = 0,
            NoDetect,
            Bypass,
            Unknown,
            AdultDetect,
            PitBarge,
            PileDike,
            Returned,
            PitTrawl,
            Transported,
            Hold,
            Sampled,
            Spillway,
            AvianColony,
            BonnLadder,
            Weir,
            AMBridge,
            NumOutcomes
        };
        enum Stage
        {
                ST_Adult = 0,
                ST_Juvenile,
                ST_Unknown,
                NumStages
        };
        enum Format
        {
                Surph = 0,
                Roster,
                NumFormats
        };

        enum JacksPolicy { JP_Combined, JP_Seperate };

        CbrPit();
        static CbrPit& getInstance();

        QString stringFromJuvenileOutcome (Outcome oc);
        QString stringFromAdultOutcome (Outcome oc, int age, JacksPolicy jacksPolicy = JP_Seperate);
        QString labelFromOutcome(Outcome oc);
        QString &stringFromStage(Stage stage);
        QChar charFromStage (Stage stage);
        Stage stageFromChar (char stage);
        Stage stageFromString (const QString stage);
        void setNumJuvenileSymbols (int num);
        void setJuvenileSymbol (Outcome oc, const QString symbol = "");
        void setOutputFormat (Format format, const QString code = "Std", bool unknownLetter = false);
        bool isRemoved (Outcome oc) const;

    private:
        QStringList juvenileSymbols;
        Format outputFormat;
        QString result;
        QChar qchar;
    };

}

#endif
