/*
 *  SitesConfigDialog.cpp
 */


#include <string>

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include <Sites.h>

#include "SitesConfigDialog.h"
#include "PitProSettings.h"
#include "PPSystemSettings.h"
#include "portability.h"

using std::string;

SitesConfigDialog::SitesConfigDialog(QWidget* parent, Qt::WindowFlags fl) : QDialog(parent, fl) {
    setupUi(this);

    connect(applyButton, SIGNAL(clicked()), SLOT(doApply()));
    connect(doneButton, SIGNAL(clicked()), SLOT(doApply()));
    connect(findSitesConfigButton, SIGNAL(clicked()), SLOT(browseForSitesConfig()));

    connect(altSitesConfigCheckBox, SIGNAL(toggled(bool)), SLOT(checkApplyButtonState()));
    connect(sitesConfigEdit, SIGNAL(textChanged(const QString&)), SLOT(checkApplyButtonState()));

    updateDialog();
}

SitesConfigDialog::~SitesConfigDialog() {
}

void SitesConfigDialog::updateDialog() {
    PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
    altSitesConfigCheckBox->setChecked(systemSettings.isChecked(PPSystemSettings::AltSitesConfig));
    sitesConfigEdit->setText(systemSettings.get(PPSystemSettings::SitesConfigFile).toString());
}

void SitesConfigDialog::browseForSitesConfig() {
    PPSystemSettings& systemSettings = PPSystemSettings::getInstance();

    QString current = sitesConfigEdit->text().section('/', 0, -2);
    QDir dir(current);
    QString path = dir.path();
    if (!dir.exists())
        current = systemSettings.get(PPSystemSettings::LastDir).toString();
    QString selected = QFileDialog::getOpenFileName(this,
            "Find alternate sites configuration file",
            current, "*.*");

    if (selected != QString::null) {
        sitesConfigEdit->setText(selected);
        systemSettings.set(PPSystemSettings::LastDir, selected.section('/', 0, -2));
    }
}

/*
 * Called from interface when sites config needs to be refreshed.
 * In this case, the interface has the config file name so we need
 * to update the settings first.
 */
void SitesConfigDialog::doApply() {
    // update the sites configuration data
    if (updateNeeded())
        refreshSitesConfig();
}

/* 
 * Called when we need to update the sites configuration
 * based on the settings.
 */
void SitesConfigDialog::doSitesConfigSettingsChanged() {
    // update the sites configuration data
    refreshSitesConfig();
    updateDialog();
}

/*
 *
 */
bool SitesConfigDialog::updateNeeded() {
    PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
    bool altChecked = systemSettings.isChecked(PPSystemSettings::AltSitesConfig);
    QString sitesConfigFile = systemSettings.get(PPSystemSettings::SitesConfigFile).toString();

    bool currentAltChecked = altSitesConfigCheckBox->isChecked();
    QString currentSitesConfigFile = sitesConfigEdit->text();

    return currentAltChecked != altChecked || sitesConfigFile.compare(currentSitesConfigFile) != 0;
}

/*
 *
 */
void SitesConfigDialog::checkApplyButtonState() {
    applyButton->setEnabled(updateNeeded());
}

/*
 * Load the sites configuration based on the settings.
 */
void SitesConfigDialog::refreshSitesConfig() {
    Sites* sites = Sites::getInstance();
    PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
    bool altChecked = altSitesConfigCheckBox->isChecked();
    systemSettings.set(PPSystemSettings::AltSitesConfig, altChecked);
    if (altChecked) {
        QString sitesConfigFile = sitesConfigEdit->text();
        systemSettings.set(PPSystemSettings::SitesConfigFile, sitesConfigFile);
    }

    systemSettings.resolveSitesConfig();
    
    QString sitesConfigFile = systemSettings.get(PPSystemSettings::SitesConfigFile).toString();

    altChecked = systemSettings.isChecked(PPSystemSettings::AltSitesConfig);
    altSitesConfigCheckBox->blockSignals(true);
    altSitesConfigCheckBox->setChecked(altChecked);
    altSitesConfigCheckBox->blockSignals(false);

    if (sitesConfigFile.isEmpty())
        QMessageBox::information(this, "PitPro", "No sites configuration file selected.");
    else if (!QFile(sitesConfigFile).exists())  {
        QDir dir;
        QMessageBox::information(this, "PitPro", "Sites configuration file doesn't exist: " + dir.absoluteFilePath(sitesConfigFile));
    } 
    else {
        try {
            sites->read(sitesConfigFile.toStdString());
            applyButton->setEnabled(false);
            emit siteConfigChanged();
        } catch (string msg) {
            QMessageBox::critical(this, "PitPro", "Unable to open sites configuration file!.");
        }
    }
}
