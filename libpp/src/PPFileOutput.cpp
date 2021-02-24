/*
 *
 */

#include <cstdio>


#include "PPFileOutput.h"
#include "portability.h"

#include <QStringList>

using std::remove;

PPFileOutput::~PPFileOutput()
{
    close();
}

// delete any existing output files for this prefix

void PPFileOutput::close()
{
    if (ofs.is_open())
        ofs.close();
}


/*
* Open the files stream. If the stream is open, close it first.
* The delete the file if it exists already. Then check the subclasses active()
* method to determine if the stream should actually be opened or not.
*/
void PPFileOutput::setPrefix (const QString p)
{
    prefix = p;
    closeAndDelete();

    if (active())
    {
        QString fileName = getFileName (prefix);
        ofs.open (fileName.toStdString().c_str());
    }
}

/*
* Delete the associated file
*/
void PPFileOutput::closeAndDelete ()
{
    if (ofs.is_open())
        ofs.close();
    QString fileName = getFileName (prefix);
    if (access( fileName.toStdString().c_str(), 0 ) != -1 )
        remove( fileName.toStdString().c_str() );
}
