#ifndef RESULTMANAGER_H
#define RESULTMANAGER_H

#include <QMainWindow>

namespace Ui {
class ResultManager;
}

class ResultsManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit ResultsManager(QWidget *parent = 0);
    ~ResultsManager();

private:
    Ui::ResultManager *ui;
};

#endif // RESULTMANAGER_H
