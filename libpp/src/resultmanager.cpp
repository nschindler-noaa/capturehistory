#include "resultmanager.h"
#include "ui_resultmanager.h"

ResultsManager::ResultsManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ResultManager)
{
    ui->setupUi(this);
}

ResultsManager::~ResultsManager()
{
    delete ui;
}
