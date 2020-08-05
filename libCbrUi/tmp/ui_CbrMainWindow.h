/********************************************************************************
** Form generated from reading UI file 'CbrMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CBRMAINWINDOW_H
#define UI_CBRMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CbrMainWindow
{
public:
    QAction *actionExit;
    QAction *actionInfo;
    QAction *actionSave;
    QAction *actionPrint;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile_;
    QMenu *menuHelp_;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CbrMainWindow)
    {
        if (CbrMainWindow->objectName().isEmpty())
            CbrMainWindow->setObjectName(QStringLiteral("CbrMainWindow"));
        CbrMainWindow->setEnabled(true);
        CbrMainWindow->resize(588, 466);
        actionExit = new QAction(CbrMainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionInfo = new QAction(CbrMainWindow);
        actionInfo->setObjectName(QStringLiteral("actionInfo"));
        actionSave = new QAction(CbrMainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionPrint = new QAction(CbrMainWindow);
        actionPrint->setObjectName(QStringLiteral("actionPrint"));
        centralwidget = new QWidget(CbrMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        CbrMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CbrMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 588, 21));
        menuFile_ = new QMenu(menubar);
        menuFile_->setObjectName(QStringLiteral("menuFile_"));
        menuHelp_ = new QMenu(menubar);
        menuHelp_->setObjectName(QStringLiteral("menuHelp_"));
        CbrMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CbrMainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        CbrMainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile_->menuAction());
        menubar->addAction(menuHelp_->menuAction());

        retranslateUi(CbrMainWindow);
        QObject::connect(actionExit, SIGNAL(activated()), CbrMainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(CbrMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CbrMainWindow)
    {
        CbrMainWindow->setWindowTitle(QApplication::translate("CbrMainWindow", "MainWindow", Q_NULLPTR));
        actionExit->setText(QApplication::translate("CbrMainWindow", "Exit", Q_NULLPTR));
        actionInfo->setText(QApplication::translate("CbrMainWindow", "About", Q_NULLPTR));
        actionSave->setText(QApplication::translate("CbrMainWindow", "Save", Q_NULLPTR));
        actionPrint->setText(QApplication::translate("CbrMainWindow", "Print", Q_NULLPTR));
        menuFile_->setTitle(QApplication::translate("CbrMainWindow", "File", Q_NULLPTR));
        menuHelp_->setTitle(QApplication::translate("CbrMainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CbrMainWindow: public Ui_CbrMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CBRMAINWINDOW_H
