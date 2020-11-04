/********************************************************************************
** Form generated from reading UI file 'TextWindow.ui'
**
** Created: Mon Nov 2 11:17:57 2020
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTWINDOW_H
#define UI_TEXTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextWindow
{
public:
    QAction *actionSaveAs;
    QAction *actionPrint;
    QAction *actionExit;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menu_File;

    void setupUi(QMainWindow *TextWindow)
    {
        if (TextWindow->objectName().isEmpty())
            TextWindow->setObjectName(QString::fromUtf8("TextWindow"));
        TextWindow->resize(706, 600);
        actionSaveAs = new QAction(TextWindow);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        actionPrint = new QAction(TextWindow);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        actionExit = new QAction(TextWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(TextWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setReadOnly(true);

        gridLayout->addWidget(textEdit, 0, 0, 1, 1);

        TextWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(TextWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        TextWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(TextWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 706, 21));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        TextWindow->setMenuBar(menubar);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(actionSaveAs);
        menu_File->addAction(actionPrint);
        menu_File->addSeparator();
        menu_File->addAction(actionExit);

        retranslateUi(TextWindow);

        QMetaObject::connectSlotsByName(TextWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TextWindow)
    {
        TextWindow->setWindowTitle(QString());
        actionSaveAs->setText(QApplication::translate("TextWindow", "&Save as...", 0, QApplication::UnicodeUTF8));
        actionPrint->setText(QApplication::translate("TextWindow", "&Print...", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("TextWindow", "Close", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("TextWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TextWindow: public Ui_TextWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTWINDOW_H
