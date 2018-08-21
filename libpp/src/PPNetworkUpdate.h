/*
 *
 */

#ifndef PPNetworkUpdate_h
#define PPNetworkUpdate_h

#include <qobject.h>

class QUrlOperator;
class QNetworkOperation;

class PPNetworkUpdate : public QObject
{
	Q_OBJECT

public:
	PPNetworkUpdate() : op(0), moreRecent( false ) {}
	void checkVersion();
	bool isMoreRecent() const { return moreRecent; }

public slots:
	void operationFinished( QNetworkOperation *op );

private:
	
	bool moreRecent;
	QUrlOperator* op;
};

#endif