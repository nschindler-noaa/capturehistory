/*
*
*/

#ifndef PPRel_h
#define PPRel_h

#include <iostream>
#include <sstream>
#include <string>

#include "PPData.h"

class PPRel : public PPData
{
public:
	enum RelFields {Key = 0, Date, Time, NFields };

	PPRel();
	bool read(std::istream& is);
	void write(std::ostream& os) const;

	std::string getKey() const { return key; }
	double getReleaseTime() const { return time; }

private:
	std::string key;
	double time;

};

class PPRelEql 
{
public:
	PPRelEql (const std::string& s) : key(s) {}
	void setKey(const std::string& s) { key = s; }
	bool operator() (const PPRel& rel)
	{
		return key.compare (rel.getKey()) == 0;
	}
private:
	std::string key;
};



#endif
