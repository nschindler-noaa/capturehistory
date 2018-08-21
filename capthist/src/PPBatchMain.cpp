/*
 * PPBatchMain.cpp
 *
 */


#include <PPBatchOutputMaker.h>
#include <PPGetOpts.h>
#include <PPBatch.h>

int main(int argc, char **argv)
{
    PPBatchOutputMaker& out = PPBatchOutputMaker::getInstance();

    // read settings
    PPGetOpts opts;
    opts.get(argc, argv, out);

    return PPBatch::run(opts, out);
}





