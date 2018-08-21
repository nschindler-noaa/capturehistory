/********************************************************************************
** Form generated from reading UI file 'newEditWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWEDITWINDOW_H
#define UI_NEWEDITWINDOW_H

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

class Ui_newEditWindow
{
public:
    QAction *fileOpenAction;
    QAction *fileSaveAction;
    QAction *fileSave_AsAction;
    QAction *filePrintAction;
    QAction *fileExitAction;
    QAction *editCopyAction;
    QAction *editCutAction;
    QAction *editPasteAction;
    QAction *editUndoAction;
    QAction *editRedoAction;
    QAction *editDeleteAction;
    QAction *editSelect_AllAction;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Edit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *newEditWindow)
    {
        if (newEditWindow->objectName().isEmpty())
            newEditWindow->setObjectName(QStringLiteral("newEditWindow"));
        newEditWindow->resize(800, 600);
        fileOpenAction = new QAction(newEditWindow);
        fileOpenAction->setObjectName(QStringLiteral("fileOpenAction"));
        fileSaveAction = new QAction(newEditWindow);
        fileSaveAction->setObjectName(QStringLiteral("fileSaveAction"));
        fileSave_AsAction = new QAction(newEditWindow);
        fileSave_AsAction->setObjectName(QStringLiteral("fileSave_AsAction"));
        filePrintAction = new QAction(newEditWindow);
        filePrintAction->setObjectName(QStringLiteral("filePrintAction"));
        fileExitAction = new QAction(newEditWindow);
        fileExitAction->setObjectName(QStringLiteral("fileExitAction"));
        editCopyAction = new QAction(newEditWindow);
        editCopyAction->setObjectName(QStringLiteral("editCopyAction"));
        editCutAction = new QAction(newEditWindow);
        editCutAction->setObjectName(QStringLiteral("editCutAction"));
        editPasteAction = new QAction(newEditWindow);
        editPasteAction->setObjectName(QStringLiteral("editPasteAction"));
        editUndoAction = new QAction(newEditWindow);
        editUndoAction->setObjectName(QStringLiteral("editUndoAction"));
        editRedoAction = new QAction(newEditWindow);
        editRedoAction->setObjectName(QStringLiteral("editRedoAction"));
        editDeleteAction = new QAction(newEditWindow);
        editDeleteAction->setObjectName(QStringLiteral("editDeleteAction"));
        editSelect_AllAction = new QAction(newEditWindow);
        editSelect_AllAction->setObjectName(QStringLiteral("editSelect_AllAction"));
        centralwidget = new QWidget(newEditWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        verticalLayout->addWidget(plainTextEdit);


        verticalLayout_2->addLayout(verticalLayout);

        newEditWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(newEditWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_Edit = new QMenu(menubar);
        menu_Edit->setObjectName(QStringLiteral("menu_Edit"));
        newEditWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(newEditWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        newEditWindow->setStatusBar(statusbar);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Edit->menuAction());
        menu_File->addAction(fileOpenAction);
        menu_File->addAction(fileSaveAction);
        menu_File->addAction(fileSave_AsAction);
        menu_File->addSeparator();
        menu_File->addAction(filePrintAction);
        menu_File->addSeparator();
        menu_File->addAction(fileExitAction);
        menu_Edit->addAction(editCopyAction);
        menu_Edit->addAction(editCutAction);
        menu_Edit->addAction(editPasteAction);
        menu_Edit->addAction(editDeleteAction);
        menu_Edit->addAction(editSelect_AllAction);
        menu_Edit->addSeparator();
        menu_Edit->addAction(editUndoAction);
        menu_Edit->addAction(editRedoAction);

        retranslateUi(newEditWindow);

        QMetaObject::connectSlotsByName(newEditWindow);
    } // setupUi

    void retranslateUi(QMainWindow *newEditWindow)
    {
        newEditWindow->setWindowTitle(QApplication::translate("newEditWindow", "MainWindow", Q_NULLPTR));
        fileOpenAction->setText(QApplication::translate("newEditWindow", "&Open", Q_NULLPTR));
        fileSaveAction->setText(QApplication::translate("newEditWindow", "&Save", Q_NULLPTR));
        fileSave_AsAction->setText(QApplication::translate("newEditWindow", "Save &As", Q_NULLPTR));
        filePrintAction->setText(QApplication::translate("newEditWindow", "&Print", Q_NULLPTR));
        fileExitAction->setText(QApplication::translate("newEditWindow", "E&xit", Q_NULLPTR));
        editCopyAction->setText(QApplication::translate("newEditWindow", "&Copy", Q_NULLPTR));
        editCutAction->setText(QApplication::translate("newEditWindow", "Cu&t", Q_NULLPTR));
        editPasteAction->setText(QApplication::translate("newEditWindow", "&Paste", Q_NULLPTR));
        editUndoAction->setText(QApplication::translate("newEditWindow", "&Undo", Q_NULLPTR));
        editRedoAction->setText(QApplication::translate("newEditWindow", "&Redo", Q_NULLPTR));
        editDeleteAction->setText(QApplication::translate("newEditWindow", "&Delete", Q_NULLPTR));
        editSelect_AllAction->setText(QApplication::translate("newEditWindow", "Select &All", Q_NULLPTR));
        menu_File->setTitle(QApplication::translate("newEditWindow", "&File", Q_NULLPTR));
        menu_Edit->setTitle(QApplication::translate("newEditWindow", "&Edit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class newEditWindow: public Ui_newEditWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWEDITWINDOW_H
