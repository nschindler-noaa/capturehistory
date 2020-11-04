/*
 * Settings.cpp
 */

#include <string>
#include <fstream>
#include <algorithm>

#include <QStringList>
#include <QDomDocument>

#include "Settings.h"
#include "StringManip.h"

using namespace std;

using namespace cbr; //::toString;

ParamDef ParamDef::null = ParamDef();

bool ParamDef::isNull() const
{
    return this == &ParamDef::null;
}

struct paramdef_eql : public unary_function<const ParamDef&, bool>
{

    paramdef_eql(const string & s) : key(s)
    {
    }

    bool operator() (const ParamDef & def) 
    {
        return key.compare(def.getKey()) == 0;
    }
    string key;
};

/*
 *
 */
Settings::Settings() : saveSettings(false), readFromFile(false), defaultMode(false)
{
}

Settings::Settings(const string& fn) : saveSettings(true), readFromFile(false), settingsFile(fn) 
{
    readSettings(fn);
}

Settings::Settings(const Settings& s)
{
    settingsFile = s.settingsFile;
    saveSettings = s.saveSettings;
    keyNames = s.keyNames;
    params = s.params;
    readFromFile = s.readFromFile;
}

Settings::~Settings()
{
    if (saveSettings && !settingsFile.empty())
        writeSettings(settingsFile);
}

/*
 * Clear all defs that have not been configured as final.
 */
void Settings::clear()
{
    for (ParamList::iterator it = params.begin(); it != params.end();) {
        if (!it->isFinal())
            it = params.erase(it);
        else
            ++it;
    }
}

/*
 * Clear all defs, including ones configured as final.
 */
void Settings::clearAll()
{
    params.clear();
}

/*
 * Delete all parameter definitions for the given key.
 */
void Settings::clearDefs(const std::string& key)
{
    ParamList::iterator it;
    it = find_if(params.begin(), params.end(), paramdef_eql(key));
    while (it != params.end())
    {
        params.erase(it);
        it = find_if(params.begin(), params.end(), paramdef_eql(key));
    }
}

/*
 *
 */
void Settings::clearDefs(int key)
{
    clearDefs(getKeyName(key));
}

/*
 *
 */
void Settings::addKeyName(const string& key, int num)
{
    keyNames[ num ] = key;
}

/*
 * 
 */
const string& Settings::getKeyName(int num)
{
    const string& key = keyNames[ num ];
    if (key.empty())
    {
        stringstream ss;
        ss << "Un-recognized key: " << num;
        lastError = ss.str();
    }
    return key;
}

/*
 *
 */
int Settings::getKeyNum(const string& keyName)
{
    int keyNum = -1;
    for (map<int, string>::const_iterator it = keyNames.begin(); it != keyNames.end(); ++it)
    {
        keyNum = (*it).first;
        const string& value = (*it).second;
        if (!value.compare(keyName))
            return keyNum;

    }
    return keyNum;
}

/*
 * Add a new parameter definition. The definition will only be
 * added if no other definition currently exists for the given key.
 * If final is true, this def will not be editable, and will not
 * be deleted when calling clear. It will be deleted if calling
 * clearAll.
 */
void Settings::addParamDef(const string& key, const string& value, bool final)
{
    bool defaultMode = getDefaultMode();
    if (!defaultMode || !isSet(key))
        params.push_back(ParamDef(key, value, final));
}

/*
 *
 */
void Settings::addParamDef(int num, const string& value, bool final)
{
    const string& key = getKeyName(num);
    addParamDef(key, value, final);
}

void Settings::addParamDef(const ParamDef& def) 
{
    params.push_back(def);
}

/*
 *
 */
ParamDef& Settings::getDef(const string& key, int skip) 
{
    size_t numParams = params.size();
    size_t i = 0;
    while (i < numParams) 
    {
        ParamDef& def = params.at(i);
        string defkey = def.getKey();
        if (defkey.compare(key) == 0)//key.compare(def.getKey()) == 0)
        {
            if (skip == 0)
                break;
            --skip;
        }
        ++i;
    }
    if (i < numParams)
        return params.at(i);
    else
        return ParamDef::null;
}

bool Settings::isSet(const string& key) 
{
    string value = getValue(key);
    if (value.empty())
        return false;
    return true;
    ParamList::iterator it;
    it = find_if(params.begin(), params.end(), paramdef_eql(key));
    return it != params.end();
}

bool Settings::isSet(int key) 
{
    return isSet(getKeyName(key));
}

bool Settings::isSet(const string& key, const string& target)
{
    int count = 0;
    string value = getValue(key, count);
    while (!value.empty())
    {
        if (value.compare(target) == 0)
            return true;
        value = getValue(key, ++count);
    }

    return false;
}

bool Settings::isSet(int key, const string& value)
{
    return isSet(getKeyName(key), value);
}

/*
 * Set the value of an exisiting parameter def, or if no parameter def
 * exists for the key, add a new parameter def. This value will not
 * be set if a parameter def exists and defined as final.
 */
void Settings::setValue(const string& key, const string& value, int skip) 
{
    bool defaultMode = getDefaultMode();
    if (!defaultMode || !isSet(key)) 
    {
        ParamDef& def = getDef(key, skip);
        if (!def.isNull() && !def.isFinal())
            def.setValue(value);
        else
            addParamDef(key, value);

    }
}

/*
 *
 */
void Settings::setValue(const string& key, int value, int skip)
{
    setValue(key, cbr::toString<int>(value), skip);
}

/*
 *
 */
void Settings::setValue(int num, const string& value, int skip) 
{
    setValue(getKeyName(num), value, skip);

}

/*
 * 
 */
void Settings::setValue(int num, double value, int skip)
{
    setValue(getKeyName(num), toString<double>(value), skip);
}

/*
 * 
 */
void Settings::setValue(int num, int value, int skip)
{
    setValue(getKeyName(num), toString<int>(value), skip);
}

/*
 * 
 */
void Settings::merge(const Settings& settings, bool overwrite) 
{
    const ParamList& newParams = settings.params;
    ParamList::const_iterator it;
    if (overwrite)
    {
        for (it = newParams.begin(); it != newParams.end(); ++it)
        {
            const ParamDef& def = *it;
            if (isSet(def.getKey()))
                clearDefs(def.getKey());
        }
    }

    for (it = newParams.begin(); it != newParams.end(); ++it)
    {
        addParamDef(*it);
    }
}

/*
 *
 */
string Settings::getValue(const string& key, int skip) {
    ParamDef& def = getDef(key, skip);
    if (!def.isNull())
        return def.getValue();
    else
        return string();
}

/*
 *
 */
int Settings::getIntValue(int num, int skip) {
    const string& key = getKeyName(num);
    return getIntValue(key, skip);
}

/*
 *
 */
int Settings::getIntValue(const string& key, int skip) {
    string value = getValue(key, skip);
    if (value.empty())
        return 0;
    else
        return cbr::fromString<int> (value);
}

/*
 *
 */
double Settings::getDoubleValue(int num, int skip) {
    const string& key = getKeyName(num);
    return getDoubleValue(key, skip);
}

/*
 *
 */
double Settings::getDoubleValue(const string& key, int skip) {
    string value = getValue(key, skip);
    if (value.empty())
        return 0;
    else
        return cbr::fromString<double> (value);
}

/*
 *
 */
string Settings::getValue(int num, int skip) {
    const string& key = getKeyName(num);
    return getValue(key, skip);
}

/*
 *
 */
bool Settings::isChecked(const string& key) {
    if (!key.empty()) {
        string value = getValue(key);
        if (value.compare("1") == 0)
            return true;
    }
    return false;
}

/*
 *
 */
bool Settings::isChecked(int num) {
    return isChecked(getKeyName(num));
}

/*
 *
 */
vector<string> Settings::getValues(const string& key) {
    int count = 0;
    vector<string> list;
    string value = getValue(key, count);
    while (!value.empty()) {
        list.push_back(value);
        value = getValue(key, ++count);
    }

    return list;
}

/*
 *
 */
vector<string> Settings::getValues(int num) {
    return getValues(getKeyName(num));
}

void Settings::addChecked(const string& key, bool rhs, bool final) {
    if (rhs)
        addParamDef(key, "1", final);
    else
        addParamDef(key, "0", final);
}

void Settings::addChecked(int key, bool rhs, bool final) {
    addChecked(getKeyName(key), rhs, final);
}

/*
 *
 */
void Settings::setChecked(const string& key, bool rhs) {
    if (rhs)
        setValue(key, "1");
    else
        setValue(key, "0");
}

void Settings::writeSettings(const string& settingsFile) {

    string outFile = settingsFile;
    if (outFile.empty())
        outFile = lastSettingsFile;
    if (!outFile.empty()) {

        if (writeXml(outFile)) {
            lastSettingsFile = outFile;
        }
    }
}

/*
 *
 */
void Settings::setChecked(int key, bool rhs) {
    setChecked(getKeyName(key), rhs);
}

bool Settings::readSettings(const string& settingsFile) {
    // attempt to read input as xml
    if (readFromXml(settingsFile)) {
        lastSettingsFile = settingsFile;
    }
    else {
        // now attempt to read old style (key: value)
        ifstream in(settingsFile.c_str());

        if (in.is_open()) {
            in >> *this;
            readFromFile = true;
            lastSettingsFile = settingsFile;
        }
    }

    return true;
}

bool Settings::writeXml(const string& outFile) {
    ofstream ofs;
    ofs.open(outFile.c_str());
    if (!ofs.is_open())
        return false;

    ofs << serialize();
    return true;
}

bool Settings::readFromXml(const std::string& inFile) {
    string xml;
    string line;
    ifstream in(inFile.c_str());
    while (std::getline(in, line))
        xml += line + "\n";
    return deserialize(xml);
}

string Settings::serialize() const {
    QDomDocument doc;
    doc.setContent(QString("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"), false);
    QDomElement root = doc.createElement("pitpro");
    doc.appendChild(root);

    // create the xml doc
    for (size_t i = 0; i < params.size(); i++) {
        const ParamDef& def = params[ i ];
        if (!def.isFinal()) {
            QDomElement elem = doc.createElement(def.getKey().c_str());
            QDomText textNode = doc.createTextNode(def.getValue().c_str());
            elem.appendChild(textNode);
            root.appendChild(elem);
        }
    }

    string xml = doc.toString().toStdString();
    return xml;
}

bool Settings::deserialize(const string& xml) {
    QDomDocument doc;

    QString errorMessage;
    int errorLine;
    int errorCol;
    bool ok = doc.setContent(QString(xml.c_str()), true, &errorMessage, &errorLine, &errorCol);
    if (!ok)
        return false;
    QDomElement docElem = doc.documentElement();
    QString docName = docElem.nodeName();
    if (docName.compare("pitpro") != 0)
        return false;

    QDomNode n = doc.documentElement().firstChild();
    while (!n.isNull()) {
        if (n.isElement()) {
            QDomElement e = n.toElement();
            string key = e.tagName().toStdString();//e.tagName().toLatin1().toStdString();
            string value = e.text().toStdString();//.toLatin1().toStdString();
            if (!key.empty() && !value.empty())
                addParamDef(key, value);
        }
        n = n.nextSibling();
    }

    return true;
}

/*
 *
 */
struct param_sort : public binary_function<const ParamDef&, const ParamDef&, bool> {

    bool operator() (const ParamDef& p1, const ParamDef & p2) {
        return p1.getKey().compare(p2.getKey()) == 0;
    }
};

void Settings::sort() {
    std::sort(params.begin(), params.end(), param_sort());
}

ostream& operator<<(ostream& os, const Settings& settings) {
    size_t numParams = settings.params.size();
    for (size_t i = 0; i < numParams; i++) {
        const ParamDef& def = settings.params[ i ];
        if (!def.isFinal())
            os << def.getKey() << ": " << def.getValue() << endl;
    }
    return os;
}

/*
 *
 */
istream& operator>>(istream& is, Settings& settings) {
    string instring;

    while (getline(is, instring)) {
        int pos = instring.find(':');
        if (pos != -1) {
            string key(instring, 0, pos);
            string value(instring, pos + 1, instring.length() - pos - 1);
            if (!key.empty() && !value.empty())
                settings.addParamDef(key, value);
        }
    }

    return is;
}
