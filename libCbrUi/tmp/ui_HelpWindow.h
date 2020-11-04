/********************************************************************************
** Form generated from reading UI file 'HelpWindow.ui'
**
** Created: Thu Oct 15 15:01:09 2020
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPWINDOW_H
#define UI_HELPWINDOW_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTextBrowser>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_HelpWindow
{
public:
    QAction *fileExitAction;
    QAction *homeAction;
    QWidget *widget;
    QHBoxLayout *hboxLayout;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QMenu *fileMenu;

    void setupUi(QMainWindow *HelpWindow)
    {
        if (HelpWindow->objectName().isEmpty())
            HelpWindow->setObjectName(QString::fromUtf8("HelpWindow"));
        HelpWindow->resize(826, 525);
        fileExitAction = new QAction(HelpWindow);
        fileExitAction->setObjectName(QString::fromUtf8("fileExitAction"));
        fileExitAction->setShortcut(4194392);
        homeAction = new QAction(HelpWindow);
        homeAction->setObjectName(QString::fromUtf8("homeAction"));
        homeAction->setShortcut(4194376);
        widget = new QWidget(HelpWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        hboxLayout = new QHBoxLayout(widget);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        textBrowser = new QTextBrowser(widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        hboxLayout->addWidget(textBrowser);

        HelpWindow->setCentralWidget(widget);
        menubar = new QMenuBar(HelpWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 826, 22));
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName(QString::fromUtf8("fileMenu"));
        HelpWindow->setMenuBar(menubar);

        menubar->addAction(fileMenu->menuAction());
        fileMenu->addAction(homeAction);
        fileMenu->addSeparator();
        fileMenu->addAction(fileExitAction);

        retranslateUi(HelpWindow);
        QObject::connect(fileExitAction, SIGNAL(activated()), HelpWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(HelpWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HelpWindow)
    {
        HelpWindow->setWindowTitle(QApplication::translate("HelpWindow", "Help Window", 0));
        fileExitAction->setText(QApplication::translate("HelpWindow", "&Close", 0));
        fileExitAction->setIconText(QApplication::translate("HelpWindow", "&Close", 0));
#ifndef QT_NO_TOOLTIP
        fileExitAction->setToolTip(QApplication::translate("HelpWindow", "Close the window", 0));
#endif // QT_NO_TOOLTIP
        homeAction->setIconText(QApplication::translate("HelpWindow", "&Home", 0));
#ifndef QT_NO_TOOLTIP
        homeAction->setToolTip(QApplication::translate("HelpWindow", "Return to the home page", 0));
#endif // QT_NO_TOOLTIP
        fileMenu->setTitle(QApplication::translate("HelpWindow", "&File", 0));
    } // retranslateUi

};

namespace Ui {
    class HelpWindow: public Ui_HelpWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPWINDOW_H
