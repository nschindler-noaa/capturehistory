/*
 *
 */


#ifndef PitProWindowImpl_h
#define PitProWindowImpl_h

#include <QMainWindow>

#include "ui_PitProWindow.h"
#include "UpdateManagerImpl.h"
#include <QtEvents>
#include <QCloseEvent>
#include <QPaintEvent>

class QProcess;
class QProgressDialog;

class ConfigWidgetImpl;
//class TextWindowSimple;
class DataConverterImpl;
class ResultsManagerImpl;
class PPComputationThread;
class HelpWindow;
class SitesConfigDialog;

class PitProWindowImpl : public QMainWindow, public Ui::PitProWindow {
    Q_OBJECT

public:
    PitProWindowImpl(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
    virtual ~PitProWindowImpl();

    void customEvent(QEvent* e);
    void paintEvent(QPaintEvent*);
    void closeEvent(QCloseEvent* ce);

public slots:
    void doLoadConfigurationAction();
    void doSaveConfigurationAction();
    void doSaveRunConfigurationAs();
    void doRestoreDefaultsAction();
    void doRunAction();
    void doExitAction();
    void doShowOutputWindowAction();
    void doShowConfigWindowAction();
    void doShowSummaryAction();
    void doCancelRunAction();
    void doShowDataManagerAction();
    void doShowManualAction();
    void doShowInfoAction();
    void cancelRun();
    void refreshConfigWindow();
    void updateStatusSlot(UpdateManagerImpl::Status status);
    void doShowUpdateManagerAction();
    void refreshSitesConfig();
    void doDataConverterAction();
    void onEditSitesConfig();
	void onCheckForUpdates();

private slots:
    void on_actionData_converter_triggered();

private:
    ConfigWidgetImpl* configWidget;
    SitesConfigDialog* sitesConfigDialog;
/*    TextWindowSimple* textWindow;
    TextWindowSimple* warningsWindow;
    TextWindowSimple* configWindow;*/
    QProgressBar* pd;
	ResultsManagerImpl* resultsManager;
	PPComputationThread* run;
//	TextWindowSimple* manWindow;
	DataConverterImpl* dataConverter;
	UpdateManagerImpl* updateManager;


	void allowInput(bool rhs);
	void loadConfig(const QString& fileName);

    QString updater_;
	QProcess *process_;
	void checkForUpdates(const QStringList &args);
};

#endif // PITPROWINDOWIMPL_H
