/*
 *
 */

#ifndef PPRunConfig_h
#define PPRunConfig_h

#include <string>
#include <QStringList>

class PPRunConfig {
public:
    void read(const QString fileName);
    void write(const QString fileName);
private:
    void processParamDef(const QString group, const QString key, const QString val);
};


#endif
