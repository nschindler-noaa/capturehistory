#ifndef PPBatch_h
#define PPBatch_h


class PPBatchOutputMaker;
class PPGetOpts;

class PPBatch
{
public:
	static int run(PPGetOpts& opts, PPBatchOutputMaker& out);

private:
	static int runBatch(PPGetOpts& opts, PPBatchOutputMaker& out);

	static int batch(PPBatchOutputMaker& out);
	static int batch1(PPBatchOutputMaker& out);

	static int dsplit(PPBatchOutputMaker& out);

	static int usage(PPGetOpts& opts);
	static int newRcFile(PPBatchOutputMaker& out);

};

#endif





