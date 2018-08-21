/*
*/

#ifndef PPTag_h
#define PPTag_h

#include <iostream>
#include <sstream>
#include <string>


#include "PPData.h"

class PPTag : public PPData
{
public:
	enum TagFields {TagGroup=0, PitCode, RelTime, RelSite, Species, Run, RearType, ICov1, NFields };
	
	PPTag();
	bool read(std::istream& is);
	void write(std::ostream& os) const;

	const std::string& getPitCode () const { return pitCode; }
	const std::string& getRelSite() const { return relSite; }
	char getSpecies () const { return species; }
	char getRun () const { return run; }
	char getRearType () const { return rear_type; }
	short getLength () const;
	const std::string& getICov(int i) const;
	const std::vector<std::string>& getICovs() const { return icovs; }
	int numICovs() const;
	double getRelTime() const { return relTime; }
	const std::string& getTagGroup() const { return tagGroup; } // only used for data converter

	void setRelTime( double time ) { relTime = time; }

private:
	std::string pitCode;
	std::string relSite;
	double relTime;
	char species;
	char run;
	char rear_type;
	std::vector<std::string> icovs;
	bool missingIcov;

	short length;

	std::string tagGroup; // not normally used, for use in data converter

	virtual void resetColumnOrder();

};


#endif
