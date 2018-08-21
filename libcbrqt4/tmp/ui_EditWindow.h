/********************************************************************************
** Form generated from reading UI file 'EditWindow.ui'
**
** Created: Thu Aug 16 14:32:27 2018
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITWINDOW_H
#define UI_EDITWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *fileOpenAction;
    QAction *fileSaveAction;
    QAction *fileSave_asAction;
    QAction *filePrintAction;
    QAction *editCutAction;
    QAction *editCopyAction;
    QAction *editPasteAction;
    QAction *editSelect_AllAction;
    QAction *editUndoAction;
    QAction *editRedoAction;
    QAction *aeditDeleteAction;
    QAction *Action;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *vboxLayout;
    QPlainTextEdit *textEdit;
    QMenuBar *MenuBarEditor;
    QMenu *File;
    QMenu *Edit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        fileOpenAction = new QAction(MainWindow);
        fileOpenAction->setObjectName(QString::fromUtf8("fileOpenAction"));
        fileSaveAction = new QAction(MainWindow);
        fileSaveAction->setObjectName(QString::fromUtf8("fileSaveAction"));
        fileSave_asAction = new QAction(MainWindow);
        fileSave_asAction->setObjectName(QString::fromUtf8("fileSave_asAction"));
        filePrintAction = new QAction(MainWindow);
        filePrintAction->setObjectName(QString::fromUtf8("filePrintAction"));
        editCutAction = new QAction(MainWindow);
        editCutAction->setObjectName(QString::fromUtf8("editCutAction"));
        editCopyAction = new QAction(MainWindow);
        editCopyAction->setObjectName(QString::fromUtf8("editCopyAction"));
        editPasteAction = new QAction(MainWindow);
        editPasteAction->setObjectName(QString::fromUtf8("editPasteAction"));
        editSelect_AllAction = new QAction(MainWindow);
        editSelect_AllAction->setObjectName(QString::fromUtf8("editSelect_AllAction"));
        editUndoAction = new QAction(MainWindow);
        editUndoAction->setObjectName(QString::fromUtf8("editUndoAction"));
        editRedoAction = new QAction(MainWindow);
        editRedoAction->setObjectName(QString::fromUtf8("editRedoAction"));
        aeditDeleteAction = new QAction(MainWindow);
        aeditDeleteAction->setObjectName(QString::fromUtf8("aeditDeleteAction"));
        Action = new QAction(MainWindow);
        Action->setObjectName(QString::fromUtf8("Action"));
        widget = new QWidget(MainWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        textEdit = new QPlainTextEdit(widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        vboxLayout->addWidget(textEdit);


        verticalLayout_2->addLayout(vboxLayout);

        MainWindow->setCentralWidget(widget);
        MenuBarEditor = new QMenuBar(MainWindow);
        MenuBarEditor->setObjectName(QString::fromUtf8("MenuBarEditor"));
        MenuBarEditor->setGeometry(QRect(0, 0, 800, 26));
        File = new QMenu(MenuBarEditor);
        File->setObjectName(QString::fromUtf8("File"));
        Edit = new QMenu(MenuBarEditor);
        Edit->setObjectName(QString::fromUtf8("Edit"));
        MainWindow->setMenuBar(MenuBarEditor);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        MenuBarEditor->addAction(File->menuAction());
        MenuBarEditor->addAction(Edit->menuAction());
        File->addAction(fileOpenAction);
        File->addAction(fileSaveAction);
        File->addAction(fileSave_asAction);
        File->addAction(filePrintAction);
        Edit->addAction(editCutAction);
        Edit->addAction(editCopyAction);
        Edit->addAction(editPasteAction);
        Edit->addAction(editSelect_AllAction);
        Edit->addAction(editUndoAction);
        Edit->addAction(editRedoAction);
        Edit->addAction(aeditDeleteAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        fileOpenAction->setText(QApplication::translate("MainWindow", "&Open", 0, QApplication::UnicodeUTF8));
        fileSaveAction->setText(QApplication::translate("MainWindow", "&Save", 0, QApplication::UnicodeUTF8));
        fileSave_asAction->setText(QApplication::translate("MainWindow", "Save&As", 0, QApplication::UnicodeUTF8));
        filePrintAction->setText(QApplication::translate("MainWindow", "&Print", 0, QApplication::UnicodeUTF8));
        editCutAction->setText(QApplication::translate("MainWindow", "Cu&t", 0, QApplication::UnicodeUTF8));
        editCopyAction->setText(QApplication::translate("MainWindow", "&Copy", 0, QApplication::UnicodeUTF8));
        editPasteAction->setText(QApplication::translate("MainWindow", "&Paste", 0, QApplication::UnicodeUTF8));
        editSelect_AllAction->setText(QApplication::translate("MainWindow", "&Select All", 0, QApplication::UnicodeUTF8));
        editUndoAction->setText(QApplication::translate("MainWindow", "&Undo", 0, QApplication::UnicodeUTF8));
        editRedoAction->setText(QApplication::translate("MainWindow", "&Redo", 0, QApplication::UnicodeUTF8));
        aeditDeleteAction->setText(QApplication::translate("MainWindow", "&Delete Action", 0, QApplication::UnicodeUTF8));
        Action->setText(QApplication::translate("MainWindow", "Action", 0, QApplication::UnicodeUTF8));
        File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITWINDOW_H
