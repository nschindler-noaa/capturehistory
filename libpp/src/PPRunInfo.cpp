/*
*/

#include <fstream>
#include <algorithm>

#include <QStringList>
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

static QStringList returnList;
static QStringList values;
//static QString value;

PPRunInfo::PPRunInfo()
{
}

PPRunInfo::~PPRunInfo() {
}

PPRunInfo& PPRunInfo::instance() {
    static PPRunInfo runInfo;
    return runInfo;
}

QString PPRunInfo::protect(const QString& str)
{
    QString s = str;

    s.replace("&", "&amp;");
    s.replace(">", "&gt;");
    s.replace("<", "&lt;");
    s.replace("\"", "&quot;");
    s.replace("\'", "&apos;");

    return s;
}

QString PPRunInfo::unProtect(const QString& str)
{
    QString s = str;

    s.replace("&amp;", "&");
    s.replace("&gt;", ">");
    s.replace("&lt;", "<");
    s.replace("&quot;", "\"");
    s.replace("&apos;", "'");

    return s;
}


/*
* This should really be done by building a dom and the writing it.
*/
QString PPRunInfo::serialize(const QString &prefix, const RunConfigVector& runConfigVector ) {
    PitProSettings& settings = PitProSettings::getInstance();
    QString xml("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n");
    xml.append("<pitpro_run_info>\n");
    xml.append(QString("<version>%1</version>\n").arg(PPVersion::versionString()));
    xml.append(QString("<prefix>%1</prefix>\n").arg(prefix));
    xml.append(QString("<datadir>%1</datadir>\n").arg(protect(settings.getValue(PitProSettings::DataDir))));
    xml.append(QString("<outdir>%1</outdir>\n").arg(protect(settings.getValue(PitProSettings::OutputDir))));
    if (!settings.isChecked(PitProSettings::GroupRuns)) {
        xml.append("<runs combined=\"false\">");
    }
    else {
        xml.append("<runs combined=\"true\">");
    }
    for (int i = 0; i < runConfigVector.count(); i++) {
        const RunConfigItem run = runConfigVector.at(i);
        xml.append("<run>\n");
        xml.append(QString("<name>%1</name>\n").arg(run.name));
        xml.append(QString("<obs>%1</obs>\n").arg(run.obs));
        xml.append(QString("<tag>%1</tag>\n").arg(run.tag));
        xml.append(QString("<recap>%1</recap>\n").arg(run.recap));
        xml.append(QString("<mort>%1</mort>\n").arg(run.mort));
        xml.append("</run>\n");
    }
    xml.append("</runs>\n");

    int numMainSites = settings.getIntValue(PitProSettings::NumMainSites);
    xml.append(QString("<numMainSites>%1</numMainSites>\n").arg(QString::number(numMainSites)));
    QStringList sites = settings.getJuvenileSites();
    for (int i = 0; i < sites.count(); i++) {
        xml.append(QString("<juvenileSite>%1</juvenileSite>\n").arg(sites.at(i)));
    }
    sites = settings.getAdultSites();
    for (int i = 0; i < sites.count(); i++) {
        xml.append(QString("<adultSite>%1</adultSite>\n").arg(sites.at(i)));
    }

    xml.append(QString("<outputFormat>%1</outputFormat>\n").arg(settings.getValue(PitProSettings::OutputFormat)));

    xml.append(QString("<siteRel>%1</siteRel>\n").arg((settings.isChecked(PitProSettings::SiteRel) ? "true" : "false")));

    xml.append("<output>\n");
    if ( settings.isChecked( PitProSettings::SurphFileSwitch ) )
        xml.append("<type>capthists</type>\n");
    if ( settings.isChecked( PitProSettings::ErrorsFileSwitch ) )
        xml.append("<type>errors</type>\n");
    if ( settings.isChecked( PitProSettings::DdFileSwitch ) )
        xml.append("<type>detectiondates</type>\n");
    if ( settings.isChecked( PitProSettings::TtFileSwitch ) )
        xml.append("<type>traveltimes</type>\n");
    if ( settings.isChecked( PitProSettings::SequenceFileSwitch ) )
        xml.append("<type>sequences</type>\n");
    xml.append("</output>\n");

    xml.append("</pitpro_run_info>\n");
    return QString(xml);
/*    stringstream ss;

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

    ss << "</pitpro_run_info>" << endl;*/

//    ss << ends;

//    string xml = ss.str();
}

bool PPRunInfo::save(const QString &prefix, const QString &xml ) {
    PitProSettings& settings = PitProSettings::getInstance();
    QString suffix = settings.getValue( PitProSettings::ConfigSuffix );
    QString outFile = settings.getOutFilePath( prefix + "." + suffix );

    ofstream ofs;
    ofs.open(outFile.toStdString());
    if (!ofs.is_open())
        return false;

    ofs << xml.toStdString();

    return true;
}

QString PPRunInfo::getConfigFileName(const QString &prefix )
{
    PitProSettings& settings = PitProSettings::getInstance();
    QString suffix = settings.getValue( PitProSettings::ConfigSuffix );
    QString inFile = settings.getOutFilePath( prefix + "." + suffix );
    return inFile;
}

bool PPRunInfo::load(const QString &inFile )
{
    return parse( read( inFile ) );
}

QString PPRunInfo::read(const QString &inFile )
{
    string xml;
    string line;
    ifstream in(getConfigFileName(inFile).toStdString());
    while(std::getline(in,line))
        xml += line;
    return QString(xml.data());
}

/*
 * Parse the xml doc represented int the <xml> string parameter.
 * Returns true if the document is valid xml and the top level element
 * is <pitpro>
 */
bool PPRunInfo::parse(const QString &xml )
{
    doc.clear();

    // this is to fix old cfg files that were created with bare ampersands
    QString escapedXml(xml);
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
                QString nodeName(configNode.nodeName());
                QString value(configNode.toElement().text());

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

QStringList &PPRunInfo::getRunNames() const {
    returnList.clear();
    returnList.append (getValues("name"));
    return returnList;
}

QStringList &PPRunInfo::getObsFiles() const {
    returnList.clear();
    returnList.append (getValues("obs"));
    return returnList;
}

QStringList &PPRunInfo::getTagFiles() const {
    returnList.clear();
    returnList.append (getValues("tag"));
    return returnList;
}

QStringList &PPRunInfo::getMortFiles() const {
    returnList.clear();
    returnList.append (getValues("mort"));
    return returnList;
}

QStringList &PPRunInfo::getRecapFiles() const {
    returnList.clear();
    returnList.append (getValues("recap"));
    return returnList;
}

QString PPRunInfo::getDataDir() const {
    return unProtect(getValue("datadir"));
}

QString PPRunInfo::getOutputDir() const {
    return unProtect(getValue("outdir"));
}

int PPRunInfo::getNumMainSites() const {
    QString numMainSites = getValue("numMainSites");
    return numMainSites.toInt();//fromString<int>(numMainSites);
}

QStringList &PPRunInfo::getJuvenileSites() const {
    returnList.clear();
    returnList.append (getValues("juvenileSite"));
    return returnList;
}
QStringList &PPRunInfo::getAdultSites() const {
    returnList.clear();
    returnList.append (getValues("adultSite"));
    return returnList;
}

QStringList &PPRunInfo::getAllSites() const {
    allSites->clear();
    allSites->append(getJuvenileSites());
    allSites->append(getAdultSites());
//    StringVector adultSites = getAdultSites();
//    allSites.insert(allSites.end(), adultSites.begin(), adultSites.end());
    return (*allSites);
}

QString PPRunInfo::getOutputFormat() const {
    return getValue("outputFormat");
}

bool PPRunInfo::isSiteRel() const {
    return (getValue("outputFormat").compare("true") == 0);
}

QString PPRunInfo::getValue(const char* tagName) const {
    QString value;

    QDomNodeList nodeList = doc.elementsByTagName(tagName);

    if (nodeList.count() > 0) {
        QDomNode node = nodeList.item(0);
        if (node.isElement()) {
            QDomElement e = node.toElement();
            value = e.text();
//            QString qval = e.text();
//            value = qval.toStdString();
        }
    }

    return QString(value);//value;
}

QStringList &PPRunInfo::getValues(const char* tagName) const {
    if (!values.isEmpty())
        values.clear();

    QDomNodeList nodeList = doc.elementsByTagName(tagName);

    for (int i = 0; i < nodeList.size(); ++i) {
        QDomNode node = nodeList.item(i);
        if (node.isElement()) {
            QDomElement e = node.toElement();
           // QString qval = e.text();
            QString value(e.text());// = qval;
            if (!values.contains(value))
                values.append(value);
//            if ( find(values.begin(), values.end(), value) == values.end() )
//                values.push_back( value );

        }
    }

    return values;
}
