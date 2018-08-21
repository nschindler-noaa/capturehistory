/*
*/

#include <string>

#include <QDomDocument>

#include <Settings.h>

#include <gtest/gtest.h>

#include "SettingsTest.h"

using std::string;

SettingsTest::SettingsTest()
{
	xml_ = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>" \
		"<pitpro>" \
  		"<groupRuns>0</groupRuns>" \
  		"<runsTable>11H04snb</runsTable>" \
  		"<runsTable>11H04snb.tag</runsTable>" \
  		"<runsTable>11H04snb.obs</runsTable>"  \
  		"<runsTable>11H04.rcp</runsTable>" \
        "<runsTable>04.mrt</runsTable>" \
        "<filterByFileType>1</filterByFileType>" \
        "<dataDir>C:/Documents and Settings/china/My Documents/Projects/PitPro/roster/data</dataDir>" \
        "<outputDir>C:/Documents and Settings/china/My Documents/Projects/PitPro/roster/output</outputDir>" \
        "<outPrefix>11H9697</outPrefix>" \
        "<surphFileSwitch>1</surphFileSwitch>" \
        "<errorsFileSwitch>1</errorsFileSwitch>" \
        "<ddFileSwitch>0</ddFileSwitch>" \
        "<ttFileSwitch>0</ttFileSwitch>" \
        "<sequenceFileSwitch>0</sequenceFileSwitch>" \
        "<lengthCovSwitch>0</lengthCovSwitch>" \
        "<outputFormat>ROSTER</outputFormat>" \
        "<siteRel>0</siteRel>" \
        "<histField>gr</histField>" \
        "<histField>go</histField>" \
        "<histField>lm</histField>" \
        "<histField>mc</histField>" \
        "<histField>jd</histField>" \
        "<histField>bv</histField>" \
        "<adultField>bv</adultField>" \
        "<adultField>mc</adultField>" \
        "<adultField>ih</adultField>" \
   		"<adultField>gr</adultField>" \
		"<numMainSites>10</numMainSites>" \
		"<species>1</species>" \
		"<run>1</run>" \
		"<rearType>H</rearType>" \
		"<adultModeSwitch>1</adultModeSwitch>" \
		"<juvenileCutoffSwitch>0</juvenileCutoffSwitch>" \
		"<migrationYearSwitch>1</migrationYearSwitch>" \
		"<juvenileCutoffDate></juvenileCutoffDate>" \
		"<migrationYear>2004</migrationYear>" \
		"<removeJacks>1</removeJacks>" \
		"<combineJacks>0</combineJacks>" \
		"<lastRouteSwitch>1</lastRouteSwitch>" \
		"<anyRouteSwitch>0</anyRouteSwitch>" \
		"<removerResidualizers>1</removerResidualizers>" \
		"<resCutoffSwitch>0</resCutoffSwitch>" \
		"<resCutoffDate></resCutoffDate>" \
		"<transSite>gr</transSite>" \
		"<transSite>go</transSite>" \
		"<altSitesConfig></altSitesConfig>" \
		"<sitesConfigSwitch>1</sitesConfigSwitch>" \
		"<removalTrumpsSwitch>1</removalTrumpsSwitch>" \
		"<lastOutcomeSwitch>0</lastOutcomeSwitch>" \
		"<ignoreReRecap>1</ignoreReRecap>" \
		"<tagCheck>1</tagCheck>" \
		"<singleCoilSwitch>0</singleCoilSwitch>" \
		"<warnings>0</warnings>" \
		"<sampTransSwitch>0</sampTransSwitch>" \
  		"</pitpro>";
}

TEST_F(SettingsTest, DeSerialize) 
{
	Settings settings;

	string xml;
	bool ok;

	xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><jnk></jnk>";
	ok = settings.deserialize(xml);
	ASSERT_FALSE(ok);

	settings.clearAll();
	xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><pitpro></pitpro>";
	ok = settings.deserialize(xml);
	ASSERT_TRUE(ok);

	settings.clearAll();
	xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><pitpro>" \
		"<warnings>0</warnings>" \
		"</pitpro>";
	ok = settings.deserialize(xml);
	ASSERT_EQ(false, settings.isChecked("warnings"));

	settings.clearAll();
	xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><pitpro>" \
		"<warnings></warnings>" \
		"</pitpro>";
	ok = settings.deserialize(xml);
	ASSERT_EQ(false, settings.isChecked("warnings"));

	settings.clearAll();
	xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><pitpro>" \
		"<warnings>1</warnings>" \
		"</pitpro>";
	ok = settings.deserialize(xml);
	ASSERT_EQ(true, settings.isChecked("warnings"));

	settings.clearAll();
	ASSERT_EQ(false, settings.isChecked("warnings"));
}    


TEST_F(SettingsTest, Serialize) 
{
	Settings settings;
	string xml;
	bool ok;

	settings.setChecked("warnings", true);
	xml = settings.serialize();
	ASSERT_FALSE(xml.empty());

	settings.clearAll();
	ASSERT_EQ(false, settings.isChecked("warnings"));

	ok = settings.deserialize(xml);
	ASSERT_TRUE(ok);

	ASSERT_EQ(true, settings.isChecked("warnings"));

}       
