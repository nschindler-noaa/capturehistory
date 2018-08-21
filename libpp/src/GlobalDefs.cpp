#include "GlobalDefs.h"


GlobalDefs* GlobalDefs::instance_ = 0;

GlobalDefs* GlobalDefs::instance()
{
	if (instance_ == 0) {
		instance_ = new GlobalDefs;
	}
	return instance_;
}
