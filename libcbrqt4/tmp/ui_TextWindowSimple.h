/********************************************************************************
** Form generated from reading UI file 'TextWindowSimple.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTWINDOWSIMPLE_H
#define UI_TEXTWINDOWSIMPLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Qt3Support/Q3TextBrowser"
#include "q3mainwindow.h"

QT_BEGIN_NAMESPACE

class Ui_TextWindowSimple
{
public:
    QAction *exitAction;
    QAction *printAction;
    QAction *clearAllAction;
    QAction *saveAction;
    QWidget *widget;
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    Q3TextBrowser *textBrowser;
    QHBoxLayout *hboxLayout;
    QLabel *findLabel;
    QLineEdit *findLineEdit;
    QPushButton *findNextButton;
    QPushButton *findPrevButton;
    QSpacerItem *spacerItem;
    QMenuBar *menubar;
    QMenu *filePopup;

    void setupUi(Q3MainWindow *TextWindowSimple)
    {
        if (TextWindowSimple->objectName().isEmpty())
            TextWindowSimple->setObjectName(QStringLiteral("TextWindowSimple"));
        TextWindowSimple->resize(600, 480);
        exitAction = new QAction(TextWindowSimple);
        exitAction->setObjectName(QStringLiteral("exitAction"));
        printAction = new QAction(TextWindowSimple);
        printAction->setObjectName(QStringLiteral("printAction"));
        clearAllAction = new QAction(TextWindowSimple);
        clearAllAction->setObjectName(QStringLiteral("clearAllAction"));
        saveAction = new QAction(TextWindowSimple);
        saveAction->setObjectName(QStringLiteral("saveAction"));
        widget = new QWidget(TextWindowSimple);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 22, 600, 458));
        vboxLayout = new QVBoxLayout(widget);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        textBrowser = new Q3TextBrowser(widget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        QFont font;
        font.setFamily(QStringLiteral("Courier"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        textBrowser->setFont(font);
        textBrowser->setWordWrap(Q3TextEdit::NoWrap);

        vboxLayout1->addWidget(textBrowser);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        findLabel = new QLabel(widget);
        findLabel->setObjectName(QStringLiteral("findLabel"));

        hboxLayout->addWidget(findLabel);

        findLineEdit = new QLineEdit(widget);
        findLineEdit->setObjectName(QStringLiteral("findLineEdit"));

        hboxLayout->addWidget(findLineEdit);

        findNextButton = new QPushButton(widget);
        findNextButton->setObjectName(QStringLiteral("findNextButton"));

        hboxLayout->addWidget(findNextButton);

        findPrevButton = new QPushButton(widget);
        findPrevButton->setObjectName(QStringLiteral("findPrevButton"));

        hboxLayout->addWidget(findPrevButton);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout1->addLayout(hboxLayout);


        vboxLayout->addLayout(vboxLayout1);

        menubar = new QMenuBar(TextWindowSimple);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 21));
        filePopup = new QMenu(menubar);
        filePopup->setObjectName(QStringLiteral("filePopup"));

        menubar->addAction(filePopup->menuAction());
        filePopup->addAction(saveAction);
        filePopup->addAction(printAction);
        filePopup->addSeparator();
        filePopup->addAction(exitAction);

        retranslateUi(TextWindowSimple);

        QMetaObject::connectSlotsByName(TextWindowSimple);
    } // setupUi

    void retranslateUi(Q3MainWindow *TextWindowSimple)
    {
        TextWindowSimple->setWindowTitle(QApplication::translate("TextWindowSimple", "Text Window", 0));
        exitAction->setText(QApplication::translate("TextWindowSimple", "Close", 0));
        exitAction->setIconText(QApplication::translate("TextWindowSimple", "Close", 0));
#ifndef QT_NO_TOOLTIP
        exitAction->setToolTip(QApplication::translate("TextWindowSimple", "Close the window", 0));
#endif // QT_NO_TOOLTIP
        exitAction->setShortcut(QApplication::translate("TextWindowSimple", "Ctrl+X", 0));
        printAction->setText(QApplication::translate("TextWindowSimple", "Print", 0));
        printAction->setIconText(QApplication::translate("TextWindowSimple", "Print", 0));
#ifndef QT_NO_TOOLTIP
        printAction->setToolTip(QApplication::translate("TextWindowSimple", "Print the contents of the window", 0));
#endif // QT_NO_TOOLTIP
        printAction->setShortcut(QApplication::translate("TextWindowSimple", "Ctrl+P", 0));
        clearAllAction->setText(QApplication::translate("TextWindowSimple", "Clear all", 0));
        clearAllAction->setIconText(QApplication::translate("TextWindowSimple", "Clear all", 0));
#ifndef QT_NO_TOOLTIP
        clearAllAction->setToolTip(QApplication::translate("TextWindowSimple", "Clear text window contents", 0));
#endif // QT_NO_TOOLTIP
        saveAction->setText(QApplication::translate("TextWindowSimple", "Save as...", 0));
        saveAction->setIconText(QApplication::translate("TextWindowSimple", "Save as...", 0));
#ifndef QT_NO_TOOLTIP
        saveAction->setToolTip(QApplication::translate("TextWindowSimple", "Save contents of text window to file", 0));
#endif // QT_NO_TOOLTIP
        findLabel->setText(QApplication::translate("TextWindowSimple", "Find:", 0));
        findNextButton->setText(QApplication::translate("TextWindowSimple", "Next", 0));
        findPrevButton->setText(QApplication::translate("TextWindowSimple", "Previous", 0));
        filePopup->setTitle(QApplication::translate("TextWindowSimple", "&File", 0));
    } // retranslateUi

};

namespace Ui {
    class TextWindowSimple: public Ui_TextWindowSimple {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTWINDOWSIMPLE_H
