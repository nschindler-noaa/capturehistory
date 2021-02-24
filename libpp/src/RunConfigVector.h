/*
 */

#ifndef RunConfigVector_h
#define RunConfigVector_h

#include <QStringList>
//#include <string>
//#include <vector>

/*
 * A data structure to hold the filenames for
 * each run
 */
typedef struct {
    QString name;
    QString tag;
    QString obs;
    QString recap;
    QString mort;
    QString outdir;
    QString datadir;
} RunConfigItem;
typedef QList<RunConfigItem> RunConfigVector;



#endif
