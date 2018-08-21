#include "ObsProcessor.h"
#include "ObsProcessorWriter.h"

std::string ObsProcessor::prefix = "dhout";

ObsProcessor::~ObsProcessor() 
{
  ObsProWriterVector::iterator it;
  for ( it = writers.begin(); it != writers.end(); it++ )
    delete *it;
}


void ObsProcessor::addWriter( ObsProcessorWriter* writer )
{
  writers.push_back( writer );
}

void ObsProcessor::pre() 
{
  ObsProWriterVector::iterator it;
  for ( it = writers.begin(); it != writers.end(); ++it )
    {
      (*it)->pre();
    }
}

void ObsProcessor::processSequence(ObsSequence& seq) 
{
  // process sequence
  process(seq);

  // call writers
  ObsProWriterVector::iterator it;
  for ( it = writers.begin(); it != writers.end(); ++it )
    {
      (*it)->write(seq);
    }
}

void ObsProcessor::post() 
{
  ObsProWriterVector::iterator it;
  for ( it = writers.begin(); it != writers.end(); ++it )
    {
      (*it)->post();
    }
}




