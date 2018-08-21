/*
 *
 */

#ifndef PPRunConfig_h
#define PPRunConfig_h

#include <string>

class PPRunConfig {
public:
    void read(const std::string& fileName);
    void write(const std::string& fileName);
private:
    void processParamDef(const std::string group, const std::string key, const std::string val);
};


#endif
