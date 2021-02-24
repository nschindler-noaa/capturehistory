/*
 * PitProWindowImpl.cpp
 */

#include <string>
#include <sstream>
#include <fstream>

#include <QFile>
#include <QMessageBox>
#include <QWhatsThis>
#include <QFileDialog>
#include <QtEvents>
//#include <QCustomEvent>
#include <QCloseEvent>
#include <QPaintEvent>
#include <QStringList>
#include <QList>
#include <QProcess>

#include <qaction.h>
#include <qinputdialog.h>
#include <qevent.h>
#include <qlabel.h>
#include <qprogressbar.h>
#include <qtextstream.h>

#include <Sites.h>
#include <charutil.h>
#include <ComputationEvent.h>
#include <DateConverter.h>
#include <HelpWindow.h>
#include <TextWindowSimple.h>

#include "PitProWindowImpl.h"
#include "PitProSettings.h"
#include "PPComputationThread.h"
#include "ConfigWidgetImpl.h"
#include "SitesConfigDialog.h"
#include "ResultsManagerImpl.h"
#include "InfoDialog.h"
#include "PPVersion.h"
#include "UpdateManagerImpl.h"
#include "DataConverterImpl.h"
#include "PPSystemSettings.h"


using std::string;
using std::stringstream;
using std::ends;
using std::endl;
using std::ifstream;
using std::ofstream;

using cbr::DateConverter;

/* 
 * Constructor
 */
PitProWindowImpl::PitProWindowImpl(QWidget* parent, const char* name, Qt::WindowFlags fl)
: QMainWindow(parent, fl)
{
    setObjectName(name);
    configWidget = nullptr;
    sitesConfigDialog = nullptr;
//    textWindow = NULL;
//    warningsWindow = NULL;
//    configWindow = NULL;
    pd = nullptr;
    resultsManager = nullptr;
    run = nullptr;
    dataConverter = nullptr;
    updateManager = nullptr;
    process_ = nullptr;
    updater_.append("updater.exe");
    setupUi(this);

    // get last config file and load it
    PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
    loadConfig(systemSettings.get(PPSystemSettings::ConfigFile).toString());

    // sites config dialog
    sitesConfigDialog = new SitesConfigDialog(this);
    sitesConfigDialog->refreshSitesConfig();

    // set the central widget to the configwidget
    configWidget = new ConfigWidgetImpl(this);
    setCentralWidget(configWidget);
    configWidget->show();

    // create text window
/*    textWindow = new TextWindowSimple(0);
    textWindow->setWindowTitle("PitPro Status");
    textWindow->appendText("PitPro - PIT tag data processor");
    textWindow->appendText("-------------------------------");
    textWindow->appendText("");*/

    // progress dialog
    pd = new QProgressBar(this);//, 0, false);
//    pd->setAutoClose(false);
    connect(pd, SIGNAL(canceled()), SLOT(cancelRun()));

    // initialize the manual window
    if (!QFile::exists("doc/index.html"))
        showManualAction->setVisible(false);
    else {
        // to do
/*        showManualAction->setEnabled(true);
        manWindow = new TextWindowSimple(0);
        manWindow->setWindowTitle("Design3D Manual");
//        manWindow->setCaption("Design3D Manual");
        QTextBrowser *browser = manWindow->textBrowser;
        //browser->mimeSourceFactory()->setFilePath("doc");
        browser->setSource(QUrl("qrc:/docs/index.html"));*/
    }

    // check for newer versions
    actionUpdate_available->setVisible(false);
    updateManager = new UpdateManagerImpl(this, "UpdateManager");

    // create run object
    run = new PPComputationThread(this, "CaptHist");

    // create the results manager object
    resultsManager = new ResultsManagerImpl(0);
    if (resultsManager) {
        QStringList trackedPits;
        PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
        QList<QVariant> trackedPitList = systemSettings.readArray(PPSystemSettings::TrackedPits);
        for (QList<QVariant>::iterator it = trackedPitList.begin(); it != trackedPitList.end(); ++it)
            trackedPits << (*it).toString();
        resultsManager->setTrackedPits(trackedPits);

        QString prefix = systemSettings.get(PPSystemSettings::Prefix).toString();
        if (!prefix.isEmpty())
            resultsManager->setSelectedPrefix(prefix);
    }

    // what this toolbar button
    toolbar->addAction(QWhatsThis::createAction(this));

    // signals and slots connections
    connect(configWidget, SIGNAL(outputDirChanged(const QString&)),
            resultsManager, SLOT(outputDirChanged(const QString&)));
    connect(updateManager, SIGNAL(updateStatus(UpdateManagerImpl::Status)),
            this, SLOT(updateStatusSlot(UpdateManagerImpl::Status)));
    connect(updateManager, SIGNAL(sitesConfigUpdated()),
            this, SLOT(refreshSitesConfig()));
    connect(cancelRunAction, SIGNAL(activated()), this, SLOT(doCancelRunAction()));
    connect(exitAction, SIGNAL(activated()), this, SLOT(doExitAction()));
    connect(loadConfigAction, SIGNAL(activated()), this, SLOT(doLoadConfigurationAction()));
    connect(restoreDefaultsAction, SIGNAL(activated()), this, SLOT(doRestoreDefaultsAction()));
    connect(runAction, SIGNAL(activated()), this, SLOT(doRunAction()));
    connect(saveConfigAction, SIGNAL(activated()), this, SLOT(doSaveConfigurationAction()));
    connect(fileSave_run_configuration_asAction, SIGNAL(activated()), this, SLOT(doSaveRunConfigurationAs()));
    connect(editSitesConfigAction, SIGNAL(activated()), this, SLOT(onEditSitesConfig()));
    connect(showSitesConfigAction, SIGNAL(activated()), this, SLOT(doShowConfigWindowAction()));
    connect(showInfoAction, SIGNAL(activated()), this, SLOT(doShowInfoAction()));
    connect(showManualAction, SIGNAL(activated()), this, SLOT(doShowManualAction()));
    connect(showOutputWindowAction, SIGNAL(activated()), this, SLOT(doShowOutputWindowAction()));
    connect(showSummariesAction, SIGNAL(activated()), this, SLOT(doShowSummaryAction()));
    connect(showUpdateManagerAction, SIGNAL(activated()), this, SLOT(doShowUpdateManagerAction()));
    connect(actionUpdate_available, SIGNAL(activated()), this, SLOT(doShowUpdateManagerAction()));
    connect(actionData_converter, SIGNAL(activated()), this, SLOT(doDataConverterAction()));
    connect(sitesConfigDialog, SIGNAL(siteConfigChanged()), configWidget, SLOT(refreshSitesTab()));
    connect(sitesConfigDialog, SIGNAL(siteConfigChanged()), SLOT(refreshConfigWindow()));


    QFile updater(updater_);
    if (updater.exists())
    {
        connect(checkForUpdatesAction, SIGNAL(activated()), SLOT(onCheckForUpdates()));
        checkForUpdates(QStringList() << "/silent");
    }
    else
    {
        checkForUpdatesAction->setEnabled(false);
    }
}

/*
 *  Destroys the object and frees any allocated resources
 */
PitProWindowImpl::~PitProWindowImpl() {
    if (resultsManager) {
        PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
        QStringList trackedPits = resultsManager->getTrackedPits();
        QList<QVariant> trackedPitList;
        for (QStringList::iterator it = trackedPits.begin(); it != trackedPits.end(); ++it)
            trackedPitList << *it;
        systemSettings.writeArray(PPSystemSettings::TrackedPits, trackedPitList);
        QString prefix = resultsManager->getSelectedPrefix();
        systemSettings.set(PPSystemSettings::Prefix, prefix);
    }

    // no need to delete child widgets, Qt does it all for us
//    delete textWindow;
//    delete configWindow;
    delete run;
    delete resultsManager;
    delete sitesConfigDialog;
}

void PitProWindowImpl::onCheckForUpdates() {
    checkForUpdates(QStringList() << "/checknow");
}

void PitProWindowImpl::checkForUpdates(const QStringList &args) {
    if (!process_)
        process_ = new QProcess(this);
    process_->start(updater_, args);
}

void PitProWindowImpl::refreshSitesConfig() {
    // initialize sites
    if (sitesConfigDialog)
        sitesConfigDialog->doSitesConfigSettingsChanged();

    if (updateManager)
        updateManager->refresh();
}

void PitProWindowImpl::onEditSitesConfig() {
    sitesConfigDialog->show();
    sitesConfigDialog->raise();
}

/*
 * Gray out the menus and buttons to suspend certain user input
 * while a run is active.
 */
void PitProWindowImpl::allowInput(bool rhs) {
    runAction->setEnabled(rhs);
}

/*
 *
 */
void PitProWindowImpl::doLoadConfigurationAction() {
    PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
    QString dataDir = systemSettings.get(PPSystemSettings::DataDir).toString();

    QString fileName =
            QFileDialog::getOpenFileName(this, "Open File", dataDir, "PitPro Config (*.ppc);;All files (*.*)");
//            QFileDialog::getOpenFileName(dataDir, "PitPro Config (*.ppc);;All files (*.*)", this);
    if (!fileName.isEmpty()) {
        loadConfig(fileName);

        if (configWidget) {
            configWidget->updateWidget();
            configWidget->updateMimeFactory();
        }

        if (resultsManager)
            resultsManager->setStale(true);
    }
}

void PitProWindowImpl::loadConfig(const QString& filePath) {
    if (filePath.isNull())
        return;

    PitProSettings& settings = PitProSettings::getInstance();
    settings.clear();
    settings.readSettings(filePath);
//    settings.readSettings(filePath.ascii());
    settings.setDefaults(); // fill in any missing parameters with defaults

    PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
    systemSettings.set(PPSystemSettings::DataDir, filePath);
    systemSettings.set(PPSystemSettings::ConfigFile, filePath);

    //this->set
    QString fileName = filePath.section("/", -1, -1);
    setWindowTitle("PitPro (" + fileName + ")");
}

/*
 *
 */
void PitProWindowImpl::doSaveConfigurationAction() {
    PitProSettings& settings = PitProSettings::getInstance();
    QString lastSettingsFile = settings.getLastSettingsFile();
    if (lastSettingsFile.isEmpty())
        doSaveRunConfigurationAs();
    else {
        if (configWidget) {
            configWidget->updateSettings();
            settings.writeSettings();
            PPSystemSettings::getInstance().set(PPSystemSettings::ConfigFile, lastSettingsFile);
        }
    }
}

/*
 *
 */
void PitProWindowImpl::doSaveRunConfigurationAs() {
    PitProSettings& settings = PitProSettings::getInstance();
    QString lastSettingsFile = settings.getLastSettingsFile();
    QString filePath =
        QFileDialog::getSaveFileName((QWidget *)this, "Save File", lastSettingsFile, "PitPro Config (*.ppc);;All files (*.*)");
//            QFileDialog::getSaveFileName(lastSettingsFile.c_str(), "PitPro Config (*.ppc);;All files (*.*)", this);

    if (filePath.isNull())
        return;

    if (!filePath.contains('.'))
        filePath += ".ppc";

    if (configWidget)
        configWidget->updateSettings();
    settings.writeSettings(filePath);
//    settings.writeSettings(filePath.ascii());
    PPSystemSettings::getInstance().set(PPSystemSettings::ConfigFile, filePath);

    QString fileName = filePath.section("/", -1, -1);
    setWindowTitle("PitPro (" + fileName + ")");
}

/*
 *
 */
void PitProWindowImpl::doRunAction() {
    configWidget->updateSettings();
    if (configWidget->getNumRuns() == 0)
        QMessageBox::critical(this, "PitPro", "No runs defined!");
    else {
        PitProSettings& settings = PitProSettings::getInstance();

        if (!settings.verify()) {
            QMessageBox::critical(this, "PitPro", settings.getLastError());
        } else {
            allowInput(false);
//            textWindow->show();
//            textWindow->raise();
            pd->show();
            run->setStatus(ComputationThread::Ok);
            run->start();
        }
    }
}

/*
 *
 */
void PitProWindowImpl::doRestoreDefaultsAction() {
    if (configWidget) {
        int answer = QMessageBox::warning(this, "PitPro", "Return settings to defaults?",
                QMessageBox::Ok, QMessageBox::Cancel);

        if (answer == QMessageBox::Ok) {
            configWidget->restoreDefaults();
        }

    }
}

/*
 *
 */
void PitProWindowImpl::doExitAction() {
    close(); // cause a call to closeEvent handler
}

void PitProWindowImpl::closeEvent(QCloseEvent* ce) {
    if (!run || !run->isRunning())
        ce->accept();
    else {
        int ans = QMessageBox::information(this, "PitPro",
                "Currently processing run. Cancel anyway?", QMessageBox::Yes, QMessageBox::No);
        if (ans == QMessageBox::Yes)
            ce->accept();
        else
            ce->ignore();
    }
}

/*
 * Show the summary dialog that allows the user to look at the
 * results in summary form
 */
void PitProWindowImpl::doShowSummaryAction() {
    configWidget->apply();

    if (resultsManager) {
        resultsManager->setStale(true);
        resultsManager->show();
        resultsManager->raise();
    }
}

/*
 * Show the output window.
 */
void PitProWindowImpl::doShowOutputWindowAction() {
//    textWindow->show();
//    textWindow->raise();
}

/*
 * Show the output window.
 */
void PitProWindowImpl::doShowConfigWindowAction() {
/*    if (!configWindow) {
        configWindow = new TextWindowSimple(0);
        configWindow->setWindowTitle("PitPro Sites Configuration");
        refreshConfigWindow();
    }

    if (configWindow) {
        configWindow->show();
        configWindow->raise();
    }
*/
}

void PitProWindowImpl::refreshConfigWindow() {
/*    if (configWindow) {
        stringstream ss;
        DateConverter dc;
        dc.setDateFormat(DateConverter::B);

        ss << "#" << endl;
        ss << "# report date: " << dc << endl;

        Sites* sites = Sites::getInstance();
        ss << *sites << ends;
        configWindow->setText(ss.str().c_str());

        if (configWindow->isVisible())
            configWindow->raise();
    }*/

    updateManager->refresh();
}

void PitProWindowImpl::cancelRun() {
    if (run->isRunning()) {
        run->setStatus(PPComputationThread::Cancel);
    }
}

/*
 * Cancel the current run.
 */
void PitProWindowImpl::doCancelRunAction() {
    if (!run->isRunning()) {
        QMessageBox::critical(this, "PitPro", "No run to cancel!");
    } else {
        int ans = QMessageBox::information(this, "PitPro",
                "Cancel run?", QMessageBox::Yes, QMessageBox::No);
        if (ans == QMessageBox::Yes)
            cancelRun();
    }

}

/*
 * Show the data manger
 */
void PitProWindowImpl::doShowDataManagerAction() {
}

/*
 * Show the user manual.
 */
void PitProWindowImpl::doShowManualAction() {
    /*if (manWindow) {
        manWindow->show();
        manWindow->raise();
    }*/
}

/*
 * Show the about dialog
 */
void PitProWindowImpl::doShowInfoAction() {
    PPSystemSettings &settings = PPSystemSettings::getInstance();
    InfoDialog* dlg = new InfoDialog(this);
    dlg->versionLabel->setText(settings.get(PPSystemSettings::Version).toString());
    dlg->exec();
    delete dlg;
}

void PitProWindowImpl::customEvent(QEvent* e) {
    ComputationEvent* ce = (ComputationEvent*) e;
    const QString& name = ce->getRunName();

    if (ce->type() == static_cast<QEvent::Type>(ComputationEvent::Completed)||
            ce->type() == static_cast<QEvent::Type>(ComputationEvent::Canceled))  {

        if (!name.compare("CaptHist")) {
            allowInput(true);
            pd->reset();
            pd->close();

            if (ce->type() == static_cast<QEvent::Type>(ComputationEvent::Completed)) {
                if (resultsManager) {
                    PitProSettings& settings = PitProSettings::getInstance();
                    if (settings.isChecked(PitProSettings::GroupRuns))
                        resultsManager->setGroup(settings.getValue(PitProSettings::OutPrefix));
                    else
                        resultsManager->setGroup(settings.getPrefix(0));

                    resultsManager->setStale(true);
                    resultsManager->show();
                    resultsManager->raise();
                }
            }
        }

        // some of the settings may have be forcibly changed during the run,
        // update the config widget
        if (configWidget)
            configWidget->updateWidget();

    } else if (ce->type() == static_cast<QEvent::Type>(ComputationEvent::Status)) {
        //textWindow->appendText(ce->getMessage());
    } else if (ce->type() == static_cast<QEvent::Type>(ComputationEvent::Error))  {
        //textWindow->appendText(ce->getMessage());
        QMessageBox msgBox;
        msgBox.setText(ce->getMessage());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setTextFormat(Qt::RichText);
        msgBox.exec();
    } else if (ce->type() == static_cast<QEvent::Type>(ComputationEvent::Progress)) {
//        pd->setLabelText(ce->getMessage());
    } else if (ce->type() == static_cast<QEvent::Type>(ComputationEvent::NumSteps))  {
        pd->reset();
//        pd->setTotalSteps(ce->getNumSteps());
    } else if (ce->type() == static_cast<QEvent::Type>(ComputationEvent::CurrentStep))  {
//        pd->setProgress(ce->getCurrentStep());
    }
}

void PitProWindowImpl::paintEvent(QPaintEvent*) {


}

void PitProWindowImpl::updateStatusSlot(UpdateManagerImpl::Status status) {
    if (status == UpdateManagerImpl::OutOfDate) {
        actionUpdate_available->setVisible(true);
    } else {
        actionUpdate_available->setVisible(false);
    }
}

void PitProWindowImpl::doShowUpdateManagerAction() {
    if (updateManager) {
        updateManager->show();
        updateManager->raise();
    }
}

void PitProWindowImpl::doDataConverterAction() {
    if (!dataConverter) {
        configWidget->updateWidget();
        dataConverter = new DataConverterImpl(this);
        connect(dataConverter, SIGNAL(dataConverted()),
                configWidget, SLOT(updateAllDataLists()));
        connect(configWidget, SIGNAL(dataDirChanged(const QString&)),
                dataConverter, SLOT(dataDirChanged(const QString&)));
    }
    dataConverter->show();
    dataConverter->raise();

}

void PitProWindowImpl::on_actionData_converter_triggered() {

}
