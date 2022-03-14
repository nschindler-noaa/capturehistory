/*
 */

#include <string>

#include <QHttpMultiPart>
#include <QUrl>
#include <QtNetwork>
#include <qstring.h>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include <QFile>
#include <qdatetime.h>
#include <qregexp.h>
#include <QTableWidget>
#include <QtXml>


#include <DateConverter.h>
#include <StringTok.h>
#include <StringUtil.h>
#include <StringManip.h>
#include <ArrayDefs.h>
#include <Sites.h>

#include "UpdateManagerImpl.h"
#include "PPVersion.h"
#include "PitProSettings.h"
#include "PPSystemSettings.h"



using namespace cbr;
using std::string;

// definition of new classes:

class DQLeftAlignTableItem : public QTableWidgetItem {
public:

    DQLeftAlignTableItem(QTableWidget *table, ItemType et, const QString &text)
    : QTableWidgetItem(text, et) {
        Q_UNUSED(table);
    }

    DQLeftAlignTableItem(QTableWidget *table, ItemType et, const QString &text, const QPixmap &p)
    : QTableWidgetItem(p, text, et) {
        Q_UNUSED(table);
    }

    int alignment() const {
        return Qt::AlignLeft | Qt::AlignVCenter;
    } // Here is the align change done.
};

class DQRightAlignTableItem : public QTableWidgetItem {
public:

    DQRightAlignTableItem(QTableWidget *table, ItemType et, const QString &text)
    : QTableWidgetItem(text, et) {
        Q_UNUSED(table);
    }

    DQRightAlignTableItem(QTableWidget *table, ItemType et, const QString &text, const QPixmap &p)
    : QTableWidgetItem(p, text, et) {
        Q_UNUSED(table);
    }

    int alignment() const {
        return Qt::AlignRight | Qt::AlignVCenter;
    } // Here is the align change done.
};

/*
 *  Constructs a UpdateManagerImpl which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
UpdateManagerImpl::UpdateManagerImpl(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
: QDialog(parent, fl)
{
    setObjectName(name);
    setModal(modal);
    server = QString("http://www.cbr.washington.edu");
    updatesUrl = QString("/downloads/paramest/");
    versionsFile = QString("pitpro_version.xml");
    sitesConfigFile = QString("sites_config.txt");
    port = (80);
    setupUi(this);

    http = new QUrl();
/*    connect(http, SIGNAL(requestFinished(int, bool)),
            this, SLOT(httpRequestFinished(int, bool)));
    connect(http, SIGNAL(dataReadProgress(int, int)),
            this, SLOT(updateDataReadProgress(int, int)));
    connect(http, SIGNAL(responseHeaderReceived(const QHttpResponseHeader &)),
            this, SLOT(readResponseHeader(const QHttpResponseHeader &)));

    updateTable->setItem(0, 0, QTableWidgetItem(tr("PitPro")));
//    updateTable->setText(0, 0, tr("PitPro"));

    QHeaderView *colHeader = updateTable->horizontalHeader();
//    Q3Header *colHeader = updateTable->horizontalHeader();
    colHeader->setLabel(0, "Item");
    colHeader->setLabel(1, "Current Version");
    colHeader->setLabel(2, "Available Version");
    colHeader->setLabel(3, "Update");

    QHeaderView *rowHeader = updateTable->verticalHeader();
    rowHeader->setLabel(0, "");

    updateTable->setItem(0, 1, new DQRightAlignTableItem(updateTable, QTableWidgetItem::OnTyping, "??"));
    updateTable->setItem(0, 2, new DQRightAlignTableItem(updateTable, QTableWidgetItem::OnTyping, "??"));
    updateTable->setItem(0, 3, new QCheckTableItem(updateTable, "Update"));

    updateTable->setEnabled(true);
    updateTable->setColumnReadOnly(0, true);
    updateTable->setColumnReadOnly(1, true);
    updateTable->setColumnReadOnly(2, true);
    updateTable->setColumnReadOnly(3, false);
    updateTable->setRowReadOnly(0, false);*/

    updateTable->resizeColumnsToContents();
/*    updateTable->setColumnStretchable(0, true);
    updateTable->setColumnStretchable(1, true);
    updateTable->setColumnStretchable(2, true);
    updateTable->setColumnStretchable(3, true);*/

    // signals and slots connections
    connect(updateButton, SIGNAL(clicked()), this, SLOT(doUpdateButton()));
    connect(doneButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(refeshButton, SIGNAL(clicked()), this, SLOT(refresh()));

    refresh();
}

/*
 *  Destroys the object and frees any allocated resources
 */
UpdateManagerImpl::~UpdateManagerImpl() {
    // no need to delete child widgets, Qt does it all for us
}

void UpdateManagerImpl::refresh() {
    PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
    if (systemSettings.isChecked(PPSystemSettings::AltSitesConfig)) {
        updateTable->setItem(0, 0, new QTableWidgetItem(tr("Alternate Site configuration")));
//        updateTable->setText(0, 0, tr("Alternate Site configuration"));
    } else {
        updateTable->setItem(0, 0, new QTableWidgetItem(tr("Site configuration")));
//        updateTable->setText(0, 0, tr("Site configuration"));
    }

    if (jobs.size() == 0) {
        // get the sites config version string
        QString sitesVersion = getCurrentConfigVersion();
        if (sitesVersion.isNull())
            sitesVersion = "??";
        updateTable->setItem(0, 1, new QTableWidgetItem(sitesVersion));
//        updateTable->setText(0, 1, sitesVersion);

        // check for updates, the callback will handle the rest
        updateTable->setItem(0, 2, new QTableWidgetItem(tr("Checking...")));
//        updateTable->setText(0, 2, "Checking...");

        QString url = server + updatesUrl + versionsFile;
        jobs.push_back(makeJob(url, Version));
        download();
    }
}

QString UpdateManagerImpl::getCurrentConfigVersion() {
    PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
    QString sitesConfigFile = systemSettings.getDefault(PPSystemSettings::SitesConfigFile).toString();

    QFile currentConfig(sitesConfigFile);
    currentConfig.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!currentConfig.isOpen())
        return QString::null;

    QStringList lines;
    QTextStream ts(&currentConfig);
    while (!ts.atEnd()) {
        QString line = ts.readLine();
        if (line.startsWith(QString("configDate")) == 0) {
            QStringList toks = line.split(" ", QString::SkipEmptyParts);//QStringList::split(" ", line);
            if (toks.size() != 2)
                return QString::null;
            return
            toks[1];
        }
    }
    currentConfig.close();

    return QString::null;
}

void UpdateManagerImpl::doUpdateButton() {
    if (jobs.size() == 0) {

        QTableWidgetItem *cb  = updateTable->item(0, 3);
//        Q3CheckTableItem* checkBox = static_cast<Q3CheckTableItem*> (updateTable->item(0, 3));
        if (cb->text().compare("0")) {
            QString url = server + updatesUrl + sitesConfigFile;
            jobs.push_back(makeJob(url, SitesConfig));
        }

        download();
    }
}

Job UpdateManagerImpl::makeJob(const QString& url, DownLoadType type) {
    QString fileName = url.section("/", -1, -1);

    QString templ = fileName + "XXXXXX";
    char buf[256];

    int retVal;

    QDir tmpDir(QDir::tempPath());
    if (!tmpDir.cd("CBR"))
    {
        tmpDir.mkdir("CBR");
        tmpDir.cd("CBR");
    }

    if (!tmpDir.cd("PitPro"))
    {
        tmpDir.mkdir("PitPro");
        tmpDir.cd("PitPro");
    }


#if 0 //WIN32
    strcpy_s(buf, templ.toStdString());
    retVal = _mktemp_s(buf, sizeof(buf));

#else
    strcpy(buf, templ.toStdString().data());
//	strcpy(buf, templ.latin1());
    retVal = mkstemp(buf);
#endif

    QString tempFile;
    if (retVal != -1)
        tempFile = QString(buf);
    else
        tempFile = fileName;

    QString tempPath = tmpDir.absoluteFilePath(tempFile);

    Job job;
    job.tempfile = tempPath;
    job.url = url;
    job.type = type;

    return job;
}

void UpdateManagerImpl::download() {
    if (!http)
        return;
    if (jobs.size() == 0)
        return;
    const Job& job = jobs.first();
    QUrl url(job.url);
    QString fileName = job.tempfile;

    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::information(this, tr("HTTP"),
                tr("Unable to save the file %1: %2.")
                .arg(fileName).arg(file->errorString()));
        delete file;
        file = 0;
        return;
    }
// TODO: Fix
//    http->setHost(url.host(), port);
//    if (!url.userName().isEmpty())
//        http->setUser(url.userName(), url.password());

    httpRequestAborted = false;
//    httpGetId = http->get(url.path(), file);

    updateButton->setEnabled(false);
}

void UpdateManagerImpl::readResponseHeader(QString &responseHeader) {
//    void UpdateManagerImpl::readResponseHeader(const QHttpResponseHeader &responseHeader) {
// TODO: Fix
/*    if (responseHeader.statusCode() != 200) {
        QMessageBox::information(this, tr("PitPro"),
                tr("Download failed: %1.")
                .arg(responseHeader.reasonPhrase()));
        httpRequestAborted = true;
        http->abort();
        return;
    }*/
}

void UpdateManagerImpl::updateDataReadProgress(int bytesRead, int totalBytes) {
    if (httpRequestAborted)
        return;
    progressBar->setRange(0, totalBytes);
    progressBar->setValue(bytesRead);
}

void UpdateManagerImpl::httpRequestFinished(int requestId, bool /*error*/) {
    if (httpRequestAborted) {
        if (file) {
            file->close();
            file->remove();
            delete file;
            file = 0;
        }

        // progressBar->something()
        return;
    }

    if (requestId != httpGetId)
        return;

    progressBar->reset();

    file->close();
    if (jobs.size() == 0)
        return;

    const Job& job = jobs.front();
    DownLoadType downLoadType = static_cast<DownLoadType> (job.type);

    switch (downLoadType) {
    case Version:
        getVersionFinished(job);
        break;
    case SitesConfig:
        getSitesConfigFinished(job);
        break;
    case Unset:
    case PitPro:
        // do nothing
        break;
    }

    jobs.pop_front();
    if (jobs.size() > 0)
        download();
}

void UpdateManagerImpl::getVersionFinished(const Job& /*job*/) {
    // TODO: Fix
/*    updateTable->setText(0, 2, "??");

    Status status;

    QDomDocument doc("version");
    file->open(QIODevice::ReadOnly);
    doc.setContent(file);

    // get the site configuration version
    QDomNodeList scList = doc.elementsByTagName("siteconfig");
    if (scList.count() > 0) {
        QDomNode scNode = scList.item(0);
        if (scNode.hasChildNodes() && scNode.firstChild().isText())
            updateTable->setText(0, 2, scNode.firstChild().nodeValue());
    }

    // compare the current version with the available version
    QString scCurrentVersion = updateTable->text(0, 1);
    QString scAvailVersion = updateTable->text(0, 2);

    status = Ok;

    Q3CheckTableItem* scItem = static_cast<Q3CheckTableItem*> (updateTable->item(0, 3));
    if (scCurrentVersion.compare("??") == 0) {
        status = OutOfDate;
        scItem->setChecked(true);
        scItem->setEnabled(true);
    } else {
        PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
        if (systemSettings.isChecked(PPSystemSettings::AltSitesConfig)) {
            scItem->setChecked(false);
            scItem->setEnabled(false);
        } else {
            DateConverter dcAvail(scAvailVersion.latin1());
            DateConverter dcCurrent(scCurrentVersion.latin1());
            if (dcAvail <= dcCurrent) {
                scItem->setChecked(false);
                scItem->setEnabled(false);
            }
            else {
                status = OutOfDate;
                scItem->setChecked(true);
                scItem->setEnabled(true);
            }
        }
    }

    if (status == OutOfDate)
        updateButton->setEnabled(true);
    else
        updateButton->setEnabled(false);

    emit updateStatus(status);*/
}

void UpdateManagerImpl::getSitesConfigFinished(const Job&) {
    updateTable->setItem (0, 2, new QTableWidgetItem("Done."));
    if (!saveOldSitesConfig())
        QMessageBox::information(this, "PitPro", "Unable to save current configuration file. Aborting.");
    else {
        PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
        QString sitesConfigFile = systemSettings.getDefault(PPSystemSettings::SitesConfigFile).toString();
        QFile currentConfig(sitesConfigFile);
        currentConfig.open(QIODevice::WriteOnly | QIODevice::Text);
        if (!currentConfig.isOpen())
            QMessageBox::information(this, "PitPro", "Unable to write new configuration file. Aborting. " + currentConfig.errorString());
        else {
            file->open(QIODevice::ReadOnly);
            QTextStream ts(&currentConfig);
            ts << QString(file->readAll());
            file->close();
            currentConfig.close();
            emit sitesConfigUpdated();
        }
    }
}

bool UpdateManagerImpl::saveOldSitesConfig() {
    PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
    QString sitesConfigFile = systemSettings.getDefault(PPSystemSettings::SitesConfigFile).toString();
    QFile currentConfig(sitesConfigFile);
    currentConfig.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!currentConfig.isOpen())
        return true; // nothing to save
    QStringList lines;
    QTextStream ts1(&currentConfig);
    QString line;
    while (!ts1.atEnd()) {
        lines += ts1.readLine();
    }
    currentConfig.close();

    QDate currentDate = QDate::currentDate();
    QString dateString = currentDate.toString("yyyyMMdd");
    QString sitesConfigBak = sitesConfigFile + "." + dateString;
    QFile configBak(sitesConfigBak);
    configBak.open(QIODevice::WriteOnly | QIODevice::Text);
    if (!configBak.isOpen())
        return false;
    QTextStream ts2(&configBak);
    for (QStringList::Iterator it = lines.begin(); it != lines.end(); ++it)
        ts2 << *it << "\n";
    configBak.close();

    return true;
}




