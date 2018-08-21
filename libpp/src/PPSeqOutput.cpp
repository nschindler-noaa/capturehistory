/*
*
*/

#include <sstream>

#include <ObsSequence.h>
#include <SitesMask.h>

#include "PPSeqOutput.h"
#include "PitProSettings.h"

using std::string;
using std::stringstream;
using std::endl;


string PPSeqOutput::getFileName (const string& prefix) const
{
	PitProSettings& settings = PitProSettings::getInstance();
	string suffix = settings.getValue (PitProSettings::SeqSuffix);
	return settings.getOutFilePath (prefix + "." + suffix);
}

void PPSeqOutput::writeHeader()
{
	if (!ofs.is_open())
		return;

}

void PPSeqOutput::write (ObsSequence& seq, const string& type)
{
	if (!ofs.is_open())
		return;
	else if (seq.numRecs() == 0 )
		return;


	string oos = seq.isOutOfSequence() ? "1" : "0";
	ofs << type << " " << oos << " " << seq << endl;
}

bool
PPSeqOutput::active() const
{
	PitProSettings& settings = PitProSettings::getInstance();
	return settings.isChecked (PitProSettings::SequenceFileSwitch);
}
