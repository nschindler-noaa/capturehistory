
/*
 *
 */

#include <boost/filesystem.hpp>

#include <QStringList>
#include <QFileInfo>
#include <QDir>

#include "PPSystemSettings.h"

//using namespace cbr;
using namespace boost::filesystem;

PPSystemSettings& PPSystemSettings::getInstance() {
    static PPSystemSettings settings;
    return settings;
}

PPSystemSettings::PPSystemSettings() : CbrSettings() {
    QDir appDataDir;
    QString appDataPath = getAppDataPath("PitPro");
    if (!appDataPath.isEmpty())
        appDataDir.setPath(appDataPath);
    QString defaultSitesConfigFile =  appDataDir.filePath("sites_config.txt");

    // set up keys  
    addKey(AltSitesConfig, "alt_config_file", false);
    addKey(AppDataPath, "app_data_path", appDataPath);
    addKey(ConfigFile, "configfile");
    addKey(DataDir, "datadir");
    addKey(EstPrecision, "est_precision", 4);
    addKey(ErrPrecision, "err_precision", 4);
    addKey(LastDir, "lastdir", false);
    addKey(OneTableCjs, "one_table_cjs", false);
    addKey(Prefix, "prefix");
    addKey(ShowLambda, "show_lambda", true);
    addKey(ShowTrackerDetails, "show_tracker_details", false);
    addKey(SitesConfigFile, "sites_config_file", defaultSitesConfigFile);
    addKey(TrackedPits, "tracked_pits");
    addKey(Version, "version", "4.22.1");

    set(Version, getDefault(Version));
}

void PPSystemSettings::saveDir(SettingKey key, const QString& path) {
    QFileInfo fi(path);
    QDir dir = fi.dir();
    QString s = dir.absolutePath();
    set(key, s);
}

QString PPSystemSettings::getDir(SettingKey key) const {
    return get(key).toString();
}


void PPSystemSettings::resolveSitesConfig()  {
	if (!isChecked(AltSitesConfig))
		set(SitesConfigFile, getDefault(SitesConfigFile).toString());

    QFile file(get(SitesConfigFile).toString());
    if (file.exists())
        return;
    
    // reset
    set(AltSitesConfig, false); 
    QString sitesConfigFile = getDefault(SitesConfigFile).toString();
    if (QFile(sitesConfigFile).exists())  {
        set(SitesConfigFile, sitesConfigFile);
        return;
    }

    // try just sites config
    sitesConfigFile = "sites_config.txt";
    if (QFile(sitesConfigFile).exists())
    {
        set(SitesConfigFile, sitesConfigFile);
        return;
    }

}

QString PPSystemSettings::getSitesConfig() const {
    QString sitesConfig = getDefault(SitesConfigFile).toString();
    return sitesConfig;
}
