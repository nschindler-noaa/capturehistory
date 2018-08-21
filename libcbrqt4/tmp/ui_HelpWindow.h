/********************************************************************************
** Form generated from reading UI file 'HelpWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPWINDOW_H
#define UI_HELPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include <QTextBrowser>
#include <QMainWindow>
//#include "Qt3Support/Q3TextBrowser"
//#include "q3mainwindow.h"

QT_BEGIN_NAMESPACE

class Ui_HelpWindow
{
public:
    QAction *fileExitAction;
    QAction *homeAction;
    QWidget *widget;
    QHBoxLayout *hboxLayout;
    Q3TextBrowser *textBrowser;
    QMenuBar *menubar;
    QMenu *fileMenu;

    void setupUi(Q3MainWindow *HelpWindow)
    {
        if (HelpWindow->objectName().isEmpty())
            HelpWindow->setObjectName(QStringLiteral("HelpWindow"));
        HelpWindow->resize(690, 405);
        fileExitAction = new QAction(HelpWindow);
        fileExitAction->setObjectName(QStringLiteral("fileExitAction"));
        fileExitAction->setShortcut(4194392);
        homeAction = new QAction(HelpWindow);
        homeAction->setObjectName(QStringLiteral("homeAction"));
        homeAction->setShortcut(4194376);
        widget = new QWidget(HelpWindow);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 22, 690, 383));
        hboxLayout = new QHBoxLayout(widget);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        textBrowser = new Q3TextBrowser(widget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        hboxLayout->addWidget(textBrowser);

        menubar = new QMenuBar(HelpWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 690, 21));
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName(QStringLiteral("fileMenu"));

        menubar->addAction(fileMenu->menuAction());
        fileMenu->addAction(homeAction);
        fileMenu->addSeparator();
        fileMenu->addAction(fileExitAction);

        retranslateUi(HelpWindow);
        QObject::connect(fileExitAction, SIGNAL(activated()), HelpWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(HelpWindow);
    } // setupUi

    void retranslateUi(Q3MainWindow *HelpWindow)
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
