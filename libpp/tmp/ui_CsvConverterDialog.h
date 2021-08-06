/********************************************************************************
** Form generated from reading UI file 'csvconverterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSVCONVERTERDIALOG_H
#define UI_CSVCONVERTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CsvConverterDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *vboxLayout;
    QGroupBox *buttonGroup1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *_2;
    QRadioButton *obsRadioButton;
    QRadioButton *tagRadioButton;
    QRadioButton *relRadioButton;
    QRadioButton *mortRadioButton;
    QHBoxLayout *_3;
    QVBoxLayout *_4;
    QLabel *textLabel1;
    QLabel *textLabel1_2;
    QSpacerItem *spacerItem;
    QGroupBox *groupBox2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *data_verticalLayout;
    QCheckBox *headerCheckBox;
    QTableView *dataTable;
    QHBoxLayout *_5;
    QSpacerItem *spacerItem1;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;

    void setupUi(QDialog *CsvConverterDialog)
    {
        if (CsvConverterDialog->objectName().isEmpty())
            CsvConverterDialog->setObjectName(QString::fromUtf8("CsvConverterDialog"));
        CsvConverterDialog->resize(750, 380);
        verticalLayout_3 = new QVBoxLayout(CsvConverterDialog);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        buttonGroup1 = new QGroupBox(CsvConverterDialog);
        buttonGroup1->setObjectName(QString::fromUtf8("buttonGroup1"));
        verticalLayout_2 = new QVBoxLayout(buttonGroup1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        _2 = new QHBoxLayout();
        _2->setSpacing(6);
        _2->setObjectName(QString::fromUtf8("_2"));
        _2->setContentsMargins(0, 0, 0, 0);
        obsRadioButton = new QRadioButton(buttonGroup1);
        obsRadioButton->setObjectName(QString::fromUtf8("obsRadioButton"));
        obsRadioButton->setChecked(true);

        _2->addWidget(obsRadioButton);

        tagRadioButton = new QRadioButton(buttonGroup1);
        tagRadioButton->setObjectName(QString::fromUtf8("tagRadioButton"));

        _2->addWidget(tagRadioButton);

        relRadioButton = new QRadioButton(buttonGroup1);
        relRadioButton->setObjectName(QString::fromUtf8("relRadioButton"));

        _2->addWidget(relRadioButton);

        mortRadioButton = new QRadioButton(buttonGroup1);
        mortRadioButton->setObjectName(QString::fromUtf8("mortRadioButton"));

        _2->addWidget(mortRadioButton);


        verticalLayout_2->addLayout(_2);


        vboxLayout->addWidget(buttonGroup1);

        _3 = new QHBoxLayout();
        _3->setSpacing(6);
        _3->setObjectName(QString::fromUtf8("_3"));
        _3->setContentsMargins(0, 0, 0, 0);
        _4 = new QVBoxLayout();
        _4->setSpacing(6);
        _4->setObjectName(QString::fromUtf8("_4"));
        _4->setContentsMargins(0, 0, 0, 0);
        textLabel1 = new QLabel(CsvConverterDialog);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));

        _4->addWidget(textLabel1);

        textLabel1_2 = new QLabel(CsvConverterDialog);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));

        _4->addWidget(textLabel1_2);


        _3->addLayout(_4);

        spacerItem = new QSpacerItem(111, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        _3->addItem(spacerItem);


        vboxLayout->addLayout(_3);

        groupBox2 = new QGroupBox(CsvConverterDialog);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        verticalLayout = new QVBoxLayout(groupBox2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        data_verticalLayout = new QVBoxLayout();
        data_verticalLayout->setSpacing(6);
        data_verticalLayout->setObjectName(QString::fromUtf8("data_verticalLayout"));
        data_verticalLayout->setContentsMargins(0, 0, 0, 0);
        headerCheckBox = new QCheckBox(groupBox2);
        headerCheckBox->setObjectName(QString::fromUtf8("headerCheckBox"));
        headerCheckBox->setChecked(true);

        data_verticalLayout->addWidget(headerCheckBox);

        dataTable = new QTableView(groupBox2);
        dataTable->setObjectName(QString::fromUtf8("dataTable"));

        data_verticalLayout->addWidget(dataTable);


        verticalLayout->addLayout(data_verticalLayout);


        vboxLayout->addWidget(groupBox2);

        _5 = new QHBoxLayout();
        _5->setSpacing(6);
        _5->setObjectName(QString::fromUtf8("_5"));
        _5->setContentsMargins(0, 0, 0, 0);
        spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        _5->addItem(spacerItem1);

        buttonOk = new QPushButton(CsvConverterDialog);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);

        _5->addWidget(buttonOk);

        buttonCancel = new QPushButton(CsvConverterDialog);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        _5->addWidget(buttonCancel);


        vboxLayout->addLayout(_5);


        verticalLayout_3->addLayout(vboxLayout);


        retranslateUi(CsvConverterDialog);

        buttonOk->setDefault(true);


        QMetaObject::connectSlotsByName(CsvConverterDialog);
    } // setupUi

    void retranslateUi(QDialog *CsvConverterDialog)
    {
        CsvConverterDialog->setWindowTitle(QApplication::translate("CsvConverterDialog", "Dialog", nullptr));
        buttonGroup1->setTitle(QApplication::translate("CsvConverterDialog", "Output type", nullptr));
        obsRadioButton->setText(QApplication::translate("CsvConverterDialog", "Observation file format", nullptr));
        tagRadioButton->setText(QApplication::translate("CsvConverterDialog", "Tag file format", nullptr));
        relRadioButton->setText(QApplication::translate("CsvConverterDialog", "Release file format", nullptr));
        mortRadioButton->setText(QApplication::translate("CsvConverterDialog", "Mortality file format", nullptr));
        textLabel1->setText(QApplication::translate("CsvConverterDialog", "CSV file:", nullptr));
        textLabel1_2->setText(QApplication::translate("CsvConverterDialog", "Output file:", nullptr));
        groupBox2->setTitle(QApplication::translate("CsvConverterDialog", "Data", nullptr));
        headerCheckBox->setText(QApplication::translate("CsvConverterDialog", "First row contains column headings", nullptr));
        buttonOk->setText(QApplication::translate("CsvConverterDialog", "&OK", nullptr));
#ifndef QT_NO_SHORTCUT
        buttonOk->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        buttonCancel->setText(QApplication::translate("CsvConverterDialog", "&Cancel", nullptr));
#ifndef QT_NO_SHORTCUT
        buttonCancel->setShortcut(QString());
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class CsvConverterDialog: public Ui_CsvConverterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSVCONVERTERDIALOG_H
