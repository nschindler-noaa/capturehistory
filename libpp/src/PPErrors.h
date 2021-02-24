/*
*/

#ifndef PPErrors_h
#define PPErrors_h

#include <iostream>

#include <QString>

#include <ErrorFlags.h>

class PPErrors : public ErrorFlags
{
public:
    enum ErrorType {
        AdultOnJuvenileDet = 0,
        Minijack,
        NoRelDate,
        NoSiteRel,
        NoTag,
        OutOfSequence,
        PreRel,
        PreRemoved,
        OneYearOldPreCutoff,
        UnknownStage,
        WrongSpecies,
        WrongRun,
        WrongRearType,
        ZeroCovariate,
        NumErrorTypes
    };

    PPErrors();
    ~PPErrors();

    void setPitCode (const QString& pc) { pitCode = pc; }

    static QString getText (ErrorType type);
    static QString getText (int type);
    bool isValid() const { return valid; }

    void write (std::ostream& os) const;
    void read (std::istream& os);

    void reset( const QString& pitCode );


private:
    QString pitCode;
    bool valid;

};

#endif
