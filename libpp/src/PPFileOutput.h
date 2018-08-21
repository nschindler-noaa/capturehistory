/*
 *
 */

#ifndef PPFileOutput_h
#define PPFileOutput_h

#include <string>
#include <iostream>
#include <fstream>

class ObsSequence;
class SitesMask;

class PPFileOutput
{
public:
	PPFileOutput() : fw(15) {}
	virtual ~PPFileOutput();
	virtual void setPrefix (const std::string& prefix);
	virtual std::string getFileName(const std::string& prefix) const = 0;
	virtual bool active() const { return true; }
	virtual void closeAndDelete ();
	void setFieldWidth(int rhs) { fw = rhs; }
	virtual void close();

protected:
	std::ofstream ofs;
	std::string prefix;
	int fw; // field width
};

#endif
