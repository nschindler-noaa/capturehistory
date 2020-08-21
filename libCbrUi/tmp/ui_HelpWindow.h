/********************************************************************************
** Form generated from reading UI file 'HelpWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

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
            HelpWindow->setObjectName(QStringLiteral("HelpWindow"));
        HelpWindow->resize(826, 525);
        fileExitAction = new QAction(HelpWindow);
        fileExitAction->setObjectName(QStringLiteral("fileExitAction"));
#ifndef QT_NO_SHORTCUT
        fileExitAction->setShortcut(4194392);
#endif // QT_NO_SHORTCUT
        homeAction = new QAction(HelpWindow);
        homeAction->setObjectName(QStringLiteral("homeAction"));
#ifndef QT_NO_SHORTCUT
        homeAction->setShortcut(4194376);
#endif // QT_NO_SHORTCUT
        widget = new QWidget(HelpWindow);
        widget->setObjectName(QStringLiteral("widget"));
        hboxLayout = new QHBoxLayout(widget);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        textBrowser = new QTextBrowser(widget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        hboxLayout->addWidget(textBrowser);

        HelpWindow->setCentralWidget(widget);
        menubar = new QMenuBar(HelpWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 826, 22));
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName(QStringLiteral("fileMenu"));
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
        HelpWindow->setWindowTitle(QApplication::translate("HelpWindow", "Help Window", Q_NULLPTR));
        fileExitAction->setText(QApplication::translate("HelpWindow", "&Close", Q_NULLPTR));
        fileExitAction->setIconText(QApplication::translate("HelpWindow", "&Close", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        fileExitAction->setToolTip(QApplication::translate("HelpWindow", "Close the window", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        homeAction->setIconText(QApplication::translate("HelpWindow", "&Home", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        homeAction->setToolTip(QApplication::translate("HelpWindow", "Return to the home page", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        fileMenu->setTitle(QApplication::translate("HelpWindow", "&File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class HelpWindow: public Ui_HelpWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPWINDOW_H
