/*
*
*/

#ifndef TEXTWINDOWSIMPLE_H
#define TEXTWINDOWSIMPLE_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QTextCursor>
#include <QPrinter>

namespace Ui {
class TextWindowSimple;
}


class TextWindowSimple : public QMainWindow
{
    Q_OBJECT

public:
    explicit TextWindowSimple(QWidget *parent = nullptr);
    ~TextWindowSimple();


protected:
    void closeEvent(QCloseEvent* e);
    void keyPressEvent (QKeyEvent* event);

public slots:
    void doPrintAction();
    void doSaveAction();
    void doClearAllAction();
    void doWindowClosing();
    void setTextFormat(Qt::TextFormat f);
    void appendText(const QString& s);// { if (!s.isNull()) textBrowser->append(s); }
    void setText(const QString& s);// { if (!s.isNull()) textBrowser->setText(s); }
    void clear();
    void setFont(const QFont& font);// { textBrowser->setFont(font); }
    void setSource(const QString& file);
    void doFindTextChanged(const QString& text);
    void doFindNextButton();
    void doFindPreviousButton();

signals:
    void windowOpen(bool rhs);

private:
    int findPara;
    int findIndex;
    QString findText;
    bool doFindText(bool forward = true);

    Ui::TextWindowSimple *ui;
};

#endif // TEXTWINDOWSIMPLE_H
