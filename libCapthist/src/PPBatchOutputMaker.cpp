#include "PPBatchOutputMaker.h"




void PPBatchOutputMaker::write (const QString& msg, OutputType type)
{
    PitProSettings& settings = PitProSettings::getInstance();
    if (type != PPOutputMaker::Warning || settings.isChecked(PitProSettings::Warnings))
        std::cerr << ppFormat(msg, type);
}
