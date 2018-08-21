/*
 *
 */

#ifndef EditWindow_H
#define EditWindow_H

#include <qstring.h>

#include "tmp/ui_editwindow.h"
//#include "ui_editwindow.h"
#include <QMainWindow>

class EditWindow : public QMainWindow, public Ui::EditWindow
{
    Q_OBJECT

public:
    EditWindow(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
    ~EditWindow();

public slots:
	void setSource(const QString& file);
	void print();
	void open();
	void save();
	void saveAs();
	void doTextChanged();

protected:
	void closeEvent (QCloseEvent* e);

private:
	QString currentFile;
	void saveFile(const QString& file);
	bool twChanged;

};

#endif
