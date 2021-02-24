/*
 * Settings.cpp
 */

#include <string>
#include <fstream>
#include <algorithm>

#include <QDomDocument>
#include <QStringList>

#include "Settings.h"
#include "StringManip.h"

using namespace std;

//using  cbr::toString;

ParamDef ParamDef::null = ParamDef();

bool ParamDef::isNull() const
{
    return this == &ParamDef::null;
}

struct paramdef_eql : public unary_function<const ParamDef&, bool>
{

    paramdef_eql(const QString s) : key(s)
    {
    }

    bool operator() (const ParamDef & def)
    {
        return key.compare(def.getKey()) == 0;
    }
    QString key;
};

/*
 *
 */
Settings::Settings() //: saveSettings(false), readFromFile(false), defaultMode(false)
{
    saveSettings = false;
    readFromFile = false;
    defaultMode = false;
}

Settings::Settings(const QString &fn) //: saveSettings(true), readFromFile(false), settingsFile(fn)
{
    saveSettings = true;
    readFromFile = false;
    settingsFile = fn;
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
    if (saveSettings && !settingsFile.isEmpty())
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
void Settings::clearDefs(const QString &key)
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
void Settings::addKeyName(const QString &key, int num)
{
    keyNames[num] = key;
}

/*
 *
 */
const QString &Settings::getKeyName(int num)
{
//    const QString key = keyNames[num];
    if (keyNames[num].isEmpty())
    {
        lastError = QString("Un-recognized key: %1").arg(QString::number(num));
//        stringstream ss;
//        ss << "Un-recognized key: " << num;
//        lastError = ss.str();
    }
    return keyNames[num];
}

/*
 *
 */
int Settings::getKeyNum(const QString &keyName)
{
    int keyNum = -1;
    for (QMap<int, QString>::const_iterator it = keyNames.begin(); it != keyNames.end(); ++it)
    {
        const QString value = it.value();// (*it).second;
        if (value.compare(keyName) == 0) {
            keyNum = it.key();//*it).first;
            break; //return keyNum;
        }
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
void Settings::addParamDef(const QString &key, const QString &value, bool final)
{
    bool defaultMode = getDefaultMode();
    if (!defaultMode || !isSet(key))
        params.push_back(ParamDef(key, value, final));
}

/*
 *
 */
void Settings::addParamDef(int num, const QString &value, bool final)
{
    QString key = getKeyName(num);
    addParamDef(key, value, final);
}

void Settings::addParamDef(const ParamDef& def)
{
    params.push_back(def);
}

/*
 *
 */
ParamDef& Settings::getDef(const QString key, int skip)
{
    int numParams = params.size();
    int i = 0;
    for (; i < numParams; i++)
//    while (i < numParams)
    {
        ParamDef& def = params[i];
        QString defkey = def.getKey();
        if (defkey.compare(key) == 0)//key.compare(def.getKey()) == 0)
        {
            if (skip == 0)
                break;
            --skip;
        }
//        ++i;
    }
    if (i < numParams)
        return params[i];
    else
        return ParamDef::null;
}

bool Settings::isSet(const QString &key)
{
    bool set = true;
    QString value = getValue(key);
    if (value.isEmpty())
        set = false;
    return set;
//    ParamList::iterator it;
//    it = find_if(params.begin(), params.end(), paramdef_eql(key));
//    return it != params.end();
}

bool Settings::isSet(int key)
{
    return isSet(getKeyName(key));
}

bool Settings::isSet(const QString &key, const QString &target)
{
    int count = 0;
    QString value = getValue(key, count);
    while (!value.isEmpty())
    {
        if (value.compare(target) == 0)
            return true;
        value = getValue(key, ++count);
    }

    return false;
}

bool Settings::isSet(int key, const QString &value)
{
    return isSet(getKeyName(key), value);
}

/*
 * Set the value of an exisiting parameter def, or if no parameter def
 * exists for the key, add a new parameter def. This value will not
 * be set if a parameter def exists and defined as final.
 */
void Settings::setValue(const QString &key, const QString &value, int skip)
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
void Settings::setValue(const QString &key, int value, int skip)
{
    setValue(key, QString::number(value), skip);
}

/*
 *
 */
void Settings::setValue(int num, const QString &value, int skip)
{
    setValue(getKeyName(num), value, skip);

}


/*
 *
 */
void Settings::setValue(int num, double value, int skip)
{
    setValue(getKeyName(num), QString::number(value, 'g'), skip);//toString<double>(value), skip);
}

/*
 *
 */
void Settings::setValue(int num, int value, int skip)
{
    setValue(getKeyName(num), QString::number(value), skip);//toString<int>(value), skip);
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
QString &Settings::getValue(const QString& key, int skip) {
    ParamDef& def = getDef(key, skip);
    tempValue = QString("");

    if (!def.isNull())
        tempValue = def.getValue();

    return tempValue;
}

/*
 *
 */
int Settings::getIntValue(int num, int skip) {
    const QString key = getKeyName(num);
    return getIntValue(key, skip);
}

/*
 *
 */
int Settings::getIntValue(const QString &key, int skip) {
    int retVal = 0;
    QString value = getValue(key, skip);
    if (!value.isEmpty())
        retVal = value.toInt();
    return retVal;
}

/*
 *
 */
double Settings::getDoubleValue(int num, int skip) {
    const QString key = getKeyName(num);
    return getDoubleValue(key, skip);
}

/*
 *
 */
double Settings::getDoubleValue(const QString &key, int skip) {
    double result = 0;
    QString value = getValue(key, skip);
    if (!value.isEmpty())
        result = value.toDouble();// cbr::fromString<double> (value);
    return result;
}

/*
 *
 */
QString &Settings::getValue(int num, int skip) {
    const QString key = getKeyName(num);
    return getValue(key, skip);
}

/*
 *
 */
bool Settings::isChecked(const QString &key) {
    bool retVal = false;
    if (!key.isEmpty()) {
        QString value = getValue(key);
        if (value.compare("1") == 0)
            retVal = true;
    }
    return retVal;
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
QStringList &Settings::getValues(const QString &key) {
    int count = 0;
    tempValueList.clear();
    QString value = getValue(key, count);
    while (!value.isEmpty()) {
        tempValueList.append(value);
        value = getValue(key, ++count);
    }

    return tempValueList;
}

/*
 *
 */
QStringList &Settings::getValues(int num) {
    return getValues(getKeyName(num));
}

void Settings::addChecked(const QString &key, bool rhs, bool final) {
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
void Settings::setChecked(const QString &key, bool rhs) {
    if (rhs)
        setValue(key, "1");
    else
        setValue(key, "0");
}

void Settings::writeSettings(const QString &settingsFile) {

    QString outFile = settingsFile;
    if (outFile.isEmpty())
        outFile = lastSettingsFile;
    if (!outFile.isEmpty()) {

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

bool Settings::readSettings(const QString &settingsFile) {
    // attempt to read input as xml
    if (readFromXml(settingsFile)) {
        lastSettingsFile = settingsFile;
    }
    else {
        // now attempt to read old style (key: value)
        ifstream in(settingsFile.toStdString());

        if (in.is_open()) {
            in >> *this;
            readFromFile = true;
            lastSettingsFile = settingsFile;
        }
    }

    return true;
}

bool Settings::writeXml(const QString &outFile) {
    ofstream ofs;
    ofs.open(outFile.toStdString());
    if (!ofs.is_open())
        return false;

    ofs << serialize().toStdString();
    return true;
}

bool Settings::readFromXml(const QString &inFile) {
    QString xml;
    std::string line;
    ifstream in(inFile.toStdString());
    while (std::getline(in, line))
        xml.append(QString(line.data()) + "\n");
    return deserialize(xml);
}

QString &Settings::serialize()  {
    QDomDocument doc;
    doc.setContent(QString("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"), false);
    QDomElement root = doc.createElement("pitpro");
    doc.appendChild(root);

    // create the xml doc
    for (int i = 0; i < params.size(); i++) {
        const ParamDef& def = params[ i ];
        if (!def.isFinal()) {
            QDomElement elem = doc.createElement(def.getKey());
            QDomText textNode = doc.createTextNode(def.getValue());
            elem.appendChild(textNode);
            root.appendChild(elem);
        }
    }

    tempValue.clear();
    tempValue.append(doc.toString());
    return tempValue;
}

bool Settings::deserialize(const QString &xml) {
    QDomDocument doc;

    QString errorMessage;
    int errorLine;
    int errorCol;
    bool ok = doc.setContent(xml, true, &errorMessage, &errorLine, &errorCol);
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
            QString key = e.tagName();//e.tagName().toLatin1().toStdString();
            QString value = e.text();//.toLatin1().toStdString();
            if (!key.isEmpty() && !value.isEmpty())
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
        QString line(instring.data());
        if (!line.isEmpty()) {
            QStringList list(line.split(':'));
            if (list.count() == 2) {
                settings.addParamDef(list.at(0).simplified(), list.at(1).simplified());
            }
        }
//        int pos = instring.find(':');
//        if (pos != -1) {
//            string key(instring, 0, pos);
//            string value(instring, pos + 1, instring.length() - pos - 1);
//            if (!key.empty() && !value.empty())
//                settings.addParamDef(key, value);
//        }
    }

    return is;
}
