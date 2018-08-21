/*
*/

#ifndef PPObs_h
#define PPObs_h

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include "PPData.h"


class PPObs : public PPData
{
public:
	enum ObsFields { PitCode=0, ObsSite, ObsTime, Coil1, NFields };
	
	PPObs();
	bool read(std::istream& is);
	void write(std::ostream& os) const;

	const std::string& getPitCode () const { return pitCode; }
	const std::string& getObsSite () const { return obsSite; }
	double getTime() const { return time; }
	std::string getCoil() const { return coil1; }

private:
	std::string pitCode;
	std::string obsSite;
	double time;
	std::string coil1;
};


struct ppobs_sort_bydate : public std::binary_function<const PPObs&, const PPObs&, bool>
{
	bool operator() (const PPObs& o1, const PPObs& o2)
	{
		return o1.getTime() < o2.getTime();
	}
};

#endif
