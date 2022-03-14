/*
 * ConfigWidgetImpl.cpp
 */

#include <string>
#include <vector>
#include <algorithm>

#include <QStringList>
#include <QVector>
#include <QMenu>
#include <QMessageBox>
#include <QSignalMapper>

#include <qdir.h>
#include <qstringlist.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qfiledialog.h>
#include <qcheckbox.h>
#include <qtabwidget.h>
#include <qradiobutton.h>
#include <qfiledialog.h>

#include <Sites.h>
#include <CbrPit.h>
#include <ArrayDefs.h>
#include <StringManip.h>

#include "ConfigWidgetImpl.h"
#include "PitProSettings.h"
#include "PitProUtilities.h"


using std::string;
using std::vector;
using std::sort;
using std::binary_function;
using namespace cbr;

/*
 *  Constructs a ConfigWidgetImpl which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 */
ConfigWidgetImpl::ConfigWidgetImpl(QWidget* parent, Qt::WindowFlags fl)
: QWidget(parent, fl), BaseNumRows(20), numRuns(0),
tagPopup(0), obsPopup(0), rcpPopup(0), mrtPopup(0), relPopup(0),
lastDir(QString::null)
 {
    setupUi(this);

    // These will contain the list of possible files
    // based on  dynamically updated input settings
    tagPopup = new QMenu(runsTable);
    obsPopup = new QMenu(runsTable);
    rcpPopup = new QMenu(runsTable);
    mrtPopup = new QMenu(runsTable);
    relPopup = new QMenu(runsTable);

    // add settings to widgets, must have sites config loaded first
    updateWidget();

    // add sites to combos before sizing
    refreshSitesTab();


    // make all columns in the runsTable stretch
//    for (int col = 0; col < runsTable->columnCount(); col++)
//        runsTable->setColumnStretchable(col, true);
    runsTable->resizeColumnsToContents();

    popupActions_[Delete] = new QAction("Remove", this);
    popupActions_[MoveUp] = new QAction("Move Up", this);
    popupActions_[MoveDown] = new QAction("Move Down", this);

    // hist field list pop-up menu
    histFieldPopup = new QMenu(histFieldList);
    histFieldPopup->addAction(popupActions_[Delete]);
    histFieldPopup->addAction(popupActions_[MoveUp]);
    histFieldPopup->addAction(popupActions_[MoveDown]);

    // last field list pop-up menu
    adultSitePopup = new QMenu(adultSiteList);
    adultSitePopup->addAction(popupActions_[Delete]);
    adultSitePopup->addAction(popupActions_[MoveUp]);
    adultSitePopup->addAction(popupActions_[MoveDown]);

    // last field list pop-up menu
    transSitePopup = new QMenu(adultSiteList);
    transSitePopup->addAction(popupActions_[Delete]);

    // set read only status on table
    runsTable->setEnabled(true);
//    runsTable->setReadOnly(false);

//    runsTable->setColumnReadOnly(0, false);
//    for (int col = 1; col < runsTable->numCols(); ++col)
//        runsTable->setColumnReadOnly(col, true);
    QStringList columnLabels;
    columnLabels << "Population Name" << "Tag File" << "Interrogation File" << "Recapture File" << "Mortality File";
    runsTable->setHorizontalHeaderLabels(columnLabels);// setColumnLabels(columnLabels);
    addTableRows();

    // update the versioncombo related items
    versionComboChanged();

    // signals and slots connections
    connect(outDirButton, SIGNAL(clicked()), this, SLOT(outDirButtonClicked()));
    connect(dataDirButton, SIGNAL(clicked()), this, SLOT(dataDirButtonClicked()));
    connect(tabWidget, SIGNAL(currentChanged(QWidget*)), this, SLOT(refreshTab(QWidget*)));
    connect(tabWidget, SIGNAL(currentChanged(QWidget*)), this, SLOT(doCurrentChanged(QWidget*)));
    connect(runsTable, SIGNAL(contextMenuRequested(int, int, const QPoint&)), this, SLOT(doContextMenuRequested(int, int, const QPoint&)));
    connect(histFieldList, SIGNAL(customContextMenuRequested(QPoint)), SLOT(doHistFieldListMenu(QPoint)));
    connect(transSiteList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(doTransSiteListMenu(QPoint)));
    connect(adultSiteList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(doAdultSiteListMenu(QPoint)));
    connect(addRunButton, SIGNAL(clicked()), this, SLOT(doAddRunButton()));
    connect(addHistFieldButton, SIGNAL(clicked()), this, SLOT(doAddHistFieldButton()));
    connect(addAdultSiteButton, SIGNAL(clicked()), this, SLOT(doAddAdultSiteButton()));
    connect(addTransSiteButton, SIGNAL(clicked()), this, SLOT(doAddTransSiteButton()));
    connect(sortJuvenileSitesButton, SIGNAL(clicked()), this, SLOT(sortJuvenileSitesList()));
    connect(sortAdultSitesButton, SIGNAL(clicked()), this, SLOT(sortAdultSitesList()));
    connect(sortTransSitesButton, SIGNAL(clicked()), this, SLOT(sortTransSitesList()));
    connect(deleteRunButton, SIGNAL(clicked()), this, SLOT(doDeleteRunButton()));
    connect(groupRunsCheckBox, SIGNAL(toggled(bool)), outPrefixEdit, SLOT(setEnabled(bool)));
    connect(dataDirEdit, SIGNAL(textChanged(const QString&)), this, SLOT(emitDataDirChanged(const QString&)));
    connect(juvCutoffRadio, SIGNAL(toggled(bool)), juvCutoffEdit, SLOT(setEnabled(bool)));
    connect(migrationYearRadio, SIGNAL(toggled(bool)), migrYearEdit, SLOT(setEnabled(bool)));
    connect(outDirEdit, SIGNAL(textChanged(const QString&)), this, SLOT(emitOutputDirChanged(const QString&)));
    connect(fileFilterSwitch, SIGNAL(toggled(bool)), this, SLOT(updateAllDataLists()));
    connect(surphVersionCombo, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(versionComboChanged()));
    connect(siteRelCheckBox, SIGNAL(clicked(bool)), SLOT(onRelSiteCheckBoxClicked(bool)));


}

/*
 *  Destroys the object and frees any allocated resources
 */
ConfigWidgetImpl::~ConfigWidgetImpl() {
    // no need to delete child widgets, Qt does it all for us
}

/*
 * Refresh the given tab
 */
void ConfigWidgetImpl::refreshTab(QWidget* w) {
    if (w) {
        QString name = w->objectName();

        if (!name.compare("runSetup"))
            refreshRunSetupTab();
        else if (!name.compare("errorChecking"))
            refreshErrorCheckingTab();
        else if (!name.compare("files"))
            refreshFilesTab();
        else if (!name.compare("sites"))
            refreshSitesTab();
        else if (!name.compare("trans"))
            refreshTransTab();
        else if (!name.compare("adultCriteria"))
            refreshAdultCriteriaTab();
        else if (!name.compare("advanced"))
            refreshAdvancedTab();
    }
}

/*
 * Refresh the current tab
 */
void ConfigWidgetImpl::refreshCurrentTab() {
    if (tabWidget)
        refreshTab(tabWidget->currentWidget());
}

/*
 * Refresh the run setup tab
 */
void ConfigWidgetImpl::refreshRunSetupTab() {
    updateAllDataLists();
}

/*
 * Refresh the error checking tab
 */
void ConfigWidgetImpl::refreshErrorCheckingTab() {
}

/*
 * Refresh the  files tab
 */
void ConfigWidgetImpl::refreshFilesTab() {
}

/*
 * Refresh the output files tab
 */
void ConfigWidgetImpl::refreshSitesTab() {
    QStringList juvenileSiteNames;
    QStringList adultSiteNames;
    Sites* sites = Sites::getInstance();
    for (int i = 0; i < sites->nsites(); i++) {
        Site* site = sites->getSite(i);
        if (site) {
            QString longName(site->getLongName());
            QString truncatedName(longName);
            if (truncatedName.size() > 30) {
                truncatedName.truncate(30);
                truncatedName.append("...");
            }
            if (site->stageMatch(CbrPit::ST_Juvenile))
                juvenileSiteNames.append(truncatedName);
            if (site->stageMatch(CbrPit::ST_Adult))
                adultSiteNames.append(truncatedName);
        }
    }
    juvenileSiteNames.sort();
    adultSiteNames.sort();

    // add sites to combo lists
    histFieldCombo->clear();
    histFieldCombo->addItems(juvenileSiteNames);// insertStringList(juvenileSiteNames);
    adultSiteCombo->clear();
    adultSiteCombo->addItems(adultSiteNames);// insertStringList(adultSiteNames);

    refreshRelSiteCombo();
    refreshLastFieldCombo();
}

/*
 * Refresh the output files tab
 */
void ConfigWidgetImpl::refreshTransTab() {
    QStringList transNames;

    Sites* sites = Sites::getInstance();
    if (!sites)
        return;

    Site* site = sites->getSite("gr");
    if (site)
        transNames.append(site->getLongName());
    site = sites->getSite("go");
    if (site)
        transNames.append(site->getLongName());
    site = sites->getSite("lm");
    if (site)
        transNames.append(site->getLongName());
    site = sites->getSite("mc");
    if (site)
        transNames.append(site->getLongName());

    transNames.sort();

    // add sites to combo lists
    transComboBox->clear();
    transComboBox->addItems(transNames);// insertStringList(transNames);
}

/*
 * Refresh the adult criteria tab
 */
void ConfigWidgetImpl::refreshAdultCriteriaTab() {
}

/*
 * Refresh the advanced tab
 */
void ConfigWidgetImpl::refreshAdvancedTab() {
}

void ConfigWidgetImpl::refreshRelSiteCombo() {
#if 0
    // update release site list with current juvenile sites
    QStringList juvenileSites;
    relSiteCombo->clear();
    for (size_t i = 0; i < histFieldList->count(); i++) {
        if (juvenileSites.findIndex(histFieldList->text(i)) == -1)
            juvenileSites += histFieldList->text(i);
    }
    juvenileSites.sort();
    relSiteCombo->insertStringList(juvenileSites);
#endif
}

void ConfigWidgetImpl::refreshHistLists() {
    PitProSettings &settings = PitProSettings::getInstance();

    Sites* sites = Sites::getInstance();
    QStringList histList = settings.getValues(PitProSettings::HistField);
    histFieldList->clear();
    for (QStringList::iterator it = histList.begin(); it != histList.end(); ++it) {
        Site* site = sites->getSite((*it));
        if (site) {
            histFieldList->addItem(QString(site->getLongName()));
        }

    }
    histFieldList->setCurrentRow(histFieldList->count() - 1);

    // get the adult fields
    QStringList lastList = settings.getValues(PitProSettings::AdultField);
    adultSiteList->clear();
    for (QStringList::iterator it = lastList.begin(); it != lastList.end(); ++it) {
        Site* site = sites->getSite((*it));
        if (site) {
            adultSiteList->addItem(site->getLongName());
        }
    }
    adultSiteList->setCurrentRow(adultSiteList->count() - 1);
    lastFieldCombo->setCurrentIndex(settings.getIntValue(PitProSettings::NumMainSites) - 1);
}

void ConfigWidgetImpl::refreshTransSitesList() {
    PitProSettings &settings = PitProSettings::getInstance();
    Sites* sites = Sites::getInstance();

    QStringList transList = settings.getValues(PitProSettings::TransSite);
    transSiteList->clear();
    for (QStringList::iterator it = transList.begin(); it != transList.end(); ++it) {
        Site* site = sites->getSite((*it));
        if (site && (*it).compare("none") != 0)
            transSiteList->addItem(site->getLongName());
    }
}

void ConfigWidgetImpl::refreshLastFieldCombo() {
    // update release site list with current juvenile sites
    QString currentText = lastFieldCombo->currentText();

    QStringList sites;
    lastFieldCombo->clear();
    QString siteText;
    int i = (siteRelCheckBox->isChecked()) ? 1 : 0;
    for (; i < histFieldList->count(); i++) {
        siteText = histFieldList->item(i)->text() + QString(" (J)");// text(i) + " (J)";
        sites << siteText;
    }
    for (i = 0; i < adultSiteList->count(); i++) {
        siteText = adultSiteList->item(i)->text() + QString(" (A)");// text(i) + " (A)";
        sites << siteText;
    }
    if (sites.count() > 1)
    {
        sites.pop_back();
        lastFieldCombo->addItems(sites);// insertStringList(sites.toList());
        if (currentText == QString::null || !sites.contains(currentText))
            lastFieldCombo->setCurrentIndex(lastFieldCombo->findText(sites.back()));//setCurrentText(sites.back());
        else
            lastFieldCombo->setCurrentIndex(lastFieldCombo->findText(currentText));//Text(currentText);
    }
}

void ConfigWidgetImpl::emitDataDirChanged(const QString& dataDir) {
    if (!dataDir.isEmpty()) {
        PitProSettings& settings = PitProSettings::getInstance();
        settings.setValue(PitProSettings::DataDir, dataDir);
        updateAllDataLists();
        emit dataDirChanged(dataDir);
    }
}

void ConfigWidgetImpl::emitOutputDirChanged(const QString& outDir) {
    if (!outDir.isEmpty()) {
        PitProSettings& settings = PitProSettings::getInstance();
        settings.setValue(PitProSettings::OutputDir, outDir);
        emit outputDirChanged(outDir);
    }
}

/*
 * Write the current settings to the dialog widgets.
 */
void ConfigWidgetImpl::updateWidget() {
    PitProSettings& settings = PitProSettings::getInstance();

    try {
        // add table (in row first order)
        QStringList runDefs = settings.getValues(PitProSettings::RunsTable);
        runsTable->setRowCount(0);
        // load the run definitions
        int i = 0;
        numRuns = 0;
        runsTable->setRowCount(settings.getNumGroups());// addRow(0, settings.getNumGroups());
        for (QStringList::iterator it = runDefs.begin(); it != runDefs.end(); ++it) {
            runsTable->setItem(numRuns, i++, new QTableWidgetItem(QString((*it))));//setText(numRuns, i++, (*it).c_str());
            if (i == runsTable->columnCount()) {
                i = 0;
                numRuns++;
            }
        }
        if (numRuns < 2) {
            groupRunsCheckBox->setChecked(false);
            groupRunsCheckBox->setEnabled(false);
        } else {
            groupRunsCheckBox->setEnabled(true);
            groupRunsCheckBox->setChecked(settings.isChecked(PitProSettings::GroupRuns));
        }
        fileFilterSwitch->setChecked(settings.isChecked(PitProSettings::FilterByFileType));


        // file tab
        dataDirEdit->setText(settings.getValue(PitProSettings::DataDir));
        QString outDir = settings.getValue(PitProSettings::OutputDir);
        outDirEdit->setText(settings.getValue(PitProSettings::OutputDir));
        outPrefixEdit->setText(settings.getValue(PitProSettings::OutPrefix));
        surphFileCheckBox->setChecked(settings.isChecked(PitProSettings::SurphFileSwitch));
        errorsFileCheckBox->setChecked(settings.isChecked(PitProSettings::ErrorsFileSwitch));
        detectionDateFileCheckBox->setChecked(settings.isChecked(PitProSettings::DdFileSwitch));
        travelTimeFileCheckBox->setChecked(settings.isChecked(PitProSettings::TtFileSwitch));
        sequenceFileCheckBox->setChecked(settings.isChecked(PitProSettings::SequenceFileSwitch));
        lengthCovCheckBox->setChecked(settings.isChecked(PitProSettings::ICovSwitch));
        zeroCovariateCheckBox->setChecked(settings.isChecked(PitProSettings::ZeroCovariateSwitch));
        nullCovariateCheckBox->setChecked(settings.isChecked(PitProSettings::NullCovariateSwitch));
        QString outputFormat = settings.getValue(PitProSettings::OutputFormat);
        if (!outputFormat.isEmpty() && (!outputFormat.compare("SURPH1") ||
                !outputFormat.compare("SURPH2") || !outputFormat.compare("ROSTER")))
            surphVersionCombo->setCurrentIndex(surphVersionCombo->findText(outputFormat));//Text(outputFormat.c_str());

        // sites tab
        refreshHistLists();
        refreshLastFieldCombo();
        siteRelCheckBox->setChecked(settings.isChecked(PitProSettings::SiteRel));


        // tag screening tab
        speciesCombo->setCurrentIndex(speciesCombo->findText(settings.getValue(PitProSettings::Species)));//Text(settings.getValue(PitProSettings::Species).c_str());
        runCombo->setCurrentIndex(runCombo->findText(settings.getValue(PitProSettings::Run)));//Text(settings.getValue(PitProSettings::Run).c_str());
        rearTypeCombo->setCurrentIndex(rearTypeCombo->findText(settings.getValue(PitProSettings::RearType)));//Text(settings.getValue(PitProSettings::RearType).c_str());


#if 0
        // error checking tab

        releaseCheckBox->setChecked(settings.isChecked(PitProSettings::ReleaseDataCheck));
#endif

        // stage tab
        assumeJuvenileCheckBox->setChecked(!settings.isChecked(PitProSettings::AdultModeSwitch));
        //censorJuvUpstreamRadio->setChecked( settings.isChecked( PitProSettings::CensorJuvUpstreamSwitch ) );
        //truncUpJuvRadio->setChecked( settings.isChecked( PitProSettings::TruncUpJuvSwitch ) );
        juvCutoffRadio->setChecked(settings.isChecked(PitProSettings::JuvenileCutoffSwitch));
        migrationYearRadio->setChecked(settings.isChecked(PitProSettings::MigrationYearSwitch));
        juvCutoffEdit->setText(settings.getValue(PitProSettings::JuvenileCutoffDate));
        migrYearEdit->setText(settings.getValue(PitProSettings::MigrationYear));
        anyRouteRadio->setChecked(settings.isChecked(PitProSettings::AnyRouteSwitch));
        lastRouteRadio->setChecked(settings.isChecked(PitProSettings::LastRouteSwitch));
        removeJacksCheckBox->setChecked(settings.isChecked(PitProSettings::RemoveJacks));
        combineJacksCheckBox->setChecked(settings.isChecked(PitProSettings::CombineJacks));
        removeResSwitch->setChecked(settings.isChecked(PitProSettings::RemoveResidualizers));
        resCutoffCheckBox->setChecked(settings.isChecked(PitProSettings::ResCutoffSwitch));
        resCutoffEdit->setText(settings.getValue(PitProSettings::ResCutoffDate));
        steelheadYearCB->setChecked(settings.isChecked(PitProSettings::UseSteelheadYear));

        // trans tab
        // get the trans sites
        refreshTransSitesList();

        // advanced tab
        removalTrumpsRadio->setChecked(settings.isChecked(PitProSettings::RemovalTrumpsSwitch));
        lastDetectionRadio->setChecked(settings.isChecked(PitProSettings::LastOutcomeSwitch));
        tagCheckBox->setChecked(!settings.isChecked(PitProSettings::TagCheck));
        ignoreReRecapsCheckBox->setChecked(settings.isChecked(PitProSettings::IgnoreReRecaps));
        singleCoilCheckBox->setChecked(settings.isChecked(PitProSettings::SingleCoilSwitch));
        warningsCheckBox->setChecked(settings.isChecked(PitProSettings::Warnings));
        sampTransCheckBox->setChecked(settings.isChecked(PitProSettings::SampTransSwitch));
    }    catch (string& e) {
        QMessageBox::critical(this, "PitPro", e.c_str());
    }

    updateAllDataLists();
}

/*
 * Write the widget state to the settings object.
 */
void ConfigWidgetImpl::updateSettings() {
    PitProSettings& settings = PitProSettings::getInstance();
    settings.clear();

    try {
        // runs tab
        settings.setChecked(PitProSettings::GroupRuns, groupRunsCheckBox->isChecked());
        // runs table
        for (int j = 0; j < numRuns; ++j) {
            for (int i = 0; i < runsTable->columnCount(); ++i) {
                settings.addParamDef(PitProSettings::RunsTable, runsTable->item(j, i)->text());// text(j, i).ascii());
            }
        }
        settings.setValue(PitProSettings::FilterByFileType, fileFilterSwitch->isChecked());

        // file tab
        settings.setValue(PitProSettings::DataDir, dataDirEdit->text());//.ascii());
        settings.setValue(PitProSettings::OutputDir, outDirEdit->text());//.ascii());
        settings.setValue(PitProSettings::OutPrefix, outPrefixEdit->text());//.ascii());
        settings.setChecked(PitProSettings::SurphFileSwitch, surphFileCheckBox->isChecked());
        settings.setChecked(PitProSettings::ErrorsFileSwitch, errorsFileCheckBox->isChecked());
        settings.setChecked(PitProSettings::DdFileSwitch, detectionDateFileCheckBox->isChecked());
        settings.setChecked(PitProSettings::TtFileSwitch, travelTimeFileCheckBox->isChecked());
        settings.setChecked(PitProSettings::SequenceFileSwitch, sequenceFileCheckBox->isChecked());
        settings.setChecked(PitProSettings::ICovSwitch, lengthCovCheckBox->isChecked());
        settings.setChecked(PitProSettings::ZeroCovariateSwitch, zeroCovariateCheckBox->isChecked());
        settings.setChecked(PitProSettings::NullCovariateSwitch, nullCovariateCheckBox->isChecked());

        settings.setValue(PitProSettings::OutputFormat, surphVersionCombo->currentText());//.ascii());

        // sites tab
        settings.setChecked(PitProSettings::SiteRel, siteRelCheckBox->isChecked());
        //settings.addParamDef( PitProSettings::RelSite, relSiteCombo->currentText().ascii() );
        Sites* sites = Sites::getInstance();
        int i;
        for (i = 0; i < histFieldList->count(); i++) {
            Site* site = sites->getSite(histFieldList->item(i)->text());//.ascii());
            if (site)
                settings.addParamDef(PitProSettings::HistField, site->getSiteCode());
        }
        for (i = 0; i < adultSiteList->count(); i++) {
            Site* site = sites->getSite(adultSiteList->item(i)->text());//.ascii());
            if (site)
                settings.addParamDef(PitProSettings::AdultField, site->getSiteCode());
        }
        settings.addParamDef(PitProSettings::NumMainSites, QString::number(lastFieldCombo->currentIndex() + 1));//toString<int>());

        // tag screening tab
        settings.setValue(PitProSettings::Species, speciesCombo->currentText());//.ascii());
        settings.setValue(PitProSettings::Run, runCombo->currentText());//.ascii());
        settings.setValue(PitProSettings::RearType, rearTypeCombo->currentText());//.ascii());

#if 0
        // error checking tab
        settings.setChecked(PitProSettings::ZeroCovariateSwitch, zeroLengthCheckBox->isChecked());
        settings.setChecked(PitProSettings::ReleaseDataCheck, releaseCheckBox->isChecked());
#endif

        // stage tab
        settings.setChecked(PitProSettings::AdultModeSwitch, !assumeJuvenileCheckBox->isChecked());
        //settings.setChecked( PitProSettings::CensorJuvUpstreamSwitch, censorJuvUpstreamRadio->isChecked() );
        //settings.setChecked( PitProSettings::TruncUpJuvSwitch, truncUpJuvRadio->isChecked() );
        settings.setChecked(PitProSettings::JuvenileCutoffSwitch, juvCutoffRadio->isChecked());
        settings.setChecked(PitProSettings::MigrationYearSwitch, migrationYearRadio->isChecked());
        settings.setValue(PitProSettings::JuvenileCutoffDate, juvCutoffEdit->text());//.ascii());
        settings.setValue(PitProSettings::MigrationYear, migrYearEdit->text());//.ascii());
        settings.setChecked(PitProSettings::RemoveJacks, removeJacksCheckBox->isChecked());
        settings.setChecked(PitProSettings::CombineJacks, combineJacksCheckBox->isChecked());
        settings.setChecked(PitProSettings::LastRouteSwitch, lastRouteRadio->isChecked());
        settings.setChecked(PitProSettings::AnyRouteSwitch, anyRouteRadio->isChecked());
        settings.setChecked(PitProSettings::RemoveResidualizers, removeResSwitch->isChecked());
        settings.setChecked(PitProSettings::ResCutoffSwitch, resCutoffCheckBox->isChecked());
        settings.setValue(PitProSettings::ResCutoffDate, resCutoffEdit->text());//.ascii());
        settings.setChecked(PitProSettings::UseSteelheadYear, steelheadYearCB->isChecked());

        // trans tab
        if (transSiteList->count() == 0)
            settings.addParamDef(PitProSettings::TransSite, "none");
        else {
            for (i = 0; i < transSiteList->count(); i++) {
                Site* site = sites->getSite(transSiteList->item(i)->text());//.ascii());
                if (site)
                    settings.addParamDef(PitProSettings::TransSite, site->getSiteCode());
            }
        }

        //advanced tab
        settings.setChecked(PitProSettings::RemovalTrumpsSwitch, removalTrumpsRadio->isChecked());
        settings.setChecked(PitProSettings::LastOutcomeSwitch, lastDetectionRadio->isChecked());
        settings.setChecked(PitProSettings::IgnoreReRecaps, ignoreReRecapsCheckBox->isChecked());
        settings.setChecked(PitProSettings::TagCheck, !tagCheckBox->isChecked());
        settings.setChecked(PitProSettings::SingleCoilSwitch, singleCoilCheckBox->isChecked());
        settings.setChecked(PitProSettings::Warnings, warningsCheckBox->isChecked());
        settings.setChecked(PitProSettings::SampTransSwitch, sampTransCheckBox->isChecked());

        updateMimeFactory();
    }    catch (QString& e) {
        QMessageBox::critical(this, "PitPro", e);
    }

}

void ConfigWidgetImpl::dataDirNameChanged(const QString& dirName) {
    if (dirName.isEmpty())
        return;

    QDir dir(dirName);

    if (dir.exists()) {
        updateAllDataLists();
    }
}

void ConfigWidgetImpl::ouputDirNameChanged(const QString&) {
}

void ConfigWidgetImpl::updateAllDataLists() {
    QString dataDir = dataDirEdit->text();
    PitProSettings& settings = PitProSettings::getInstance();

    updateDataList(dataDir, settings.getValue(PitProSettings::ObsSuffix), obsCombo, obsPopup, false);
    updateDataList(dataDir, settings.getValue(PitProSettings::TagSuffix), tagCombo, tagPopup, false);
    updateDataList(dataDir, settings.getValue(PitProSettings::RecapSuffix), recapCombo, rcpPopup, true);
    updateDataList(dataDir, settings.getValue(PitProSettings::MrtSuffix), mortCombo, mrtPopup, true);
}

void ConfigWidgetImpl::updateDataList(const QString& dirPath, const QString& suffix,
        QComboBox* combo, QMenu* popup, bool noneOk) {

    QDir dir(dirPath);
    dir.setFilter(QDir::Files);
    QStringList fileNameFilters;
    if (fileFilterSwitch->isChecked())
        fileNameFilters.append("*." + suffix);
    else
        fileNameFilters.append("*.*");
    dir.setNameFilters(fileNameFilters);

    combo->clear();
    if (noneOk)
        combo->addItem("none");
    combo->addItems(dir.entryList());//insertStringList(dir.entryList());

    if (popup) {
        popup->clear();
        if (noneOk)
            popup->addAction("none");
        QStringList list = dir.entryList();
        for (QStringList::Iterator it = list.begin(); it != list.end(); it++) {
            popup->addAction(*it);
        }
    }
}

/*
 *
 */
void ConfigWidgetImpl::doAddRunButton() {
    int row = checkForDuplicateRun();
    if (row != -1) {
        QMessageBox::information(this, "PitPro",
                "Duplicate run defined at row " + QString::number(row + 1) + ".");
    } else {
        QString runName = runNameEdit->text();
        if (runName.isEmpty()) {
            QMessageBox::information(this, "PitPro", "No population name given.");
            runNameEdit->setFocus();
        } else if (checkForDuplicateRunName(runName)) {
            QMessageBox::information(this, "PitPro", "Duplicate population name found.");
            runNameEdit->setFocus();
        } else {
            runsTable->insertRow(numRuns);//insertRows(numRuns);
            runsTable->item(numRuns, PitProSettings::RUN)->setText(runNameEdit->text());
//            runsTable->setText(numRuns, PitProSettings::RUN, runNameEdit->text());
            runsTable->item(numRuns, PitProSettings::TAG)->setText(tagCombo->currentText());
//            runsTable->setText(numRuns, PitProSettings::TAG, tagCombo->currentText());
            runsTable->item(numRuns, PitProSettings::OBS)->setText(obsCombo->currentText());
//            runsTable->setText(numRuns, PitProSettings::OBS, obsCombo->currentText());
            runsTable->item(numRuns, PitProSettings::RCP)->setText(recapCombo->currentText());
//            runsTable->setText(numRuns, PitProSettings::RCP, recapCombo->currentText());
            runsTable->item(numRuns, PitProSettings::MRT)->setText(mortCombo->currentText());
//            runsTable->setText(numRuns, PitProSettings::MRT, mortCombo->currentText());

            ++numRuns;

            if (numRuns > 1) {
                PitProSettings& settings = PitProSettings::getInstance();
                groupRunsCheckBox->setChecked(settings.isChecked(PitProSettings::GroupRuns));
                groupRunsCheckBox->setEnabled(true);
            }
        }
    }
}

/*
 * Delete selected runs.
 */
void ConfigWidgetImpl::doDeleteRunButton() {
/*    // build an array of selected runs
    QMemArray<int> selected(runsTable->numSelections());
    int i = 0;
    for (int run = 0; run < numRuns; ++run) {
        if (runsTable->isRowSelected(run, false)) {
            selected[ i++ ] = run;
        }
    }
    selected.resize(i);

    // delete selected runs
    runsTable->removeRows(selected);
    numRuns -= selected.size();*/

    for (int run = runsTable->rowCount(); run > 0; run--)
    {
        int index = run - 1;
        if (runsTable->item(index, 0)->isSelected())
            runsTable->removeRow(index);
    }

    if (numRuns < 2) {
        groupRunsCheckBox->setChecked(false);
        groupRunsCheckBox->setEnabled(false);
    }

    // add empty rows to maintain the min number of
    // table rows (for appearance only)
    addTableRows();
}

void ConfigWidgetImpl::addTableRows() {
#if 0
    int numRows = runsTable->numRows();
    if (numRows < BaseNumRows)
        runsTable->insertRows(numRows, BaseNumRows - numRows);
#endif
}

/*
 * If the run defined in the combo boxes is already defined, return
 * the row of the duplicate run definition. Else, return -1.
 */
int ConfigWidgetImpl::checkForDuplicateRun() {
    QString tagFile = tagCombo->currentText();
    QString obsFile = obsCombo->currentText();
    QString rcpFile = recapCombo->currentText();
    QString mrtFile = mortCombo->currentText();

    for (int i = 0; i < numRuns; i++) {
        if (tagFile.compare(runsTable->item(i, PitProSettings::TAG)->text()) == 0 &&
                obsFile.compare(runsTable->item(i, PitProSettings::OBS)->text()) == 0 &&
                rcpFile.compare(runsTable->item(i, PitProSettings::RCP)->text()) == 0 &&
                mrtFile.compare(runsTable->item(i, PitProSettings::MRT)->text()) == 0)
            return i;
    }

    return -1;
}

bool ConfigWidgetImpl::checkForDuplicateRunName(const QString& runName) {
    for (int i = 0; i < numRuns; i++) {
        if (runName.compare(runsTable->item(i, PitProSettings::RUN)->text()) == 0)
            return true;
    }
    return false;
}

/*
 *
 */
void ConfigWidgetImpl::doAddHistFieldButton() {
    QString field = histFieldCombo->currentText();
    histFieldList->addItem(field);
    refreshRelSiteCombo();
    refreshLastFieldCombo();
}

/*
 *
 */
void ConfigWidgetImpl::doAddAdultSiteButton() {
    QString field = adultSiteCombo->currentText();
    adultSiteList->addItem(field);
    refreshLastFieldCombo();
}

/*
 *
 */
void ConfigWidgetImpl::onRelSiteCheckBoxClicked(bool /*rhs*/) {
    refreshLastFieldCombo();
}

/*
 *
 */
void ConfigWidgetImpl::doAddTransSiteButton() {
    QString field = transComboBox->currentText();
    for (int i = 0; i < transSiteList->count(); ++i) {
        if (field.compare(transSiteList->item(i)->text()) == 0)
            return;
    }
    transSiteList->addItem(field);
}

/*
 *
 */
void ConfigWidgetImpl::doHistFieldListMenu(const QPoint& mousePos) {
    QAction *action = histFieldPopup->exec(mousePos);
    QListWidgetItem *item = histFieldList->itemAt(mousePos);

    int index = histFieldList->indexAt(mousePos).row();

    switch (popupActions_.key(action)) {
        case Delete:
            histFieldList->removeItemWidget(item);
            break;
        case MoveUp:
            if (index > 0) {
//                QString text = histFieldList->text(index);
                histFieldList->removeItemWidget(item);
                --index;
                histFieldList->insertItem(index, item);//(text, index);
                histFieldList->setCurrentItem(item);
            }
            break;
        case MoveDown:
            if (index < histFieldList->count() - 1) {
//                QString text = histFieldList->text(index);
                histFieldList->removeItemWidget(item);
                ++index;
                histFieldList->insertItem(index, item);//text, index);
                histFieldList->setCurrentItem(item);
            }
            break;
    }

    refreshRelSiteCombo();
    refreshLastFieldCombo();

}

/*
 *
 */
void ConfigWidgetImpl::doAdultSiteListMenu(const QPoint& mousePos) {
    QAction *action = adultSitePopup->exec(mousePos);
    QListWidgetItem *item = histFieldList->itemAt(mousePos);

    int index = adultSiteList->indexAt(mousePos).row();// index(item);

    switch (popupActions_.key(action)) {
        case Delete:
            adultSiteList->removeItemWidget(item);//(index);
            refreshLastFieldCombo();
            break;
        case MoveUp:
            if (index > 0) {
                adultSiteList->removeItemWidget(item);
                --index;
                adultSiteList->insertItem(index, item);
                adultSiteList->setCurrentItem(item);
/*                QString text = adultSiteList->text(index);
                adultSiteList->removeItem(index);
                --index;
                adultSiteList->insertItem(text, index);
                adultSiteList->setCurrentItem(index);*/
            }
            break;
        case MoveDown:
            if (index < adultSiteList->count() - 1) {
                adultSiteList->removeItemWidget(item);
                ++index;
                adultSiteList->insertItem(index, item);
                adultSiteList->setCurrentItem(item);
/*            if (index < static_cast<int>(adultSiteList->count()) - 1) {
                QString text = adultSiteList->text(index);
                adultSiteList->removeItem(index);
                ++index;
                adultSiteList->insertItem(text, index);
                adultSiteList->setCurrentItem(index);*/
            }
            break;
    }


}

void ConfigWidgetImpl::doTransSiteListMenu(const QPoint& mousePos) {
    QAction *action = transSitePopup->exec(mousePos);
    QListWidgetItem *item = histFieldList->itemAt(mousePos);

//    int index = transSiteList->index(item);
    if (popupActions_.key(action) == Delete)
        transSiteList->removeItemWidget(item);
//        transSiteList->removeItem(index);
}

void ConfigWidgetImpl::doApplyButton() {
    apply();
}

void ConfigWidgetImpl::apply() {
    updateSettings();
}

/*
 *
 */
void ConfigWidgetImpl::restoreDefaults() {
    PitProSettings& settings = PitProSettings::getInstance();
    settings.setDefaults(true);
    updateWidget();
}

/*
 *
 */
void ConfigWidgetImpl::doContextMenuRequested(int row, int col, const QPoint& pt) {
    if (row < numRuns) {
        if (col == PitProSettings::TAG)
            showPopup(pt, tagPopup, row, PitProSettings::TAG);
        else if (col == PitProSettings::OBS)
            showPopup(pt, obsPopup, row, PitProSettings::OBS);
        else if (col == PitProSettings::RCP)
            showPopup(pt, rcpPopup, row, PitProSettings::RCP);
        else if (col == PitProSettings::MRT)
            showPopup(pt, mrtPopup, row, PitProSettings::MRT);
    }
}

/*
 * Show a particular popup
 */
void ConfigWidgetImpl::showPopup(const QPoint& pt, QMenu* popupMenu, int row, int col) {
    if (row >= 0 && col >= 0) {
        QAction *action = popupMenu->exec(pt);
        if (action) {
            const QString& file = action->text();
            if (file != QString::null)
                runsTable->item(row, col)->setText(file);
        }
    }
}

void ConfigWidgetImpl::updateMimeFactory() {
    // Set up the default mime factor for the output data. This allows
    // the data results manager to browse the output directory
/*    QMimeSourceFactory* mf = QMimeSourceFactory::defaultFactory();
    QStringList filePaths;
    PitProSettings& settings = PitProSettings::getInstance();
    filePaths << settings.getValue(PitProSettings::OutputDir).c_str();
    filePaths << settings.getValue(PitProSettings::DataDir).c_str();
    mf->setFilePath(filePaths);
    mf->setExtensionType(settings.getValue(PitProSettings::SurphSuffix).c_str(), "text/utf8");
    mf->setExtensionType(settings.getValue(PitProSettings::SeqSuffix).c_str(), "text/utf8");
    mf->setExtensionType(settings.getValue(PitProSettings::ErrorSuffix).c_str(), "text/utf8");
    mf->setExtensionType(settings.getValue(PitProSettings::TtSuffix).c_str(), "text/utf8");
    mf->setExtensionType(settings.getValue(PitProSettings::DdSuffix).c_str(), "text/utf8");
    mf->setExtensionType(settings.getValue(PitProSettings::CoilSuffix).c_str(), "text/utf8");
    mf->setExtensionType(settings.getValue(PitProSettings::ObsSuffix).c_str(), "text/utf8");
    mf->setExtensionType(settings.getValue(PitProSettings::TagSuffix).c_str(), "text/utf8");
    mf->setExtensionType(settings.getValue(PitProSettings::RelSuffix).c_str(), "text/utf8");
    mf->setExtensionType(settings.getValue(PitProSettings::MrtSuffix).c_str(), "text/utf8");
    mf->setExtensionType(settings.getValue(PitProSettings::RecapSuffix).c_str(), "text/utf8");
*/}

void ConfigWidgetImpl::doCurrentChanged(QWidget* w) {
    refreshTab(w);
}

void ConfigWidgetImpl::dataDirButtonClicked() {
    QString current = dataDirEdit->text();
    QDir dir(current);
    if (!dir.exists())
        current = lastDir;
    QString selected = QFileDialog::getExistingDirectory(0, QString("Select Input Directory"), current);
    if (selected != QString::null) {
        dataDirEdit->setText(selected);
        lastDir = selected;
    }
}

void ConfigWidgetImpl::outDirButtonClicked() {
    QString current = outDirEdit->text();
    QDir dir(current);
    if (!dir.exists())
        current = lastDir;
    QString selected = QFileDialog::getExistingDirectory(0, QString("Select Output Directory"), current);
    if (selected != QString::null) {
        outDirEdit->setText(selected);
        lastDir = selected;
    }
}

struct sites_km_gt : public binary_function<Site*, Site*, bool> {

    bool operator()(Site* a, Site * b) {
        return b->isDownstream(a);
    }
};

struct sites_km_lt : public binary_function<Site*, Site*, bool> {

    bool operator()(Site* a, Site * b) {
        return a->isDownstream(b);
    }
};

void ConfigWidgetImpl::sortJuvenileSitesList() {
    sortSitesList(histFieldList);
    refreshLastFieldCombo();
}

void ConfigWidgetImpl::sortAdultSitesList() {
    sortSitesList(adultSiteList, true);
    refreshLastFieldCombo();
}

void ConfigWidgetImpl::sortTransSitesList() {
    sortSitesList(transSiteList);
}

void ConfigWidgetImpl::sortSitesList(QListWidget* list, bool reverse) {
    Sites* sites = Sites::getInstance();
    vector<Site*> sitesVector;

    int i;
    for (i = 0; i < list->count(); i++) {
        Site* site = sites->getSite(list->item(i)->text());//text(i).ascii());
        if (site)
            sitesVector.push_back(site);
    }

    if (reverse)
        std::sort(sitesVector.begin(), sitesVector.end(), sites_km_lt());
    else
        std::sort(sitesVector.begin(), sitesVector.end(), sites_km_gt());


    QStringList sl;
    for (vector<Site*>::iterator it = sitesVector.begin(); it != sitesVector.end(); ++it) {
        Site* site = *it;
        sl.append(site->getLongName());
    }

    list->clear();
    list->addItems(sl);


}

void ConfigWidgetImpl::versionComboChanged() {
    QString version = surphVersionCombo->currentText();
    if (!version.compare("ROSTER")) {
        lengthCovCheckBox->setEnabled(false);
        zeroCovariateCheckBox->setEnabled(false);
        nullCovariateCheckBox->setEnabled(false);
        groupRunsCheckBox->setEnabled(false);

    }
    else {
        lengthCovCheckBox->setEnabled(true);
        zeroCovariateCheckBox->setEnabled(zeroCovariateCheckBox->isChecked());
        nullCovariateCheckBox->setEnabled(nullCovariateCheckBox->isChecked());
        groupRunsCheckBox->setEnabled(true);

    }
}




