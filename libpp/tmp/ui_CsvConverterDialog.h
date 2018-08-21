/********************************************************************************
** Form generated from reading UI file 'CsvConverterDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSVCONVERTERDIALOG_H
#define UI_CSVCONVERTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
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

class Ui_ConvertCsvDialog
{
public:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QGroupBox *buttonGroup1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *hboxLayout;
    QRadioButton *obsRadioButton;
    QRadioButton *tagRadioButton;
    QRadioButton *relRadioButton;
    QRadioButton *mortRadioButton;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout2;
    QLabel *textLabel1;
    QLabel *textLabel1_2;
    QSpacerItem *spacerItem;
    QGroupBox *groupBox2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *data_verticalLayout;
    QCheckBox *headerCheckBox;
    QTableView *dataTable;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem1;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;

    void setupUi(QDialog *ConvertCsvDialog)
    {
        if (ConvertCsvDialog->objectName().isEmpty())
            ConvertCsvDialog->setObjectName(QStringLiteral("ConvertCsvDialog"));
        ConvertCsvDialog->resize(627, 375);
        ConvertCsvDialog->setSizeGripEnabled(true);
        vboxLayout = new QVBoxLayout(ConvertCsvDialog);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        buttonGroup1 = new QGroupBox(ConvertCsvDialog);
        buttonGroup1->setObjectName(QStringLiteral("buttonGroup1"));
        verticalLayout_2 = new QVBoxLayout(buttonGroup1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        obsRadioButton = new QRadioButton(buttonGroup1);
        obsRadioButton->setObjectName(QStringLiteral("obsRadioButton"));
        obsRadioButton->setChecked(true);

        hboxLayout->addWidget(obsRadioButton);

        tagRadioButton = new QRadioButton(buttonGroup1);
        tagRadioButton->setObjectName(QStringLiteral("tagRadioButton"));

        hboxLayout->addWidget(tagRadioButton);

        relRadioButton = new QRadioButton(buttonGroup1);
        relRadioButton->setObjectName(QStringLiteral("relRadioButton"));

        hboxLayout->addWidget(relRadioButton);

        mortRadioButton = new QRadioButton(buttonGroup1);
        mortRadioButton->setObjectName(QStringLiteral("mortRadioButton"));

        hboxLayout->addWidget(mortRadioButton);


        verticalLayout_2->addLayout(hboxLayout);


        vboxLayout1->addWidget(buttonGroup1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setSpacing(6);
        vboxLayout2->setObjectName(QStringLiteral("vboxLayout2"));
        vboxLayout2->setContentsMargins(0, 0, 0, 0);
        textLabel1 = new QLabel(ConvertCsvDialog);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));

        vboxLayout2->addWidget(textLabel1);

        textLabel1_2 = new QLabel(ConvertCsvDialog);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));

        vboxLayout2->addWidget(textLabel1_2);


        hboxLayout1->addLayout(vboxLayout2);

        spacerItem = new QSpacerItem(111, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem);


        vboxLayout1->addLayout(hboxLayout1);

        groupBox2 = new QGroupBox(ConvertCsvDialog);
        groupBox2->setObjectName(QStringLiteral("groupBox2"));
        verticalLayout = new QVBoxLayout(groupBox2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        data_verticalLayout = new QVBoxLayout();
        data_verticalLayout->setSpacing(6);
        data_verticalLayout->setObjectName(QStringLiteral("data_verticalLayout"));
        data_verticalLayout->setContentsMargins(0, 0, 0, 0);
        headerCheckBox = new QCheckBox(groupBox2);
        headerCheckBox->setObjectName(QStringLiteral("headerCheckBox"));
        headerCheckBox->setChecked(true);

        data_verticalLayout->addWidget(headerCheckBox);

        dataTable = new QTableView(groupBox2);
        dataTable->setObjectName(QStringLiteral("dataTable"));

        data_verticalLayout->addWidget(dataTable);


        verticalLayout->addLayout(data_verticalLayout);


        vboxLayout1->addWidget(groupBox2);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QStringLiteral("hboxLayout2"));
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem1);

        buttonOk = new QPushButton(ConvertCsvDialog);
        buttonOk->setObjectName(QStringLiteral("buttonOk"));
        buttonOk->setAutoDefault(true);

        hboxLayout2->addWidget(buttonOk);

        buttonCancel = new QPushButton(ConvertCsvDialog);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        hboxLayout2->addWidget(buttonCancel);


        vboxLayout1->addLayout(hboxLayout2);


        vboxLayout->addLayout(vboxLayout1);


        retranslateUi(ConvertCsvDialog);
        QObject::connect(buttonOk, SIGNAL(clicked()), ConvertCsvDialog, SLOT(accept()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), ConvertCsvDialog, SLOT(reject()));

        buttonOk->setDefault(true);


        QMetaObject::connectSlotsByName(ConvertCsvDialog);
    } // setupUi

    void retranslateUi(QDialog *ConvertCsvDialog)
    {
        ConvertCsvDialog->setWindowTitle(QApplication::translate("ConvertCsvDialog", "CSV Converter", Q_NULLPTR));
        buttonGroup1->setTitle(QApplication::translate("ConvertCsvDialog", "Output type", Q_NULLPTR));
        obsRadioButton->setText(QApplication::translate("ConvertCsvDialog", "Observation file format", Q_NULLPTR));
        tagRadioButton->setText(QApplication::translate("ConvertCsvDialog", "Tag file format", Q_NULLPTR));
        relRadioButton->setText(QApplication::translate("ConvertCsvDialog", "Release file format", Q_NULLPTR));
        mortRadioButton->setText(QApplication::translate("ConvertCsvDialog", "Mortality file format", Q_NULLPTR));
        textLabel1->setText(QApplication::translate("ConvertCsvDialog", "CSV file:", Q_NULLPTR));
        textLabel1_2->setText(QApplication::translate("ConvertCsvDialog", "Output file:", Q_NULLPTR));
        groupBox2->setTitle(QApplication::translate("ConvertCsvDialog", "Data", Q_NULLPTR));
        headerCheckBox->setText(QApplication::translate("ConvertCsvDialog", "First row contains column headings", Q_NULLPTR));
        buttonOk->setText(QApplication::translate("ConvertCsvDialog", "&OK", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        buttonOk->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        buttonCancel->setText(QApplication::translate("ConvertCsvDialog", "&Cancel", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        buttonCancel->setShortcut(QString());
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class ConvertCsvDialog: public Ui_ConvertCsvDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSVCONVERTERDIALOG_H
