/********************************************************************************
** Form generated from reading UI file 'infodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFODIALOG_H
#define UI_INFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InfoDialog
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *vboxLayout;
    QFrame *frame5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *_2;
    QSpacerItem *spacerItem;
    QLabel *TextLabel1;
    QLabel *versionLabel;
    QSpacerItem *spacerItem1;
    QHBoxLayout *_3;
    QSpacerItem *spacerItem2;
    QLabel *TextLabel2;
    QSpacerItem *spacerItem3;
    QFrame *frame7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *_4;
    QSpacerItem *spacerItem4;
    QLabel *TextLabel1_2;
    QSpacerItem *spacerItem5;
    QHBoxLayout *_5;
    QSpacerItem *spacerItem6;
    QLabel *TextLabel4;
    QSpacerItem *spacerItem7;
    QHBoxLayout *_6;
    QSpacerItem *spacerItem8;
    QLabel *TextLabel5;
    QSpacerItem *spacerItem9;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *spacerItem10;
    QLabel *TextLabel3_2;
    QSpacerItem *spacerItem11;
    QLabel *TextLabel4_2;
    QSpacerItem *spacerItem12;
    QFrame *frame6;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *spacerItem13;
    QLabel *TextLabel6;
    QSpacerItem *spacerItem14;
    QHBoxLayout *_7;
    QSpacerItem *spacerItem15;
    QLabel *TextLabel7;
    QSpacerItem *spacerItem16;
    QHBoxLayout *_8;
    QSpacerItem *spacerItem17;
    QPushButton *buttonOk;
    QSpacerItem *spacerItem18;

    void setupUi(QDialog *InfoDialog)
    {
        if (InfoDialog->objectName().isEmpty())
            InfoDialog->setObjectName(QString::fromUtf8("InfoDialog"));
        InfoDialog->resize(400, 300);
        verticalLayout_4 = new QVBoxLayout(InfoDialog);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        frame5 = new QFrame(InfoDialog);
        frame5->setObjectName(QString::fromUtf8("frame5"));
        frame5->setFrameShape(QFrame::StyledPanel);
        frame5->setFrameShadow(QFrame::Plain);
        verticalLayout = new QVBoxLayout(frame5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        _2 = new QHBoxLayout();
        _2->setSpacing(6);
        _2->setObjectName(QString::fromUtf8("_2"));
        _2->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _2->addItem(spacerItem);

        TextLabel1 = new QLabel(frame5);
        TextLabel1->setObjectName(QString::fromUtf8("TextLabel1"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        TextLabel1->setFont(font);

        _2->addWidget(TextLabel1);

        versionLabel = new QLabel(frame5);
        versionLabel->setObjectName(QString::fromUtf8("versionLabel"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        versionLabel->setFont(font1);
        versionLabel->setAlignment(Qt::AlignVCenter);

        _2->addWidget(versionLabel);

        spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _2->addItem(spacerItem1);


        verticalLayout->addLayout(_2);

        _3 = new QHBoxLayout();
        _3->setSpacing(6);
        _3->setObjectName(QString::fromUtf8("_3"));
        _3->setContentsMargins(0, 0, 0, 0);
        spacerItem2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _3->addItem(spacerItem2);

        TextLabel2 = new QLabel(frame5);
        TextLabel2->setObjectName(QString::fromUtf8("TextLabel2"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setUnderline(false);
        font2.setWeight(50);
        font2.setStrikeOut(false);
        TextLabel2->setFont(font2);

        _3->addWidget(TextLabel2);

        spacerItem3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _3->addItem(spacerItem3);


        verticalLayout->addLayout(_3);


        vboxLayout->addWidget(frame5);

        frame7 = new QFrame(InfoDialog);
        frame7->setObjectName(QString::fromUtf8("frame7"));
        frame7->setFrameShape(QFrame::StyledPanel);
        frame7->setFrameShadow(QFrame::Plain);
        verticalLayout_2 = new QVBoxLayout(frame7);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        _4 = new QHBoxLayout();
        _4->setSpacing(6);
        _4->setObjectName(QString::fromUtf8("_4"));
        _4->setContentsMargins(0, 0, 0, 0);
        spacerItem4 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _4->addItem(spacerItem4);

        TextLabel1_2 = new QLabel(frame7);
        TextLabel1_2->setObjectName(QString::fromUtf8("TextLabel1_2"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(8);
        font3.setBold(false);
        font3.setItalic(true);
        font3.setUnderline(false);
        font3.setWeight(50);
        font3.setStrikeOut(false);
        TextLabel1_2->setFont(font3);

        _4->addWidget(TextLabel1_2);

        spacerItem5 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _4->addItem(spacerItem5);


        verticalLayout_2->addLayout(_4);

        _5 = new QHBoxLayout();
        _5->setSpacing(6);
        _5->setObjectName(QString::fromUtf8("_5"));
        _5->setContentsMargins(0, 0, 0, 0);
        spacerItem6 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _5->addItem(spacerItem6);

        TextLabel4 = new QLabel(frame7);
        TextLabel4->setObjectName(QString::fromUtf8("TextLabel4"));
        TextLabel4->setFont(font1);

        _5->addWidget(TextLabel4);

        spacerItem7 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _5->addItem(spacerItem7);


        verticalLayout_2->addLayout(_5);

        _6 = new QHBoxLayout();
        _6->setSpacing(6);
        _6->setObjectName(QString::fromUtf8("_6"));
        _6->setContentsMargins(0, 0, 0, 0);
        spacerItem8 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _6->addItem(spacerItem8);

        TextLabel5 = new QLabel(frame7);
        TextLabel5->setObjectName(QString::fromUtf8("TextLabel5"));
        TextLabel5->setFont(font2);

        _6->addWidget(TextLabel5);

        spacerItem9 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _6->addItem(spacerItem9);


        verticalLayout_2->addLayout(_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        spacerItem10 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacerItem10);

        TextLabel3_2 = new QLabel(frame7);
        TextLabel3_2->setObjectName(QString::fromUtf8("TextLabel3_2"));

        horizontalLayout->addWidget(TextLabel3_2);

        spacerItem11 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacerItem11);

        TextLabel4_2 = new QLabel(frame7);
        TextLabel4_2->setObjectName(QString::fromUtf8("TextLabel4_2"));

        horizontalLayout->addWidget(TextLabel4_2);

        spacerItem12 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacerItem12);


        verticalLayout_2->addLayout(horizontalLayout);


        vboxLayout->addWidget(frame7);

        frame6 = new QFrame(InfoDialog);
        frame6->setObjectName(QString::fromUtf8("frame6"));
        frame6->setFrameShape(QFrame::StyledPanel);
        frame6->setFrameShadow(QFrame::Plain);
        verticalLayout_3 = new QVBoxLayout(frame6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        spacerItem13 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(spacerItem13);

        TextLabel6 = new QLabel(frame6);
        TextLabel6->setObjectName(QString::fromUtf8("TextLabel6"));
        TextLabel6->setFont(font3);

        horizontalLayout_3->addWidget(TextLabel6);

        spacerItem14 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(spacerItem14);


        verticalLayout_3->addLayout(horizontalLayout_3);

        _7 = new QHBoxLayout();
        _7->setSpacing(6);
        _7->setObjectName(QString::fromUtf8("_7"));
        _7->setContentsMargins(0, 0, 0, 0);
        spacerItem15 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _7->addItem(spacerItem15);

        TextLabel7 = new QLabel(frame6);
        TextLabel7->setObjectName(QString::fromUtf8("TextLabel7"));
        TextLabel7->setFont(font1);

        _7->addWidget(TextLabel7);

        spacerItem16 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _7->addItem(spacerItem16);


        verticalLayout_3->addLayout(_7);


        vboxLayout->addWidget(frame6);

        _8 = new QHBoxLayout();
        _8->setSpacing(6);
        _8->setObjectName(QString::fromUtf8("_8"));
        _8->setContentsMargins(0, 0, 0, 0);
        spacerItem17 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _8->addItem(spacerItem17);

        buttonOk = new QPushButton(InfoDialog);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);

        _8->addWidget(buttonOk);

        spacerItem18 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _8->addItem(spacerItem18);


        vboxLayout->addLayout(_8);


        verticalLayout_4->addLayout(vboxLayout);


        retranslateUi(InfoDialog);

        buttonOk->setDefault(true);


        QMetaObject::connectSlotsByName(InfoDialog);
    } // setupUi

    void retranslateUi(QDialog *InfoDialog)
    {
        InfoDialog->setWindowTitle(QApplication::translate("InfoDialog", "Dialog", nullptr));
        TextLabel1->setText(QApplication::translate("InfoDialog", "PitPro", nullptr));
        versionLabel->setText(QApplication::translate("InfoDialog", "<blank>", nullptr));
        TextLabel2->setText(QApplication::translate("InfoDialog", "PIT Tag Data Pre-Processor", nullptr));
        TextLabel1_2->setText(QApplication::translate("InfoDialog", "created by", nullptr));
        TextLabel4->setText(QApplication::translate("InfoDialog", "University of Washington", nullptr));
        TextLabel5->setText(QApplication::translate("InfoDialog", "School of Aquatic and Fisheries Science", nullptr));
        TextLabel3_2->setText(QApplication::translate("InfoDialog", "Peter Westhagen", nullptr));
        TextLabel4_2->setText(QApplication::translate("InfoDialog", "John R. Skalski", nullptr));
        TextLabel6->setText(QApplication::translate("InfoDialog", "funded by", nullptr));
        TextLabel7->setText(QApplication::translate("InfoDialog", "Bonneville Power Administration", nullptr));
        buttonOk->setText(QApplication::translate("InfoDialog", "OK", nullptr));
#ifndef QT_NO_SHORTCUT
        buttonOk->setShortcut(QString());
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class InfoDialog: public Ui_InfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFODIALOG_H
