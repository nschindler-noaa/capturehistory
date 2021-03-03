#include "FileChooser.h"
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qfiledialog.h>
#include <qlayout.h>


void Preview::previewUrl(const QUrl &u) {
    QString path = u.path();
    if (QFile::exists(path))
        setSource(path);
    else
        setSource(QUrl(QString::null));
}

FileChooser::FileChooser(QWidget *parent, const char *name)
    : QHBoxLayout(parent), md(File), tp(Open), pv(false), p(nullptr)
{
    setObjectName(name);
    lineEdit = new QLineEdit();//, "filechooser_lineedit");
    lineEdit->setObjectName("filechooser_lineedit");

    connect(lineEdit, SIGNAL(textChanged(const QString &)),
        this, SIGNAL(fileNameChanged(const QString &)));

    button = new QPushButton("..."); //, "filechooser_button");
    button->setObjectName("filechooser_button");
    button->setFixedWidth(button->fontMetrics().width(" ... "));

    connect(button, SIGNAL(clicked()),
        this, SLOT(chooseFile()));

//    setFocusProxy(lineEdit);
}

void FileChooser::setMode(Mode m)
{
    md = m;
}

FileChooser::Mode FileChooser::mode() const
{
    return md;
}

void FileChooser::setType(Type t)
{
    tp = t;
}

FileChooser::Type FileChooser::type() const
{
    return tp;
}


void FileChooser::setFileName(const QString &fn)
{
    lineEdit->setText(fn);
}

QString FileChooser::fileName() const
{
    return lineEdit->text();
}

void FileChooser::setPreview(bool rhs)
{
    pv = rhs;
}

bool FileChooser::preview() const
{
    return pv;
}

void FileChooser::chooseFile()
{
    QString fn("");
    if (mode() == File)
    {
        QFileDialog* fd = new QFileDialog();
        fd->setModal(true);
        QString types("Text files (*.txt);;");
        fd->setWindowTitle(tr("Select File"));
        fd->setNameFilter(types);

        if (preview()) {
            if (!p)
                p = new Preview();
//			fd->setContentsPreviewEnabled(TRUE);
//			fd->setContentsPreview(p, p);
//            fd->setPreviewMode(QFileDialog::Contents);
        }
        if (type() == Open) {
            fn = QFileDialog::getOpenFileName(nullptr, tr("Select File to Open"), QString(), types);
        }
        else { // if (type() == Save)
            fn = QFileDialog::getSaveFileName(nullptr, tr("Select File to Save"), QString(), types);
        }
    }
    else
    {
        fn = QFileDialog::getExistingDirectory(nullptr, tr("Select Directory"), lineEdit->text(),
                                               QFileDialog::ShowDirsOnly);
    }
    if (!fn.isEmpty()) {
        lineEdit->setText(fn);
        emit fileNameChanged(fn);
    }
}

