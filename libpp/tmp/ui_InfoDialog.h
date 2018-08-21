/********************************************************************************
** Form generated from reading UI file 'InfoDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFODIALOG_H
#define UI_INFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InfoDialog
{
public:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QFrame *frame5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QLabel *TextLabel1;
    QLabel *versionLabel;
    QSpacerItem *spacerItem1;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem2;
    QLabel *TextLabel2;
    QSpacerItem *spacerItem3;
    QFrame *frame7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem4;
    QLabel *TextLabel1_2;
    QSpacerItem *spacerItem5;
    QHBoxLayout *hboxLayout3;
    QSpacerItem *spacerItem6;
    QLabel *TextLabel4;
    QSpacerItem *spacerItem7;
    QHBoxLayout *hboxLayout4;
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
    QHBoxLayout *hboxLayout5;
    QSpacerItem *spacerItem15;
    QLabel *TextLabel7;
    QSpacerItem *spacerItem16;
    QHBoxLayout *hboxLayout6;
    QSpacerItem *spacerItem17;
    QPushButton *buttonOk;
    QSpacerItem *spacerItem18;

    void setupUi(QDialog *InfoDialog)
    {
        if (InfoDialog->objectName().isEmpty())
            InfoDialog->setObjectName(QStringLiteral("InfoDialog"));
        InfoDialog->resize(361, 361);
        InfoDialog->setSizeGripEnabled(true);
        vboxLayout = new QVBoxLayout(InfoDialog);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        frame5 = new QFrame(InfoDialog);
        frame5->setObjectName(QStringLiteral("frame5"));
        frame5->setFrameShape(QFrame::StyledPanel);
        frame5->setFrameShadow(QFrame::Plain);
        verticalLayout = new QVBoxLayout(frame5);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        TextLabel1 = new QLabel(frame5);
        TextLabel1->setObjectName(QStringLiteral("TextLabel1"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        TextLabel1->setFont(font);

        hboxLayout->addWidget(TextLabel1);

        versionLabel = new QLabel(frame5);
        versionLabel->setObjectName(QStringLiteral("versionLabel"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        versionLabel->setFont(font1);
        versionLabel->setAlignment(Qt::AlignVCenter);

        hboxLayout->addWidget(versionLabel);

        spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);


        verticalLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        spacerItem2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem2);

        TextLabel2 = new QLabel(frame5);
        TextLabel2->setObjectName(QStringLiteral("TextLabel2"));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setUnderline(false);
        font2.setWeight(50);
        font2.setStrikeOut(false);
        TextLabel2->setFont(font2);

        hboxLayout1->addWidget(TextLabel2);

        spacerItem3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem3);


        verticalLayout->addLayout(hboxLayout1);


        vboxLayout1->addWidget(frame5);

        frame7 = new QFrame(InfoDialog);
        frame7->setObjectName(QStringLiteral("frame7"));
        frame7->setFrameShape(QFrame::StyledPanel);
        frame7->setFrameShadow(QFrame::Plain);
        verticalLayout_2 = new QVBoxLayout(frame7);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QStringLiteral("hboxLayout2"));
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        spacerItem4 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem4);

        TextLabel1_2 = new QLabel(frame7);
        TextLabel1_2->setObjectName(QStringLiteral("TextLabel1_2"));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(8);
        font3.setBold(false);
        font3.setItalic(true);
        font3.setUnderline(false);
        font3.setWeight(50);
        font3.setStrikeOut(false);
        TextLabel1_2->setFont(font3);

        hboxLayout2->addWidget(TextLabel1_2);

        spacerItem5 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem5);


        verticalLayout_2->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName(QStringLiteral("hboxLayout3"));
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        spacerItem6 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacerItem6);

        TextLabel4 = new QLabel(frame7);
        TextLabel4->setObjectName(QStringLiteral("TextLabel4"));
        TextLabel4->setFont(font1);

        hboxLayout3->addWidget(TextLabel4);

        spacerItem7 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout3->addItem(spacerItem7);


        verticalLayout_2->addLayout(hboxLayout3);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName(QStringLiteral("hboxLayout4"));
        hboxLayout4->setContentsMargins(0, 0, 0, 0);
        spacerItem8 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout4->addItem(spacerItem8);

        TextLabel5 = new QLabel(frame7);
        TextLabel5->setObjectName(QStringLiteral("TextLabel5"));
        TextLabel5->setFont(font2);

        hboxLayout4->addWidget(TextLabel5);

        spacerItem9 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout4->addItem(spacerItem9);


        verticalLayout_2->addLayout(hboxLayout4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        spacerItem10 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacerItem10);

        TextLabel3_2 = new QLabel(frame7);
        TextLabel3_2->setObjectName(QStringLiteral("TextLabel3_2"));

        horizontalLayout->addWidget(TextLabel3_2);

        spacerItem11 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacerItem11);

        TextLabel4_2 = new QLabel(frame7);
        TextLabel4_2->setObjectName(QStringLiteral("TextLabel4_2"));

        horizontalLayout->addWidget(TextLabel4_2);

        spacerItem12 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacerItem12);


        verticalLayout_2->addLayout(horizontalLayout);


        vboxLayout1->addWidget(frame7);

        frame6 = new QFrame(InfoDialog);
        frame6->setObjectName(QStringLiteral("frame6"));
        frame6->setFrameShape(QFrame::StyledPanel);
        frame6->setFrameShadow(QFrame::Plain);
        verticalLayout_3 = new QVBoxLayout(frame6);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        spacerItem13 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(spacerItem13);

        TextLabel6 = new QLabel(frame6);
        TextLabel6->setObjectName(QStringLiteral("TextLabel6"));
        TextLabel6->setFont(font3);

        horizontalLayout_3->addWidget(TextLabel6);

        spacerItem14 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(spacerItem14);


        verticalLayout_3->addLayout(horizontalLayout_3);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(6);
        hboxLayout5->setObjectName(QStringLiteral("hboxLayout5"));
        hboxLayout5->setContentsMargins(0, 0, 0, 0);
        spacerItem15 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout5->addItem(spacerItem15);

        TextLabel7 = new QLabel(frame6);
        TextLabel7->setObjectName(QStringLiteral("TextLabel7"));
        TextLabel7->setFont(font1);

        hboxLayout5->addWidget(TextLabel7);

        spacerItem16 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout5->addItem(spacerItem16);


        verticalLayout_3->addLayout(hboxLayout5);


        vboxLayout1->addWidget(frame6);

        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setSpacing(6);
        hboxLayout6->setObjectName(QStringLiteral("hboxLayout6"));
        hboxLayout6->setContentsMargins(0, 0, 0, 0);
        spacerItem17 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout6->addItem(spacerItem17);

        buttonOk = new QPushButton(InfoDialog);
        buttonOk->setObjectName(QStringLiteral("buttonOk"));
        buttonOk->setAutoDefault(true);

        hboxLayout6->addWidget(buttonOk);

        spacerItem18 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout6->addItem(spacerItem18);


        vboxLayout1->addLayout(hboxLayout6);


        vboxLayout->addLayout(vboxLayout1);


        retranslateUi(InfoDialog);
        QObject::connect(buttonOk, SIGNAL(clicked()), InfoDialog, SLOT(accept()));

        buttonOk->setDefault(true);


        QMetaObject::connectSlotsByName(InfoDialog);
    } // setupUi

    void retranslateUi(QDialog *InfoDialog)
    {
        InfoDialog->setWindowTitle(QApplication::translate("InfoDialog", "About PitPro", Q_NULLPTR));
        TextLabel1->setText(QApplication::translate("InfoDialog", "PitPro", Q_NULLPTR));
        versionLabel->setText(QApplication::translate("InfoDialog", "<blank>", Q_NULLPTR));
        TextLabel2->setText(QApplication::translate("InfoDialog", "PIT Tag Data Pre-Processor", Q_NULLPTR));
        TextLabel1_2->setText(QApplication::translate("InfoDialog", "created by", Q_NULLPTR));
        TextLabel4->setText(QApplication::translate("InfoDialog", "University of Washington", Q_NULLPTR));
        TextLabel5->setText(QApplication::translate("InfoDialog", "School of Aquatic and Fisheries Science", Q_NULLPTR));
        TextLabel3_2->setText(QApplication::translate("InfoDialog", "Peter Westhagen", Q_NULLPTR));
        TextLabel4_2->setText(QApplication::translate("InfoDialog", "John R. Skalski", Q_NULLPTR));
        TextLabel6->setText(QApplication::translate("InfoDialog", "funded by", Q_NULLPTR));
        TextLabel7->setText(QApplication::translate("InfoDialog", "Bonneville Power Administration", Q_NULLPTR));
        buttonOk->setText(QApplication::translate("InfoDialog", "OK", Q_NULLPTR));
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
