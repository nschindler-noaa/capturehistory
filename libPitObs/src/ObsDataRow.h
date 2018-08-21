/*
 *
 * Pure abstract class for observation data rows
 *
 */

#ifndef ObsDataRow_h
#define ObsDataRow_h

#include "DataRow.h"
#include "CbrPit.h"

class ObsDataRow  : public DataRow
{
 public:
  virtual double relDate() const = 0;
  virtual const char* pitCode() const = 0;
  virtual const char* obsSite() const = 0;
  virtual const char* lastDet() const = 0;
  virtual double firstDate() const = 0;
  virtual double lastDate() const = 0;
  virtual cbr::CbrPit::Stage stage() const = 0;
};

#endif
