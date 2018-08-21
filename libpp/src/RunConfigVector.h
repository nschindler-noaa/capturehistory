/*
 */

#ifndef RunConfigVector_h
#define RunConfigVector_h

#include <string>
#include <vector>

/*
 * A data structure to hold the filenames for
 * each run
 */
typedef struct {
	std::string name;
	std::string tag;
	std::string obs;
	std::string recap;
	std::string mort;
	std::string outdir;
	std::string datadir;
} RunConfigItem;
typedef std::vector<RunConfigItem> RunConfigVector;



#endif
