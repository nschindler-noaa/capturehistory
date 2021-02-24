/*
 * Settings.h
 *
 * Generalized settings class. Settings are read from a file
 * with the format:
 *
 *   key: value
 *
 */

#ifndef Settings_h
#define Settings_h

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <QStringList>
#include <QMap>

#include <ArrayDefs.h>

class ParamDef {
public:

    ParamDef() : key(""), value(""), final(false) {}

    ParamDef(const QString &k, const QString &v, bool f = false) : key(k), value(v), final(f) {}

    virtual ~ParamDef() {}

    void setKey(const QString &k) { key = k;}

    void setValue(const QString &v) { value = v;}

    const QString &getKey() const { return key;}

    const QString &getValue() const { return value;}

    static ParamDef null; // null object
    bool isNull() const;

    bool isFinal() const { return final;}

    bool operator<(const ParamDef& def) { return def.key.compare(key) < 0;}

private:
    QString key;
    QString value;
    bool final;
};

typedef QList<ParamDef> ParamList;

/*
 * Settings are stored with a string key. The ability to map a number
 * to a key is provided for convenience and for helping in enforcing
 * consistency with parameter names.
 */
class Settings {
public:
    Settings();
    Settings(const QString &settingsFile);
    Settings(const Settings& settings);
    virtual ~Settings();

    // mutators
    virtual void clear();
    void clearAll();
    void clearDefs(const QString &key);
    void clearDefs(int key);
    void addParamDef(const QString &key, const QString &value, bool final = false);
    void addParamDef(int key, const QString &value, bool final = false);
    void addParamDef(const ParamDef& def);
    void setValue(const QString &key, const QString &value, int skip = 0);
    void setValue(const QString &key, int value, int skip = 0);
    void setValue(int key, const QString &value, int skip = 0);
    void setValue(int key, double value, int skip = 0);
    void setValue(int key, int value, int skip = 0);
    void addChecked(const QString &key, bool rhs, bool final = false);
    void addChecked(int key, bool rhs, bool final = false);
    void setChecked(const QString &key, bool rhs);
    void setChecked(int key, bool rhs);
    void merge(const Settings& settings, bool overwrite = false);
    void sort();

    // accessors
    bool isSet(const QString &key);
    bool isSet(const QString &key, const QString &value);
    bool isSet(int key);
    bool isSet(int key, const QString &value);
    QString &getValue(const QString &key, int skip = 0);
    QString &getValue(int key, int skip = 0);
    int getIntValue(const QString &key, int skip = 0);
    int getIntValue(int key, int skip = 0);
    double getDoubleValue(const QString &key, int skip = 0);
    double getDoubleValue(int key, int skip = 0);
    QStringList &getValues(const QString &key);
    QStringList &getValues(int key);
    bool isChecked(const QString &key);
    bool isChecked(int key);

    // key names
    void addKeyName(const QString &key, int num);
    const QString &getKeyName(int num);
    int getKeyNum(const QString &key);

    // error handling

    void clearError() {lastError = "";}

    bool isError() const {return !lastError.isEmpty();}

    // io methods

    bool isReadFromFile() {return readFromFile;}

    const QString &getLastSettingsFile() const {return lastSettingsFile;}
    void writeSettings(const QString &settingsFile = "");
    bool readSettings(const QString &settingsFile);

    const QString &getLastError() const {return lastError;}
    friend std::ostream& operator<<(std::ostream& ts, const Settings& settings);
    friend std::istream& operator>>(std::istream& ts, Settings& settings);

    void setDefaultMode(bool rhs) {defaultMode = rhs;}

    bool getDefaultMode() const {return defaultMode;}

    bool writeXml(const QString &outFile);
    bool readFromXml(const QString &inFile);
    QString &serialize();
    bool deserialize(const QString &xml);

    const QMap<int, QString>& getKeyNames() const {return keyNames;}
    ParamDef& getDef(const QString key, int skip);

protected:
    ParamList params;
    QString lastError;
    QMap<int, QString> keyNames;


private:
    QString lastSettingsFile;

    bool saveSettings;
    bool readFromFile;
    QString settingsFile;
    bool defaultMode;

    QStringList tempValueList;
    QString tempValue;
};

#endif // Settings_h
