#ifndef CbrMainWindow_h
#define CbrMainWindow_h

#include <QMainWindow>
#include <QMap>
#include <QVector>
#include <QFlags>
#include <QThread>

#include "NavPanelItem.h"
#include "NavPanelModel.h"
#include "NavPanelView.h"
#include "OutputDockWidget.h"
#include "CbrUiFlags.h"
#include "CbrPlot.h"
#include "CbrSettings.h"

#include <QMdiArea>
#include <QLabel>
#include <QString>
#include <QDockWidget>
#include <QModelIndex>
#include <QMdiSubWindow>
#include <QProgressDialog>
#include <QSplashScreen>
#include <QAction>
#include <QTimer>
#include <QSignalMapper>
#include <QProcess>
#include <QtXml>

/*class QMdiArea;
class QLabel;
class QString;
class QDockWidget;
class QModelIndex;
class QMdiSubWindow;
class QProgressDialog;
class QSplashScreen;
class QAction;
class QTimer;
class QSignalMapper;
class QProcess;*/

namespace cbr {
//    class NavPanelModel;
//    class NavPanelView;
//    class QThread;
//    class ThreadRunner;
//    class ThreadRunnable;
//    class OutputDockWidget;
//    class QtReport;
//    class CbrPlot;
//    class CbrSettings;

    class CbrMainWindow : public QMainWindow {

        Q_OBJECT

    public:
        enum DockWidget {
            DW_NavPanel = 0,
            DW_Output,
            DW_Num
        };

        enum SubWindows {
            SW_NUM = 0
        };

        enum Menu {
            M_FileMenu = 0,
            M_HelpMenu,
            M_ViewMenu,
            M_WindowMenu,
            M_ExitMenu,
            M_Num
        };

        enum Action {
            A_Exit = 0,
            A_Help,
            A_Info,
            A_Print,
            A_PrintPreview,
            A_Save,
            A_SaveAs,
            A_WindowsCascade,
            A_WindowsClose,
            A_WindowsTile,
            A_Num
        };

        enum NavItem {
            NI_Num = 0
        };

        CbrMainWindow(QWidget* parent = 0, const char* name = "CBR", Qt::WindowFlags fl = 0,
            cbr::WFlags cfl = WindowNavDockWidget | WindowOutputDockWidget);
        virtual ~CbrMainWindow();

        void loadSplashScreen(const QImage &img, int timeout = 4000);
//        virtual QtReport *getReport(int reportKey);
//        virtual CbrPlot *getPlot(int plotKey);

    protected:
        QMdiArea *getMdiArea() const;

        NavPanelView *getNavPanelView() const {
            return navPanelView_;
        }

        NavPanelModel *getNavPanelModel() const {
            return navPanelModel_;
        }

        QSignalMapper *navSignalMapper_;
        NavPanelItem *addNavItem(int navItemKey, NavPanelItem::ItemType type,
                const QString &label, NavPanelItem *parent = 0,
                QMenu *menu = 0);
        NavPanelItem *addNavItem(int navItemKey, NavPanelItem::ItemType type,
                const QString &label, NavPanelItem *parent,
                QMenu *menu,
                const QObject *receiver, const char *slot);
        NavPanelItem *addNavItem(NavPanelItem::ItemType type,
                const QString &label, NavPanelItem *parent = 0,
                QMenu *menu = 0,
                const QObject *receiver = 0, const char *slot = 0);

        void navInit();
        void removeNavChildren(int key);
        NavPanelItem *getNavItem(int key) const;
        void setNavItemEnabled(int ikey, bool rhs);
        void clearNavItems();
        NavPanelItem *getRootNavItem() const {
            return navRoot_;
        }

        QMap<int, NavPanelItem*> & getNavItems() {
            return navItems_;
        }

        QMenu *addMenu(int menuKey, const QString &label, int before = M_Num);
        QMenu *addMenu(int ikey, QMenu *menu);
        QMenu *addSubMenu(int menuKey, int subMenukey, const QString &label);
        QMenu *getMenu(int ikey);
        QAction *getAction(int ikey);
        void setActionEnabled(int ikey, bool rhs);
        QAction *addAction(QMenu *menu, QAction *action);
        QAction *addAction(int ikey, int actionKey, const QString &label);
        QAction *addAction(int ikey, const QString &label);
        void setActionEnabled(int ikey, bool enabled) const;

  //      void setRunnable(ThreadRunnable *runnable);
        void startRun();

        QThread *getThreadRunner() {
//        ThreadRunner *getThreadRunner() {
            return threadRunner_;
        }
        bool isRunCanceled() const;

        const QString &getProgramName() const {
            return programName_;
        }

        QProgressDialog *progressDialog() {
            return pd_;
        }
        void setProgressBusy();
        void setProgressRange(int min, int max);
        void setProgressText(const QString &txt);
        void setProgressCaption(const QString &txt);
        void showProgress();
        void resetProgress();
        void cancelProgress();
        void startProgressTimer();
        void stopProgressTimer();

        QMap<int, QDockWidget*> dockWidgets_;
        QMap<int, QMdiSubWindow*> subWindows_;
        QMap<int, QWidget*> subWidgets_;
        QMap<int, int> reportSubWinMap_;
//        QMap<int, QReport*> reports_;
        QMap<int, QMdiSubWindow*> plotWindows_;
//        QMap<int, CbrPlot*> plots_;

        void addCbrDockWidget(Qt::DockWidgetArea area, QDockWidget *dockWidget, int key);
        QDockWidget *getDockWidget(int key) const;
        void showDockWidget(int key, bool show = true) const;
        void showAllDockWidgets(bool show = true) const;

        void addSubWin(QMdiSubWindow *w);
        void addSubWin(int key, QMdiSubWindow *w);
        void addSubWin(int key, int geomKey, QMdiSubWindow *w);
        void removeSubWindows();
        void removeSubWin(int key);
        void hideSubWin(int key);
        QMdiSubWindow *addSubWidget(int key, QWidget *widget);
        QMdiSubWindow *addSubWidget(QWidget *widget) { return addSubWidget(0, widget); }
        QMdiSubWindow *getSubWin(int key) const;
        QWidget *getSubWidget(int key) const;
        int getSubWinKey(QMdiSubWindow *subWin) const;
        QMdiSubWindow *getActiveSubWin();

        void deleteSubWidget(int key);

        int getActiveSubWinKey() const {
            return activeSubWinKey_;
        }
        void setActiveSubWindow(QMdiSubWindow *subWin);
        void closeAllSubWindows();
        QMdiSubWindow *getCurrentSubWindow() const;
        void showSubWin(int key, bool modal = false) const;
        void showSubWin(QMdiSubWindow *subWin, bool modal = false) const;

        //QMdiSubWindow *addReport(int reportKey, QtReport *report);
//        void addReport(int reportKey, QReport *report);
//        QMdiSubWindow *addReportSubWindow(int subWinKey, int reportKey, QReport *report);
        QMdiSubWindow *getReportSubWindow(int reportKey);

        int getSubWinReportKey(int subWinKey) {
            return reportSubWinMap_.key(subWinKey, -1);
        }
        bool isReportWin(int subWinKey);
//        virtual void removeReport(int reportKey);
        void resetReports();

//        void addPlot(int plotKey, CbrPlot *plot);
//        void removePlot(int plotKey);

        // geom
        QMap<int, int> geomMap_;
        int mainWindowGeomKey_;
        CbrSettings *cbrSettings_;
        void initGeomSystem(CbrSettings* settings, int mainWindowGeomKey);
        void mapGeomKey(int settingsKey, int subWinKey);
        void restoreAllGeometry();
        void restoreGeometry(int subWinKey);
        void closeEvent(QCloseEvent *event);

        void saveSubWinGeometry();

    protected slots:
        virtual void onRunComplete();
        virtual void onRunTerminated();
        virtual void onProgressCanceled();
        virtual void setRunProgress(int percentComplete);
        virtual void onRunStatus(const QString msg);
        virtual void onRunProgressStatus(const QString msg);
        virtual void onRunError(const QString msg);
        virtual void onRunWarning(const QString msg);
        virtual void onRunBusy();

        virtual void onSubWindowActivated(QMdiSubWindow *subWin);

        virtual void onHelpAbout() {}
        virtual void doActionSave() {}
        virtual void doActionSaveAs() {}
        virtual void doActionPrint() {}
        virtual void doActionPrintPreview() {}

        virtual void out(QString msg, OutputDockWidget::OutputType type);
        virtual void heading(const QString msg);
        virtual void out(QString msg);
        virtual void err(QString msg);
        virtual void warn(QString msg);

        virtual void updateNav();
        virtual void onNavItemDoubleClicked(const QModelIndex&);
        virtual void onNavItemDoubleClicked(int /*navItemKey*/) {}
        virtual void onNavItemClicked(const QModelIndex&) {}
        virtual void onNavContextMenuRequested(const QPoint&) {}

        void cascadeSubWindows();

        void onCheckForUpdates();

    signals:
        void navItemClicked(const QModelIndex&);
        void navItemDoubleClicked(const QModelIndex&);
        void navContextMenuRequested(const QPoint&);

    private:
        QMdiArea *mdiArea_;
        QLabel *splashScreen_;
        void scaleSplashScreen();
        QString programName_;
        int activeSubWinKey_;

        QMap<int, QMenu*> menus_;
        void setupMenus();

        QMap<int, QAction*> actions_;

        QMap<int, NavPanelItem*> navItems_;

        NavPanelModel *navPanelModel_;
        NavPanelView *navPanelView_;
        NavPanelItem *navRoot_;

        QAction *fileSeparator_;
        QAction *tileWindowsAction_;
        QAction *windowSeparator_;
        QAction *helpSeparator_;

        QThread *threadRunner_;

        QProgressDialog *pd_;
        QTimer* showProgressTimer_;
        int ProgressDelay_;

        cbr::OutputDockWidget *output_;

        void keyReleaseEvent(QKeyEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void resizeEvent(QResizeEvent *event);

        const QString updater_;
        bool usingUpdater_;
        QProcess *process_;
        void checkForUpdates(const QStringList &args);
        QAction *checkForUpdatesAction_;

    };
}



#endif
