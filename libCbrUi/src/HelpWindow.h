#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QMainWindow>

namespace Ui {
class HelpWindow;
}

class HelpWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HelpWindow(QWidget *parent = 0);
    ~HelpWindow();

public slots:
    void doSaveAsAction();
    void doHomeAction();

private:
    Ui::HelpWindow *ui;
};

#endif // HELPWINDOW_H
