/*
*/

#ifndef PPMort_h
#define PPMort_h

#include <string>
#include <iostream>
#include <functional>

class PPMort 
{
public:
	friend std::istream& operator>> (std::istream& is, PPMort& mort)
	{
		is >> mort.pitCode;
		return is;
	}

	friend std::ostream& operator<< (std::ostream& os, const PPMort& mort)
	{
		os << mort.pitCode;
		return os;
	}

	const std::string& getPitCode () const { return pitCode; }

private:
	std::string pitCode;

};


struct ppmort_eql 
{
	ppmort_eql (const std::string& s) : pc(s) {}
	bool operator() (const PPMort& mort)
	{
		return pc.compare (mort.getPitCode()) == 0;
	}
	std::string pc;
};

#endif
