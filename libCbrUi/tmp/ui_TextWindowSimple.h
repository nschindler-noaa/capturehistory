/********************************************************************************
** Form generated from reading UI file 'TextWindowSimple.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
    QTextBrowser *textBrowser;
    QHBoxLayout *hboxLayout;
    QLabel *findLabel;
    QLineEdit *findLineEdit;
    QPushButton *findNextButton;
    QPushButton *findPrevButton;
    QSpacerItem *spacerItem;
    QMenuBar *menubar;
    QMenu *filePopup;

    void setupUi(QMainWindow *TextWindowSimple)
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
        textBrowser = new QTextBrowser(widget);
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

        TextWindowSimple->setCentralWidget(widget);
        menubar = new QMenuBar(TextWindowSimple);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 21));
        filePopup = new QMenu(menubar);
        filePopup->setObjectName(QStringLiteral("filePopup"));
        TextWindowSimple->setMenuBar(menubar);

        menubar->addAction(filePopup->menuAction());
        filePopup->addAction(saveAction);
        filePopup->addAction(printAction);
        filePopup->addSeparator();
        filePopup->addAction(exitAction);

        retranslateUi(TextWindowSimple);

        QMetaObject::connectSlotsByName(TextWindowSimple);
    } // setupUi

    void retranslateUi(QMainWindow *TextWindowSimple)
    {
        TextWindowSimple->setWindowTitle(QApplication::translate("TextWindowSimple", "Text Window", Q_NULLPTR));
        exitAction->setText(QApplication::translate("TextWindowSimple", "Close", Q_NULLPTR));
        exitAction->setIconText(QApplication::translate("TextWindowSimple", "Close", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        exitAction->setToolTip(QApplication::translate("TextWindowSimple", "Close the window", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        exitAction->setShortcut(QApplication::translate("TextWindowSimple", "Ctrl+X", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        printAction->setText(QApplication::translate("TextWindowSimple", "Print", Q_NULLPTR));
        printAction->setIconText(QApplication::translate("TextWindowSimple", "Print", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        printAction->setToolTip(QApplication::translate("TextWindowSimple", "Print the contents of the window", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        printAction->setShortcut(QApplication::translate("TextWindowSimple", "Ctrl+P", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        clearAllAction->setText(QApplication::translate("TextWindowSimple", "Clear all", Q_NULLPTR));
        clearAllAction->setIconText(QApplication::translate("TextWindowSimple", "Clear all", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        clearAllAction->setToolTip(QApplication::translate("TextWindowSimple", "Clear text window contents", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        saveAction->setText(QApplication::translate("TextWindowSimple", "Save as...", Q_NULLPTR));
        saveAction->setIconText(QApplication::translate("TextWindowSimple", "Save as...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        saveAction->setToolTip(QApplication::translate("TextWindowSimple", "Save contents of text window to file", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        findLabel->setText(QApplication::translate("TextWindowSimple", "Find:", Q_NULLPTR));
        findNextButton->setText(QApplication::translate("TextWindowSimple", "Next", Q_NULLPTR));
        findPrevButton->setText(QApplication::translate("TextWindowSimple", "Previous", Q_NULLPTR));
        filePopup->setTitle(QApplication::translate("TextWindowSimple", "&File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TextWindowSimple: public Ui_TextWindowSimple {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTWINDOWSIMPLE_H
