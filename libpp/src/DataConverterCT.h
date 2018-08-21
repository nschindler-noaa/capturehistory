/*
*/

#ifndef DataConverterCT_h
#define DataConverterCT_h

#include <QThread>
#include <ComputationThread.h>

class DataConverterCT : public ComputationThread
{
public:
	enum ConvertType { Obs, Tag, Both, Invalid };
	DataConverterCT( QObject* object, const QString& name );
	void compute();
	void setConvertType( ConvertType type ) { convertType = type; }

public slots:
	void setFiles( const QString& obs, const QString& tag, const QString& rel, const QString& tobs, const QString& ttag );

private:
	QString obs;
	QString tag;
	QString rel;
	QString tobs;
	QString ttag;
	ConvertType convertType;

	int getTotalBytes();
	void cancel();

};

#endif
