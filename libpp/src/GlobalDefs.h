#ifndef GlobalDefs_H
#define GlobalDefs_H

// Singleton class for all global definitions

class GlobalDefs
{
public:
	static GlobalDefs* instance();
	int reportPrecision() const {return reportPrecision_;}
	void setReportPrecision(int rhs) {reportPrecision_ = rhs;}
private:
	GlobalDefs() : reportPrecision_(4) {}
	static GlobalDefs* instance_;
	int reportPrecision_;
};
#endif
