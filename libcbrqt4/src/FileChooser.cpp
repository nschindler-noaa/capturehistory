#include "FileChooser.h"
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qfiledialog.h>
#include <qlayout.h>


void Preview::previewUrl(const QUrl &u) {
	QString path = u.path();
	if (QFile::exists(path)) 
		setSource(path);
//	else
//		setSource(QString::null);
}

FileChooser::FileChooser(QWidget *parent, const char *name)
    : QHBoxLayout(parent), md(File), tp(Open), pv(false), p(0)
{
    setObjectName(name);
    lineEdit = new QLineEdit(0);//, "filechooser_lineedit");
    lineEdit->setObjectName("filechooser_lineedit");
    
    connect(lineEdit, SIGNAL(textChanged(const QString &)),
        this, SIGNAL(fileNameChanged(const QString &)));
    
    button = new QPushButton("...", 0); //, "filechooser_button");
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
    QString fn;
/*    if (mode() == File) {
        QFileDialog* fd = new QFileDialog(this);
		fd->setModal(true);

		if (preview()) {
			if (!p)
				p = new Preview(this);
			fd->setContentsPreviewEnabled(TRUE);
			fd->setContentsPreview(p, p);
            fd->setPreviewMode(QFileDialog::Contents);
			QString types("Text files (*.txt);;");
			fd->setFilters(types);
		}

#if 0
        if (type() == Open)
            fn = Q3FileDialog::getOpenFileName(lineEdit->text(), QString::null, this);
        else if (type() == Save)
            fn = Q3FileDialog::getSaveFileName(lineEdit->text(), QString::null, this);
#endif

		if (fd->exec() == QDialog::Accepted)
			fn = fd->selectedFile();
    }
    else
        fn = QFileDialog::getExistingDirectory(lineEdit->text(),this);
    
    if (!fn.isEmpty()) {
        lineEdit->setText(fn);
        emit fileNameChanged(fn);
    }*/
}

