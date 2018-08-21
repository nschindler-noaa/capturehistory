/*
 *
 */

#ifndef NEWEDITWINDOW_H
#define NEWEDITWINDOW_H

#include <QMainWindow>

namespace Ui {
class newEditWindow;
}

class newEditWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit newEditWindow(QWidget *parent = 0, const QString &name = QString(""), Qt::WindowFlags f = 0);
    ~newEditWindow();

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


    Ui::newEditWindow *ui;

};

#endif // NEWEDITWINDOW_H
