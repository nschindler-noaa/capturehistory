/*
*
*/

#include "TextWindowSimple.h"
#include "ui_TextWindowSimple.h"

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

/*
 *  Constructs a TextWindowSimple which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 */
TextWindowSimple::TextWindowSimple(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::TextWindowSimple)
{
    ui->setupUi(this);
    findIndex = 0;
    findPara = 0;

    // signals and slots connections
    connect(ui->printAction, SIGNAL(activated()), this, SLOT(doPrintAction()));
    connect(ui->clearAction, SIGNAL(activated()), this, SLOT(doClearAllAction()));
    connect(ui->saveAction, SIGNAL(activated()), this, SLOT(doSaveAction()));
    connect(ui->exitAction, SIGNAL(activated()), this, SLOT(close()));
    connect(ui->exitAction, SIGNAL(activated()), this, SLOT(doWindowClosing()));
    connect(ui->findLineEdit, SIGNAL(textChanged(const QString&)),
        this, SLOT(doFindTextChanged(const QString&)));
    connect(ui->findNextButton, SIGNAL(clicked()), this, SLOT(doFindNextButton()));
    connect(ui->findPrevButton, SIGNAL(clicked()), this, SLOT(doFindPreviousButton()));
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
    ui->textBrowser->print(&printer);
}

void TextWindowSimple::doSaveAction() {
    QString text = ui->textBrowser->toPlainText();
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
        t << ui->textBrowser->toPlainText() << endl;
    }
    f.close();

}

void TextWindowSimple::clear() {
    ui->textBrowser->clear();
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

void TextWindowSimple::appendText(const QString& s) {
    if (!s.isNull()) ui->textBrowser->append(s);
}

void TextWindowSimple::setText(const QString& s) {
    if (!s.isNull()) ui->textBrowser->setText(s);
}

void TextWindowSimple::setFont(const QFont& font) {
    ui->textBrowser->setFont(font);
}

void TextWindowSimple::setSource (const QString& file) {
    ui->textBrowser->setSource(file);
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
        ui->findLineEdit->setFocus();
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
    QTextCursor oldCursor = ui->textBrowser->textCursor();
    doFindText(true);
    if (oldCursor == ui->textBrowser->textCursor()) {
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
    bool found = false;
    if (!findText.isEmpty()) {
        if (forward) {
            found = ui->textBrowser->find(findText);
        }
        else {
            found = ui->textBrowser->find(findText, QTextDocument::FindBackward);
        }
    }
    if (found) {
        //set background to QColor::fromRgb(255, 255, 255)
        ui->findLineEdit->setBackgroundRole(QPalette::Base);
    }
    else {
        //set backround to QColor::fromRgb(255, 0, 0, 50)
        ui->findLineEdit->setBackgroundRole(QPalette::AlternateBase);
    }
    return found;
}
