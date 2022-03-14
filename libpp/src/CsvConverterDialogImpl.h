/*
 * CsvConverterDialogImpl.h
 *
 */

#ifndef CsvConverterDialogImpl_h
#define CsvConverterDialogImpl_h

#include <qcheckbox.h>

#include "ui_csvconverterdialog.h"
#include "CsvConverter.h"

class CsvConverterDialogImpl : public QDialog, public Ui::CsvConverterDialog
{
    Q_OBJECT

private:
    QString csvFile;
    QString outFile;

    QString getDataSuffix();

public:

    CsvConverterDialogImpl( QWidget* parent = 0, Qt::WindowFlags fl = 0 );
    ~CsvConverterDialogImpl();

    QString getCsvFile();
    QString getOutFile();
    bool getIsHeader();
    CsvConverter::DataType getCsvType();


/*
 * Refresh the run setup tab
 */
public slots:
    void csvFileSelected( const QString& fileName );
    void accept();
    void reject();
    void updateTable();
    void doTypeToggled( bool rhs );

};

#endif // CsvConverterDialogImpl_h
