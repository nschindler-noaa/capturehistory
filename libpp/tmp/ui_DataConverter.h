/********************************************************************************
** Form generated from reading UI file 'dataconverter.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATACONVERTER_H
#define UI_DATACONVERTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataConverter
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *layout_dataconverter;
    QTabWidget *tabWidget;
    QWidget *obsTab;
    QVBoxLayout *vboxLayout;
    QVBoxLayout *layout_convertObs;
    QCheckBox *obsCheckBox;
    QGroupBox *obsSourceGroupBox;
    QVBoxLayout *_2;
    QHBoxLayout *layout_obsFile;
    QLabel *label_oldObsFile;
    QComboBox *obsCombo;
    QSpacerItem *spacer_obsFile;
    QGroupBox *obsTargetGroupBox;
    QVBoxLayout *_3;
    QHBoxLayout *layout_obsTarget;
    QLabel *label_newObsFile;
    QLineEdit *obsInput;
    QSpacerItem *spacer_obsTarget;
    QSpacerItem *spacer_convertObs;
    QWidget *tagTab;
    QVBoxLayout *_4;
    QVBoxLayout *layout_tag;
    QCheckBox *tagCheckBox;
    QGroupBox *tagSourceGroupBox;
    QVBoxLayout *_5;
    QHBoxLayout *layout_tagFile;
    QVBoxLayout *layout_tagrelFile;
    QLabel *label_tagFIle;
    QLabel *label_relFile;
    QVBoxLayout *layout_tagCombo;
    QComboBox *tagCombo;
    QComboBox *relCombo;
    QSpacerItem *spacer_tagCombo;
    QGroupBox *tagTargetGroupBox;
    QVBoxLayout *_6;
    QHBoxLayout *layout_tagTarget;
    QLabel *label_tagTarget;
    QLineEdit *tagInput;
    QSpacerItem *spacer_tagTarget;
    QSpacerItem *spacer_tag;
    QHBoxLayout *layout_buttons;
    QProgressBar *progressBar;
    QPushButton *buttonConvert;
    QPushButton *buttonDone;
    QLabel *statusText;

    void setupUi(QDialog *DataConverter)
    {
        if (DataConverter->objectName().isEmpty())
            DataConverter->setObjectName(QString::fromUtf8("DataConverter"));
        DataConverter->resize(486, 387);
        verticalLayout = new QVBoxLayout(DataConverter);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        layout_dataconverter = new QVBoxLayout();
        layout_dataconverter->setSpacing(6);
        layout_dataconverter->setObjectName(QString::fromUtf8("layout_dataconverter"));
        layout_dataconverter->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(DataConverter);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        obsTab = new QWidget();
        obsTab->setObjectName(QString::fromUtf8("obsTab"));
        vboxLayout = new QVBoxLayout(obsTab);
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        layout_convertObs = new QVBoxLayout();
        layout_convertObs->setSpacing(6);
        layout_convertObs->setObjectName(QString::fromUtf8("layout_convertObs"));
        layout_convertObs->setContentsMargins(0, 0, 0, 0);
        obsCheckBox = new QCheckBox(obsTab);
        obsCheckBox->setObjectName(QString::fromUtf8("obsCheckBox"));
        obsCheckBox->setChecked(true);

        layout_convertObs->addWidget(obsCheckBox);

        obsSourceGroupBox = new QGroupBox(obsTab);
        obsSourceGroupBox->setObjectName(QString::fromUtf8("obsSourceGroupBox"));
        _2 = new QVBoxLayout(obsSourceGroupBox);
        _2->setSpacing(6);
        _2->setObjectName(QString::fromUtf8("_2"));
        _2->setContentsMargins(9, 9, 9, 9);
        layout_obsFile = new QHBoxLayout();
        layout_obsFile->setSpacing(6);
        layout_obsFile->setObjectName(QString::fromUtf8("layout_obsFile"));
        layout_obsFile->setContentsMargins(0, 0, 0, 0);
        label_oldObsFile = new QLabel(obsSourceGroupBox);
        label_oldObsFile->setObjectName(QString::fromUtf8("label_oldObsFile"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_oldObsFile->sizePolicy().hasHeightForWidth());
        label_oldObsFile->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font.setPointSize(8);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        label_oldObsFile->setFont(font);

        layout_obsFile->addWidget(label_oldObsFile);

        obsCombo = new QComboBox(obsSourceGroupBox);
        obsCombo->setObjectName(QString::fromUtf8("obsCombo"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(obsCombo->sizePolicy().hasHeightForWidth());
        obsCombo->setSizePolicy(sizePolicy1);

        layout_obsFile->addWidget(obsCombo);

        spacer_obsFile = new QSpacerItem(71, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        layout_obsFile->addItem(spacer_obsFile);


        _2->addLayout(layout_obsFile);


        layout_convertObs->addWidget(obsSourceGroupBox);

        obsTargetGroupBox = new QGroupBox(obsTab);
        obsTargetGroupBox->setObjectName(QString::fromUtf8("obsTargetGroupBox"));
        _3 = new QVBoxLayout(obsTargetGroupBox);
        _3->setSpacing(6);
        _3->setObjectName(QString::fromUtf8("_3"));
        _3->setContentsMargins(9, 9, 9, 9);
        layout_obsTarget = new QHBoxLayout();
        layout_obsTarget->setSpacing(6);
        layout_obsTarget->setObjectName(QString::fromUtf8("layout_obsTarget"));
        layout_obsTarget->setContentsMargins(0, 0, 0, 0);
        label_newObsFile = new QLabel(obsTargetGroupBox);
        label_newObsFile->setObjectName(QString::fromUtf8("label_newObsFile"));
        sizePolicy.setHeightForWidth(label_newObsFile->sizePolicy().hasHeightForWidth());
        label_newObsFile->setSizePolicy(sizePolicy);
        label_newObsFile->setFont(font);

        layout_obsTarget->addWidget(label_newObsFile);

        obsInput = new QLineEdit(obsTargetGroupBox);
        obsInput->setObjectName(QString::fromUtf8("obsInput"));

        layout_obsTarget->addWidget(obsInput);

        spacer_obsTarget = new QSpacerItem(71, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        layout_obsTarget->addItem(spacer_obsTarget);


        _3->addLayout(layout_obsTarget);


        layout_convertObs->addWidget(obsTargetGroupBox);

        spacer_convertObs = new QSpacerItem(20, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

        layout_convertObs->addItem(spacer_convertObs);


        vboxLayout->addLayout(layout_convertObs);

        tabWidget->addTab(obsTab, QString());
        tagTab = new QWidget();
        tagTab->setObjectName(QString::fromUtf8("tagTab"));
        _4 = new QVBoxLayout(tagTab);
        _4->setSpacing(6);
        _4->setObjectName(QString::fromUtf8("_4"));
        _4->setContentsMargins(9, 9, 9, 9);
        layout_tag = new QVBoxLayout();
        layout_tag->setSpacing(6);
        layout_tag->setObjectName(QString::fromUtf8("layout_tag"));
        layout_tag->setContentsMargins(0, 0, 0, 0);
        tagCheckBox = new QCheckBox(tagTab);
        tagCheckBox->setObjectName(QString::fromUtf8("tagCheckBox"));
        tagCheckBox->setChecked(true);

        layout_tag->addWidget(tagCheckBox);

        tagSourceGroupBox = new QGroupBox(tagTab);
        tagSourceGroupBox->setObjectName(QString::fromUtf8("tagSourceGroupBox"));
        _5 = new QVBoxLayout(tagSourceGroupBox);
        _5->setSpacing(6);
        _5->setObjectName(QString::fromUtf8("_5"));
        _5->setContentsMargins(9, 9, 9, 9);
        layout_tagFile = new QHBoxLayout();
        layout_tagFile->setSpacing(6);
        layout_tagFile->setObjectName(QString::fromUtf8("layout_tagFile"));
        layout_tagFile->setContentsMargins(0, 0, 0, 0);
        layout_tagrelFile = new QVBoxLayout();
        layout_tagrelFile->setSpacing(6);
        layout_tagrelFile->setObjectName(QString::fromUtf8("layout_tagrelFile"));
        layout_tagrelFile->setContentsMargins(0, 0, 0, 0);
        label_tagFIle = new QLabel(tagSourceGroupBox);
        label_tagFIle->setObjectName(QString::fromUtf8("label_tagFIle"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_tagFIle->sizePolicy().hasHeightForWidth());
        label_tagFIle->setSizePolicy(sizePolicy2);
        label_tagFIle->setFont(font);
        label_tagFIle->setAlignment(Qt::AlignVCenter);

        layout_tagrelFile->addWidget(label_tagFIle);

        label_relFile = new QLabel(tagSourceGroupBox);
        label_relFile->setObjectName(QString::fromUtf8("label_relFile"));

        layout_tagrelFile->addWidget(label_relFile);


        layout_tagFile->addLayout(layout_tagrelFile);

        layout_tagCombo = new QVBoxLayout();
        layout_tagCombo->setSpacing(6);
        layout_tagCombo->setObjectName(QString::fromUtf8("layout_tagCombo"));
        layout_tagCombo->setContentsMargins(0, 0, 0, 0);
        tagCombo = new QComboBox(tagSourceGroupBox);
        tagCombo->setObjectName(QString::fromUtf8("tagCombo"));
        sizePolicy1.setHeightForWidth(tagCombo->sizePolicy().hasHeightForWidth());
        tagCombo->setSizePolicy(sizePolicy1);

        layout_tagCombo->addWidget(tagCombo);

        relCombo = new QComboBox(tagSourceGroupBox);
        relCombo->setObjectName(QString::fromUtf8("relCombo"));
        sizePolicy1.setHeightForWidth(relCombo->sizePolicy().hasHeightForWidth());
        relCombo->setSizePolicy(sizePolicy1);

        layout_tagCombo->addWidget(relCombo);


        layout_tagFile->addLayout(layout_tagCombo);

        spacer_tagCombo = new QSpacerItem(71, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        layout_tagFile->addItem(spacer_tagCombo);


        _5->addLayout(layout_tagFile);


        layout_tag->addWidget(tagSourceGroupBox);

        tagTargetGroupBox = new QGroupBox(tagTab);
        tagTargetGroupBox->setObjectName(QString::fromUtf8("tagTargetGroupBox"));
        _6 = new QVBoxLayout(tagTargetGroupBox);
        _6->setSpacing(6);
        _6->setObjectName(QString::fromUtf8("_6"));
        _6->setContentsMargins(9, 9, 9, 9);
        layout_tagTarget = new QHBoxLayout();
        layout_tagTarget->setSpacing(6);
        layout_tagTarget->setObjectName(QString::fromUtf8("layout_tagTarget"));
        layout_tagTarget->setContentsMargins(0, 0, 0, 0);
        label_tagTarget = new QLabel(tagTargetGroupBox);
        label_tagTarget->setObjectName(QString::fromUtf8("label_tagTarget"));
        label_tagTarget->setFont(font);
        label_tagTarget->setAlignment(Qt::AlignVCenter);

        layout_tagTarget->addWidget(label_tagTarget);

        tagInput = new QLineEdit(tagTargetGroupBox);
        tagInput->setObjectName(QString::fromUtf8("tagInput"));

        layout_tagTarget->addWidget(tagInput);

        spacer_tagTarget = new QSpacerItem(71, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        layout_tagTarget->addItem(spacer_tagTarget);


        _6->addLayout(layout_tagTarget);


        layout_tag->addWidget(tagTargetGroupBox);

        spacer_tag = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        layout_tag->addItem(spacer_tag);


        _4->addLayout(layout_tag);

        tabWidget->addTab(tagTab, QString());

        layout_dataconverter->addWidget(tabWidget);

        layout_buttons = new QHBoxLayout();
        layout_buttons->setSpacing(6);
        layout_buttons->setObjectName(QString::fromUtf8("layout_buttons"));
        layout_buttons->setContentsMargins(0, 0, 0, 0);
        progressBar = new QProgressBar(DataConverter);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(10);

        layout_buttons->addWidget(progressBar);

        buttonConvert = new QPushButton(DataConverter);
        buttonConvert->setObjectName(QString::fromUtf8("buttonConvert"));
        buttonConvert->setAutoDefault(true);

        layout_buttons->addWidget(buttonConvert);

        buttonDone = new QPushButton(DataConverter);
        buttonDone->setObjectName(QString::fromUtf8("buttonDone"));
        buttonDone->setAutoDefault(true);

        layout_buttons->addWidget(buttonDone);


        layout_dataconverter->addLayout(layout_buttons);

        statusText = new QLabel(DataConverter);
        statusText->setObjectName(QString::fromUtf8("statusText"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(statusText->sizePolicy().hasHeightForWidth());
        statusText->setSizePolicy(sizePolicy3);
        statusText->setMinimumSize(QSize(0, 24));
        statusText->setMaximumSize(QSize(32767, 24));
        statusText->setFrameShape(QFrame::Panel);
        statusText->setFrameShadow(QFrame::Sunken);
        statusText->setIndent(6);

        layout_dataconverter->addWidget(statusText);


        verticalLayout->addLayout(layout_dataconverter);


        retranslateUi(DataConverter);

        tabWidget->setCurrentIndex(0);
        buttonConvert->setDefault(true);


        QMetaObject::connectSlotsByName(DataConverter);
    } // setupUi

    void retranslateUi(QDialog *DataConverter)
    {
        DataConverter->setWindowTitle(QApplication::translate("DataConverter", "Dialog", nullptr));
        obsCheckBox->setText(QApplication::translate("DataConverter", "Convert observation data", nullptr));
        obsSourceGroupBox->setTitle(QApplication::translate("DataConverter", "Source (Pre Version 4 Data)", nullptr));
        label_oldObsFile->setText(QApplication::translate("DataConverter", "Obs file:", nullptr));
        obsTargetGroupBox->setTitle(QApplication::translate("DataConverter", "Target", nullptr));
        label_newObsFile->setText(QApplication::translate("DataConverter", "New obs file:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(obsTab), QApplication::translate("DataConverter", "Observation data", nullptr));
        tagCheckBox->setText(QApplication::translate("DataConverter", "Convert tagging data", nullptr));
        tagSourceGroupBox->setTitle(QApplication::translate("DataConverter", "Source (Pre Version 4 Data)", nullptr));
        label_tagFIle->setText(QApplication::translate("DataConverter", "Tag file:", nullptr));
        label_relFile->setText(QApplication::translate("DataConverter", "Release file:", nullptr));
        tagTargetGroupBox->setTitle(QApplication::translate("DataConverter", "Target", nullptr));
        label_tagTarget->setText(QApplication::translate("DataConverter", "New tag file:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tagTab), QApplication::translate("DataConverter", "Tagging data", nullptr));
        buttonConvert->setText(QApplication::translate("DataConverter", "Convert", nullptr));
#ifndef QT_NO_SHORTCUT
        buttonConvert->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        buttonDone->setText(QApplication::translate("DataConverter", "Done", nullptr));
#ifndef QT_NO_SHORTCUT
        buttonDone->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        statusText->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DataConverter: public Ui_DataConverter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATACONVERTER_H
