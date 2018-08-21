/********************************************************************************
** Form generated from reading UI file 'TextWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTWINDOW_H
#define UI_TEXTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

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
            TextWindow->setObjectName(QStringLiteral("TextWindow"));
        TextWindow->resize(706, 600);
        actionSaveAs = new QAction(TextWindow);
        actionSaveAs->setObjectName(QStringLiteral("actionSaveAs"));
        actionPrint = new QAction(TextWindow);
        actionPrint->setObjectName(QStringLiteral("actionPrint"));
        actionExit = new QAction(TextWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralwidget = new QWidget(TextWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setReadOnly(true);

        gridLayout->addWidget(textEdit, 0, 0, 1, 1);

        TextWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(TextWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        TextWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(TextWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 706, 21));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
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
        actionSaveAs->setText(QApplication::translate("TextWindow", "&Save as...", Q_NULLPTR));
        actionPrint->setText(QApplication::translate("TextWindow", "&Print...", Q_NULLPTR));
        actionExit->setText(QApplication::translate("TextWindow", "Close", Q_NULLPTR));
        menu_File->setTitle(QApplication::translate("TextWindow", "&File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TextWindow: public Ui_TextWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTWINDOW_H
