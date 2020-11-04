/*
 *
 */

#ifndef UpdateManagerImpl_h
#define UpdateManagerImpl_h

#include <qstring.h>
#include <qpair.h>
#include <qfile.h>
#include <qdatastream.h>
#include <QProgressBar>
#include <QFile>
#include <QHttpMultiPart>
#include <QHttpPart>

#include "ui_UpdateManager.h"

// TODO: Redo this with Qt5 capabilities

typedef struct {
	int type;
	QString url;
	QString tempfile;
} Job;

class UpdateManagerImpl : public QDialog, public Ui::UpdateManager
{
    Q_OBJECT

public:
	enum Status {Ok, OutOfDate, Failed};
	enum DownLoadType {Version, SitesConfig, PitPro, Unset};

    UpdateManagerImpl( QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0 );
    ~UpdateManagerImpl();

public slots:
	void refresh();

private slots:
	void doUpdateButton();

    void httpRequestFinished(int requestId, bool error);
    void readResponseHeader(QString &responseHeader);//const QHttpResponseHeader &responseHeader);
    void updateDataReadProgress(int bytesRead, int totalBytes);


signals:
	void updateStatus(UpdateManagerImpl::Status status);
	void sitesConfigUpdated();

private:
	QVector<Job> jobs;

     QUrl *http;
     QFile *file;
     QString server;
     QString updatesUrl;
     QString versionsFile;
     QString sitesConfigFile;
	 int port;
     int httpGetId;
     bool httpRequestAborted;

	int comparePPVersions( const QString& current, const QString& avail ) const;
	void download();
	bool saveOldSitesConfig();
	QString getCurrentConfigVersion();
	void getVersionFinished(  const Job& job );
	void getSitesConfigFinished(  const Job& job  );
	void getPitProFinished(  const Job& job  );
	Job makeJob( const QString& url, DownLoadType type );

};

#endif // UPDATEMANAGERIMPL_H
