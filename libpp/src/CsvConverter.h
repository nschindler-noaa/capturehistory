/*
 * CsvConverter.h
 */

#ifndef CsvConverter_h
#define CsvConverter_h

#include <QStringList>
#include <QThread>
#include "ComputationThread.h"

class CsvConverter : public ComputationThread {

public:
    enum DataType { Obs=0, Tag, Rel, Mort, Error};
    enum ObsCols { O_TagGroup=0, O_PitCode, O_Site, O_Date, 
        O_Time, O_NumCoils, O_Coil1, O_Coil2, O_TravelTime };
    enum TagCols { T_TagGroup=0, T_RelDate, T_RelTime, T_Species, 
        T_RearType, T_Length, T_Flags };
    enum MortCols { M_PitCode=0 };
    enum RelCols { R_TagGroup=0, R_Date, R_Time };

 	CsvConverter( QObject* parent, const QString& name );
	void compute();

public slots:
    void setCsvFile( const QString& csvFile );
    void setOutFile( const QString& outFile );
    void setIsHeader( bool rhs );
    void setDataType( DataType type );

private:
    QString csvFile;
    QString outFile;
    bool isHeader;
    DataType dataType;
};

#endif // CsvConverter_h
