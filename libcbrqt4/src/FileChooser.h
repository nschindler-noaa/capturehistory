#ifndef FILECHOOSER_H
#define FILECHOOSER_H

#include <QHBoxLayout>
#include <QTextBrowser>
#include <QFileDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
//#include <QFileSelector>
//#include <q3hbox.h>
//#include <q3textbrowser.h>
//#include <q3filedialog.h>

class QLineEdit;
class QPushButton;

class Preview : public QTextBrowser//, public QFilePreview
{
public:
    Preview(QWidget *parent = nullptr) : QTextBrowser(parent) {}
    void previewUrl(const QUrl &u);
};

class FileChooser : public QHBoxLayout// QHBox
{
    Q_OBJECT

    Q_ENUMS(Mode)
    Q_ENUMS(Type)
    Q_PROPERTY(Mode mode READ mode WRITE setMode)
    Q_PROPERTY(Type type READ type WRITE setType)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName)
    Q_PROPERTY(bool preview READ preview WRITE setPreview)

public:
    FileChooser(QWidget *parent = nullptr, const char *name = nullptr);

    enum Mode { File, Directory };
    enum Type { Open, Save };

    QString fileName() const;
    Mode mode() const;
    Type type() const;
    bool preview() const;

public slots:
    void setFileName(const QString &fn);
    void setMode(Mode m);
    void setType(Type t);
    void setPreview(bool rhs);

signals:
    void fileNameChanged(const QString &);

private slots:
    void chooseFile();

private:
    QLineEdit *lineEdit;
    QPushButton *button;
    Mode md;
    Type tp;
    bool pv;
    Preview* p;

};

#endif
