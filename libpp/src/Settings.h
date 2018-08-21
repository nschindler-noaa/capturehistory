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

#include <ArrayDefs.h>

class ParamDef {
public:

    ParamDef() {
    }

    ParamDef(const std::string& k, const std::string& v, bool f = false) : key(k), value(v), final(f) {
    }

    virtual ~ParamDef() {
    }

    void setKey(const std::string& k) {
        key = k;
    }

    void setValue(const std::string& v) {
        value = v;
    }

    const std::string& getKey() const {
        return key;
    }

    const std::string& getValue() const {
        return value;
    }

    static ParamDef null; // null object
    bool isNull() const;

    bool isFinal() const {
        return final;
    }

    bool operator<(const ParamDef& def) {
        return def.key.compare(key) < 0;
    }

private:
    std::string key;
    std::string value;
    bool final;
};

typedef std::vector<ParamDef> ParamList;

/*
 * Settings are stored with a string key. The ability to map a number
 * to a key is provided for convenience and for helping in enforcing
 * consistency with parameter names.
 */
class Settings {
public:
    Settings();
    Settings(const std::string& settingsFile);
    Settings(const Settings& settings);
    virtual ~Settings();

    // mutators
    virtual void clear();
    void clearAll();
    void clearDefs(const std::string& key);
    void clearDefs(int key);
    void addParamDef(const std::string& key, const std::string& value, bool final = false);
    void addParamDef(int key, const std::string& value, bool final = false);
    void addParamDef(const ParamDef& def);
    void setValue(const std::string& key, const std::string& value, int skip = 0);
    void setValue(const std::string& key, int value, int skip = 0);
    void setValue(int key, const std::string& value, int skip = 0);
    void setValue(int key, double value, int skip = 0);
    void setValue(int key, int value, int skip = 0);
    void addChecked(const std::string& key, bool rhs, bool final = false);
    void addChecked(int key, bool rhs, bool final = false);
    void setChecked(const std::string& key, bool rhs);
    void setChecked(int key, bool rhs);
    void merge(const Settings& settings, bool overwrite = false);
    void sort();

    // accessors
    bool isSet(const std::string& key);
    bool isSet(const std::string& key, const std::string &value);
    bool isSet(int key);
    bool isSet(int key, const std::string& value);
    std::string getValue(const std::string& key, int skip = 0);
    std::string getValue(int key, int skip = 0);
    int getIntValue(const std::string& key, int skip = 0);
    int getIntValue(int key, int skip = 0);
    double getDoubleValue(const std::string& key, int skip = 0);
    double getDoubleValue(int key, int skip = 0);
    cbr::StringVector getValues(const std::string& key);
    cbr::StringVector getValues(int key);
    bool isChecked(const std::string& key);
    bool isChecked(int key);

    // key names
    void addKeyName(const std::string& key, int num);
    const std::string& getKeyName(int num);
    int getKeyNum(const std::string& key);

    // error handling

    void clearError() {
        lastError = "";
    }

    bool isError() const {
        return !lastError.empty();
    }

    // io methods

    bool isReadFromFile() {
        return readFromFile;
    }

    const std::string& getLastSettingsFile() const {
        return lastSettingsFile;
    }
    void writeSettings(const std::string& settingsFile = "");
    bool readSettings(const std::string& settingsFile);

    const std::string& getLastError() const {
        return lastError;
    }
    friend std::ostream& operator<<(std::ostream& ts, const Settings& settings);
    friend std::istream& operator>>(std::istream& ts, Settings& settings);

    void setDefaultMode(bool rhs) {
        defaultMode = rhs;
    }

    bool getDefaultMode() const {
        return defaultMode;
    }

    bool writeXml(const std::string& outFile);
    bool readFromXml(const std::string& inFile);
    std::string serialize() const;
    bool deserialize(const std::string& xml);

    const std::map<int, std::string>& getKeyNames() const {
        return keyNames;
    }
    ParamDef& getDef(const std::string& key, int skip);

protected:
    ParamList params;
    std::string lastError;
    std::map<int, std::string> keyNames;


private:
    std::string lastSettingsFile;

    bool saveSettings;
    bool readFromFile;
    std::string settingsFile;
    bool defaultMode;
};

#endif // Settings_h
