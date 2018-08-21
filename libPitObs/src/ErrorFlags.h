/*
*/

#ifndef ErrorFlags_h
#define ErrorFlags_h

#include <iostream>

#include <ArrayDefs.h>

class ErrorFlags
{
public:
	ErrorFlags(size_t num);
	virtual ~ErrorFlags();
	virtual void setError (size_t index);
	virtual void clear();
	bool isOk() const;
	bool isSet (size_t index) const;

	virtual void write (std::ostream& os) const;
	virtual void read (std::istream& is);

	friend std::ostream& operator<< (std::ostream&, const ErrorFlags&);
	friend std::istream& operator>> (std::istream&, ErrorFlags&);

protected:
	cbr::BoolVector errors;

};

#endif
