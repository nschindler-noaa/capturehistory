/********************************************************************************
** Form generated from reading UI file 'PitProWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PITPROWINDOW_H
#define UI_PITPROWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

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
            PitProWindow->setObjectName(QStringLiteral("PitProWindow"));
        PitProWindow->resize(640, 480);
        runAction = new QAction(PitProWindow);
        runAction->setObjectName(QStringLiteral("runAction"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/misc.png"), QSize(), QIcon::Normal, QIcon::Off);
        runAction->setIcon(icon);
        cancelRunAction = new QAction(PitProWindow);
        cancelRunAction->setObjectName(QStringLiteral("cancelRunAction"));
        loadConfigAction = new QAction(PitProWindow);
        loadConfigAction->setObjectName(QStringLiteral("loadConfigAction"));
        saveConfigAction = new QAction(PitProWindow);
        saveConfigAction->setObjectName(QStringLiteral("saveConfigAction"));
        fileSave_run_configuration_asAction = new QAction(PitProWindow);
        fileSave_run_configuration_asAction->setObjectName(QStringLiteral("fileSave_run_configuration_asAction"));
        exitAction = new QAction(PitProWindow);
        exitAction->setObjectName(QStringLiteral("exitAction"));
        actionData_converter = new QAction(PitProWindow);
        actionData_converter->setObjectName(QStringLiteral("actionData_converter"));
        showSitesConfigAction = new QAction(PitProWindow);
        showSitesConfigAction->setObjectName(QStringLiteral("showSitesConfigAction"));
        showOutputWindowAction = new QAction(PitProWindow);
        showOutputWindowAction->setObjectName(QStringLiteral("showOutputWindowAction"));
        showSummariesAction = new QAction(PitProWindow);
        showSummariesAction->setObjectName(QStringLiteral("showSummariesAction"));
        showManualAction = new QAction(PitProWindow);
        showManualAction->setObjectName(QStringLiteral("showManualAction"));
        showUpdateManagerAction = new QAction(PitProWindow);
        showUpdateManagerAction->setObjectName(QStringLiteral("showUpdateManagerAction"));
        showInfoAction = new QAction(PitProWindow);
        showInfoAction->setObjectName(QStringLiteral("showInfoAction"));
        restoreDefaultsAction = new QAction(PitProWindow);
        restoreDefaultsAction->setObjectName(QStringLiteral("restoreDefaultsAction"));
        actionUpdate_available = new QAction(PitProWindow);
        actionUpdate_available->setObjectName(QStringLiteral("actionUpdate_available"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/messagebox_warning.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUpdate_available->setIcon(icon1);
        editSitesConfigAction = new QAction(PitProWindow);
        editSitesConfigAction->setObjectName(QStringLiteral("editSitesConfigAction"));
        checkForUpdatesAction = new QAction(PitProWindow);
        checkForUpdatesAction->setObjectName(QStringLiteral("checkForUpdatesAction"));
        centralWidget = new QWidget(PitProWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PitProWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PitProWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 640, 21));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuOutput = new QMenu(menuBar);
        menuOutput->setObjectName(QStringLiteral("menuOutput"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuData = new QMenu(menuBar);
        menuData->setObjectName(QStringLiteral("menuData"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        PitProWindow->setMenuBar(menuBar);
        toolbar = new QToolBar(PitProWindow);
        toolbar->setObjectName(QStringLiteral("toolbar"));
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
        PitProWindow->setWindowTitle(QApplication::translate("PitProWindow", "MainWindow", Q_NULLPTR));
        runAction->setText(QApplication::translate("PitProWindow", "Run PitPro", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        runAction->setWhatsThis(QApplication::translate("PitProWindow", "Run the program using the current configuration.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        cancelRunAction->setText(QApplication::translate("PitProWindow", "Cancel run", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        cancelRunAction->setWhatsThis(QApplication::translate("PitProWindow", "Cancel the current run.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        loadConfigAction->setText(QApplication::translate("PitProWindow", "Load run configuration file...", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        loadConfigAction->setWhatsThis(QApplication::translate("PitProWindow", "Load a configuration from file.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        saveConfigAction->setText(QApplication::translate("PitProWindow", "Save run configuration", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        saveConfigAction->setWhatsThis(QApplication::translate("PitProWindow", "Save the current run configuration with the current configuration name.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        fileSave_run_configuration_asAction->setText(QApplication::translate("PitProWindow", "Save run configuration as...", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        fileSave_run_configuration_asAction->setWhatsThis(QApplication::translate("PitProWindow", "Save the run configuration with a new name.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        exitAction->setText(QApplication::translate("PitProWindow", "Exit", Q_NULLPTR));
        actionData_converter->setText(QApplication::translate("PitProWindow", "Data converter...", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        actionData_converter->setWhatsThis(QApplication::translate("PitProWindow", "Show the data converter.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        showSitesConfigAction->setText(QApplication::translate("PitProWindow", "Show current sites configuration...", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        showSitesConfigAction->setWhatsThis(QApplication::translate("PitProWindow", "Show the sites configuration.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        showOutputWindowAction->setText(QApplication::translate("PitProWindow", "Show status window...", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        showOutputWindowAction->setWhatsThis(QApplication::translate("PitProWindow", "Show the program message console.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        showSummariesAction->setText(QApplication::translate("PitProWindow", "Results manager...", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        showSummariesAction->setWhatsThis(QApplication::translate("PitProWindow", "Show the data manager.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        showManualAction->setText(QApplication::translate("PitProWindow", "Manual...", Q_NULLPTR));
        showUpdateManagerAction->setText(QApplication::translate("PitProWindow", "Check for configuration updates...", Q_NULLPTR));
        showInfoAction->setText(QApplication::translate("PitProWindow", "About...", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        showInfoAction->setWhatsThis(QApplication::translate("PitProWindow", "Show program information.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        restoreDefaultsAction->setText(QApplication::translate("PitProWindow", "Restore defaults", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        restoreDefaultsAction->setWhatsThis(QApplication::translate("PitProWindow", "Restore the settings to program defaults.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        actionUpdate_available->setText(QApplication::translate("PitProWindow", "Update available", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        actionUpdate_available->setWhatsThis(QApplication::translate("PitProWindow", "This icon indicates that an update is available, either for the program, or for the sites configuration file. Click this toolbar icon to bring up the update manager.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        editSitesConfigAction->setText(QApplication::translate("PitProWindow", "Select active sites configuration...", Q_NULLPTR));
        checkForUpdatesAction->setText(QApplication::translate("PitProWindow", "Check for updates", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("PitProWindow", "Help", Q_NULLPTR));
        menuOutput->setTitle(QApplication::translate("PitProWindow", "Output", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("PitProWindow", "Edit", Q_NULLPTR));
        menuData->setTitle(QApplication::translate("PitProWindow", "Sites", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("PitProWindow", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PitProWindow: public Ui_PitProWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PITPROWINDOW_H
