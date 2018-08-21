/*
 *
 */

#include <string>
#include <cstdio>


#include "PPFileOutput.h"
#include "portability.h"

using std::string;
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
void PPFileOutput::setPrefix (const	string& p)
{
	prefix = p;
	closeAndDelete();

	if (active())
	{
		string fileName = getFileName (prefix);
		ofs.open (fileName.c_str());
	}
}

/* 
* Delete the associated file
*/
void PPFileOutput::closeAndDelete ()
{
	if (ofs.is_open())
		ofs.close();
	string fileName = getFileName (prefix);
	if (access( fileName.c_str(), 0 ) != -1 )
		remove( fileName.c_str() );
}
