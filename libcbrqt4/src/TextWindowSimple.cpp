/*
*
*/

#include <QPrinter>
#include <QPainter>
#include <QString>
//#include <Q3TextBrowser>
#include <QTextBrowser>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QEvent>
#include <qregexp.h>
#include <QTextEdit>
//#include <Q3SimpleRichText>
#include <qurl.h>
#include <QKeyEvent>

#include "TextWindowSimple.h"

/* 
 *  Constructs a TextWindowSimple which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
TextWindowSimple::TextWindowSimple(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QMainWindow(parent,  name, fl), findPara(0), findIndex(0)
{
	setupUi(this);

	// cancel word wrap in the text browser
    textBrowser->setWordWrap(QTextEdit::WidgetWidth);

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
    printer.setFullPage(TRUE);
    if (printer.setup(this)) {
        QPainter p(&printer);
		
		// get the device sizes
		QPaintDevice* device = p.device();
        int dpix = device->logicalDpiX();
        int dpiy = device->logicalDpiY();
        const int margin = 72; // pt
        QRect body(margin * dpix / 72, margin * dpiy / 72,
                   device->width() - margin * dpix / 72 * 2,
                  device->height() - margin * dpiy / 72 * 2);

		// get the font
        QFont font(textBrowser->font());

		// set up the rich text object
		QString outstring = "<pre>" + textBrowser->text() + "</pre>";
        QTextEdit richText(outstring, font, textBrowser->context(),
			textBrowser->styleSheet(), textBrowser->mimeSourceFactory(), 
			body.height());
        richText.setWidth(&p, body.width());

		// initialize view to the display 
        QRect view(body);
        int page = 1;
		int totalPrinted = 0;
        do {

			// print the page
            richText.draw(&p, body.left(), body.top(), view, colorGroup());

			// move the view and adjust the printer coordinates 
            view.moveBy(0, body.height());
   			totalPrinted += body.height();
			p.translate(0 , -body.height());
 
			// print the page number
			p.setFont(font);
			QString pageNum = QString::number(page);
            p.drawText(view.right() - p.fontMetrics().width(pageNum),
                        view.bottom() + p.fontMetrics().ascent() + 5, 
						pageNum);

			// check if there are more pages
            if (totalPrinted  >= richText.height())
                break;
            printer.newPage();
            page++;
        } while (TRUE);
    }
}

void TextWindowSimple::doSaveAction() {
	QString text = textBrowser->text();
	QString filter;
    if (QStyleSheet::mightBeRichText(text))
		filter = "Rich Text (*.rtf)";
	else
		filter = "Text (*.txt)";
	filter += ";;All files (*.*)";
	QString fileName = 
		QFileDialog::getSaveFileName("", filter, this);
     
	if (fileName.isNull())
		return;

	if (fileName.find(QRegExp("\\.\\w{3}$")) == -1) {
        if (QStyleSheet::mightBeRichText(text))
			fileName += ".rtf";
		else
			fileName += ".txt";
	}
	
	QFile f(fileName);
	if (f.open(IO_WriteOnly | IO_Translate)) {    // file opened successfully
		QTextStream t(&f);        // use a text stream	
		t << textBrowser->text() << endl;
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
    textBrowser->setTextFormat(f);
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
    int oldFindIndex = findIndex;
    int oldFindPara = findPara;
    doFindText(true);
    if (oldFindIndex == findIndex && oldFindPara == findPara) {
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
    if (textBrowser->find(findText, false, false, forward, &findPara, &findIndex)) {
        findLineEdit->setBackgroundColor(QColor::fromRgb(255, 255, 255));
        return true;
    } else {
        findLineEdit->setBackgroundColor(QColor::fromRgb(255, 0, 0, 50));
        return false;
    }
}
