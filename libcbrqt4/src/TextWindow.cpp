#include "TextWindow.h"
#include <QMainWindow>
#include <QWidget>
#include <QTextTable>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

TextWindow::TextWindow(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    saveMode_ = (TXT);
    headerFont_ = (font());
    subheaderFont_ = (font());
    tableHeaderFont_ = (font());

    setupUi(this);
    connect(actionSaveAs, SIGNAL(triggered()), SLOT(doSaveAsAction()));
    connect(actionPrint, SIGNAL(triggered()), SLOT(doPrintAction()));
    connect(actionExit, SIGNAL(triggered()), SLOT(close()));

    headerBlockFormat_.setAlignment(Qt::AlignLeft);
    headerBlockFormat_.setBottomMargin(18);
    headerFont_.setFamily("Arial");
    headerFont_.setPointSize(14);
    headerFont_.setBold(true);
    headerFont_.setUnderline(true);

    headerCharFormat_.setFont(headerFont_);

    subheaderBlockFormat_.setAlignment(Qt::AlignLeft);
    subheaderBlockFormat_.setTopMargin(18);
    subheaderBlockFormat_.setBottomMargin(12);
    subheaderFont_.setPointSize(14);//.setPixelSize(14);
    subheaderFont_.setBold(true);
    subheaderCharFormat_.setFont(subheaderFont_);

    tableFormat_.setCellPadding(0.1 * 72);
    tableFormat_.setMargin(12);
    tableHeaderFont_.setPointSize(14);//.setPixelSize(12);
    tableHeaderFont_.setBold(true);
    tableHeaderCharFormat_.setFont(tableHeaderFont_);

    cursor_ = QTextCursor(textEdit->document());
}

QTextCursor &TextWindow::cursor() {
    return cursor_;
}

void TextWindow::goToTop() {
    textEdit->setTextCursor(textEdit->document()->rootFrame()->firstCursorPosition());
    textEdit->ensureCursorVisible();
}

void TextWindow::doSaveAsAction() {
    QString filter;
    QString csvFilter = "CSV (*.csv)";
    QString htmlFilter = "HTML (*.htm *.html)";
    QString textFilter = "Text (*.txt)";
    QString allFilter = "All (*.*)";
    QString startFile = QDir::home().filePath("output");
    switch (saveMode_) {
        case CSV:
            filter = csvFilter;
            startFile += ".csv";
            break;
        case TXT:
            filter = textFilter;
            startFile += ".txt";
            break;
        default:
            filter = htmlFilter;
            startFile += ".thml";
    }

    QFileDialog fd(this, "Save File", startFile, filter);
    fd.setFileMode(QFileDialog::AnyFile);
    fd.setAcceptMode(QFileDialog::AcceptSave);
    fd.setViewMode(QFileDialog::List);
    if (fd.exec()) {
        QFile file(fd.selectedFiles().first());// selectedFile());
        file.open(QIODevice::ReadWrite);
        QTextStream os(&file);
        if (!filter.compare(htmlFilter))
            os << textEdit->toHtml();
        else
            os << textEdit->toPlainText();
        file.close();

        emit saved(fd.selectedFiles().first());
    }
}

void TextWindow::doPrintAction() {
    QTextDocument* document = textEdit->document();
    QPrinter printer;
    QPrintDialog* dlg = new QPrintDialog(&printer, this);
    if (dlg->exec() != QDialog::Accepted)
        return;
    document->print(&printer);
}

void TextWindow::insertHeader(const QString& headerText) {
    cursor_.movePosition(QTextCursor::End);
    cursor_.insertBlock(headerBlockFormat_, headerCharFormat_);
    cursor_.insertText(headerText);
}

void TextWindow::insertSubheader(const QString& subheaderText) {
    cursor_.movePosition(QTextCursor::End);
    cursor_.insertBlock(subheaderBlockFormat_, subheaderCharFormat_);
    cursor_.insertText(subheaderText);
}

QTextTable* TextWindow::insertTable(int nrow, int ncol) {
    cursor_.movePosition(QTextCursor::End);
    return cursor_.insertTable(nrow, ncol, tableFormat_);
}

void TextWindow::addTableColumnHeaders(QTextTable* table, const std::vector<QString>& headers, int startingColumn) {
    for (unsigned int i = startingColumn; i < headers.size(); ++i)
        table->cellAt(0, i).firstCursorPosition().insertText(headers[i], tableHeaderCharFormat_);
}
