#ifndef ObsProcessor_h
#define ObsProcessor_h

#include <iostream>
#include <string>
#include <vector>

class ObsSequence;
class SitesMask;
class ObsProcessorWriter;

typedef std::vector<ObsProcessorWriter*> ObsProWriterVector;

class ObsProcessor 
{
 public:
  ObsProcessor() {}
  virtual ~ObsProcessor();

  void processSequence(ObsSequence& seq );

  virtual void pre();
  virtual void post();

  void printError( std::ostream& os ) const { os << errorMessage << std::endl; }
  static void setPrefix( std::string s ) { prefix = s; }

  void addWriter( ObsProcessorWriter* writer );

 protected:
  static std::string prefix;
  ObsProWriterVector writers;
  std::string  errorMessage;

  virtual void process(ObsSequence& ) {}
};


#endif
