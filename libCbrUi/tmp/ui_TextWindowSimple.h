/********************************************************************************
** Form generated from reading UI file 'TextWindowSimple.ui'
**
** Created: Mon Nov 2 11:18:15 2020
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTWINDOWSIMPLE_H
#define UI_TEXTWINDOWSIMPLE_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextWindowSimple
{
public:
    QAction *exitAction;
    QAction *printAction;
    QAction *clearAllAction;
    QAction *saveAction;
    QWidget *widget;
    QVBoxLayout *vboxLayout;
    QVBoxLayout *mainLayout;
    QTextBrowser *textBrowser;
    QHBoxLayout *footerLayout;
    QLabel *findLabel;
    QLineEdit *findLineEdit;
    QPushButton *findNextButton;
    QPushButton *findPrevButton;
    QSpacerItem *footerSpacer;
    QMenuBar *menubar;
    QMenu *filePopup;

    void setupUi(QMainWindow *TextWindowSimple)
    {
        if (TextWindowSimple->objectName().isEmpty())
            TextWindowSimple->setObjectName(QString::fromUtf8("TextWindowSimple"));
        TextWindowSimple->resize(600, 480);
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("file")));
        TextWindowSimple->setWindowIcon(icon);
        exitAction = new QAction(TextWindowSimple);
        exitAction->setObjectName(QString::fromUtf8("exitAction"));
        printAction = new QAction(TextWindowSimple);
        printAction->setObjectName(QString::fromUtf8("printAction"));
        clearAllAction = new QAction(TextWindowSimple);
        clearAllAction->setObjectName(QString::fromUtf8("clearAllAction"));
        saveAction = new QAction(TextWindowSimple);
        saveAction->setObjectName(QString::fromUtf8("saveAction"));
        widget = new QWidget(TextWindowSimple);
        widget->setObjectName(QString::fromUtf8("widget"));
        vboxLayout = new QVBoxLayout(widget);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        mainLayout = new QVBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        textBrowser = new QTextBrowser(widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        textBrowser->setFont(font);

        mainLayout->addWidget(textBrowser);

        footerLayout = new QHBoxLayout();
        footerLayout->setSpacing(6);
        footerLayout->setObjectName(QString::fromUtf8("footerLayout"));
        footerLayout->setContentsMargins(0, 0, 0, 0);
        findLabel = new QLabel(widget);
        findLabel->setObjectName(QString::fromUtf8("findLabel"));

        footerLayout->addWidget(findLabel);

        findLineEdit = new QLineEdit(widget);
        findLineEdit->setObjectName(QString::fromUtf8("findLineEdit"));

        footerLayout->addWidget(findLineEdit);

        findNextButton = new QPushButton(widget);
        findNextButton->setObjectName(QString::fromUtf8("findNextButton"));

        footerLayout->addWidget(findNextButton);

        findPrevButton = new QPushButton(widget);
        findPrevButton->setObjectName(QString::fromUtf8("findPrevButton"));

        footerLayout->addWidget(findPrevButton);

        footerSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        footerLayout->addItem(footerSpacer);


        mainLayout->addLayout(footerLayout);


        vboxLayout->addLayout(mainLayout);

        TextWindowSimple->setCentralWidget(widget);
        menubar = new QMenuBar(TextWindowSimple);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 22));
        filePopup = new QMenu(menubar);
        filePopup->setObjectName(QString::fromUtf8("filePopup"));
        TextWindowSimple->setMenuBar(menubar);

        menubar->addAction(filePopup->menuAction());
        filePopup->addAction(saveAction);
        filePopup->addAction(printAction);
        filePopup->addSeparator();
        filePopup->addAction(exitAction);

        retranslateUi(TextWindowSimple);

        QMetaObject::connectSlotsByName(TextWindowSimple);
    } // setupUi

    void retranslateUi(QMainWindow *TextWindowSimple)
    {
        TextWindowSimple->setWindowTitle(QApplication::translate("TextWindowSimple", "Text Window", 0, QApplication::UnicodeUTF8));
        exitAction->setText(QApplication::translate("TextWindowSimple", "Close", 0, QApplication::UnicodeUTF8));
        exitAction->setIconText(QApplication::translate("TextWindowSimple", "Close", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        exitAction->setToolTip(QApplication::translate("TextWindowSimple", "Close the window", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        exitAction->setShortcut(QApplication::translate("TextWindowSimple", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        printAction->setText(QApplication::translate("TextWindowSimple", "Print", 0, QApplication::UnicodeUTF8));
        printAction->setIconText(QApplication::translate("TextWindowSimple", "Print", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        printAction->setToolTip(QApplication::translate("TextWindowSimple", "Print the contents of the window", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        printAction->setShortcut(QApplication::translate("TextWindowSimple", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        clearAllAction->setText(QApplication::translate("TextWindowSimple", "Clear all", 0, QApplication::UnicodeUTF8));
        clearAllAction->setIconText(QApplication::translate("TextWindowSimple", "Clear all", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        clearAllAction->setToolTip(QApplication::translate("TextWindowSimple", "Clear text window contents", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saveAction->setText(QApplication::translate("TextWindowSimple", "Save as...", 0, QApplication::UnicodeUTF8));
        saveAction->setIconText(QApplication::translate("TextWindowSimple", "Save as...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saveAction->setToolTip(QApplication::translate("TextWindowSimple", "Save contents of text window to file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        findLabel->setText(QApplication::translate("TextWindowSimple", "Find:", 0, QApplication::UnicodeUTF8));
        findNextButton->setText(QApplication::translate("TextWindowSimple", "Next", 0, QApplication::UnicodeUTF8));
        findPrevButton->setText(QApplication::translate("TextWindowSimple", "Previous", 0, QApplication::UnicodeUTF8));
        filePopup->setTitle(QApplication::translate("TextWindowSimple", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TextWindowSimple: public Ui_TextWindowSimple {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTWINDOWSIMPLE_H
