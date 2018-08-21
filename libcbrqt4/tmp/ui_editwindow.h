/********************************************************************************
** Form generated from reading UI file 'editwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITWINDOW_H
#define UI_EDITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        fileOpenAction = new QAction(MainWindow);
        fileOpenAction->setObjectName(QStringLiteral("fileOpenAction"));
        fileSaveAction = new QAction(MainWindow);
        fileSaveAction->setObjectName(QStringLiteral("fileSaveAction"));
        fileSave_asAction = new QAction(MainWindow);
        fileSave_asAction->setObjectName(QStringLiteral("fileSave_asAction"));
        filePrintAction = new QAction(MainWindow);
        filePrintAction->setObjectName(QStringLiteral("filePrintAction"));
        editCutAction = new QAction(MainWindow);
        editCutAction->setObjectName(QStringLiteral("editCutAction"));
        editCopyAction = new QAction(MainWindow);
        editCopyAction->setObjectName(QStringLiteral("editCopyAction"));
        editPasteAction = new QAction(MainWindow);
        editPasteAction->setObjectName(QStringLiteral("editPasteAction"));
        editSelect_AllAction = new QAction(MainWindow);
        editSelect_AllAction->setObjectName(QStringLiteral("editSelect_AllAction"));
        editUndoAction = new QAction(MainWindow);
        editUndoAction->setObjectName(QStringLiteral("editUndoAction"));
        editRedoAction = new QAction(MainWindow);
        editRedoAction->setObjectName(QStringLiteral("editRedoAction"));
        aeditDeleteAction = new QAction(MainWindow);
        aeditDeleteAction->setObjectName(QStringLiteral("aeditDeleteAction"));
        Action = new QAction(MainWindow);
        Action->setObjectName(QStringLiteral("Action"));
        widget = new QWidget(MainWindow);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        textEdit = new QPlainTextEdit(widget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        vboxLayout->addWidget(textEdit);


        verticalLayout_2->addLayout(vboxLayout);

        MainWindow->setCentralWidget(widget);
        MenuBarEditor = new QMenuBar(MainWindow);
        MenuBarEditor->setObjectName(QStringLiteral("MenuBarEditor"));
        MenuBarEditor->setGeometry(QRect(0, 0, 800, 26));
        File = new QMenu(MenuBarEditor);
        File->setObjectName(QStringLiteral("File"));
        Edit = new QMenu(MenuBarEditor);
        Edit->setObjectName(QStringLiteral("Edit"));
        MainWindow->setMenuBar(MenuBarEditor);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        fileOpenAction->setText(QApplication::translate("MainWindow", "&Open", 0));
        fileSaveAction->setText(QApplication::translate("MainWindow", "&Save", 0));
        fileSave_asAction->setText(QApplication::translate("MainWindow", "Save&As", 0));
        filePrintAction->setText(QApplication::translate("MainWindow", "&Print", 0));
        editCutAction->setText(QApplication::translate("MainWindow", "Cu&t", 0));
        editCopyAction->setText(QApplication::translate("MainWindow", "&Copy", 0));
        editPasteAction->setText(QApplication::translate("MainWindow", "&Paste", 0));
        editSelect_AllAction->setText(QApplication::translate("MainWindow", "&Select All", 0));
        editUndoAction->setText(QApplication::translate("MainWindow", "&Undo", 0));
        editRedoAction->setText(QApplication::translate("MainWindow", "&Redo", 0));
        aeditDeleteAction->setText(QApplication::translate("MainWindow", "&Delete Action", 0));
        Action->setText(QApplication::translate("MainWindow", "Action", 0));
        File->setTitle(QApplication::translate("MainWindow", "&File", 0));
        Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITWINDOW_H
