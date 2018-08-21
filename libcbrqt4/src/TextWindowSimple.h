/*
*
*/

#ifndef TEXTWINDOWSIMPLE_H
#define TEXTWINDOWSIMPLE_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QStyle>
//#include <Q3MainWindow>
//#include <Q3TextBrowser>
//#include <Q3StyleSheet>

#include <QTextCursor>

class QCloseEvent;

#include "ui_TextWindowSimple.h"

class QPrinter;

class TextWindowSimple : public QMainWindow, public Ui_TextWindowSimple
{ 
    Q_OBJECT

public:
    TextWindowSimple(QWidget* parent = 0, const char* name=0, Qt::WindowFlags fl = 0);
    virtual ~TextWindowSimple();

    QStyleSheet* styleSheet() { return textBrowser->styleSheet(); }



protected:
	void closeEvent(QCloseEvent* e);
    void keyPressEvent (QKeyEvent* event);

public slots:
	void doPrintAction();
	void doSaveAction();
	void doClearAllAction();
	void doWindowClosing();
    void setTextFormat(Qt::TextFormat f);
    void appendText(const QString& s) { if (!s.isNull()) textBrowser->append(s); }
	void setText(const QString& s) { if (!s.isNull()) textBrowser->setText(s); }
	void clear();
	void setFont(const QFont& font) { textBrowser->setFont(font); }
	void setSource(const QString& file);
    void doFindTextChanged(const QString& text);
	//void setStyleSheet(QStyleSheet* ss) { textBrowser->setStyleSheet(ss); }
    void doFindNextButton();
    void doFindPreviousButton();

signals:
	void windowOpen(bool rhs);

private:
    int findPara;
    int findIndex;
    QString findText;
    bool doFindText(bool forward = true);
};

#endif // TEXTWINDOWSIMPLE_H
