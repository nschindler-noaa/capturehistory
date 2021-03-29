/*
*/

#include "HelpWindow.h"
#include "ui_HelpWindow.h"


HelpWindow::HelpWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
}

HelpWindow::~HelpWindow()
{
    delete ui;
}



void HelpWindow::doSaveAsAction()
{
}

void HelpWindow::doHomeAction()
{
}
