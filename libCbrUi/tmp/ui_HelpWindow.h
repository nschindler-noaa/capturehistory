/********************************************************************************
** Form generated from reading UI file 'helpwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPWINDOW_H
#define UI_HELPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HelpWindow
{
public:
    QAction *homeAction;
    QAction *fileExitAction;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HelpWindow)
    {
        if (HelpWindow->objectName().isEmpty())
            HelpWindow->setObjectName(QString::fromUtf8("HelpWindow"));
        HelpWindow->resize(800, 600);
        homeAction = new QAction(HelpWindow);
        homeAction->setObjectName(QString::fromUtf8("homeAction"));
        fileExitAction = new QAction(HelpWindow);
        fileExitAction->setObjectName(QString::fromUtf8("fileExitAction"));
        centralwidget = new QWidget(HelpWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        HelpWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(HelpWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        HelpWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(HelpWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        HelpWindow->setStatusBar(statusbar);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(homeAction);
        menu_File->addAction(fileExitAction);

        retranslateUi(HelpWindow);

        QMetaObject::connectSlotsByName(HelpWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HelpWindow)
    {
        HelpWindow->setWindowTitle(QApplication::translate("HelpWindow", "Help Window", nullptr));
        homeAction->setText(QApplication::translate("HelpWindow", "&Home", nullptr));
        fileExitAction->setText(QApplication::translate("HelpWindow", "&Close", nullptr));
        menu_File->setTitle(QApplication::translate("HelpWindow", "&File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HelpWindow: public Ui_HelpWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPWINDOW_H
