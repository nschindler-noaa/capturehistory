/*
*/

#ifndef PPErrors_h
#define PPErrors_h

#include <iostream>

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
	
	void setPitCode (const std::string& pc) { pitCode = pc; }

	static std::string getText (ErrorType type);
	static std::string getText (int type);
    bool isValid() const { return valid; }

	void write (std::ostream& os) const;
	void read (std::istream& os);

	void reset( const std::string& pitCode );

	
private:
	std::string pitCode;
    bool valid;

};

#endif
