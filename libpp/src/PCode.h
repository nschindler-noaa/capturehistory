/**********************************************************************
file:  PCode.h
***********************************************************************/

#ifndef PCode_H
#define PCode_H

#include <string>

#include <CbrPit.h>
#include <DateConverter.h>
#include <ObsSequence.h>
#include <Site.h>

class PCode 
{
public:
    PCode(const std::string& pc, const Site* site);
  ~PCode() {}
  double getTime() const;
  void compress(); 
  void addRecord( cbr::CbrPit::Outcome outcome, double obsdate );
  bool isReturned() const;
  const std::string& getPitcode() const;
  
  friend int operator==(const PCode& pc, const char *s);

private:
  const Site* site;
  ObsSequence seq;
    
};

#endif
