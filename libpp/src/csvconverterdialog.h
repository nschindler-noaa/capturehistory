#ifndef CSVCONVERTERDIALOG_H
#define CSVCONVERTERDIALOG_H

#include <QDialog>

namespace Ui {
class CsvConverterDialog;
}

class CsvConverterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CsvConverterDialog(QWidget *parent = 0);
    ~CsvConverterDialog();

private:
    Ui::CsvConverterDialog *ui;
};

#endif // CSVCONVERTERDIALOG_H
