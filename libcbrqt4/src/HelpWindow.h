#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include "ui_HelpWindow.h"

class HelpWindow : public Q3MainWindow, public Ui_HelpWindow
{
    Q_OBJECT

public:
    HelpWindow(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = Qt::WType_TopLevel);
    ~HelpWindow();

public slots:
	void doSaveAsAction();
	void doHomeAction();

};

#endif // HELPWINDOW_H
