#ifndef TextWindow_h
#define TextWindow_h

#include <QTextCursor>
#include <QTextBlockFormat>
#include <QTextCharFormat>
#include <QTextTableFormat>
#include <QFont>
#include <QWidget>
#include <QTextTable>
#include <QMainWindow>
#include <vector>

#include "ui_TextWindow.h"


class TextWindow : public QMainWindow, public Ui::TextWindow {

    Q_OBJECT
public:
    enum SaveMode {
        HTML = 0, TXT, CSV, ALL
    };

    TextWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

    ~TextWindow() {
    }

    const QTextBlockFormat& headerBlockFormat() const {
        return headerBlockFormat_;
    }

    const QTextCharFormat& headerCharFormat() const {
        return headerCharFormat_;
    }

    const QTextBlockFormat& subheaderBlockFormat() const {
        return subheaderBlockFormat_;
    }

    const QTextCharFormat& subheaderCharFormat() const {
        return subheaderCharFormat_;
    }

    const QTextTableFormat& tableFormat() const {
        return tableFormat_;
    }

    const QFont& tableHeaderFont() const {
        return tableHeaderFont_;
    }
    void insertHeader(const QString& headerText);
    void insertSubheader(const QString& subheaderText);
    QTextTable* insertTable(int nrow, int ncol);

    QTextCursor& textCursor() {
        return cursor_;
    }

    void clear() {
        textEdit->clear();
    }
    void addTableColumnHeaders(QTextTable* table, const std::vector<QString>& headers, int startingColumn);

    void setAcceptRichText(bool rhs) {
        textEdit->setAcceptRichText(rhs);
    }

    void setSaveMode(SaveMode mode) {
        saveMode_ = mode;
    }

    SaveMode getSaveMode() const {
        return saveMode_;
    }

    QTextCursor &cursor();
    void goToTop();

private slots:
    void doPrintAction();
    void doSaveAsAction();

signals:
    void saved(const QString&);

private:
    SaveMode saveMode_;

    QTextBlockFormat headerBlockFormat_;
    QTextBlockFormat subheaderBlockFormat_;
    QTextCharFormat headerCharFormat_;
    QTextCharFormat subheaderCharFormat_;
    QTextCharFormat tableHeaderCharFormat_;
    QTextTableFormat tableFormat_;
    QTextCharFormat tableHeaderFormat_;
    QFont headerFont_;
    QFont subheaderFont_;
    QFont tableHeaderFont_;
    QTextCursor cursor_;
};


#endif
