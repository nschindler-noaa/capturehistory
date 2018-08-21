#ifndef Code_h
#define Code_h

#include <vector>
#include <string>

#include "CbrPit.h"
#include "Range.h"
#include "Exception.h"

class Code
{
  public:
	  Code( const std::string& siteCode ) : allReturned( 0 ) { name = siteCode; }
    ~Code();
    
    // insert the returned object at the end of the list,
    // returned rules defined earlier in the config file
    // have higher precedence
    void addRange( Range* oc );

    // insert the exception at the end of the list,
    // exceptions defined earlier in the config file
    // have higher precedence
    void addException( Exception* ex );

    void setAllReturned() { allReturned = 1; }
    
    int entries() { return ranges.size(); }
	const std::string& getName() { return name; }
	cbr::CbrPit::Outcome getOutcome( const std::string& detector, double jd ) const;
	cbr::StringVector getCoils( const std::string& detector, double jd ) const;
	const Detector* getDetector( const std::string& coil, double jd ) const;
    const Range* getRange( double jd ) const;
    const std::vector<Exception*> getExceptions (double jd) const; 

    friend std::ostream &operator <<( std::ostream &o, const Code &code );

private:
	std::string name;
    std::vector< Range* > ranges;
    std::vector< Exception* > exceptions;
    int allReturned;
 
};

#endif
