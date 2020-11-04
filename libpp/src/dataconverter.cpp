#include "dataconverter.h"
#include "ui_dataconverter.h"

DataConverter::DataConverter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataConverter)
{
    ui->setupUi(this);
}

DataConverter::~DataConverter()
{
    delete ui;
}
