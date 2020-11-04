/*
 *
 */

#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QWidget *parent = 0);
    ~InfoDialog();

    void setVersion(QString ver);

private:
    Ui::InfoDialog *ui;
};

#endif // INFODIALOG_H

/*
#include "ui_InfoDialog.h"   

class InfoDialog : public QDialog, public Ui::InfoDialog
{
public:
        InfoDialog(QWidget* parent, Qt::WindowFlags fl = 0)
		: QDialog(parent, fl)
	{ setupUi(this); }
};*/
