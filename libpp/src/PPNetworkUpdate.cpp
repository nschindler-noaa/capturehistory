/*
 *
 */

#include <string>

#include <qurloperator.h>
#include <qnetworkprotocol.h>

#include "PPNetworkUpdate.h"
#include "PPVersion.h"

using std::string;

void PPNetworkUpdate::checkVersion()
{
	string version = PPVersion::versionString();
	string url = "http://www.cbr.washington.edu/paramest/pitpro/version/version.txt";

	op = new QUrlOperator();
	connect(op, SIGNAL( finished(QNetworkOperation*) ), SLOT(operationFinished(QNetworkOperation*)));
	op->copy(url, "file:/cbr", false );
	bool here = true;
}

void PPNetworkUpdate::operationFinished( QNetworkOperation *op )
{
    switch ( op->operation() ) {
    case QNetworkProtocol::StDone: 
		moreRecent = true;
        break;
    }
}
