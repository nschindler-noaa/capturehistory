/*
 *
 */

#ifndef SitesConfigDialog_h
#define SitesConfigDialog_h

#include <ui_SitesConfigDialog.h>

class SitesConfigDialog : public QDialog, public Ui::SitesConfigDialog {
    Q_OBJECT

public:
    SitesConfigDialog(QWidget * parent = nullptr, Qt::WindowFlags f = 0);
    ~SitesConfigDialog();

    void doSitesConfigSettingsChanged();

public slots:
    void updateDialog();
    void refreshSitesConfig();

private slots:
    void browseForSitesConfig();
    void doApply();
    void checkApplyButtonState();

signals:
    void siteConfigChanged();

private:
    void updateSettings();
    bool updateNeeded();

};

#endif
