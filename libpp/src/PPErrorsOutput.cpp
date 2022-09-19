/*
*
*/

#include <sstream>


#include "PPErrorsOutput.h"
#include "PitProSettings.h"
#include "PPErrors.h"

using std::string;
using std::stringstream;
using std::endl;


string PPErrorsOutput::getFileName (const string& prefix) const
{
	PitProSettings& settings = PitProSettings::getInstance();
	string suffix = settings.getValue (PitProSettings::ErrorSuffix);
	return settings.getOutFilePath (prefix + "." + suffix);
}

void PPErrorsOutput::writeHeader()
{
    if (ofs.is_open()) {
        ofs << "#" << endl;
        ofs << "# Fields Key:" << endl;
        ofs << "#\t 1: PIT-tag id\n";
        for ( int i = 0; i < PPErrors::NumErrorTypes; ++i ) {
            ofs << "#\t";
            ofs.width(2);
            ofs << i + 2 << ": " << PPErrors::getText( i ) << endl;
        }
        ofs << "#" << endl << endl;
    }
}

void PPErrorsOutput::write (const PPErrors& errors)
{
	if (!ofs.is_open())
		return;

	ofs << errors << endl;
}

bool
PPErrorsOutput::active() const
{
	PitProSettings& settings = PitProSettings::getInstance();
	return settings.isChecked( PitProSettings::ErrorsFileSwitch ) &&
		settings.isChecked( PitProSettings::ErrorsCheck );
}
