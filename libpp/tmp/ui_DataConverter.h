/********************************************************************************
** Form generated from reading UI file 'DataConverter.ui'
**
** Created: Thu Oct 15 14:13:42 2020
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATACONVERTER_H
#define UI_DATACONVERTER_H

//#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataConverter
{
public:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *layout_dataconverter;
    QTabWidget *tabWidget;
    QWidget *obsTab;
    QVBoxLayout *vboxLayout1;
    QVBoxLayout *layout_convertObs;
    QCheckBox *obsCheckBox;
    QGroupBox *obsSourceGroupBox;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *layout_obsFile;
    QLabel *label_oldObsFile;
    QComboBox *obsCombo;
    QSpacerItem *spacer_obsFile;
    QGroupBox *obsTargetGroupBox;
    QVBoxLayout *vboxLayout3;
    QHBoxLayout *layout_obsTarget;
    QLabel *label_newObsFile;
    QLineEdit *obsInput;
    QSpacerItem *spacer_obsTarget;
    QSpacerItem *spacer_convertObs;
    QWidget *tagTab;
    QVBoxLayout *vboxLayout4;
    QVBoxLayout *layout_tag;
    QCheckBox *tagCheckBox;
    QGroupBox *tagSourceGroupBox;
    QVBoxLayout *vboxLayout5;
    QHBoxLayout *layout_tagFile;
    QVBoxLayout *layout_tagrelFile;
    QLabel *label_tagFIle;
    QLabel *label_relFile;
    QVBoxLayout *layout_tagCombo;
    QComboBox *tagCombo;
    QComboBox *relCombo;
    QSpacerItem *spacer_tagCombo;
    QGroupBox *tagTargetGroupBox;
    QVBoxLayout *vboxLayout6;
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
        DataConverter->resize(408, 370);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/misc.png"), QSize(), QIcon::Normal, QIcon::Off);
        DataConverter->setWindowIcon(icon);
        DataConverter->setSizeGripEnabled(true);
        vboxLayout = new QVBoxLayout(DataConverter);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        layout_dataconverter = new QVBoxLayout();
        layout_dataconverter->setSpacing(6);
        layout_dataconverter->setObjectName(QString::fromUtf8("layout_dataconverter"));
        layout_dataconverter->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(DataConverter);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        obsTab = new QWidget();
        obsTab->setObjectName(QString::fromUtf8("obsTab"));
        vboxLayout1 = new QVBoxLayout(obsTab);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(11, 11, 11, 11);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
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
        vboxLayout2 = new QVBoxLayout(obsSourceGroupBox);
        vboxLayout2->setSpacing(6);
        vboxLayout2->setContentsMargins(11, 11, 11, 11);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        vboxLayout2->setContentsMargins(9, 9, 9, 9);
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


        vboxLayout2->addLayout(layout_obsFile);


        layout_convertObs->addWidget(obsSourceGroupBox);

        obsTargetGroupBox = new QGroupBox(obsTab);
        obsTargetGroupBox->setObjectName(QString::fromUtf8("obsTargetGroupBox"));
        vboxLayout3 = new QVBoxLayout(obsTargetGroupBox);
        vboxLayout3->setSpacing(6);
        vboxLayout3->setContentsMargins(11, 11, 11, 11);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        vboxLayout3->setContentsMargins(9, 9, 9, 9);
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


        vboxLayout3->addLayout(layout_obsTarget);


        layout_convertObs->addWidget(obsTargetGroupBox);

        spacer_convertObs = new QSpacerItem(20, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

        layout_convertObs->addItem(spacer_convertObs);


        vboxLayout1->addLayout(layout_convertObs);

        tabWidget->addTab(obsTab, QString());
        tagTab = new QWidget();
        tagTab->setObjectName(QString::fromUtf8("tagTab"));
        vboxLayout4 = new QVBoxLayout(tagTab);
        vboxLayout4->setSpacing(6);
        vboxLayout4->setContentsMargins(11, 11, 11, 11);
        vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
        vboxLayout4->setContentsMargins(9, 9, 9, 9);
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
        vboxLayout5 = new QVBoxLayout(tagSourceGroupBox);
        vboxLayout5->setSpacing(6);
        vboxLayout5->setContentsMargins(11, 11, 11, 11);
        vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
        vboxLayout5->setContentsMargins(9, 9, 9, 9);
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


        vboxLayout5->addLayout(layout_tagFile);


        layout_tag->addWidget(tagSourceGroupBox);

        tagTargetGroupBox = new QGroupBox(tagTab);
        tagTargetGroupBox->setObjectName(QString::fromUtf8("tagTargetGroupBox"));
        vboxLayout6 = new QVBoxLayout(tagTargetGroupBox);
        vboxLayout6->setSpacing(6);
        vboxLayout6->setContentsMargins(11, 11, 11, 11);
        vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
        vboxLayout6->setContentsMargins(9, 9, 9, 9);
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


        vboxLayout6->addLayout(layout_tagTarget);


        layout_tag->addWidget(tagTargetGroupBox);

        spacer_tag = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        layout_tag->addItem(spacer_tag);


        vboxLayout4->addLayout(layout_tag);

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
        buttonConvert->setDefault(true);

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


        vboxLayout->addLayout(layout_dataconverter);


        retranslateUi(DataConverter);
        QObject::connect(buttonDone, SIGNAL(clicked()), DataConverter, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DataConverter);
    } // setupUi

    void retranslateUi(QDialog *DataConverter)
    {
        DataConverter->setWindowTitle(QApplication::translate("DataConverter", "Data Converter", 0));
#ifndef QT_NO_WHATSTHIS
        DataConverter->setWhatsThis(QApplication::translate("DataConverter", "The Data Converter converts data files from the old PitPro format (pre-version 4) into the current format. This is only useful when running PitPro with old data. The tagging and observation data can be converted seperately, or consecutively. The new observation data file requires fewer fields than the old one, and so the conversion simply involves removing unnecessary columns. The tagging data file now includes release date, and release site. By including the pre-version 4 release data file in the tagging data conversion, the program will add the release data to the new tagging data file. The release site will be unavailable when converting old tagging data to new. Currently the release site is only used when comparing recapture sites to release sites in the case where this type of recapture is ignored, which is an optional setting.", 0));
#endif // QT_NO_WHATSTHIS
        obsCheckBox->setText(QApplication::translate("DataConverter", "Convert observation data", 0));
        obsSourceGroupBox->setTitle(QApplication::translate("DataConverter", "Source (Pre Version 4 Data)", 0));
        label_oldObsFile->setText(QApplication::translate("DataConverter", "Obs file:", 0));
        obsTargetGroupBox->setTitle(QApplication::translate("DataConverter", "Target", 0));
        label_newObsFile->setText(QApplication::translate("DataConverter", "New obs file:", 0));
        tabWidget->setTabText(tabWidget->indexOf(obsTab), QApplication::translate("DataConverter", "Observation data", 0));
        tagCheckBox->setText(QApplication::translate("DataConverter", "Convert tagging data", 0));
        tagSourceGroupBox->setTitle(QApplication::translate("DataConverter", "Source (Pre Version 4 Data)", 0));
        label_tagFIle->setText(QApplication::translate("DataConverter", "Tag file:", 0));
        label_relFile->setText(QApplication::translate("DataConverter", "Release file:", 0));
        tagTargetGroupBox->setTitle(QApplication::translate("DataConverter", "Target", 0));
        label_tagTarget->setText(QApplication::translate("DataConverter", "New tag file:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tagTab), QApplication::translate("DataConverter", "Tagging data", 0));
        buttonConvert->setText(QApplication::translate("DataConverter", "Convert", 0));
        buttonConvert->setShortcut(QString());
        buttonDone->setText(QApplication::translate("DataConverter", "Done", 0));
        buttonDone->setShortcut(QString());
        statusText->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DataConverter: public Ui_DataConverter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATACONVERTER_H
