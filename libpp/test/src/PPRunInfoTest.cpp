/*
*/

#include <string>

#include <PPRunInfo.h>

#include <gtest/gtest.h>

#include "PPRunInfoTest.h"

using std::string;

PPRunInfoTest::PPRunInfoTest()
{
	xml_ = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>" \
		"<pitpro_run_info>" \
		"<version>4.1</version>" \
		"<prefix>WebDataCap2006</prefix>" \
		"<datadir>C:/Documents and Settings/peterc/My Documents/Grand Ronde M&E/Project 473/Data/MY2006/Survival Data/WebSystem</datadir>" \
		"<outdir>C:/Documents and Settings/peterc/My Documents/Grand Ronde M&amp;E/Project 473/Data/MY2006/Survival Data/WebSystem</outdir>" \
		"<runs combined=\"false\">" \
		"<run>" \
		"<name>WebDataCap2006</name>" \
		"<obs>capt06.obs</obs>" \
		"<tag>capt06.tag</tag>" \
		"<recap>capt06.rcp</recap>" \
		"<mort>capt06.mrt</mort>" \
		"</run>" \
		"<run>" \
		"<name>WebDataCap2007</name>" \
		"<obs>capt07.obs</obs>" \
		"<tag>capt07.tag</tag>" \
		"<recap>capt07.rcp</recap>" \
		"<mort>capt07.mrt</mort>" \
		"</run>" \
		"</runs>" \
		"<output>" \
		"<type>capthists</type>" \
		"<type>errors</type>" \
		"<type>detectiondates</type>" \
		"</output>" \
		"</pitpro_run_info>";
}


TEST_F(PPRunInfoTest, CanParse) {

	PPRunInfo &info = PPRunInfo::instance();

	string xml = "";
	ASSERT_FALSE(info.parse(xml));

	xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>";
	ASSERT_FALSE(info.parse(xml));

	xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><badelem></badelem>";
	ASSERT_FALSE(info.parse(xml));

	xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><pitpro_run_info></pitpro_run_info>";
	ASSERT_TRUE(info.parse(xml));

	ASSERT_TRUE(info.parse(xml_));
}                                             

TEST_F(PPRunInfoTest, CanSerialize) {

	PPRunInfo &info = PPRunInfo::instance();

	RunConfigVector vec;

	RunConfigItem item1;
	item1.name = "run1";
	item1.tag = "tag1.tag";
	item1.obs = "obs1.obs";
	item1.recap = "recap1.rcp";
	item1.mort = "mort1.mrt";
	item1.outdir = "data";
	item1.datadir = "data";
	vec.push_back(item1);

	RunConfigItem item2;
	item2.name = "run2";
	item2.tag = "tag2.tag";
	item2.obs = "obs2.obs";
	item2.recap = "recap2.rcp";
	item2.mort = "mort2.mrt";
	item2.outdir = "data";
	item2.datadir = "data";
	vec.push_back(item2);

	string xml = info.serialize("test", vec);
	ASSERT_FALSE(xml.empty());

	ASSERT_TRUE(info.parse(xml));

	cbr::StringVector runNames = info.getRunNames();
	ASSERT_TRUE(runNames.size() == 2);
	if (runNames.size() == 2) {
		const string& runName1 = runNames.at(0);
		ASSERT_STREQ("run1", runName1.c_str());
		const string& runName2 = runNames.at(1);
		ASSERT_STREQ("run2", runName2.c_str());
	}

	ASSERT_STREQ("data", info.getDataDir().c_str());
	ASSERT_STREQ("output", info.getOutputDir().c_str());

	ASSERT_EQ(false, info.isCombined());
}   


TEST_F(PPRunInfoTest, CanGetRunConfig) {
	PPRunInfo &info = PPRunInfo::instance();
	info.parse(xml_);

	RunConfigVector runConfig = info.getRunConfig();
	ASSERT_EQ(2, runConfig.size());

	RunConfigItem item1 = runConfig.at(0);
	ASSERT_STREQ("WebDataCap2006", item1.name.c_str());
	ASSERT_STREQ("capt06.obs", item1.obs.c_str());
	ASSERT_STREQ("capt06.tag", item1.tag.c_str());
	ASSERT_STREQ("capt06.mrt", item1.mort.c_str());
	ASSERT_STREQ("capt06.rcp", item1.recap.c_str());

	char *datadir = "C:/Documents and Settings/peterc/My Documents/Grand Ronde M&E/Project 473/Data/MY2006/Survival Data/WebSystem";
	ASSERT_STREQ(datadir, item1.datadir.c_str());

	char *outdir = "C:/Documents and Settings/peterc/My Documents/Grand Ronde M&E/Project 473/Data/MY2006/Survival Data/WebSystem";
	ASSERT_STREQ(outdir, item1.outdir.c_str());

	RunConfigItem item2 = runConfig.at(1);
	ASSERT_STREQ("WebDataCap2007", item2.name.c_str());
	ASSERT_STREQ("capt07.obs", item2.obs.c_str());
	ASSERT_STREQ("capt07.tag", item2.tag.c_str());
	ASSERT_STREQ("capt07.mrt", item2.mort.c_str());
	ASSERT_STREQ("capt07.rcp", item2.recap.c_str());

	ASSERT_STREQ(datadir, item1.datadir.c_str());
	ASSERT_STREQ(datadir, item1.outdir.c_str());
 
}

TEST_F(PPRunInfoTest, Protect) {
	ASSERT_STREQ("&amp;&lt;&gt;&apos;&quot;", PPRunInfo::protect("&<>'\"").c_str());
	ASSERT_STREQ("&<>'\"", PPRunInfo::unProtect("&amp;&lt;&gt;&apos;&quot;").c_str());
}

