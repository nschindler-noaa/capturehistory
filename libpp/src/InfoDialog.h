#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QWidget *parent = nullptr);
    ~InfoDialog();

    void setVersion(QString ver);
    void setDate(QString date);

private:
    Ui::InfoDialog *ui;
};

#endif // INFODIALOG_H
