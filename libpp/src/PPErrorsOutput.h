/*
 *
 */

#ifndef PPErrorsOutput_h
#define PPErrorsOutput_h

#include <QString>

#include "PPFileOutput.h"

class PPErrors;

class PPErrorsOutput : public PPFileOutput
{
public:
    QString getFileName (const QString prefix) const;
    void writeHeader ();
    void write (const PPErrors& errors);
    bool active() const;
};

#endif
