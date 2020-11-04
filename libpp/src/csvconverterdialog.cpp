#include "csvconverterdialog.h"
#include "ui_csvconverterdialog.h"

CsvConverterDialog::CsvConverterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CsvConverterDialog)
{
    ui->setupUi(this);
}

CsvConverterDialog::~CsvConverterDialog()
{
    delete ui;
}
