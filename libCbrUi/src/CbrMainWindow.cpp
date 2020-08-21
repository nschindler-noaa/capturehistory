/*
 */

#include <QWidget>
#include <QRect>
#include <QMdiArea>
#include <QLabel>
#include <QDockWidget>
#include <QMenu>
#include <QMdiSubWindow>
#include <QProgressDialog>
#include <QMessageBox>
#include <QTimer>
#include <QSplashScreen>
#include <QMenuBar>
#include <QSignalMapper>
#include <QProcess>
#include <QFile>
#include <QCloseEvent>

//#include <QtRTextWidget.h>
//#include <QtReport.h>
//#include <ThreadRunner.h>
#include <QTextEdit>
//#include
#include <QThread>

#include "CbrMainWindow.h"
#include "NavPanelView.h"
#include "NavPanelModel.h"
#include "OutputDockWidget.h"
#include "CbrSettings.h"
#include "CbrPlot.h"

using namespace cbr;

/* 
 *
 */
CbrMainWindow::CbrMainWindow(QWidget* parent, const char* name, Qt::WindowFlags fl, cbr::WFlags cfl)
: QMainWindow(parent, fl),
navSignalMapper_(0),
cbrSettings_(0),
mdiArea_(0), splashScreen_(0), programName_(name), activeSubWinKey_(-1),
navPanelModel_(0), navPanelView_(0), navRoot_(0),
fileSeparator_(0), tileWindowsAction_(0), windowSeparator_(0), helpSeparator_(0),
threadRunner_(0), 
pd_(0), showProgressTimer_(0), ProgressDelay_(1000),
output_(0), updater_("updater.exe"), usingUpdater_(false),
process_(0), checkForUpdatesAction_(0)  
{
    setWindowTitle(name);

    QFile updater(updater_);
    if (updater.exists())
        usingUpdater_ = true;

    mdiArea_ = new QMdiArea;
    setCentralWidget(mdiArea_);

    // set background gradient
    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 800));
    gradient.setColorAt(0, QColor(206, 206, 206));
    gradient.setColorAt(1, QColor(255, 255, 255));
    QBrush brush(gradient);
    mdiArea_->setBackground(brush);

    // Set up actions
    setupMenus();

    // Set up the navigation panel
	navPanelModel_ = new NavPanelModel(this);
	navRoot_ = addNavItem(NavPanelItem::Config, "root");

	if (cfl & WindowNavDockWidget)
	{
		navPanelView_ = new NavPanelView(this);
		navPanelView_->setContextMenuPolicy(Qt::CustomContextMenu);
		navPanelView_->setModel(navPanelModel_);
		navPanelView_->setContextMenuPolicy(Qt::CustomContextMenu);

		QDockWidget *dockWidget = new QDockWidget("Navigation Panel", this);
		dockWidget->setWidget(navPanelView_);
		addCbrDockWidget(Qt::LeftDockWidgetArea, dockWidget, DW_NavPanel);
		addAction(getMenu(M_ViewMenu), dockWidget->toggleViewAction());
	}

    // Output window
    output_ = new OutputDockWidget(this);
    addCbrDockWidget(Qt::BottomDockWidgetArea, output_, DW_Output);
    addAction(getMenu(M_ViewMenu), output_->toggleViewAction());

    // set up the progress dalog show progress timer
    pd_ = new QProgressDialog(this);
    pd_->setWindowTitle(name);
    showProgressTimer_ = new QTimer(this);
    showProgressTimer_->setSingleShot(true);

    connect(showProgressTimer_, SIGNAL(timeout()), progressDialog(), SLOT(show()));
    connect(pd_, SIGNAL(canceled()), SLOT(onProgressCanceled()));

    // signal mapppers
    navSignalMapper_ = new QSignalMapper(this);
    connect(navSignalMapper_, SIGNAL(mapped(int)), SLOT(onNavItemDoubleClicked(int)));

    // thread runner items
    threadRunner_ = new QThread;
    connect(threadRunner_, SIGNAL(runComplete()), SLOT(onRunComplete()));
    connect(threadRunner_, SIGNAL(runCanceled()), SLOT(onRunTerminated()));
    connect(threadRunner_, SIGNAL(percentComplete(int)), SLOT(setRunProgress(int)));
    connect(threadRunner_, SIGNAL(status(const QString&)), SLOT(onRunStatus(const QString)));
    connect(threadRunner_, SIGNAL(progressStatus(const QString&)), SLOT(onRunProgressStatus(const QString)));
    connect(threadRunner_, SIGNAL(error(const QString&)), SLOT(onRunError(const QString)));
    connect(threadRunner_, SIGNAL(warning(const QString&)), SLOT(onRunWarning(const QString)));
    connect(threadRunner_, SIGNAL(busy()), SLOT(onRunBusy()));

	if (cfl & WindowNavDockWidget)
	{
		// connections
		connect(navPanelView_, SIGNAL(doubleClicked(const QModelIndex&)), SLOT(onNavItemDoubleClicked(const QModelIndex&)));
		connect(navPanelView_, SIGNAL(clicked(const QModelIndex&)), SLOT(onNavItemClicked(const QModelIndex&)));
		connect(navPanelView_, SIGNAL(customContextMenuRequested(const QPoint&)), SLOT(onNavContextMenuRequested(const QPoint&)));
		connect(mdiArea_, SIGNAL(subWindowActivated(QMdiSubWindow*)), SLOT(onSubWindowActivated(QMdiSubWindow*)));
	}

    if (usingUpdater_)
        checkForUpdates(QStringList() << "/silent");
}

/*
 *
 */
CbrMainWindow::~CbrMainWindow() {
    delete threadRunner_;
    delete pd_;
    delete showProgressTimer_;
    delete process_;
}

void CbrMainWindow::onCheckForUpdates() {
    checkForUpdates(QStringList() << "/checknow");
}

void CbrMainWindow::checkForUpdates(const QStringList &args) {
    if (!process_)
        process_ = new QProcess(this);
    process_->start(updater_, args);
}

void CbrMainWindow::setupMenus() {
    // File menu
    addMenu(M_FileMenu, tr("&File"));

    addAction(M_FileMenu, A_Save, tr("Save"));
    addAction(M_FileMenu, A_SaveAs, tr("Save as"));
    addAction(M_FileMenu, A_PrintPreview, tr("Print preview"));
    addAction(M_FileMenu, A_Print, tr("Print"));
    getMenu(M_FileMenu)->addSeparator();
    addAction(M_FileMenu, A_Exit, tr("Exit"));
    connect(getAction(A_Save), SIGNAL(triggered()), SLOT(doActionSave()));
    connect(getAction(A_SaveAs), SIGNAL(triggered()), SLOT(doActionSaveAs()));
    connect(getAction(A_Print), SIGNAL(triggered()), SLOT(doActionPrint()));
    connect(getAction(A_PrintPreview), SIGNAL(triggered()), SLOT(doActionPrintPreview()));
    connect(getAction(A_Exit), SIGNAL(triggered()), SLOT(close()));

    addMenu(M_ViewMenu, tr("&View"));

    addMenu(M_WindowMenu, tr("&Window"));
    addAction(M_WindowMenu, A_WindowsTile, tr("Tile Windows"));
    addAction(M_WindowMenu, A_WindowsCascade, tr("Cascade Windows"));
    addAction(M_WindowMenu, A_WindowsClose, tr("Close All"));

    connect(getAction(A_WindowsTile), SIGNAL(triggered()), mdiArea_, SLOT(tileSubWindows()));
    connect(getAction(A_WindowsCascade), SIGNAL(triggered()), mdiArea_, SLOT(cascadeSubWindows()));
    connect(getAction(A_WindowsClose), SIGNAL(triggered()), mdiArea_, SLOT(closeAllSubWindows()));

    addMenu(M_HelpMenu, tr("&Help"));
    addAction(M_HelpMenu, A_Help, tr("About"));
    connect(getAction(A_Help), SIGNAL(triggered()), SLOT(onHelpAbout()));

    // add the update action
    if (usingUpdater_) {
        QAction *action = new QAction(tr("Check for updates"), 0);
        addAction(getMenu(A_Help), action);
        connect(action, SIGNAL(triggered()), SLOT(onCheckForUpdates()));
    }
}

void CbrMainWindow::cascadeSubWindows() {
    if (mdiArea_)
        mdiArea_->cascadeSubWindows();
}

void CbrMainWindow::loadSplashScreen(const QImage &img, int timeout) {
    if (!img.isNull()) {
        splashScreen_ = new QLabel(this);
        splashScreen_->setPixmap(QPixmap::fromImage(img));

        scaleSplashScreen();

        connect(mdiArea_, SIGNAL(subWindowActivated(QMdiSubWindow*)), splashScreen_, SLOT(hide()));
        QTimer::singleShot(timeout, splashScreen_, SLOT(hide()));
        splashScreen_->show();
    }
}

void CbrMainWindow::scaleSplashScreen() {
    if (splashScreen_) {
        double p = 0.9;
        int vw = width() * p;
        int vh = height() * p;

        QPixmap splashImage(*splashScreen_->pixmap());
        int iw = splashImage.width();
        int ih = splashImage.height();
        int dw = vw - iw;
        int dh = vh - ih;

        int w;
        int h;
        if (dw > 0 && dh > 0) {
            w = iw;
            h = ih;
        } else if (dw < dh) {
            w = vw;
            h = ih * (static_cast<double> (w) / iw);
        } else {
            h = vh;
            w = iw * (static_cast<double> (h) / ih);
        }

        splashImage = splashImage.scaled(w, h);
        splashScreen_->setPixmap(splashImage);

        int x = (width() - w) * 0.5;
        int y = (height() - h) * 0.48;

        splashScreen_->setGeometry(QRect(x, y, w, h));
    }
}

QMdiArea *CbrMainWindow::getMdiArea() const {
    return mdiArea_;
}

NavPanelItem *CbrMainWindow::addNavItem(int navItemKey, NavPanelItem::ItemType type,
        const QString &label, NavPanelItem *parent, QMenu *menu) {
    QObject *receiver = 0;
    const char *slot = 0;
    if (type != NavPanelItem::Heading) {
        receiver = navSignalMapper_;
        slot = SLOT(map());
    }

    NavPanelItem *item = addNavItem(navItemKey, type, label, parent, menu, receiver, slot);
    navSignalMapper_->setMapping(item, navItemKey);
    return item;
}

NavPanelItem *CbrMainWindow::addNavItem(int navItemKey, NavPanelItem::ItemType type,
        const QString &label, NavPanelItem *parent,
        QMenu *menu, const QObject *receiver, const char *slot) {
    navItems_[navItemKey] = addNavItem(type, label, parent, menu, receiver, slot);
    return navItems_[navItemKey];
}

NavPanelItem *CbrMainWindow::addNavItem(NavPanelItem::ItemType type,
        const QString &label, NavPanelItem *parent,
        QMenu *menu, const QObject *receiver, const char *slot) {
    if (!parent)
        parent = navRoot_;

    NavPanelItem *item = navPanelModel_->addItem(label, parent);
    item->setItemType(type);

    if (menu)
        addAction(menu, item);

    if (slot)
        connect(item, SIGNAL(triggered()), receiver, slot);
    else {
        item->setItemEnabled(false);
        item->setEnabled(false);
    }

    return item;
}

NavPanelItem *CbrMainWindow::getNavItem(int key) const {
    if (!navItems_.contains(key))
        return 0;
    return navItems_[key];
}

void CbrMainWindow::setNavItemEnabled(int ikey, bool rhs) {
	NavPanelItem *item = getNavItem(ikey);
	if (item)
		item->setEnabled(rhs);
}

void CbrMainWindow::clearNavItems() {
	navPanelModel_->removeRootChildren();
	navItems_.clear();
}

void CbrMainWindow::removeNavChildren(int key) {
	if (navItems_.contains(key))
		navPanelModel_->removeChildren(navItems_[key]);
}

QAction *CbrMainWindow::addAction(QMenu *menu, QAction *action) {
	if (menu == getMenu(M_FileMenu)) {
		if (!fileSeparator_)
			fileSeparator_ = menu->insertSeparator(getAction(A_Save));
		menu->insertAction(fileSeparator_, action);
	} else if (menu == getMenu(M_WindowMenu)) {
		if (!windowSeparator_)
			windowSeparator_ = menu->insertSeparator(tileWindowsAction_);
		menu->insertAction(windowSeparator_, action);
	} else if (menu == getMenu(M_HelpMenu)) {
		if (!helpSeparator_)
			helpSeparator_ = menu->insertSeparator(getAction(A_Help));
		menu->insertAction(helpSeparator_, action);
	} else
		menu->addAction(action);

	return action;
}

QAction *CbrMainWindow::addAction(int menuKey, int actionKey, const QString &label) {
    QAction *action = addAction(menuKey, label);
    if (action)
        actions_[actionKey] = action;
    return action;
}

QAction *CbrMainWindow::addAction(int menuKey, const QString &label) {
    QMenu *menu = getMenu(menuKey);
    if (!menu)
        return 0;
    return menu->addAction(label);
}

void CbrMainWindow::setActionEnabled(int ikey, bool enabled) const {
    if (actions_.contains(ikey))
        actions_[ikey]->setEnabled(enabled);
}

void CbrMainWindow::navInit() {
	if (navPanelView_)
		navPanelView_->expandAll();
}

void CbrMainWindow::onNavItemDoubleClicked(const QModelIndex &modelIndex) {
    NavPanelItem *item = static_cast<NavPanelItem*> (modelIndex.internalPointer());
    if (item->isEnabled() && item->isItemEnabled())
        item->trigger();
}

void CbrMainWindow::addCbrDockWidget(Qt::DockWidgetArea area, QDockWidget *dockWidget, int key) {
    dockWidgets_[key] = dockWidget;
    addDockWidget(area, dockWidget);
}

QDockWidget *CbrMainWindow::getDockWidget(int key) const {
    if (!dockWidgets_.contains(key))
        return 0;
    return dockWidgets_[key];
}

void CbrMainWindow::showDockWidget(int ikey, bool showWidget) const {
    QDockWidget *dw = getDockWidget(ikey);
    if (dw) {
        if (showWidget)
            dw->show();
        else
            dw->hide();
    }
}

void CbrMainWindow::showAllDockWidgets(bool show) const {
    QList<int> dockWidgetKeys = dockWidgets_.keys();
    foreach(int ikey, dockWidgetKeys)
    showDockWidget(ikey, show);
}

void CbrMainWindow::addSubWin(QMdiSubWindow *subWin) {
    mdiArea_->addSubWindow(subWin);
}

void CbrMainWindow::addSubWin(int key, QMdiSubWindow *subWin) {
    if (!subWindows_.contains(key)) {
        addSubWin(subWin);
        subWindows_[key] = subWin;
    }
}

/*
QMdiSubWindow *CbrMainWindow::addReport(int ikey, QtReport *report)
{
        reports_[ikey] = report;

        QMdiSubWindow *subWin = new QMdiSubWindow;
        subWin->setWidget(report->getTextWidget());
        subWin->setAttribute(Qt::WA_DeleteOnClose, false);	
        subWin->hide();
        reportWindows_[ikey] = subWin;
        addSubWin(subWin);
        return subWin;
}
 */

/*void CbrMainWindow::addReport(int reportKey, QReport *report) {
    reports_[reportKey] = report;
}*/

/*void CbrMainWindow::addPlot(int plotKey, CbrPlot *plot) {
    plots_[plotKey] = plot;
}*/

/*QMdiSubWindow *CbrMainWindow::addReportSubWindow(int subWinKey, int reportKey, QReport *report) {
    reportSubWinMap_[reportKey] = subWinKey;
    QMdiSubWindow *subWin = addSubWidget(subWinKey, report->getTextWidget());
    return subWin;
}*/

/*void CbrMainWindow::removeSubWindows() {
    QList<int> reportKeys = reports_.keys();
    foreach(int ikey, reportKeys)
    removeReport(ikey);

    QMapIterator<int, QMdiSubWindow*> it2(subWindows_);
    while (it2.hasNext()) {
        it2.next();
        removeSubWin(it2.key());
    }
}*/

void CbrMainWindow::removeSubWin(int key) {
    QMdiSubWindow *subWin = getSubWin(key);
    if (subWin) {
        mdiArea_->removeSubWindow(subWin);
        subWindows_.remove(key);
        delete subWin;
        subWidgets_.remove(key);
    }
}

void CbrMainWindow::hideSubWin(int key) {
    QMdiSubWindow *subWin = getSubWin(key);
    if (subWin)
        subWin->hide();
}

/*void CbrMainWindow::removeReport(int reportKey) {
    if (reportSubWinMap_.contains(reportKey)) {
        int subWinKey = reportSubWinMap_[reportKey];

        subWindows_[subWinKey]->close();

        delete reports_[reportKey];

        reports_.remove(reportKey);
        reportSubWinMap_.remove(reportKey);

        removeSubWin(subWinKey);
    }
}*/

/*void CbrMainWindow::removePlot(int plotKey) {
    if (plots_.contains(plotKey)) {
        delete plots_[plotKey];
        plots_.remove(plotKey);
    }
}*/

QMdiSubWindow *CbrMainWindow::addSubWidget(int key, QWidget *widget) {
    QMdiSubWindow *subWin = new QMdiSubWindow;
    subWin->setWidget(widget);
    if (subWidgets_[key]) {
        delete subWidgets_[key];
        subWidgets_.remove(key);
    }
	if (key > 0)
		subWidgets_[key] = widget;
    subWin->setAttribute(Qt::WA_DeleteOnClose, false);
    subWin->hide();
    addSubWin(key, subWin);
    return subWin;
}

void CbrMainWindow::deleteSubWidget(int key)
{
	QMap<int, QWidget*>::iterator iter = subWidgets_.find(key);
	if (iter != subWidgets_.end())
	{
		delete iter.value();
		subWidgets_.remove(key);
	}
	QMap<int, QMdiSubWindow*>::iterator winIter = subWindows_.find(key);
	if (winIter != subWindows_.end())
	{
		delete winIter.value();
		subWindows_.remove(key);
	}
}

QMdiSubWindow *CbrMainWindow::getSubWin(int key) const {
    if (!subWindows_.contains(key))
        return 0;
    return subWindows_[key];
}

QWidget *CbrMainWindow::getSubWidget(int key) const {
    QMdiSubWindow *subWin = getSubWin(key);
    if (!subWin)
        return 0;
    return subWin->widget();
}

int CbrMainWindow::getSubWinKey(QMdiSubWindow *subWin) const {
    if (subWin) {
        QMapIterator<int, QMdiSubWindow*> i(subWindows_);
        while (i.hasNext()) {
            i.next();
            if (i.value() == subWin)
                return i.key();
        }
    }

    return -1;
}

QMdiSubWindow *CbrMainWindow::getActiveSubWin()  {
	QMdiSubWindow *subWin =  mdiArea_->activeSubWindow();
	if (subWin == 0) {
		QList<QMdiSubWindow*> subWindows = mdiArea_->subWindowList();
		if (subWindows.size() > 0) {
			subWin = subWindows[0];
			setActiveSubWindow(subWin);
		}
	}
    return subWin;
}

void CbrMainWindow::setActiveSubWindow(QMdiSubWindow *subWin) {
    if (mdiArea_)
        mdiArea_->setActiveSubWindow(subWin);
}

void CbrMainWindow::showSubWin(int key, bool modal) const {
    QMdiSubWindow *subWin = getSubWin(key);
    showSubWin(subWin, modal);
}

void CbrMainWindow::showSubWin(QMdiSubWindow *subWin, bool modal) const {
    if (subWin) {
		if (subWin->isMinimized())
			subWin->showNormal();
        subWin->show();
        if (subWin->widget())
            subWin->widget()->show();
        subWin->raise();

        if (modal)
            subWin->setWindowModality(Qt::WindowModal);
    }
}

/*QtReport *CbrMainWindow::getReport(int reportKey) {
    if (reports_.contains(reportKey))
        return reports_[reportKey];
    return 0;
}*/

/*CbrPlot *CbrMainWindow::getPlot(int plotKey) {
    if (plots_.contains(plotKey))
        return plots_[plotKey];
    return 0;
}*/

/*void CbrMainWindow::resetReports() {
    QMapIterator<int, QReport*> it(reports_);
    while (it.hasNext()) {
        it.next();
        QReport* report = it.value();
        report->reset();
    }
}*/

QMdiSubWindow *CbrMainWindow::getReportSubWindow(int reportKey) {
    if (reportSubWinMap_.contains(reportKey)) {
        int subWinKey = reportSubWinMap_[reportKey];
        return subWindows_[subWinKey];
    }
    return 0;
}

bool CbrMainWindow::isReportWin(int subWinKey) {
    return reportSubWinMap_.key(subWinKey, -1) != -1;
}

void CbrMainWindow::closeAllSubWindows() {
    if (mdiArea_)
        mdiArea_->closeAllSubWindows();
}

QMdiSubWindow *CbrMainWindow::getCurrentSubWindow() const {
    if (!mdiArea_)
        return 0;
    return mdiArea_->currentSubWindow();
}

void CbrMainWindow::onSubWindowActivated(QMdiSubWindow *subWin) {
    if (subWin)
        activeSubWinKey_ = getSubWinKey(subWin);
}

/*
 * Add a menu to the main menu bar, before the give menu if specified
 */
QMenu *CbrMainWindow::addMenu(int menuKey, const QString &label, int before) {
    QMenu *beforeMenu = getMenu(before);
    QMenu *menu;
    if (!beforeMenu)
        menu = menuBar()->addMenu(tr(label.toLatin1()));
    else {
        menu = new QMenu(label);
        QAction *beforeAction = beforeMenu->menuAction();
        menuBar()->insertMenu(beforeAction, menu);
    }
    menus_[menuKey] = menu;
    return menu;
}

/*
 * Add a menu to the main menu bar, before the give menu if specified
 */
QMenu *CbrMainWindow::addSubMenu(int menuKey, int subMenuKey, const QString &label) {
    QMenu *menu = getMenu(menuKey);
    menus_[subMenuKey] = menu->addMenu(label);
    return menus_[subMenuKey];
}

QMenu *CbrMainWindow::addMenu(int ikey, QMenu *subMenu) {
    if (menus_.contains(ikey))
        menus_[ikey]->addMenu(subMenu);
    return subMenu;
}

QMenu *CbrMainWindow::getMenu(int ikey) {
    if (menus_.contains(ikey))
        return menus_[ikey];
    return 0;
}

QAction *CbrMainWindow::getAction(int ikey) {
    if (actions_.contains(ikey))
        return actions_[ikey];
    return 0;
}

void CbrMainWindow::setActionEnabled(int ikey, bool rhs) {
    QAction *action = getAction(ikey);
    if (action)
        action->setEnabled(rhs);
}

/*void CbrMainWindow::setRunnable(ThreadRunnable *runnable) {
    threadRunner_-> setRunnable(runnable);
}*/

void CbrMainWindow::startRun() {
    threadRunner_->start();
}

void CbrMainWindow::setProgressBusy() {
    pd_->setRange(0, 0);
}

void CbrMainWindow::setProgressRange(int min, int max) {
    pd_->setRange(min, max);
}

void CbrMainWindow::setProgressText(const QString &txt) {
    pd_->setLabelText(txt);
}

void CbrMainWindow::setProgressCaption(const QString &txt) {
	pd_->setWindowTitle(txt);
}

void CbrMainWindow::resetProgress() {
    pd_->reset();
}

void CbrMainWindow::cancelProgress() {
    pd_->cancel();
}

void CbrMainWindow::showProgress() {
    pd_->show();
}

void CbrMainWindow::onRunComplete() {
    pd_->hide();
}

void CbrMainWindow::onRunTerminated() {
    pd_->reset();
    pd_->close();
}

void CbrMainWindow::startProgressTimer() {
    if (showProgressTimer_)
        showProgressTimer_->start(ProgressDelay_);
}

void CbrMainWindow::stopProgressTimer() {
    if (showProgressTimer_ && showProgressTimer_->isActive()) {
        showProgressTimer_->stop();

    }
    resetProgress();
    cancelProgress();
}

void CbrMainWindow::onProgressCanceled() {
    if (threadRunner_)
        threadRunner_->terminate();
//        threadRunner_->requestInterruption();// setCanceled(true);
}

void CbrMainWindow::setRunProgress(int percentComplete) {
    if (pd_->maximum() != 100)
        pd_->setMaximum(100);
    pd_->setValue(percentComplete);
}

void CbrMainWindow::onRunProgressStatus(const QString msg) {
    pd_->setLabelText(msg);
    out(msg);
}

void CbrMainWindow::onRunStatus(const QString msg) {
    out(msg);
}

void CbrMainWindow::onRunError(const QString msg) {
    QMessageBox::critical(this, programName_, msg);
    err(msg);
}

void CbrMainWindow::onRunWarning(const QString msg) {
    warn(msg);
}

void CbrMainWindow::onRunBusy() {
    pd_->setMinimum(0);
    pd_->setMaximum(0);
}

bool CbrMainWindow::isRunCanceled() const {
    return !(threadRunner_->isRunning());//isInterruptionRequested();// ->isCanceled();
}

void CbrMainWindow::out(QString msg, OutputDockWidget::OutputType type) {
    if (output_)
        output_->append(msg, type);
}

void CbrMainWindow::heading(QString msg) {
    out(msg, OutputDockWidget::Heading);
}

void CbrMainWindow::out(QString msg) {
    out(msg, OutputDockWidget::Status);
}

void CbrMainWindow::err(QString msg) {
    out(msg, OutputDockWidget::Error);
}

void CbrMainWindow::warn(QString msg) {
    out(msg, OutputDockWidget::Warning);
}

void CbrMainWindow::updateNav() {
    if (navPanelModel_)
        navPanelModel_->updateLayout();
}

void CbrMainWindow::keyReleaseEvent(QKeyEvent*) {
    if (splashScreen_)
        splashScreen_->hide();
}

void CbrMainWindow::mouseReleaseEvent(QMouseEvent*) {
    if (splashScreen_)
        splashScreen_->hide();
}

void CbrMainWindow::resizeEvent(QResizeEvent * /*event*/) {
    if (splashScreen_)
        splashScreen_->hide();
}

/*
 * Geom
 */
void CbrMainWindow::initGeomSystem(CbrSettings* settings, int mainWindowGeomKey) {
    cbrSettings_ = settings;
    mainWindowGeomKey_ = mainWindowGeomKey;
}

void CbrMainWindow::mapGeomKey(int settingsKey, int subWinKey) {
    geomMap_[subWinKey] = settingsKey;
}

void CbrMainWindow::restoreAllGeometry() {
    if (cbrSettings_) {
        QMainWindow::restoreGeometry(cbrSettings_->get(mainWindowGeomKey_).toByteArray());

        QMapIterator<int, int> i(geomMap_);
        while (i.hasNext()) {
            i.next();
            restoreGeometry(i.key());
        }
    }
}

void CbrMainWindow::restoreGeometry(int subWinKey) {
    if (cbrSettings_) {
        QMdiSubWindow *subWin = getSubWin(subWinKey);

        if (subWin) {
            QVariant geom = cbrSettings_->get(geomMap_[subWinKey]);
            if (geom.isValid())
                subWin->restoreGeometry(geom.toByteArray());
        }
    }
}

void CbrMainWindow::closeEvent(QCloseEvent *evt) {
    if (cbrSettings_) {
        cbrSettings_->set(mainWindowGeomKey_, saveGeometry());
        saveSubWinGeometry();
    }

    if (threadRunner_->isRunning()) {
        evt->ignore();
        err("Program busy, can't exit. Try after computations have finished.");
    } else
        evt->accept();
}

void CbrMainWindow::saveSubWinGeometry() {
    if (cbrSettings_) {
        QMapIterator<int, int> i(geomMap_);
        while (i.hasNext()) {
            i.next();
            QMdiSubWindow *subWin = getSubWin(i.key());
            if (subWin) {
                if (subWin->isMaximized())
                    subWin->showNormal();
                cbrSettings_->set(i.value(), subWin->saveGeometry());
            }
        }
    }
}
