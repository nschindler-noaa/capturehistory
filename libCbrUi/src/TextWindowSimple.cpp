/*
*
*/

#include <QPrinter>
#include <QPainter>
#include <QString>
#include <QTextBrowser>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QEvent>
#include <qregexp.h>
#include <qurl.h>
#include <QKeyEvent>
#include <QTextStream>
#include <QTextCursor>
#include <QPrinter>
#include <QPrintDialog>

#include "TextWindowSimple.h"

/* 
 *  Constructs a TextWindowSimple which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
TextWindowSimple::TextWindowSimple(QWidget* parent)
    : QMainWindow(parent), findPara(0), findIndex(0)
{
	setupUi(this);

    // signals and slots connections
    connect(printAction, SIGNAL(activated()), this, SLOT(doPrintAction()));
    connect(clearAllAction, SIGNAL(activated()), this, SLOT(doClearAllAction()));
    connect(saveAction, SIGNAL(activated()), this, SLOT(doSaveAction()));
    connect(exitAction, SIGNAL(activated()), this, SLOT(close()));
    connect(exitAction, SIGNAL(activated()), this, SLOT(doWindowClosing()));
    connect(findLineEdit, SIGNAL(textChanged(const QString&)),
        this, SLOT(doFindTextChanged(const QString&)));
    connect(findNextButton, SIGNAL(clicked()), this, SLOT(doFindNextButton()));
    connect(findPrevButton, SIGNAL(clicked()), this, SLOT(doFindPreviousButton()));
}

/*  
 *  Destroys the object and frees any allocated resources
 */
TextWindowSimple::~TextWindowSimple()
{
    // no need to delete child widgets, Qt does it all for us
}

void TextWindowSimple::doPrintAction() {
	QPrinter printer;
	QPrintDialog printDialog(&printer, this);
	if (printDialog.exec() != QDialog::Accepted)
		return;
	textBrowser->print(&printer);
}

void TextWindowSimple::doSaveAction() {
	QString text = textBrowser->toPlainText();
	QString filter;
	if (Qt::mightBeRichText(text)) 
		filter = "Rich Text (*.rtf)";
	else
		filter = "Text (*.txt)";
	filter += ";;All files (*.*)";
	QString fileName = 
		QFileDialog::getSaveFileName(this, QString(), QString(), filter);
     
	if (fileName.isNull())
		return;

	if (fileName.indexOf(QRegExp("\\.\\w{3}$")) == -1) {
		if (Qt::mightBeRichText(text)) 
			fileName += ".rtf";
		else
			fileName += ".txt";
	}
	
	QFile f(fileName);
	if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {    // file opened successfully
		QTextStream t(&f);        // use a text stream	
		t << textBrowser->toPlainText() << endl;
	}
	f.close();

}

void TextWindowSimple::clear() {
	textBrowser->clear();
}

void TextWindowSimple::doClearAllAction() {
	int button = QMessageBox::warning(this, "USER", "Clear all text?",
		QMessageBox::Yes, QMessageBox::No);
	if (button == 3) {
		clear();
	}
}

void TextWindowSimple::setTextFormat(Qt::TextFormat f) {
	Q_UNUSED(f);
	//textBrowser->setTextFormat(f);
}

void TextWindowSimple::setSource (const QString& file) {
	textBrowser->setSource(file);
}

void TextWindowSimple::doWindowClosing() {
	emit windowOpen(false);
}

void TextWindowSimple::closeEvent(QCloseEvent* e) {
	emit windowOpen(false);
	QWidget::closeEvent(e);
}

void TextWindowSimple::keyPressEvent (QKeyEvent* event) {
    if (event->key() == Qt::Key_F && event->modifiers() == Qt::ControlModifier) 
        findLineEdit->setFocus();
    else 
        event->ignore();
}

void TextWindowSimple::doFindTextChanged(const QString& text) {
    int textLength = text.length();
    findIndex -= textLength;
    findText = text;
    if (!doFindText(true))
        doFindText(false);
}

void TextWindowSimple::doFindNextButton() {
    QTextCursor oldCursor = textBrowser->textCursor();
    doFindText(true);
    if (oldCursor == textBrowser->textCursor()) {
        findIndex += findText.length();
        if (!doFindText(true)) 
            doFindText(false);
    }
}

void TextWindowSimple::doFindPreviousButton() {
    if (!doFindText(false)) 
        doFindText(true);
}

bool TextWindowSimple::doFindText(bool forward) {
	Q_UNUSED(forward);
	if (textBrowser->find(findText)) { //, false, false, forward, &findPara, &findIndex)) {
		//set background to QColor::fromRgb(255, 255, 255)
		return true;
	} 
	else {
		//set backround to QColor::fromRgb(255, 0, 0, 50)
		return false;
	}
	return false;
}
