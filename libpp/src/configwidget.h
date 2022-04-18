#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include "PPOutputMaker.h"

#include <QWidget>
#include <QStringList>
#include <QDir>
#include <QMenu>
#include <QPoint>
#include <QMap>

#include <QComboBox>
#include <QListWidget>

namespace Ui {
class ConfigWidget;
}

class ConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigWidget(QWidget *parent = 0);
    ~ConfigWidget();

    int getNumRuns() { return numRuns; }
    void restoreDefaults();

public slots:
    void apply();
    void updateWidget();
    void updateSettings();
    void dataDirNameChanged(const QString&);
    void ouputDirNameChanged(const QString&);
    void doAddRunButton();
    void doDeleteRunButton();
    void doAddHistFieldButton();
    void doAddAdultSiteButton();
    void doAddTransSiteButton();
    void doHistFieldListMenu(const QPoint&);
    void doAdultSiteListMenu(const QPoint&);
    void doTransSiteListMenu(const QPoint&);
    void doApplyButton();
    void doContextMenuRequested(int,int,const QPoint&);
    void doCurrentChanged(QWidget*);
    void onRelSiteCheckBoxClicked(bool rhs);
    void refreshCurrentTab();
    void refreshTab( QWidget* w );
    void refreshRunSetupTab();
    void refreshRelSiteCombo();
    void refreshLastFieldCombo();
    void refreshTransSitesList();
    void refreshHistLists();
    void updateMimeFactory();
    void dataDirButtonClicked();
    void outDirButtonClicked();
    void sortJuvenileSitesList();
    void sortAdultSitesList();
    void sortTransSitesList();
    void emitDataDirChanged(const QString&);
    void emitOutputDirChanged(const QString&);
    void updateAllDataLists();
    void versionComboChanged();
    void refreshSitesTab();


private:
    Ui::ConfigWidget *ui;

    enum PopupMenu { Delete = 0, MoveUp, MoveDown };
    QMap<int, QAction*> popupActions_;

    const int BaseNumRows;

    int numRuns;
    int checkForDuplicateRun();
    bool checkForDuplicateRunName( const QString& runName );

    QMenu* histFieldPopup;
    QMenu* adultSitePopup;
    QMenu* transSitePopup;

    QMenu* tagPopup; // these menus popup when the user clicks...
    QMenu* obsPopup;
    QMenu* rcpPopup;
    QMenu* mrtPopup;
    QMenu* relPopup;
    void showPopup( const QPoint& pt, QMenu* popup, int row, int col);


    QString lastDir;

    void updateDataList( const QString& dirPath, const QString& suffix, QComboBox* combo, QMenu* popup, bool noneOk);

    // refresh tab stuff

    void refreshErrorCheckingTab();
    void refreshFilesTab();
    void refreshTransTab();
    void refreshAdultCriteriaTab();
    void refreshAdvancedTab();

    void addTableRows();

    void sortSitesList(QListWidget *list, bool reverse = false);

signals:
    void dataDirChanged(const QString&);
    void outputDirChanged(const QString&);

};

#endif // CONFIGWIDGET_H
