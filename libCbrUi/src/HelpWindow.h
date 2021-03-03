#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QMainWindow>

#include "ui_HelpWindow.h"

class HelpWindow : public QMainWindow, public Ui_HelpWindow
{
    Q_OBJECT

public:
    HelpWindow(QWidget* parent = nullptr);
    ~HelpWindow();

public slots:
    void doSaveAsAction();
    void doHomeAction();

};

#endif // HELPWINDOW_H
