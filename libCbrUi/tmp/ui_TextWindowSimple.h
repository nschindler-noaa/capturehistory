/********************************************************************************
** Form generated from reading UI file 'textwindowsimple.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTWINDOWSIMPLE_H
#define UI_TEXTWINDOWSIMPLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextWindowSimple
{
public:
    QAction *saveAction;
    QAction *printAction;
    QAction *exitAction;
    QAction *clearAction;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *mainLayout;
    QTextBrowser *textBrowser;
    QHBoxLayout *footerLayout;
    QLabel *FindLabel;
    QLineEdit *findLineEdit;
    QPushButton *findNextButton;
    QPushButton *findPrevButton;
    QSpacerItem *footerSpacer;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TextWindowSimple)
    {
        if (TextWindowSimple->objectName().isEmpty())
            TextWindowSimple->setObjectName(QString::fromUtf8("TextWindowSimple"));
        TextWindowSimple->resize(755, 444);
        saveAction = new QAction(TextWindowSimple);
        saveAction->setObjectName(QString::fromUtf8("saveAction"));
        printAction = new QAction(TextWindowSimple);
        printAction->setObjectName(QString::fromUtf8("printAction"));
        exitAction = new QAction(TextWindowSimple);
        exitAction->setObjectName(QString::fromUtf8("exitAction"));
        clearAction = new QAction(TextWindowSimple);
        clearAction->setObjectName(QString::fromUtf8("clearAction"));
        centralwidget = new QWidget(TextWindowSimple);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mainLayout = new QVBoxLayout();
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        mainLayout->addWidget(textBrowser);

        footerLayout = new QHBoxLayout();
        footerLayout->setObjectName(QString::fromUtf8("footerLayout"));
        FindLabel = new QLabel(centralwidget);
        FindLabel->setObjectName(QString::fromUtf8("FindLabel"));

        footerLayout->addWidget(FindLabel);

        findLineEdit = new QLineEdit(centralwidget);
        findLineEdit->setObjectName(QString::fromUtf8("findLineEdit"));

        footerLayout->addWidget(findLineEdit);

        findNextButton = new QPushButton(centralwidget);
        findNextButton->setObjectName(QString::fromUtf8("findNextButton"));

        footerLayout->addWidget(findNextButton);

        findPrevButton = new QPushButton(centralwidget);
        findPrevButton->setObjectName(QString::fromUtf8("findPrevButton"));

        footerLayout->addWidget(findPrevButton);

        footerSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        footerLayout->addItem(footerSpacer);


        mainLayout->addLayout(footerLayout);


        verticalLayout->addLayout(mainLayout);

        TextWindowSimple->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TextWindowSimple);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 755, 21));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        TextWindowSimple->setMenuBar(menubar);
        statusbar = new QStatusBar(TextWindowSimple);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        TextWindowSimple->setStatusBar(statusbar);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(saveAction);
        menu_File->addAction(printAction);
        menu_File->addSeparator();
        menu_File->addAction(exitAction);

        retranslateUi(TextWindowSimple);

        QMetaObject::connectSlotsByName(TextWindowSimple);
    } // setupUi

    void retranslateUi(QMainWindow *TextWindowSimple)
    {
        TextWindowSimple->setWindowTitle(QApplication::translate("TextWindowSimple", "MainWindow", nullptr));
        saveAction->setText(QApplication::translate("TextWindowSimple", "Save as ...", nullptr));
#ifndef QT_NO_TOOLTIP
        saveAction->setToolTip(QApplication::translate("TextWindowSimple", "Save contents of window to file", nullptr));
#endif // QT_NO_TOOLTIP
        printAction->setText(QApplication::translate("TextWindowSimple", "&Print", nullptr));
#ifndef QT_NO_TOOLTIP
        printAction->setToolTip(QApplication::translate("TextWindowSimple", "Print the contents of the window", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        printAction->setShortcut(QApplication::translate("TextWindowSimple", "Ctrl+P", nullptr));
#endif // QT_NO_SHORTCUT
        exitAction->setText(QApplication::translate("TextWindowSimple", "&Close", nullptr));
#ifndef QT_NO_TOOLTIP
        exitAction->setToolTip(QApplication::translate("TextWindowSimple", "Close the window", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        exitAction->setShortcut(QApplication::translate("TextWindowSimple", "Ctrl+X", nullptr));
#endif // QT_NO_SHORTCUT
        clearAction->setText(QApplication::translate("TextWindowSimple", "Clear all", nullptr));
#ifndef QT_NO_TOOLTIP
        clearAction->setToolTip(QApplication::translate("TextWindowSimple", "Clear text window contents", nullptr));
#endif // QT_NO_TOOLTIP
        FindLabel->setText(QApplication::translate("TextWindowSimple", "Find:", nullptr));
        findNextButton->setText(QApplication::translate("TextWindowSimple", "Next", nullptr));
        findPrevButton->setText(QApplication::translate("TextWindowSimple", "Previous", nullptr));
        menu_File->setTitle(QApplication::translate("TextWindowSimple", "&File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TextWindowSimple: public Ui_TextWindowSimple {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTWINDOWSIMPLE_H
