/*
 *
 */

#ifndef ObsPreProcessor_h
#define ObsPreProcessor_h

#include <vector>

#include "ObsProcessor.h"

class ObsSequence;
class Site;

typedef std::vector<const Site*> SitePtrVector;

class ObsPreProcessor : public ObsProcessor
{
 public:
  ObsPreProcessor() {}
  ~ObsPreProcessor() {}

  void post();

  const SitePtrVector& getJuvenileSites() const { return juvenileSites; }
  const SitePtrVector& getAdultSites() const { return adultSites; }

 protected:
  void process( ObsSequence& seq );

 private:
  SitePtrVector juvenileSites;
  SitePtrVector adultSites;
};

#endif
