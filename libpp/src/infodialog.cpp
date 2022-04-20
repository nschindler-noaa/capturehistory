#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);

    connect (ui->button_ok, SIGNAL(released()), this, SLOT(close()));
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::setVersion(QString ver)
{
    ui->label_version->setText(ver);
}

void InfoDialog::setDate(QString date)
{
    ui->label_date->setText(date);
}
