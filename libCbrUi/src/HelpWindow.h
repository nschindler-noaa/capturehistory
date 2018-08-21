#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include "ui_HelpWindow.h"

class HelpWindow : public QMainWindow, public Ui_HelpWindow
{
    Q_OBJECT

public:
	HelpWindow(QWidget* parent = 0);
    ~HelpWindow();

public slots:
	void doSaveAsAction();
	void doHomeAction();

};

#endif // HELPWINDOW_H
