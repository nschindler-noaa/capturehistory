/*
 */

#ifndef ObsProcessorWriter_h
#define ObsProcessorWriter_h


class SitesMask;
class ObsProcessor;
class ObsSequence;

class ObsProcessorWriter
{
 public:
  ObsProcessorWriter() {}
  virtual ~ObsProcessorWriter() {}
  virtual void pre() {}
  virtual void write(ObsSequence&) {}
  virtual void post() {}

 protected:
	 std::string errorMessage;
  
};

#endif
