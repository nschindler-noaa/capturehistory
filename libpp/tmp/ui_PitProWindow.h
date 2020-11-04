/********************************************************************************
** Form generated from reading UI file 'PitProWindow.ui'
**
** Created: Mon Nov 2 11:21:14 2020
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PITPROWINDOW_H
#define UI_PITPROWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PitProWindow
{
public:
    QAction *runAction;
    QAction *cancelRunAction;
    QAction *loadConfigAction;
    QAction *saveConfigAction;
    QAction *fileSave_run_configuration_asAction;
    QAction *exitAction;
    QAction *actionData_converter;
    QAction *showSitesConfigAction;
    QAction *showOutputWindowAction;
    QAction *showSummariesAction;
    QAction *showManualAction;
    QAction *showUpdateManagerAction;
    QAction *showInfoAction;
    QAction *restoreDefaultsAction;
    QAction *actionUpdate_available;
    QAction *editSitesConfigAction;
    QAction *checkForUpdatesAction;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QMenu *menuOutput;
    QMenu *menuEdit;
    QMenu *menuData;
    QMenu *menuFile;
    QToolBar *toolbar;

    void setupUi(QMainWindow *PitProWindow)
    {
        if (PitProWindow->objectName().isEmpty())
            PitProWindow->setObjectName(QString::fromUtf8("PitProWindow"));
        PitProWindow->resize(640, 480);
        runAction = new QAction(PitProWindow);
        runAction->setObjectName(QString::fromUtf8("runAction"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/misc.png"), QSize(), QIcon::Normal, QIcon::Off);
        runAction->setIcon(icon);
        cancelRunAction = new QAction(PitProWindow);
        cancelRunAction->setObjectName(QString::fromUtf8("cancelRunAction"));
        loadConfigAction = new QAction(PitProWindow);
        loadConfigAction->setObjectName(QString::fromUtf8("loadConfigAction"));
        saveConfigAction = new QAction(PitProWindow);
        saveConfigAction->setObjectName(QString::fromUtf8("saveConfigAction"));
        fileSave_run_configuration_asAction = new QAction(PitProWindow);
        fileSave_run_configuration_asAction->setObjectName(QString::fromUtf8("fileSave_run_configuration_asAction"));
        exitAction = new QAction(PitProWindow);
        exitAction->setObjectName(QString::fromUtf8("exitAction"));
        actionData_converter = new QAction(PitProWindow);
        actionData_converter->setObjectName(QString::fromUtf8("actionData_converter"));
        showSitesConfigAction = new QAction(PitProWindow);
        showSitesConfigAction->setObjectName(QString::fromUtf8("showSitesConfigAction"));
        showOutputWindowAction = new QAction(PitProWindow);
        showOutputWindowAction->setObjectName(QString::fromUtf8("showOutputWindowAction"));
        showSummariesAction = new QAction(PitProWindow);
        showSummariesAction->setObjectName(QString::fromUtf8("showSummariesAction"));
        showManualAction = new QAction(PitProWindow);
        showManualAction->setObjectName(QString::fromUtf8("showManualAction"));
        showUpdateManagerAction = new QAction(PitProWindow);
        showUpdateManagerAction->setObjectName(QString::fromUtf8("showUpdateManagerAction"));
        showInfoAction = new QAction(PitProWindow);
        showInfoAction->setObjectName(QString::fromUtf8("showInfoAction"));
        restoreDefaultsAction = new QAction(PitProWindow);
        restoreDefaultsAction->setObjectName(QString::fromUtf8("restoreDefaultsAction"));
        actionUpdate_available = new QAction(PitProWindow);
        actionUpdate_available->setObjectName(QString::fromUtf8("actionUpdate_available"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/messagebox_warning.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUpdate_available->setIcon(icon1);
        editSitesConfigAction = new QAction(PitProWindow);
        editSitesConfigAction->setObjectName(QString::fromUtf8("editSitesConfigAction"));
        checkForUpdatesAction = new QAction(PitProWindow);
        checkForUpdatesAction->setObjectName(QString::fromUtf8("checkForUpdatesAction"));
        centralWidget = new QWidget(PitProWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        PitProWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PitProWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 640, 21));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuOutput = new QMenu(menuBar);
        menuOutput->setObjectName(QString::fromUtf8("menuOutput"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuData = new QMenu(menuBar);
        menuData->setObjectName(QString::fromUtf8("menuData"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        PitProWindow->setMenuBar(menuBar);
        toolbar = new QToolBar(PitProWindow);
        toolbar->setObjectName(QString::fromUtf8("toolbar"));
        toolbar->setOrientation(Qt::Horizontal);
        PitProWindow->addToolBar(Qt::TopToolBarArea, toolbar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuData->menuAction());
        menuBar->addAction(menuOutput->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(showManualAction);
        menuHelp->addAction(checkForUpdatesAction);
        menuHelp->addSeparator();
        menuHelp->addAction(showInfoAction);
        menuOutput->addAction(showOutputWindowAction);
        menuOutput->addSeparator();
        menuOutput->addAction(showSummariesAction);
        menuEdit->addAction(restoreDefaultsAction);
        menuData->addAction(editSitesConfigAction);
        menuData->addAction(showSitesConfigAction);
        menuData->addSeparator();
        menuData->addAction(showUpdateManagerAction);
        menuFile->addAction(runAction);
        menuFile->addAction(cancelRunAction);
        menuFile->addSeparator();
        menuFile->addAction(loadConfigAction);
        menuFile->addAction(saveConfigAction);
        menuFile->addAction(fileSave_run_configuration_asAction);
        menuFile->addSeparator();
        menuFile->addAction(exitAction);
        toolbar->addAction(runAction);
        toolbar->addAction(actionUpdate_available);

        retranslateUi(PitProWindow);

        QMetaObject::connectSlotsByName(PitProWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PitProWindow)
    {
        PitProWindow->setWindowTitle(QApplication::translate("PitProWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        runAction->setText(QApplication::translate("PitProWindow", "Run PitPro", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        runAction->setWhatsThis(QApplication::translate("PitProWindow", "Run the program using the current configuration.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        cancelRunAction->setText(QApplication::translate("PitProWindow", "Cancel run", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        cancelRunAction->setWhatsThis(QApplication::translate("PitProWindow", "Cancel the current run.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        loadConfigAction->setText(QApplication::translate("PitProWindow", "Load run configuration file...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        loadConfigAction->setWhatsThis(QApplication::translate("PitProWindow", "Load a configuration from file.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        saveConfigAction->setText(QApplication::translate("PitProWindow", "Save run configuration", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        saveConfigAction->setWhatsThis(QApplication::translate("PitProWindow", "Save the current run configuration with the current configuration name.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        fileSave_run_configuration_asAction->setText(QApplication::translate("PitProWindow", "Save run configuration as...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        fileSave_run_configuration_asAction->setWhatsThis(QApplication::translate("PitProWindow", "Save the run configuration with a new name.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        exitAction->setText(QApplication::translate("PitProWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionData_converter->setText(QApplication::translate("PitProWindow", "Data converter...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        actionData_converter->setWhatsThis(QApplication::translate("PitProWindow", "Show the data converter.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        showSitesConfigAction->setText(QApplication::translate("PitProWindow", "Show current sites configuration...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        showSitesConfigAction->setWhatsThis(QApplication::translate("PitProWindow", "Show the sites configuration.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        showOutputWindowAction->setText(QApplication::translate("PitProWindow", "Show status window...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        showOutputWindowAction->setWhatsThis(QApplication::translate("PitProWindow", "Show the program message console.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        showSummariesAction->setText(QApplication::translate("PitProWindow", "Results manager...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        showSummariesAction->setWhatsThis(QApplication::translate("PitProWindow", "Show the data manager.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        showManualAction->setText(QApplication::translate("PitProWindow", "Manual...", 0, QApplication::UnicodeUTF8));
        showUpdateManagerAction->setText(QApplication::translate("PitProWindow", "Check for configuration updates...", 0, QApplication::UnicodeUTF8));
        showInfoAction->setText(QApplication::translate("PitProWindow", "About...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        showInfoAction->setWhatsThis(QApplication::translate("PitProWindow", "Show program information.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        restoreDefaultsAction->setText(QApplication::translate("PitProWindow", "Restore defaults", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        restoreDefaultsAction->setWhatsThis(QApplication::translate("PitProWindow", "Restore the settings to program defaults.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionUpdate_available->setText(QApplication::translate("PitProWindow", "Update available", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        actionUpdate_available->setWhatsThis(QApplication::translate("PitProWindow", "This icon indicates that an update is available, either for the program, or for the sites configuration file. Click this toolbar icon to bring up the update manager.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        editSitesConfigAction->setText(QApplication::translate("PitProWindow", "Select active sites configuration...", 0, QApplication::UnicodeUTF8));
        checkForUpdatesAction->setText(QApplication::translate("PitProWindow", "Check for updates", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("PitProWindow", "Help", 0, QApplication::UnicodeUTF8));
        menuOutput->setTitle(QApplication::translate("PitProWindow", "Output", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("PitProWindow", "Edit", 0, QApplication::UnicodeUTF8));
        menuData->setTitle(QApplication::translate("PitProWindow", "Sites", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("PitProWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PitProWindow: public Ui_PitProWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PITPROWINDOW_H
