/***********************************************************************
  file: PCode.cpp
 ***********************************************************************/

#include <string>
#include <iostream>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "PCode.h"
#include "Site.h"
#include "DateConverter.h"


using std::string;
using std::cerr;
using std::endl; 

using namespace cbr;

PCode::PCode(const string& pc, const Site* site) : site(site)
{
  seq.setPitCode(pc);
}

void PCode::compress() {
  seq.compress(ObsSequence::RemovalTrumpsAll);
}

bool PCode::isReturned() const
{ 
    bool returned = false;
    const ObsRecord& rec = seq.getFirstRecord();

    switch (rec.getOutcome()) {
    case CbrPit::Bypass:
    case CbrPit::AdultDetect:
    case CbrPit::PitBarge:
    case CbrPit::PileDike:
    case CbrPit::Returned:
    case CbrPit::Spillway:
    case CbrPit::BonnLadder:
    case CbrPit::Weir:
    case CbrPit::AMBridge:
        returned = true;  // fish that are returned, or stay in, the river
        break;
    default:
        returned = false; // fish that do not proceed (dead)
        break;
    }
    return returned;
}

const string& PCode::getPitcode() const 
{ return seq.getPitCode(); }

double PCode::getTime() const
{
  const ObsRecord& rec = seq.getFirstRecord();
  return rec.getLastDate();
}

void PCode::addRecord( CbrPit::Outcome outcome, double obsdate ) 
{
  seq.addRecord( site, CbrPit::ST_Juvenile, outcome, obsdate, obsdate, 1 );
}


int operator==(const PCode& pc, const char *s)
{ 
  const string& pitCode = pc.getPitcode();
  return (pitCode.compare( s ) == 0); 
}

