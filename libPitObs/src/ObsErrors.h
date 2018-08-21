/*
*/

#ifndef ObsErrors_h
#define ObsErrors_h

#include <iostream>

#include <ErrorFlags.h>

class ObsErrors : public ErrorFlags
{
public:
	enum  {
		NotTransported,
		Num
	};

	ObsErrors() : ErrorFlags (Num) {}
};

#endif
