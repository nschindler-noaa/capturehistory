/*
*/

#include <fstream>
#include <algorithm>

#include <QTextDocument>
#include <QDomElement>

#include <Site.h>
#include <StringManip.h>

#include "PPRunInfo.h"

#include "PitProSettings.h"
#include "PPVersion.h"
#include "SitesMask.h"

using namespace std;
using namespace cbr;


PPRunInfo::PPRunInfo() 
{
}

PPRunInfo::~PPRunInfo() {
}

PPRunInfo& PPRunInfo::instance() {
	static PPRunInfo runInfo;
	return runInfo;
}

string PPRunInfo::protect(const string& str)
{
	QString s = str.c_str();

    s.replace("&", "&amp;");
    s.replace(">", "&gt;");
    s.replace("<", "&lt;");
    s.replace("\"", "&quot;");
    s.replace("\'", "&apos;");

    return s.toStdString();
//    return s.latin1();
}

string PPRunInfo::unProtect(const string& str)
{
	QString s = str.c_str();

    s.replace("&amp;", "&");
    s.replace("&gt;", ">");
    s.replace("&lt;", "<");
    s.replace("&quot;", "\"");
    s.replace("&apos;", "'");

    return s.toStdString();
//    return s.latin1();
}


/*
* This should really be done by building a dom and the writing it.
*/
string PPRunInfo::serialize( const std::string& prefix, const RunConfigVector& runConfigVector ) {
	PitProSettings& settings = PitProSettings::getInstance();
	stringstream ss;

	ss << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
	ss << "<pitpro_run_info>" << endl;
	ss << "<version>" << PPVersion::versionString() << "</version>" << endl;
	ss << "<prefix>" << prefix << "</prefix>" << endl;
	ss << "<datadir>" << protect(settings.getValue( PitProSettings::DataDir )) << "</datadir>" << endl;
	ss << "<outdir>" << protect(settings.getValue( PitProSettings::OutputDir)) << "</outdir>" << endl;
	if ( !settings.isChecked( PitProSettings::GroupRuns ) )
		ss << "<runs combined=\"false\">";
	else {
		ss << "<runs combined=\"true\">";
	}
	for ( RunConfigVector::const_iterator it = runConfigVector.begin(); it != runConfigVector.end(); ++it ) {
		const RunConfigItem& run = *it;
		ss << "<run>" << endl;
		ss << "<name>" << run.name << "</name>" << endl;
		ss << "<obs>" << run.obs << "</obs>" << endl;
		ss << "<tag>" << run.tag << "</tag>" << endl;
		ss << "<recap>" << run.recap << "</recap>" << endl;
		ss << "<mort>" << run.mort << "</mort>" << endl;
		ss << "</run>" << endl;
	}
	ss << "</runs>" << endl;

	int numMainSites = settings.getIntValue(PitProSettings::NumMainSites);
	ss << "<numMainSites>" << numMainSites << "</numMainSites>" << endl;
	StringVector juvenileSites = settings.getJuvenileSites();
	for (StringVector::const_iterator it = juvenileSites.begin(); it != juvenileSites.end(); ++it) {
		ss << "<juvenileSite>" << *it << "</juvenileSite>" << endl;
	}
	StringVector adultSites = settings.getAdultSites();
	for (StringVector::const_iterator it2 = adultSites.begin(); it2 != adultSites.end(); ++it2) {
		ss << "<adultSite>" << *it2 << "</adultSite>" << endl;
	}
	ss << "<outputFormat>" << settings.getValue(PitProSettings::OutputFormat) << "</outputFormat>" << endl;
 
	ss << "<siteRel>" << (settings.isChecked(PitProSettings::SiteRel) ? "true" : "false") << "</siteRel>" << endl;

	ss << "<output>" << endl;
	if ( settings.isChecked( PitProSettings::SurphFileSwitch ) ) 
		ss << "<type>capthists</type>" << endl;
	if ( settings.isChecked( PitProSettings::ErrorsFileSwitch ) ) 
		ss << "<type>errors</type>" << endl;
	if ( settings.isChecked( PitProSettings::DdFileSwitch ) ) 
		ss << "<type>detectiondates</type>" << endl;
	if ( settings.isChecked( PitProSettings::TtFileSwitch ) ) 
		ss << "<type>traveltimes</type>" << endl;
	if ( settings.isChecked( PitProSettings::SequenceFileSwitch ) ) 
		ss << "<type>sequences</type>" << endl;
	ss << "</output>" << endl;

	ss << "</pitpro_run_info>" << endl;

	ss << ends;

	string xml = ss.str();
	return xml;
}

bool PPRunInfo::save( const string& prefix, const string& xml ) {
	PitProSettings& settings = PitProSettings::getInstance();
	string suffix = settings.getValue( PitProSettings::ConfigSuffix );
	string outFile = settings.getOutFilePath( prefix + "." + suffix );

	ofstream ofs;
	ofs.open( outFile.c_str() );
	if ( !ofs.is_open() ) 
		return false;

	ofs << xml;

	return true;
}

string PPRunInfo::getConfigFileName( const std::string& prefix )
{
	PitProSettings& settings = PitProSettings::getInstance();
	string suffix = settings.getValue( PitProSettings::ConfigSuffix );
	string inFile = settings.getOutFilePath( prefix + "." + suffix );
	return inFile;
}

bool PPRunInfo::load( const std::string& inFile )
{
	return parse( read( inFile ) );
}

string PPRunInfo::read( const std::string& inFile )
{
	string xml;
	string line;
	ifstream in(getConfigFileName(inFile).c_str());
	while(std::getline(in,line))
		xml += line;		
	return xml;
}

/*
 * Parse the xml doc represented int the <xml> string parameter.
 * Returns true if the document is valid xml and the top level element
 * is <pitpro>
 */
bool PPRunInfo::parse( const std::string& xml )
{
	doc.clear();

	// this is to fix old cfg files that were created with bare ampersands
	QString escapedXml = xml.c_str();
	escapedXml.replace("&amp;", "&"); // in case the file already has the &s replaced
	escapedXml.replace("&", "&amp;");

	bool ok = doc.setContent(escapedXml);
	if (!ok)
		return false;
	QDomElement docElem = doc.documentElement();
	QString docName = docElem.nodeName();
	if (docName.compare("pitpro_run_info") != 0)
		return false;
	return true;
}

bool PPRunInfo::isCombined() {
	QDomNodeList nodeList = doc.elementsByTagName("runs");

	if (nodeList.count() > 0) {
		QDomNode node = nodeList.item(0);
		if (node.hasAttributes()) {
			QDomNamedNodeMap attributes = node.attributes();
			QDomNode combined = attributes.namedItem("combined");
			if (combined.isAttr()) {
				QDomAttr attr = node.toAttr();
				return attr.value().compare("true") == 0;
			}
		}
	}

	return false;
}

RunConfigVector PPRunInfo::getRunConfig() const {

	RunConfigVector runConfig;

	QDomNodeList runNodeList = doc.elementsByTagName( "run" );
	for (int i = 0; i < runNodeList.size(); ++i) {
		RunConfigItem runItem;
		QDomNode runNode = runNodeList.at(i);
		QDomNodeList configNodeList = runNode.childNodes();

		for (int j = 0; j <configNodeList.size(); ++j ) {
			QDomNode configNode = configNodeList.at( j );
			if (configNode.isElement()) {
				QString nodeName = configNode.nodeName();
				string value = configNode.toElement().text().toStdString();

				if ( !nodeName.compare( "name" ) )
					runItem.name = value;
				else if ( !nodeName.compare( "obs" ) )
					runItem.obs = value;
				else if ( !nodeName.compare( "tag" ) )
					runItem.tag = value;
				else if ( !nodeName.compare( "mort" ) )
					runItem.mort = value;
				else if ( !nodeName.compare( "recap" ) )
					runItem.recap = value;
			}
		}

		runItem.outdir = getOutputDir();
		runItem.datadir = getDataDir();
		
		runConfig.push_back( runItem );

	}


#if 0
	if (!doc)
		return runConfig;

	DOMNodeList* runNodeList = doc->getElementsByTagName( XMLString::transcode( "run" ) );
	for (unsigned int i = 0; i < runNodeList->getLength(); ++i ) {
		RunConfigItem runItem;
		DOMNode* runNode = runNodeList->item( i );
		DOMNodeList* configNodeList = runNode->getChildNodes();
		for (unsigned int j = 0; j < configNodeList->getLength(); ++j ) {
			DOMNode* configNode = configNodeList->item( j );
			string nodeName = XMLString::transcode( configNode->getNodeName()  );
			if ( !nodeName.compare( "name" ) )
				runItem.name = XMLString::transcode( configNode->getTextContent() );
			else if ( !nodeName.compare( "obs" ) )
				runItem.obs = XMLString::transcode( configNode->getTextContent() );
			else if ( !nodeName.compare( "tag" ) )
				runItem.tag = XMLString::transcode( configNode->getTextContent() );
			else if ( !nodeName.compare( "mort" ) )
				runItem.mort = XMLString::transcode( configNode->getTextContent() );
			else if ( !nodeName.compare( "recap" ) )
				runItem.recap = XMLString::transcode( configNode->getTextContent() );
		}

		DOMNodeList* nodeList = doc->getElementsByTagName( XMLString::transcode( "outdir" ) );
		if (nodeList->getLength() > 0) 
			runItem.outdir = XMLString::transcode( nodeList->item(0)->getTextContent() );
		nodeList = doc->getElementsByTagName( XMLString::transcode( "datadir" ) );
		if (nodeList->getLength() > 0) 
			runItem.datadir = XMLString::transcode( nodeList->item(0)->getTextContent() );

		//files.push_back( XMLString::transcode( node->getTextContent() ) );
		runConfig.push_back( runItem );
	}
   
#endif

	return runConfig;

}

StringVector PPRunInfo::getRunNames() const {
	return getValues( "name" );
}

StringVector PPRunInfo::getObsFiles() const {
	return getValues( "obs" );
}

StringVector PPRunInfo::getTagFiles() const {
	return getValues( "tag" );
}

StringVector PPRunInfo::getMortFiles() const {
	return getValues( "mort" );
}

StringVector PPRunInfo::getRecapFiles() const {
	return getValues( "recap" );
}

string PPRunInfo::getDataDir() const {
    return unProtect(getValue("datadir"));
}

string PPRunInfo::getOutputDir() const {
    return unProtect(getValue("outdir"));
}

int PPRunInfo::getNumMainSites() const {
    string numMainSites = getValue("numMainSites");
    return fromString<int>(numMainSites);
}

StringVector PPRunInfo::getJuvenileSites() const {
    return getValues("juvenileSite");
}
StringVector PPRunInfo::getAdultSites() const {
    return getValues("adultSite");
}

StringVector PPRunInfo::getAllSites() const {
	StringVector allSites = getJuvenileSites();
	StringVector adultSites = getAdultSites();
	allSites.insert(allSites.end(), adultSites.begin(), adultSites.end());
	return allSites;
}

std::string PPRunInfo::getOutputFormat() const {
    return getValue("outputFormat");
}

bool PPRunInfo::isSiteRel() const {
    return getValue("outputFormat").compare("true") == 0;
}

string PPRunInfo::getValue( const char* tagName ) const {
    string value;

	QDomNodeList nodeList = doc.elementsByTagName(tagName);

	if (nodeList.count() > 0) {
		QDomNode node = nodeList.item(0);
		if (node.isElement()) {
			QDomElement e = node.toElement();
			QString qval = e.text();
			value = qval.toStdString();
		}
	}

    return value;
}

StringVector PPRunInfo::getValues( const char* tagName ) const {
	StringVector values;

	QDomNodeList nodeList = doc.elementsByTagName(tagName);

	for (int i = 0; i < nodeList.size(); ++i) {
		QDomNode node = nodeList.item(i);
		if (node.isElement()) {
			QDomElement e = node.toElement();
			QString qval = e.text();
			string value = qval.toStdString();
			if ( find(values.begin(), values.end(), value) == values.end() )
				values.push_back( value );

		}
	}

	return values;
}
