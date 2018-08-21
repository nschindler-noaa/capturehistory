/*
*/

#ifndef PPRecap_h
#define PPRecap_h

#include <string>
#include <iostream>

#include "PPData.h"

class PPRecap : public PPData
{
public:
	enum ObsFields { PitCode = 0, RecapTime, Site, RiverKM, NFields };
	
	PPRecap();

	bool read(std::istream& is);
	void write(std::ostream& os) const;

	const std::string& getPitCode () const { return pitCode; }
	double getTime() const { return recapTime; }
	const std::string& getSite () const { return site; }
	const std::string& getRiverKM () const { return riverkm; }
	bool validRiverkm() const;

private:
	std::string pitCode;
	double recapTime;
	std::string site;
	std::string riverkm;
};


#endif
