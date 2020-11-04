#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);

    connect (ui->buttonOk, SIGNAL(released()), this, SLOT(close()));
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::setVersion(QString ver)
{
    ui->versionLabel->setText(ver);
}
