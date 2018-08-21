/********************************************************************************
** Form generated from reading UI file 'ConfigWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGWIDGET_H
#define UI_CONFIGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigWidget
{
public:
    QVBoxLayout *vboxLayout;
    QTabWidget *tabWidget;
    QWidget *runSetup;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *filesInputGroupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *InputFolderLayout;
    QLabel *dataFolderLabel;
    QLineEdit *dataDirEdit;
    QPushButton *dataDirButton;
    QHBoxLayout *OutputFolderLayout;
    QLabel *outputFolderLabel;
    QLineEdit *outDirEdit;
    QPushButton *outDirButton;
    QGroupBox *runConfigGroupBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *runConfigLayout;
    QHBoxLayout *runConfigPopLayout;
    QVBoxLayout *runConfigPopLabels;
    QLabel *popNameTextLabel;
    QLabel *tagFileTextLabel;
    QLabel *obsFileTextLabel;
    QVBoxLayout *runConfigPopSelectLayout;
    QHBoxLayout *runConfigPopNameLayout;
    QLineEdit *runNameEdit;
    QSpacerItem *runConfigPopNameSpacer;
    QComboBox *tagCombo;
    QComboBox *obsCombo;
    QSpacerItem *runConfigSpacer;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *runConfig;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_6;
    QLabel *mortFileTextLabel;
    QLabel *recaptureFileTextLabel;
    QVBoxLayout *verticalLayout_7;
    QComboBox *mortCombo;
    QComboBox *recapCombo;
    QCheckBox *fileFilterSwitch;
    QHBoxLayout *runButtonsLayout;
    QSpacerItem *runButtonsSpacer;
    QPushButton *addRunButton;
    QPushButton *deleteRunButton;
    QGroupBox *definedRunsGroupBox;
    QVBoxLayout *vboxLayout1;
    QVBoxLayout *definedRunsLayout;
    QTableWidget *runsTable;
    QHBoxLayout *definedRunsCombineLayout;
    QCheckBox *groupRunsCheckBox;
    QSpacerItem *definedRunsCombineSpacer;
    QLabel *runPrefixTextLabel;
    QLineEdit *outPrefixEdit;
    QWidget *files;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *selectFilesGroup;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *surphFileCheckBox;
    QCheckBox *errorsFileCheckBox;
    QCheckBox *detectionDateFileCheckBox;
    QCheckBox *travelTimeFileCheckBox;
    QCheckBox *sequenceFileCheckBox;
    QGroupBox *captureHistGroup;
    QVBoxLayout *vboxLayout3;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_4;
    QLabel *formatTextlabel;
    QComboBox *surphVersionCombo;
    QSpacerItem *spacer_3;
    QGroupBox *covariatesGroup;
    QVBoxLayout *vboxLayout4;
    QCheckBox *lengthCovCheckBox;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *spacer_2;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *zeroCovariateCheckBox;
    QCheckBox *nullCovariateCheckBox;
    QSpacerItem *spacer;
    QWidget *sites;
    QVBoxLayout *vboxLayout5;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox_4;
    QVBoxLayout *vboxLayout6;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_6;
    QComboBox *histFieldCombo;
    QPushButton *addHistFieldButton;
    QPushButton *sortJuvenileSitesButton;
    QSpacerItem *spacer_4;
    QListWidget *histFieldList;
    QGroupBox *groupBox_5;
    QVBoxLayout *vboxLayout7;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *adultSiteCombo;
    QPushButton *addAdultSiteButton;
    QPushButton *sortAdultSitesButton;
    QSpacerItem *spacer_5;
    QListWidget *adultSiteList;
    QGroupBox *groupBox_6;
    QVBoxLayout *vboxLayout8;
    QCheckBox *siteRelCheckBox;
    QGroupBox *lastFieldGroupBox;
    QVBoxLayout *vboxLayout9;
    QHBoxLayout *horizontalLayout_8;
    QLabel *lastFieldTextLabel;
    QComboBox *lastFieldCombo;
    QSpacerItem *spacer_6;
    QWidget *tagScreening;
    QVBoxLayout *vboxLayout10;
    QVBoxLayout *verticalLayout_13;
    QGroupBox *groupBox_7;
    QVBoxLayout *vboxLayout11;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_14;
    QLabel *speciesTextLabel;
    QLabel *runTextLabel;
    QLabel *rtTextLabel;
    QVBoxLayout *verticalLayout_15;
    QComboBox *speciesCombo;
    QComboBox *runCombo;
    QComboBox *rearTypeCombo;
    QSpacerItem *spacer_8;
    QSpacerItem *spacer_7;
    QWidget *adultCriteria;
    QVBoxLayout *vboxLayout12;
    QCheckBox *assumeJuvenileCheckBox;
    QGroupBox *groupBox_18;
    QVBoxLayout *vboxLayout13;
    QCheckBox *steelheadYearCB;
    QGroupBox *groupBox_11;
    QVBoxLayout *vboxLayout14;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_17;
    QRadioButton *migrationYearRadio;
    QRadioButton *juvCutoffRadio;
    QVBoxLayout *verticalLayout_18;
    QLineEdit *migrYearEdit;
    QLineEdit *juvCutoffEdit;
    QSpacerItem *spacer_10;
    QGroupBox *groupBox_10;
    QVBoxLayout *vboxLayout15;
    QVBoxLayout *verticalLayout_16;
    QLabel *miniJackTextLabel;
    QRadioButton *combineJacksCheckBox;
    QRadioButton *removeJacksCheckBox;
    QGroupBox *groupBox_8;
    QVBoxLayout *vboxLayout16;
    QHBoxLayout *horizontalLayout_11;
    QLabel *textLabel2;
    QRadioButton *lastRouteRadio;
    QRadioButton *anyRouteRadio;
    QSpacerItem *spacer_11;
    QGroupBox *groupBox_9;
    QVBoxLayout *vboxLayout17;
    QVBoxLayout *verticalLayout_19;
    QCheckBox *removeResSwitch;
    QCheckBox *resCutoffCheckBox;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *spacer_12;
    QLabel *label;
    QLineEdit *resCutoffEdit;
    QSpacerItem *spacerItem;
    QSpacerItem *spacer_9;
    QWidget *trans;
    QVBoxLayout *vboxLayout18;
    QVBoxLayout *verticalLayout_20;
    QLabel *label_3;
    QGroupBox *groupBox_16;
    QVBoxLayout *vboxLayout19;
    QVBoxLayout *verticalLayout_21;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_13;
    QVBoxLayout *verticalLayout_22;
    QHBoxLayout *horizontalLayout_14;
    QComboBox *transComboBox;
    QPushButton *addTransSiteButton;
    QPushButton *sortTransSitesButton;
    QSpacerItem *spacer_14;
    QListWidget *transSiteList;
    QSpacerItem *spacer_15;
    QGroupBox *groupBox_17;
    QVBoxLayout *vboxLayout20;
    QCheckBox *sampTransCheckBox;
    QSpacerItem *spacer_13;
    QWidget *advanced;
    QVBoxLayout *vboxLayout21;
    QGroupBox *groupBox_14;
    QVBoxLayout *vboxLayout22;
    QHBoxLayout *horizontalLayout_15;
    QLabel *methodTextLabel;
    QRadioButton *removalTrumpsRadio;
    QRadioButton *lastDetectionRadio;
    QSpacerItem *spacer_17;
    QGroupBox *groupBox_13;
    QVBoxLayout *vboxLayout23;
    QCheckBox *ignoreReRecapsCheckBox;
    QGroupBox *groupBox_12;
    QVBoxLayout *vboxLayout24;
    QCheckBox *singleCoilCheckBox;
    QCheckBox *tagCheckBox;
    QCheckBox *warningsCheckBox;
    QSpacerItem *spacer_16;

    void setupUi(QWidget *ConfigWidget)
    {
        if (ConfigWidget->objectName().isEmpty())
            ConfigWidget->setObjectName(QStringLiteral("ConfigWidget"));
        ConfigWidget->resize(666, 573);
        vboxLayout = new QVBoxLayout(ConfigWidget);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        tabWidget = new QTabWidget(ConfigWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setFocusPolicy(Qt::NoFocus);
        runSetup = new QWidget();
        runSetup->setObjectName(QStringLiteral("runSetup"));
        verticalLayout_5 = new QVBoxLayout(runSetup);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        filesInputGroupBox_2 = new QGroupBox(runSetup);
        filesInputGroupBox_2->setObjectName(QStringLiteral("filesInputGroupBox_2"));
        verticalLayout = new QVBoxLayout(filesInputGroupBox_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        InputFolderLayout = new QHBoxLayout();
        InputFolderLayout->setSpacing(6);
        InputFolderLayout->setObjectName(QStringLiteral("InputFolderLayout"));
        InputFolderLayout->setContentsMargins(0, 0, 0, 0);
        dataFolderLabel = new QLabel(filesInputGroupBox_2);
        dataFolderLabel->setObjectName(QStringLiteral("dataFolderLabel"));

        InputFolderLayout->addWidget(dataFolderLabel);

        dataDirEdit = new QLineEdit(filesInputGroupBox_2);
        dataDirEdit->setObjectName(QStringLiteral("dataDirEdit"));

        InputFolderLayout->addWidget(dataDirEdit);

        dataDirButton = new QPushButton(filesInputGroupBox_2);
        dataDirButton->setObjectName(QStringLiteral("dataDirButton"));
        dataDirButton->setMaximumSize(QSize(40, 32767));

        InputFolderLayout->addWidget(dataDirButton);


        verticalLayout->addLayout(InputFolderLayout);

        OutputFolderLayout = new QHBoxLayout();
        OutputFolderLayout->setSpacing(6);
        OutputFolderLayout->setObjectName(QStringLiteral("OutputFolderLayout"));
        OutputFolderLayout->setContentsMargins(0, 0, 0, 0);
        outputFolderLabel = new QLabel(filesInputGroupBox_2);
        outputFolderLabel->setObjectName(QStringLiteral("outputFolderLabel"));
        outputFolderLabel->setAlignment(Qt::AlignVCenter);

        OutputFolderLayout->addWidget(outputFolderLabel);

        outDirEdit = new QLineEdit(filesInputGroupBox_2);
        outDirEdit->setObjectName(QStringLiteral("outDirEdit"));

        OutputFolderLayout->addWidget(outDirEdit);

        outDirButton = new QPushButton(filesInputGroupBox_2);
        outDirButton->setObjectName(QStringLiteral("outDirButton"));
        outDirButton->setMaximumSize(QSize(40, 32767));

        OutputFolderLayout->addWidget(outDirButton);


        verticalLayout->addLayout(OutputFolderLayout);


        verticalLayout_5->addWidget(filesInputGroupBox_2);

        runConfigGroupBox = new QGroupBox(runSetup);
        runConfigGroupBox->setObjectName(QStringLiteral("runConfigGroupBox"));
        verticalLayout_4 = new QVBoxLayout(runConfigGroupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        runConfigLayout = new QHBoxLayout();
        runConfigLayout->setSpacing(6);
        runConfigLayout->setObjectName(QStringLiteral("runConfigLayout"));
        runConfigPopLayout = new QHBoxLayout();
        runConfigPopLayout->setSpacing(6);
        runConfigPopLayout->setObjectName(QStringLiteral("runConfigPopLayout"));
        runConfigPopLayout->setContentsMargins(0, 0, 0, 0);
        runConfigPopLabels = new QVBoxLayout();
        runConfigPopLabels->setSpacing(6);
        runConfigPopLabels->setObjectName(QStringLiteral("runConfigPopLabels"));
        runConfigPopLabels->setContentsMargins(0, 0, 0, 0);
        popNameTextLabel = new QLabel(runConfigGroupBox);
        popNameTextLabel->setObjectName(QStringLiteral("popNameTextLabel"));
        QFont font;
        font.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font.setPointSize(8);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        popNameTextLabel->setFont(font);

        runConfigPopLabels->addWidget(popNameTextLabel);

        tagFileTextLabel = new QLabel(runConfigGroupBox);
        tagFileTextLabel->setObjectName(QStringLiteral("tagFileTextLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tagFileTextLabel->sizePolicy().hasHeightForWidth());
        tagFileTextLabel->setSizePolicy(sizePolicy);
        tagFileTextLabel->setFont(font);

        runConfigPopLabels->addWidget(tagFileTextLabel);

        obsFileTextLabel = new QLabel(runConfigGroupBox);
        obsFileTextLabel->setObjectName(QStringLiteral("obsFileTextLabel"));
        obsFileTextLabel->setFont(font);
        obsFileTextLabel->setAlignment(Qt::AlignVCenter);

        runConfigPopLabels->addWidget(obsFileTextLabel);


        runConfigPopLayout->addLayout(runConfigPopLabels);

        runConfigPopSelectLayout = new QVBoxLayout();
        runConfigPopSelectLayout->setSpacing(6);
        runConfigPopSelectLayout->setObjectName(QStringLiteral("runConfigPopSelectLayout"));
        runConfigPopSelectLayout->setContentsMargins(0, 0, 0, 0);
        runConfigPopNameLayout = new QHBoxLayout();
        runConfigPopNameLayout->setSpacing(6);
        runConfigPopNameLayout->setObjectName(QStringLiteral("runConfigPopNameLayout"));
        runConfigPopNameLayout->setContentsMargins(0, 0, 0, 0);
        runNameEdit = new QLineEdit(runConfigGroupBox);
        runNameEdit->setObjectName(QStringLiteral("runNameEdit"));

        runConfigPopNameLayout->addWidget(runNameEdit);

        runConfigPopNameSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        runConfigPopNameLayout->addItem(runConfigPopNameSpacer);


        runConfigPopSelectLayout->addLayout(runConfigPopNameLayout);

        tagCombo = new QComboBox(runConfigGroupBox);
        tagCombo->setObjectName(QStringLiteral("tagCombo"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tagCombo->sizePolicy().hasHeightForWidth());
        tagCombo->setSizePolicy(sizePolicy1);

        runConfigPopSelectLayout->addWidget(tagCombo);

        obsCombo = new QComboBox(runConfigGroupBox);
        obsCombo->setObjectName(QStringLiteral("obsCombo"));
        sizePolicy1.setHeightForWidth(obsCombo->sizePolicy().hasHeightForWidth());
        obsCombo->setSizePolicy(sizePolicy1);

        runConfigPopSelectLayout->addWidget(obsCombo);


        runConfigPopLayout->addLayout(runConfigPopSelectLayout);


        runConfigLayout->addLayout(runConfigPopLayout);

        runConfigSpacer = new QSpacerItem(71, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        runConfigLayout->addItem(runConfigSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        runConfig = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(runConfig);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        mortFileTextLabel = new QLabel(runConfigGroupBox);
        mortFileTextLabel->setObjectName(QStringLiteral("mortFileTextLabel"));
        sizePolicy.setHeightForWidth(mortFileTextLabel->sizePolicy().hasHeightForWidth());
        mortFileTextLabel->setSizePolicy(sizePolicy);
        mortFileTextLabel->setFont(font);

        verticalLayout_6->addWidget(mortFileTextLabel);

        recaptureFileTextLabel = new QLabel(runConfigGroupBox);
        recaptureFileTextLabel->setObjectName(QStringLiteral("recaptureFileTextLabel"));
        sizePolicy.setHeightForWidth(recaptureFileTextLabel->sizePolicy().hasHeightForWidth());
        recaptureFileTextLabel->setSizePolicy(sizePolicy);
        recaptureFileTextLabel->setFont(font);

        verticalLayout_6->addWidget(recaptureFileTextLabel);


        horizontalLayout->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        mortCombo = new QComboBox(runConfigGroupBox);
        mortCombo->setObjectName(QStringLiteral("mortCombo"));
        sizePolicy1.setHeightForWidth(mortCombo->sizePolicy().hasHeightForWidth());
        mortCombo->setSizePolicy(sizePolicy1);

        verticalLayout_7->addWidget(mortCombo);

        recapCombo = new QComboBox(runConfigGroupBox);
        recapCombo->setObjectName(QStringLiteral("recapCombo"));
        sizePolicy1.setHeightForWidth(recapCombo->sizePolicy().hasHeightForWidth());
        recapCombo->setSizePolicy(sizePolicy1);

        verticalLayout_7->addWidget(recapCombo);


        horizontalLayout->addLayout(verticalLayout_7);


        verticalLayout_2->addLayout(horizontalLayout);


        runConfigLayout->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(runConfigLayout);

        fileFilterSwitch = new QCheckBox(runConfigGroupBox);
        fileFilterSwitch->setObjectName(QStringLiteral("fileFilterSwitch"));

        verticalLayout_4->addWidget(fileFilterSwitch);


        verticalLayout_5->addWidget(runConfigGroupBox);

        runButtonsLayout = new QHBoxLayout();
        runButtonsLayout->setSpacing(6);
        runButtonsLayout->setObjectName(QStringLiteral("runButtonsLayout"));
        runButtonsLayout->setContentsMargins(0, 0, 0, 0);
        runButtonsSpacer = new QSpacerItem(289, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        runButtonsLayout->addItem(runButtonsSpacer);

        addRunButton = new QPushButton(runSetup);
        addRunButton->setObjectName(QStringLiteral("addRunButton"));
        addRunButton->setFont(font);
        addRunButton->setFocusPolicy(Qt::TabFocus);
        addRunButton->setAutoDefault(false);

        runButtonsLayout->addWidget(addRunButton);

        deleteRunButton = new QPushButton(runSetup);
        deleteRunButton->setObjectName(QStringLiteral("deleteRunButton"));
        deleteRunButton->setFocusPolicy(Qt::NoFocus);

        runButtonsLayout->addWidget(deleteRunButton);


        verticalLayout_5->addLayout(runButtonsLayout);

        definedRunsGroupBox = new QGroupBox(runSetup);
        definedRunsGroupBox->setObjectName(QStringLiteral("definedRunsGroupBox"));
        vboxLayout1 = new QVBoxLayout(definedRunsGroupBox);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(11, 11, 11, 11);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
        definedRunsLayout = new QVBoxLayout();
        definedRunsLayout->setSpacing(6);
        definedRunsLayout->setObjectName(QStringLiteral("definedRunsLayout"));
        definedRunsLayout->setContentsMargins(0, 0, 0, 0);
        runsTable = new QTableWidget(definedRunsGroupBox);
        runsTable->setObjectName(QStringLiteral("runsTable"));

        definedRunsLayout->addWidget(runsTable);

        definedRunsCombineLayout = new QHBoxLayout();
        definedRunsCombineLayout->setSpacing(6);
        definedRunsCombineLayout->setObjectName(QStringLiteral("definedRunsCombineLayout"));
        definedRunsCombineLayout->setContentsMargins(0, 0, 0, 0);
        groupRunsCheckBox = new QCheckBox(definedRunsGroupBox);
        groupRunsCheckBox->setObjectName(QStringLiteral("groupRunsCheckBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupRunsCheckBox->sizePolicy().hasHeightForWidth());
        groupRunsCheckBox->setSizePolicy(sizePolicy2);
        groupRunsCheckBox->setFont(font);
        groupRunsCheckBox->setFocusPolicy(Qt::NoFocus);

        definedRunsCombineLayout->addWidget(groupRunsCheckBox);

        definedRunsCombineSpacer = new QSpacerItem(80, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        definedRunsCombineLayout->addItem(definedRunsCombineSpacer);

        runPrefixTextLabel = new QLabel(definedRunsGroupBox);
        runPrefixTextLabel->setObjectName(QStringLiteral("runPrefixTextLabel"));
        runPrefixTextLabel->setAlignment(Qt::AlignVCenter);

        definedRunsCombineLayout->addWidget(runPrefixTextLabel);

        outPrefixEdit = new QLineEdit(definedRunsGroupBox);
        outPrefixEdit->setObjectName(QStringLiteral("outPrefixEdit"));
        outPrefixEdit->setEnabled(false);

        definedRunsCombineLayout->addWidget(outPrefixEdit);


        definedRunsLayout->addLayout(definedRunsCombineLayout);


        vboxLayout1->addLayout(definedRunsLayout);


        verticalLayout_5->addWidget(definedRunsGroupBox);

        tabWidget->addTab(runSetup, QString());
        files = new QWidget();
        files->setObjectName(QStringLiteral("files"));
        verticalLayout_3 = new QVBoxLayout(files);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        selectFilesGroup = new QGroupBox(files);
        selectFilesGroup->setObjectName(QStringLiteral("selectFilesGroup"));
        vboxLayout2 = new QVBoxLayout(selectFilesGroup);
        vboxLayout2->setSpacing(6);
        vboxLayout2->setContentsMargins(11, 11, 11, 11);
        vboxLayout2->setObjectName(QStringLiteral("vboxLayout2"));
        vboxLayout2->setContentsMargins(9, 9, 9, 9);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        surphFileCheckBox = new QCheckBox(selectFilesGroup);
        surphFileCheckBox->setObjectName(QStringLiteral("surphFileCheckBox"));
        surphFileCheckBox->setChecked(true);

        horizontalLayout_2->addWidget(surphFileCheckBox);

        errorsFileCheckBox = new QCheckBox(selectFilesGroup);
        errorsFileCheckBox->setObjectName(QStringLiteral("errorsFileCheckBox"));
        errorsFileCheckBox->setChecked(true);

        horizontalLayout_2->addWidget(errorsFileCheckBox);

        detectionDateFileCheckBox = new QCheckBox(selectFilesGroup);
        detectionDateFileCheckBox->setObjectName(QStringLiteral("detectionDateFileCheckBox"));
        detectionDateFileCheckBox->setChecked(true);

        horizontalLayout_2->addWidget(detectionDateFileCheckBox);

        travelTimeFileCheckBox = new QCheckBox(selectFilesGroup);
        travelTimeFileCheckBox->setObjectName(QStringLiteral("travelTimeFileCheckBox"));

        horizontalLayout_2->addWidget(travelTimeFileCheckBox);

        sequenceFileCheckBox = new QCheckBox(selectFilesGroup);
        sequenceFileCheckBox->setObjectName(QStringLiteral("sequenceFileCheckBox"));

        horizontalLayout_2->addWidget(sequenceFileCheckBox);


        vboxLayout2->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(selectFilesGroup);

        captureHistGroup = new QGroupBox(files);
        captureHistGroup->setObjectName(QStringLiteral("captureHistGroup"));
        vboxLayout3 = new QVBoxLayout(captureHistGroup);
        vboxLayout3->setSpacing(6);
        vboxLayout3->setContentsMargins(11, 11, 11, 11);
        vboxLayout3->setObjectName(QStringLiteral("vboxLayout3"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        formatTextlabel = new QLabel(captureHistGroup);
        formatTextlabel->setObjectName(QStringLiteral("formatTextlabel"));

        horizontalLayout_4->addWidget(formatTextlabel);

        surphVersionCombo = new QComboBox(captureHistGroup);
        surphVersionCombo->setObjectName(QStringLiteral("surphVersionCombo"));

        horizontalLayout_4->addWidget(surphVersionCombo);

        spacer_3 = new QSpacerItem(589, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(spacer_3);


        verticalLayout_9->addLayout(horizontalLayout_4);


        vboxLayout3->addLayout(verticalLayout_9);


        verticalLayout_3->addWidget(captureHistGroup);

        covariatesGroup = new QGroupBox(files);
        covariatesGroup->setObjectName(QStringLiteral("covariatesGroup"));
        vboxLayout4 = new QVBoxLayout(covariatesGroup);
        vboxLayout4->setSpacing(6);
        vboxLayout4->setContentsMargins(11, 11, 11, 11);
        vboxLayout4->setObjectName(QStringLiteral("vboxLayout4"));
        lengthCovCheckBox = new QCheckBox(covariatesGroup);
        lengthCovCheckBox->setObjectName(QStringLiteral("lengthCovCheckBox"));

        vboxLayout4->addWidget(lengthCovCheckBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        spacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(spacer_2);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        zeroCovariateCheckBox = new QCheckBox(covariatesGroup);
        zeroCovariateCheckBox->setObjectName(QStringLiteral("zeroCovariateCheckBox"));
        zeroCovariateCheckBox->setEnabled(false);

        verticalLayout_8->addWidget(zeroCovariateCheckBox);

        nullCovariateCheckBox = new QCheckBox(covariatesGroup);
        nullCovariateCheckBox->setObjectName(QStringLiteral("nullCovariateCheckBox"));
        nullCovariateCheckBox->setEnabled(false);

        verticalLayout_8->addWidget(nullCovariateCheckBox);


        horizontalLayout_3->addLayout(verticalLayout_8);


        vboxLayout4->addLayout(horizontalLayout_3);


        verticalLayout_3->addWidget(covariatesGroup);

        spacer = new QSpacerItem(616, 291, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(spacer);

        tabWidget->addTab(files, QString());
        covariatesGroup->raise();
        selectFilesGroup->raise();
        captureHistGroup->raise();
        sites = new QWidget();
        sites->setObjectName(QStringLiteral("sites"));
        vboxLayout5 = new QVBoxLayout(sites);
        vboxLayout5->setSpacing(6);
        vboxLayout5->setContentsMargins(11, 11, 11, 11);
        vboxLayout5->setObjectName(QStringLiteral("vboxLayout5"));
        vboxLayout5->setContentsMargins(9, 9, 9, 9);
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        groupBox_4 = new QGroupBox(sites);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        vboxLayout6 = new QVBoxLayout(groupBox_4);
        vboxLayout6->setSpacing(6);
        vboxLayout6->setContentsMargins(11, 11, 11, 11);
        vboxLayout6->setObjectName(QStringLiteral("vboxLayout6"));
        vboxLayout6->setContentsMargins(9, 9, 9, 9);
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        histFieldCombo = new QComboBox(groupBox_4);
        histFieldCombo->setObjectName(QStringLiteral("histFieldCombo"));
        sizePolicy1.setHeightForWidth(histFieldCombo->sizePolicy().hasHeightForWidth());
        histFieldCombo->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(histFieldCombo);

        addHistFieldButton = new QPushButton(groupBox_4);
        addHistFieldButton->setObjectName(QStringLiteral("addHistFieldButton"));
        addHistFieldButton->setMaximumSize(QSize(40, 40));

        horizontalLayout_6->addWidget(addHistFieldButton);

        sortJuvenileSitesButton = new QPushButton(groupBox_4);
        sortJuvenileSitesButton->setObjectName(QStringLiteral("sortJuvenileSitesButton"));
        sortJuvenileSitesButton->setMaximumSize(QSize(40, 40));

        horizontalLayout_6->addWidget(sortJuvenileSitesButton);

        spacer_4 = new QSpacerItem(30, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(spacer_4);


        verticalLayout_11->addLayout(horizontalLayout_6);

        histFieldList = new QListWidget(groupBox_4);
        histFieldList->setObjectName(QStringLiteral("histFieldList"));

        verticalLayout_11->addWidget(histFieldList);


        vboxLayout6->addLayout(verticalLayout_11);


        horizontalLayout_5->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(sites);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        vboxLayout7 = new QVBoxLayout(groupBox_5);
        vboxLayout7->setSpacing(6);
        vboxLayout7->setContentsMargins(11, 11, 11, 11);
        vboxLayout7->setObjectName(QStringLiteral("vboxLayout7"));
        vboxLayout7->setContentsMargins(9, 9, 9, 9);
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        adultSiteCombo = new QComboBox(groupBox_5);
        adultSiteCombo->setObjectName(QStringLiteral("adultSiteCombo"));
        adultSiteCombo->setEnabled(true);
        sizePolicy1.setHeightForWidth(adultSiteCombo->sizePolicy().hasHeightForWidth());
        adultSiteCombo->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(adultSiteCombo);

        addAdultSiteButton = new QPushButton(groupBox_5);
        addAdultSiteButton->setObjectName(QStringLiteral("addAdultSiteButton"));
        addAdultSiteButton->setEnabled(true);
        addAdultSiteButton->setMaximumSize(QSize(40, 40));

        horizontalLayout_7->addWidget(addAdultSiteButton);

        sortAdultSitesButton = new QPushButton(groupBox_5);
        sortAdultSitesButton->setObjectName(QStringLiteral("sortAdultSitesButton"));
        sortAdultSitesButton->setMaximumSize(QSize(40, 40));

        horizontalLayout_7->addWidget(sortAdultSitesButton);

        spacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(spacer_5);


        verticalLayout_12->addLayout(horizontalLayout_7);

        adultSiteList = new QListWidget(groupBox_5);
        adultSiteList->setObjectName(QStringLiteral("adultSiteList"));

        verticalLayout_12->addWidget(adultSiteList);


        vboxLayout7->addLayout(verticalLayout_12);


        horizontalLayout_5->addWidget(groupBox_5);


        verticalLayout_10->addLayout(horizontalLayout_5);

        groupBox_6 = new QGroupBox(sites);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        vboxLayout8 = new QVBoxLayout(groupBox_6);
        vboxLayout8->setSpacing(6);
        vboxLayout8->setContentsMargins(11, 11, 11, 11);
        vboxLayout8->setObjectName(QStringLiteral("vboxLayout8"));
        vboxLayout8->setContentsMargins(9, 9, 9, 9);
        siteRelCheckBox = new QCheckBox(groupBox_6);
        siteRelCheckBox->setObjectName(QStringLiteral("siteRelCheckBox"));

        vboxLayout8->addWidget(siteRelCheckBox);


        verticalLayout_10->addWidget(groupBox_6);

        lastFieldGroupBox = new QGroupBox(sites);
        lastFieldGroupBox->setObjectName(QStringLiteral("lastFieldGroupBox"));
        vboxLayout9 = new QVBoxLayout(lastFieldGroupBox);
        vboxLayout9->setSpacing(6);
        vboxLayout9->setContentsMargins(11, 11, 11, 11);
        vboxLayout9->setObjectName(QStringLiteral("vboxLayout9"));
        vboxLayout9->setContentsMargins(9, 9, 9, 9);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        lastFieldTextLabel = new QLabel(lastFieldGroupBox);
        lastFieldTextLabel->setObjectName(QStringLiteral("lastFieldTextLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lastFieldTextLabel->sizePolicy().hasHeightForWidth());
        lastFieldTextLabel->setSizePolicy(sizePolicy3);
        lastFieldTextLabel->setAlignment(Qt::AlignVCenter);

        horizontalLayout_8->addWidget(lastFieldTextLabel);

        lastFieldCombo = new QComboBox(lastFieldGroupBox);
        lastFieldCombo->setObjectName(QStringLiteral("lastFieldCombo"));
        sizePolicy1.setHeightForWidth(lastFieldCombo->sizePolicy().hasHeightForWidth());
        lastFieldCombo->setSizePolicy(sizePolicy1);

        horizontalLayout_8->addWidget(lastFieldCombo);

        spacer_6 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(spacer_6);


        vboxLayout9->addLayout(horizontalLayout_8);


        verticalLayout_10->addWidget(lastFieldGroupBox);


        vboxLayout5->addLayout(verticalLayout_10);

        tabWidget->addTab(sites, QString());
        tagScreening = new QWidget();
        tagScreening->setObjectName(QStringLiteral("tagScreening"));
        vboxLayout10 = new QVBoxLayout(tagScreening);
        vboxLayout10->setSpacing(6);
        vboxLayout10->setContentsMargins(11, 11, 11, 11);
        vboxLayout10->setObjectName(QStringLiteral("vboxLayout10"));
        vboxLayout10->setContentsMargins(9, 9, 9, 9);
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        groupBox_7 = new QGroupBox(tagScreening);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        vboxLayout11 = new QVBoxLayout(groupBox_7);
        vboxLayout11->setSpacing(6);
        vboxLayout11->setContentsMargins(11, 11, 11, 11);
        vboxLayout11->setObjectName(QStringLiteral("vboxLayout11"));
        vboxLayout11->setContentsMargins(9, 9, 9, 9);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        speciesTextLabel = new QLabel(groupBox_7);
        speciesTextLabel->setObjectName(QStringLiteral("speciesTextLabel"));
        speciesTextLabel->setEnabled(true);

        verticalLayout_14->addWidget(speciesTextLabel);

        runTextLabel = new QLabel(groupBox_7);
        runTextLabel->setObjectName(QStringLiteral("runTextLabel"));

        verticalLayout_14->addWidget(runTextLabel);

        rtTextLabel = new QLabel(groupBox_7);
        rtTextLabel->setObjectName(QStringLiteral("rtTextLabel"));
        rtTextLabel->setEnabled(true);
        rtTextLabel->setAlignment(Qt::AlignVCenter);

        verticalLayout_14->addWidget(rtTextLabel);


        horizontalLayout_9->addLayout(verticalLayout_14);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(0, 0, 0, 0);
        speciesCombo = new QComboBox(groupBox_7);
        speciesCombo->setObjectName(QStringLiteral("speciesCombo"));
        speciesCombo->setEnabled(true);

        verticalLayout_15->addWidget(speciesCombo);

        runCombo = new QComboBox(groupBox_7);
        runCombo->setObjectName(QStringLiteral("runCombo"));

        verticalLayout_15->addWidget(runCombo);

        rearTypeCombo = new QComboBox(groupBox_7);
        rearTypeCombo->setObjectName(QStringLiteral("rearTypeCombo"));
        rearTypeCombo->setEnabled(true);

        verticalLayout_15->addWidget(rearTypeCombo);


        horizontalLayout_9->addLayout(verticalLayout_15);

        spacer_8 = new QSpacerItem(352, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(spacer_8);


        vboxLayout11->addLayout(horizontalLayout_9);


        verticalLayout_13->addWidget(groupBox_7);

        spacer_7 = new QSpacerItem(20, 101, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(spacer_7);


        vboxLayout10->addLayout(verticalLayout_13);

        tabWidget->addTab(tagScreening, QString());
        adultCriteria = new QWidget();
        adultCriteria->setObjectName(QStringLiteral("adultCriteria"));
        vboxLayout12 = new QVBoxLayout(adultCriteria);
        vboxLayout12->setSpacing(6);
        vboxLayout12->setContentsMargins(11, 11, 11, 11);
        vboxLayout12->setObjectName(QStringLiteral("vboxLayout12"));
        assumeJuvenileCheckBox = new QCheckBox(adultCriteria);
        assumeJuvenileCheckBox->setObjectName(QStringLiteral("assumeJuvenileCheckBox"));
        assumeJuvenileCheckBox->setChecked(false);

        vboxLayout12->addWidget(assumeJuvenileCheckBox);

        groupBox_18 = new QGroupBox(adultCriteria);
        groupBox_18->setObjectName(QStringLiteral("groupBox_18"));
        vboxLayout13 = new QVBoxLayout(groupBox_18);
        vboxLayout13->setSpacing(6);
        vboxLayout13->setContentsMargins(11, 11, 11, 11);
        vboxLayout13->setObjectName(QStringLiteral("vboxLayout13"));
        steelheadYearCB = new QCheckBox(groupBox_18);
        steelheadYearCB->setObjectName(QStringLiteral("steelheadYearCB"));

        vboxLayout13->addWidget(steelheadYearCB);

        groupBox_11 = new QGroupBox(groupBox_18);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        vboxLayout14 = new QVBoxLayout(groupBox_11);
        vboxLayout14->setSpacing(6);
        vboxLayout14->setContentsMargins(11, 11, 11, 11);
        vboxLayout14->setObjectName(QStringLiteral("vboxLayout14"));
        vboxLayout14->setContentsMargins(9, 9, 9, 9);
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(0, 0, 0, 0);
        migrationYearRadio = new QRadioButton(groupBox_11);
        migrationYearRadio->setObjectName(QStringLiteral("migrationYearRadio"));
        migrationYearRadio->setChecked(true);

        verticalLayout_17->addWidget(migrationYearRadio);

        juvCutoffRadio = new QRadioButton(groupBox_11);
        juvCutoffRadio->setObjectName(QStringLiteral("juvCutoffRadio"));

        verticalLayout_17->addWidget(juvCutoffRadio);


        horizontalLayout_10->addLayout(verticalLayout_17);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        verticalLayout_18->setContentsMargins(0, 0, 0, 0);
        migrYearEdit = new QLineEdit(groupBox_11);
        migrYearEdit->setObjectName(QStringLiteral("migrYearEdit"));
        migrYearEdit->setMinimumSize(QSize(100, 0));
        migrYearEdit->setMaximumSize(QSize(100, 32767));

        verticalLayout_18->addWidget(migrYearEdit);

        juvCutoffEdit = new QLineEdit(groupBox_11);
        juvCutoffEdit->setObjectName(QStringLiteral("juvCutoffEdit"));
        juvCutoffEdit->setEnabled(false);
        juvCutoffEdit->setMinimumSize(QSize(100, 0));
        juvCutoffEdit->setMaximumSize(QSize(100, 32767));

        verticalLayout_18->addWidget(juvCutoffEdit);


        horizontalLayout_10->addLayout(verticalLayout_18);

        spacer_10 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(spacer_10);


        vboxLayout14->addLayout(horizontalLayout_10);


        vboxLayout13->addWidget(groupBox_11);

        groupBox_10 = new QGroupBox(groupBox_18);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        vboxLayout15 = new QVBoxLayout(groupBox_10);
        vboxLayout15->setSpacing(6);
        vboxLayout15->setContentsMargins(11, 11, 11, 11);
        vboxLayout15->setObjectName(QStringLiteral("vboxLayout15"));
        vboxLayout15->setContentsMargins(9, 9, 9, 9);
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(0, 0, 0, 0);
        miniJackTextLabel = new QLabel(groupBox_10);
        miniJackTextLabel->setObjectName(QStringLiteral("miniJackTextLabel"));
        miniJackTextLabel->setAlignment(Qt::AlignVCenter);

        verticalLayout_16->addWidget(miniJackTextLabel);

        combineJacksCheckBox = new QRadioButton(groupBox_10);
        combineJacksCheckBox->setObjectName(QStringLiteral("combineJacksCheckBox"));

        verticalLayout_16->addWidget(combineJacksCheckBox);

        removeJacksCheckBox = new QRadioButton(groupBox_10);
        removeJacksCheckBox->setObjectName(QStringLiteral("removeJacksCheckBox"));
        removeJacksCheckBox->setChecked(true);

        verticalLayout_16->addWidget(removeJacksCheckBox);


        vboxLayout15->addLayout(verticalLayout_16);


        vboxLayout13->addWidget(groupBox_10);

        groupBox_8 = new QGroupBox(groupBox_18);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        vboxLayout16 = new QVBoxLayout(groupBox_8);
        vboxLayout16->setSpacing(6);
        vboxLayout16->setContentsMargins(11, 11, 11, 11);
        vboxLayout16->setObjectName(QStringLiteral("vboxLayout16"));
        vboxLayout16->setContentsMargins(9, 9, 9, 9);
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        textLabel2 = new QLabel(groupBox_8);
        textLabel2->setObjectName(QStringLiteral("textLabel2"));
        textLabel2->setAlignment(Qt::AlignVCenter);

        horizontalLayout_11->addWidget(textLabel2);

        lastRouteRadio = new QRadioButton(groupBox_8);
        lastRouteRadio->setObjectName(QStringLiteral("lastRouteRadio"));
        lastRouteRadio->setChecked(true);

        horizontalLayout_11->addWidget(lastRouteRadio);

        anyRouteRadio = new QRadioButton(groupBox_8);
        anyRouteRadio->setObjectName(QStringLiteral("anyRouteRadio"));

        horizontalLayout_11->addWidget(anyRouteRadio);

        spacer_11 = new QSpacerItem(305, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(spacer_11);


        vboxLayout16->addLayout(horizontalLayout_11);


        vboxLayout13->addWidget(groupBox_8);

        groupBox_9 = new QGroupBox(groupBox_18);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        vboxLayout17 = new QVBoxLayout(groupBox_9);
        vboxLayout17->setSpacing(6);
        vboxLayout17->setContentsMargins(11, 11, 11, 11);
        vboxLayout17->setObjectName(QStringLiteral("vboxLayout17"));
        vboxLayout17->setContentsMargins(9, 9, 9, 9);
        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(0, 0, 0, 0);
        removeResSwitch = new QCheckBox(groupBox_9);
        removeResSwitch->setObjectName(QStringLiteral("removeResSwitch"));

        verticalLayout_19->addWidget(removeResSwitch);

        resCutoffCheckBox = new QCheckBox(groupBox_9);
        resCutoffCheckBox->setObjectName(QStringLiteral("resCutoffCheckBox"));

        verticalLayout_19->addWidget(resCutoffCheckBox);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        spacer_12 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(spacer_12);

        label = new QLabel(groupBox_9);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_12->addWidget(label);

        resCutoffEdit = new QLineEdit(groupBox_9);
        resCutoffEdit->setObjectName(QStringLiteral("resCutoffEdit"));
        resCutoffEdit->setEnabled(false);
        resCutoffEdit->setMinimumSize(QSize(100, 0));
        resCutoffEdit->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_12->addWidget(resCutoffEdit);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(spacerItem);


        verticalLayout_19->addLayout(horizontalLayout_12);


        vboxLayout17->addLayout(verticalLayout_19);


        vboxLayout13->addWidget(groupBox_9);


        vboxLayout12->addWidget(groupBox_18);

        spacer_9 = new QSpacerItem(20, 81, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout12->addItem(spacer_9);

        tabWidget->addTab(adultCriteria, QString());
        trans = new QWidget();
        trans->setObjectName(QStringLiteral("trans"));
        vboxLayout18 = new QVBoxLayout(trans);
        vboxLayout18->setSpacing(6);
        vboxLayout18->setContentsMargins(11, 11, 11, 11);
        vboxLayout18->setObjectName(QStringLiteral("vboxLayout18"));
        vboxLayout18->setContentsMargins(9, 9, 9, 9);
        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
        verticalLayout_20->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(trans);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setWordWrap(true);

        verticalLayout_20->addWidget(label_3);

        groupBox_16 = new QGroupBox(trans);
        groupBox_16->setObjectName(QStringLiteral("groupBox_16"));
        vboxLayout19 = new QVBoxLayout(groupBox_16);
        vboxLayout19->setSpacing(6);
        vboxLayout19->setContentsMargins(11, 11, 11, 11);
        vboxLayout19->setObjectName(QStringLiteral("vboxLayout19"));
        vboxLayout19->setContentsMargins(9, 9, 9, 9);
        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        verticalLayout_21->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(groupBox_16);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setWordWrap(true);

        verticalLayout_21->addWidget(label_2);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        verticalLayout_22 = new QVBoxLayout();
        verticalLayout_22->setSpacing(6);
        verticalLayout_22->setObjectName(QStringLiteral("verticalLayout_22"));
        verticalLayout_22->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        transComboBox = new QComboBox(groupBox_16);
        transComboBox->setObjectName(QStringLiteral("transComboBox"));
        sizePolicy1.setHeightForWidth(transComboBox->sizePolicy().hasHeightForWidth());
        transComboBox->setSizePolicy(sizePolicy1);

        horizontalLayout_14->addWidget(transComboBox);

        addTransSiteButton = new QPushButton(groupBox_16);
        addTransSiteButton->setObjectName(QStringLiteral("addTransSiteButton"));
        addTransSiteButton->setMaximumSize(QSize(40, 40));

        horizontalLayout_14->addWidget(addTransSiteButton);

        sortTransSitesButton = new QPushButton(groupBox_16);
        sortTransSitesButton->setObjectName(QStringLiteral("sortTransSitesButton"));
        sortTransSitesButton->setMaximumSize(QSize(40, 40));

        horizontalLayout_14->addWidget(sortTransSitesButton);

        spacer_14 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(spacer_14);


        verticalLayout_22->addLayout(horizontalLayout_14);

        transSiteList = new QListWidget(groupBox_16);
        transSiteList->setObjectName(QStringLiteral("transSiteList"));

        verticalLayout_22->addWidget(transSiteList);


        horizontalLayout_13->addLayout(verticalLayout_22);

        spacer_15 = new QSpacerItem(301, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(spacer_15);


        verticalLayout_21->addLayout(horizontalLayout_13);


        vboxLayout19->addLayout(verticalLayout_21);


        verticalLayout_20->addWidget(groupBox_16);

        groupBox_17 = new QGroupBox(trans);
        groupBox_17->setObjectName(QStringLiteral("groupBox_17"));
        vboxLayout20 = new QVBoxLayout(groupBox_17);
        vboxLayout20->setSpacing(6);
        vboxLayout20->setContentsMargins(11, 11, 11, 11);
        vboxLayout20->setObjectName(QStringLiteral("vboxLayout20"));
        vboxLayout20->setContentsMargins(9, 9, 9, 9);
        sampTransCheckBox = new QCheckBox(groupBox_17);
        sampTransCheckBox->setObjectName(QStringLiteral("sampTransCheckBox"));

        vboxLayout20->addWidget(sampTransCheckBox);


        verticalLayout_20->addWidget(groupBox_17);

        spacer_13 = new QSpacerItem(20, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_20->addItem(spacer_13);


        vboxLayout18->addLayout(verticalLayout_20);

        tabWidget->addTab(trans, QString());
        advanced = new QWidget();
        advanced->setObjectName(QStringLiteral("advanced"));
        vboxLayout21 = new QVBoxLayout(advanced);
        vboxLayout21->setSpacing(6);
        vboxLayout21->setContentsMargins(11, 11, 11, 11);
        vboxLayout21->setObjectName(QStringLiteral("vboxLayout21"));
        groupBox_14 = new QGroupBox(advanced);
        groupBox_14->setObjectName(QStringLiteral("groupBox_14"));
        vboxLayout22 = new QVBoxLayout(groupBox_14);
        vboxLayout22->setSpacing(6);
        vboxLayout22->setContentsMargins(11, 11, 11, 11);
        vboxLayout22->setObjectName(QStringLiteral("vboxLayout22"));
        vboxLayout22->setContentsMargins(9, 9, 9, 9);
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        methodTextLabel = new QLabel(groupBox_14);
        methodTextLabel->setObjectName(QStringLiteral("methodTextLabel"));

        horizontalLayout_15->addWidget(methodTextLabel);

        removalTrumpsRadio = new QRadioButton(groupBox_14);
        removalTrumpsRadio->setObjectName(QStringLiteral("removalTrumpsRadio"));
        removalTrumpsRadio->setChecked(true);

        horizontalLayout_15->addWidget(removalTrumpsRadio);

        lastDetectionRadio = new QRadioButton(groupBox_14);
        lastDetectionRadio->setObjectName(QStringLiteral("lastDetectionRadio"));
        lastDetectionRadio->setEnabled(true);

        horizontalLayout_15->addWidget(lastDetectionRadio);

        spacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(spacer_17);


        vboxLayout22->addLayout(horizontalLayout_15);


        vboxLayout21->addWidget(groupBox_14);

        groupBox_13 = new QGroupBox(advanced);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        vboxLayout23 = new QVBoxLayout(groupBox_13);
        vboxLayout23->setSpacing(6);
        vboxLayout23->setContentsMargins(11, 11, 11, 11);
        vboxLayout23->setObjectName(QStringLiteral("vboxLayout23"));
        vboxLayout23->setContentsMargins(9, 9, 9, 9);
        ignoreReRecapsCheckBox = new QCheckBox(groupBox_13);
        ignoreReRecapsCheckBox->setObjectName(QStringLiteral("ignoreReRecapsCheckBox"));

        vboxLayout23->addWidget(ignoreReRecapsCheckBox);


        vboxLayout21->addWidget(groupBox_13);

        groupBox_12 = new QGroupBox(advanced);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        vboxLayout24 = new QVBoxLayout(groupBox_12);
        vboxLayout24->setSpacing(6);
        vboxLayout24->setContentsMargins(11, 11, 11, 11);
        vboxLayout24->setObjectName(QStringLiteral("vboxLayout24"));
        singleCoilCheckBox = new QCheckBox(groupBox_12);
        singleCoilCheckBox->setObjectName(QStringLiteral("singleCoilCheckBox"));

        vboxLayout24->addWidget(singleCoilCheckBox);

        tagCheckBox = new QCheckBox(groupBox_12);
        tagCheckBox->setObjectName(QStringLiteral("tagCheckBox"));

        vboxLayout24->addWidget(tagCheckBox);

        warningsCheckBox = new QCheckBox(groupBox_12);
        warningsCheckBox->setObjectName(QStringLiteral("warningsCheckBox"));

        vboxLayout24->addWidget(warningsCheckBox);


        vboxLayout21->addWidget(groupBox_12);

        spacer_16 = new QSpacerItem(614, 81, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout21->addItem(spacer_16);

        tabWidget->addTab(advanced, QString());

        vboxLayout->addWidget(tabWidget);

        QWidget::setTabOrder(fileFilterSwitch, runNameEdit);
        QWidget::setTabOrder(runNameEdit, tagCombo);
        QWidget::setTabOrder(tagCombo, obsCombo);
        QWidget::setTabOrder(obsCombo, mortCombo);
        QWidget::setTabOrder(mortCombo, recapCombo);
        QWidget::setTabOrder(recapCombo, outPrefixEdit);
        QWidget::setTabOrder(outPrefixEdit, addRunButton);
        QWidget::setTabOrder(addRunButton, surphFileCheckBox);
        QWidget::setTabOrder(surphFileCheckBox, errorsFileCheckBox);
        QWidget::setTabOrder(errorsFileCheckBox, detectionDateFileCheckBox);
        QWidget::setTabOrder(detectionDateFileCheckBox, travelTimeFileCheckBox);
        QWidget::setTabOrder(travelTimeFileCheckBox, sequenceFileCheckBox);
        QWidget::setTabOrder(sequenceFileCheckBox, surphVersionCombo);
        QWidget::setTabOrder(surphVersionCombo, siteRelCheckBox);
        QWidget::setTabOrder(siteRelCheckBox, histFieldCombo);
        QWidget::setTabOrder(histFieldCombo, addHistFieldButton);
        QWidget::setTabOrder(addHistFieldButton, sortJuvenileSitesButton);
        QWidget::setTabOrder(sortJuvenileSitesButton, adultSiteCombo);
        QWidget::setTabOrder(adultSiteCombo, addAdultSiteButton);
        QWidget::setTabOrder(addAdultSiteButton, sortAdultSitesButton);
        QWidget::setTabOrder(sortAdultSitesButton, lastFieldCombo);
        QWidget::setTabOrder(lastFieldCombo, speciesCombo);
        QWidget::setTabOrder(speciesCombo, runCombo);
        QWidget::setTabOrder(runCombo, rearTypeCombo);
        QWidget::setTabOrder(rearTypeCombo, assumeJuvenileCheckBox);
        QWidget::setTabOrder(assumeJuvenileCheckBox, removalTrumpsRadio);
        QWidget::setTabOrder(removalTrumpsRadio, lastDetectionRadio);
        QWidget::setTabOrder(lastDetectionRadio, ignoreReRecapsCheckBox);
        QWidget::setTabOrder(ignoreReRecapsCheckBox, singleCoilCheckBox);
        QWidget::setTabOrder(singleCoilCheckBox, tagCheckBox);

        retranslateUi(ConfigWidget);
        QObject::connect(groupRunsCheckBox, SIGNAL(toggled(bool)), outPrefixEdit, SLOT(setEnabled(bool)));
        QObject::connect(assumeJuvenileCheckBox, SIGNAL(toggled(bool)), groupBox_18, SLOT(setDisabled(bool)));
        QObject::connect(resCutoffCheckBox, SIGNAL(toggled(bool)), resCutoffEdit, SLOT(setEnabled(bool)));
        QObject::connect(steelheadYearCB, SIGNAL(toggled(bool)), groupBox_10, SLOT(setDisabled(bool)));
        QObject::connect(steelheadYearCB, SIGNAL(toggled(bool)), groupBox_9, SLOT(setDisabled(bool)));
        QObject::connect(steelheadYearCB, SIGNAL(toggled(bool)), migrationYearRadio, SLOT(setChecked(bool)));
        QObject::connect(steelheadYearCB, SIGNAL(toggled(bool)), juvCutoffRadio, SLOT(setDisabled(bool)));
        QObject::connect(lengthCovCheckBox, SIGNAL(toggled(bool)), zeroCovariateCheckBox, SLOT(setEnabled(bool)));
        QObject::connect(lengthCovCheckBox, SIGNAL(toggled(bool)), nullCovariateCheckBox, SLOT(setEnabled(bool)));

        tabWidget->setCurrentIndex(0);
        addRunButton->setDefault(true);
        surphVersionCombo->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ConfigWidget);
    } // setupUi

    void retranslateUi(QWidget *ConfigWidget)
    {
        ConfigWidget->setWindowTitle(QApplication::translate("ConfigWidget", "Config Widget", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        tabWidget->setWhatsThis(QApplication::translate("ConfigWidget", "The program is configured via the tabs in the main window", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        filesInputGroupBox_2->setWhatsThis(QApplication::translate("ConfigWidget", "The folder control where data flow into and out of the program. The Input folder is where PitPro searches for the tag, obs, recapture, and mortality files. For your data fiels to appear in the Run Config menus below the Input folder needs to be set correctly. The Output folder is where output is written to.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        filesInputGroupBox_2->setTitle(QApplication::translate("ConfigWidget", "Folders", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        dataFolderLabel->setWhatsThis(QApplication::translate("ConfigWidget", "The Data Folder is where, not surprisingly, data files are searched for. For a file to be available for run definition on the Run Setup tab, or in the Data Converter, it must be in the folder defined here.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        dataFolderLabel->setText(QApplication::translate("ConfigWidget", "Input:", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        dataDirEdit->setWhatsThis(QApplication::translate("ConfigWidget", "The Data Folder is where, not surprisingly, data files are searched for. For a file to be available for run definition on the Run Setup tab, or in the Data Converter, it must be in the folder defined here.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        dataDirButton->setWhatsThis(QApplication::translate("ConfigWidget", "Click to browse file system.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        dataDirButton->setText(QApplication::translate("ConfigWidget", "...", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        outputFolderLabel->setWhatsThis(QApplication::translate("ConfigWidget", "The folder where output is written to. This can be the same as the Data Folder, or different.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        outputFolderLabel->setText(QApplication::translate("ConfigWidget", "Output", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        outDirEdit->setWhatsThis(QApplication::translate("ConfigWidget", "The folder where output is written to. This can be the same as the Data Folder, or different.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        outDirButton->setWhatsThis(QApplication::translate("ConfigWidget", "Click to browse file system.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        outDirButton->setText(QApplication::translate("ConfigWidget", "...", Q_NULLPTR));
        runConfigGroupBox->setTitle(QApplication::translate("ConfigWidget", "Run config", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        popNameTextLabel->setWhatsThis(QApplication::translate("ConfigWidget", "The population name identifies the group and is used as the default prefix for the output. When grouping several runs into a single run, an alternate prefix should be provided below in the box labled \"prefix.\"", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        popNameTextLabel->setText(QApplication::translate("ConfigWidget", "Population Name:", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        tagFileTextLabel->setWhatsThis(QApplication::translate("ConfigWidget", "The tag file provides the release group information for the run. Only files with a \".tag\" suffix will show up in this menu.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        tagFileTextLabel->setText(QApplication::translate("ConfigWidget", "Tag file:", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        obsFileTextLabel->setWhatsThis(QApplication::translate("ConfigWidget", "The interrogation file provides detection data for the run. Only files with a \".obs\" suffix will show up in this menu.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        obsFileTextLabel->setText(QApplication::translate("ConfigWidget", "Interrogation file:", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        runNameEdit->setWhatsThis(QApplication::translate("ConfigWidget", "The population name identifies the group and is used as the default prefix for the output. When grouping several runs into a single run, an alternate prefix should be provided below in the box labled \"prefix.\"", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        tagCombo->setWhatsThis(QApplication::translate("ConfigWidget", "The tag file provides the release group information for the run. Only files with a \".tag\" suffix will show up in this menu.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        obsCombo->setWhatsThis(QApplication::translate("ConfigWidget", "The interrogation file provides detection data for the run. Only files with a \".obs\" suffix will show up in this menu.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        mortFileTextLabel->setWhatsThis(QApplication::translate("ConfigWidget", "A mortality is flagged as removed at the last defined site traversed by the fish prior to the mortality. Only files with a \".mrt\" suffix will show up in this menu.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        mortFileTextLabel->setText(QApplication::translate("ConfigWidget", "Mortality file:", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        recaptureFileTextLabel->setWhatsThis(QApplication::translate("ConfigWidget", "Recapture data is used for censoring only. A recaptured fish is treated in the same way as a sampled fish, it is flagged as removed. The exception is when a fish is recaptured at the release site, in which case it can optinally be treated as re-released. Only files with a \"rcp\" suffix will show up in this menu.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        recaptureFileTextLabel->setText(QApplication::translate("ConfigWidget", "Recapture file:", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        mortCombo->setWhatsThis(QApplication::translate("ConfigWidget", "A mortality is flagged as removed at the last defined site traversed by the fish prior to the mortality. Only files with a \".mrt\" suffix will show up in this menu.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_WHATSTHIS
        recapCombo->setWhatsThis(QApplication::translate("ConfigWidget", "Recapture data is used for censoring only. A recaptured fish is treated in the same way as a sampled fish, it is flagged as removed. The exception is when a fish is recaptured at the release site, in which case it can optinally be treated as re-released. Only files with a \"rcp\" suffix will show up in this menu.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        fileFilterSwitch->setText(QApplication::translate("ConfigWidget", "Filter by file type", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        addRunButton->setWhatsThis(QApplication::translate("ConfigWidget", "Add the data files defined above to the runs table. The run definition only configures the data input for a given run, all of the other settings used for the run are the ones configured in the other tabs at the time of the run. In other words, the settings configured in the various tabs at the time a run is added will not necessarily be the ones that are configured at the time of run execution, and therefore, will not be the settings that are used for run execution.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        addRunButton->setText(QApplication::translate("ConfigWidget", "Add Run", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        deleteRunButton->setWhatsThis(QApplication::translate("ConfigWidget", "Remove the run from the runs table.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        deleteRunButton->setText(QApplication::translate("ConfigWidget", "Delete Run", Q_NULLPTR));
        definedRunsGroupBox->setTitle(QApplication::translate("ConfigWidget", "Defined runs", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        groupRunsCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "When the capture history format is SURPH1 or SURPH2, the defined runs may be processed together so that all runs will be combined into one SURPH file, where each run is listed as a seperate population, associated with the given population name.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        groupRunsCheckBox->setText(QApplication::translate("ConfigWidget", "Combine runs into one", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        runPrefixTextLabel->setWhatsThis(QApplication::translate("ConfigWidget", "An alternate output prefix should be provided when combining runs.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        runPrefixTextLabel->setText(QApplication::translate("ConfigWidget", "prefix", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        outPrefixEdit->setWhatsThis(QApplication::translate("ConfigWidget", "An alternate output prefix should be provided when combining runs.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        tabWidget->setTabText(tabWidget->indexOf(runSetup), QApplication::translate("ConfigWidget", "Run Setup", Q_NULLPTR));
        selectFilesGroup->setTitle(QApplication::translate("ConfigWidget", "Select which files to output", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        surphFileCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "The primary output for the program.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        surphFileCheckBox->setText(QApplication::translate("ConfigWidget", "Capture histories", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        errorsFileCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "The errors table in the Results Manager is generated from this file.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        errorsFileCheckBox->setText(QApplication::translate("ConfigWidget", "Errors", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        detectionDateFileCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "The travel time matrix in the Results Manager is generated from this file.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        detectionDateFileCheckBox->setText(QApplication::translate("ConfigWidget", "Detection date", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        travelTimeFileCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "This file is not used, and is only provided for post processing by the user.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        travelTimeFileCheckBox->setText(QApplication::translate("ConfigWidget", "Travel time", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        sequenceFileCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "This output is provided for examination of internal diagnostics.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        sequenceFileCheckBox->setText(QApplication::translate("ConfigWidget", "Sequence", Q_NULLPTR));
        captureHistGroup->setTitle(QApplication::translate("ConfigWidget", "Capture histories file", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        formatTextlabel->setWhatsThis(QApplication::translate("ConfigWidget", "Currently the output is geared to either SURPH or ROSTER. The current version of SURPH uses the SURPH2 format files.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        formatTextlabel->setText(QApplication::translate("ConfigWidget", "Format", Q_NULLPTR));
        surphVersionCombo->clear();
        surphVersionCombo->insertItems(0, QStringList()
         << QApplication::translate("ConfigWidget", "SURPH1", Q_NULLPTR)
         << QApplication::translate("ConfigWidget", "SURPH2", Q_NULLPTR)
         << QApplication::translate("ConfigWidget", "ROSTER", Q_NULLPTR)
        );
#ifndef QT_NO_WHATSTHIS
        surphVersionCombo->setWhatsThis(QApplication::translate("ConfigWidget", "Currently the output is geared to either SURPH or ROSTER. The current version of SURPH uses the SURPH2 format files.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        covariatesGroup->setTitle(QApplication::translate("ConfigWidget", "Covariates", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        lengthCovCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "Length can be included as an individual covariate in the SURPH output file. Length data is provided by the tagging data.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        lengthCovCheckBox->setText(QApplication::translate("ConfigWidget", "Include covariate(s)  in SURPH file output", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        zeroCovariateCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "Generally when length covariates are included in the output, it is appropriate to also remove fish that have zero length.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        zeroCovariateCheckBox->setText(QApplication::translate("ConfigWidget", "Remove zero valued covariates", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        nullCovariateCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "Generally when length covariates are included in the output, it is appropriate to also remove fish that have zero length.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        nullCovariateCheckBox->setText(QApplication::translate("ConfigWidget", "Remove null valued covariates", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(files), QApplication::translate("ConfigWidget", "Files", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("ConfigWidget", "Juvenile sites", Q_NULLPTR));
        addHistFieldButton->setText(QApplication::translate("ConfigWidget", "&Add", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        addHistFieldButton->setShortcut(QApplication::translate("ConfigWidget", "Alt+A", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_WHATSTHIS
        sortJuvenileSitesButton->setWhatsThis(QApplication::translate("ConfigWidget", "Sort the sites in upstream to downstream order.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        sortJuvenileSitesButton->setText(QApplication::translate("ConfigWidget", "Sort", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("ConfigWidget", "Adult sites", Q_NULLPTR));
        addAdultSiteButton->setText(QApplication::translate("ConfigWidget", "Add", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        sortAdultSitesButton->setWhatsThis(QApplication::translate("ConfigWidget", "Sort the streams in downstream to upstream order.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        sortAdultSitesButton->setText(QApplication::translate("ConfigWidget", "Sort", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("ConfigWidget", "Release site", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        siteRelCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "A site release is the situation where fish are released at an interrogation site, and some fish may be removed, by transportation or sampling, and only fish known to be returned-to-river should be included in the release group.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        siteRelCheckBox->setText(QApplication::translate("ConfigWidget", "Site release", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        lastFieldGroupBox->setWhatsThis(QApplication::translate("ConfigWidget", "All detections downstream of this site are grouped into the final capture history site.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        lastFieldGroupBox->setTitle(QApplication::translate("ConfigWidget", "Last capture history survival site", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        lastFieldTextLabel->setWhatsThis(QApplication::translate("ConfigWidget", "The last site has has two meanings, depending on it's position in the list of selected sites. When this site is not the last selected site, the associated field in the resulting capture history will be the last site for which survivals are calculated, with all subsequent sites pooled into the final capture history field. If the last site is the last selected site, the associated field in the capture history will be the actual last field, with no survival calculated for the reach preceeding the site.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        lastFieldTextLabel->setText(QApplication::translate("ConfigWidget", "Last survival site:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(sites), QApplication::translate("ConfigWidget", "Sites", Q_NULLPTR));
        groupBox_7->setTitle(QApplication::translate("ConfigWidget", "Screen by", Q_NULLPTR));
        speciesTextLabel->setText(QApplication::translate("ConfigWidget", "Species:", Q_NULLPTR));
        runTextLabel->setText(QApplication::translate("ConfigWidget", "Run:", Q_NULLPTR));
        rtTextLabel->setText(QApplication::translate("ConfigWidget", "Rearing Type:", Q_NULLPTR));
        speciesCombo->clear();
        speciesCombo->insertItems(0, QStringList()
         << QApplication::translate("ConfigWidget", "All", Q_NULLPTR)
         << QApplication::translate("ConfigWidget", "1", Q_NULLPTR)
         << QApplication::translate("ConfigWidget", "2", Q_NULLPTR)
         << QApplication::translate("ConfigWidget", "3", Q_NULLPTR)
         << QApplication::translate("ConfigWidget", "4", Q_NULLPTR)
         << QApplication::translate("ConfigWidget", "5", Q_NULLPTR)
         << QApplication::translate("ConfigWidget", "9", Q_NULLPTR)
        );
        runCombo->clear();
        runCombo->insertItems(0, QStringList()
         << QApplication::translate("ConfigWidget", "All", Q_NULLPTR)
         << QApplication::translate("ConfigWidget", "1", Q_NULLPTR)
         << QApplication::translate("ConfigWidget", "2", Q_NULLPTR)
         << QApplication::translate("ConfigWidget", "3", Q_NULLPTR)
        );
        rearTypeCombo->clear();
        rearTypeCombo->insertItems(0, QStringList()
         << QApplication::translate("ConfigWidget", "All", Q_NULLPTR)
         << QApplication::translate("ConfigWidget", "U", Q_NULLPTR)
         << QApplication::translate("ConfigWidget", "W", Q_NULLPTR)
         << QApplication::translate("ConfigWidget", "H", Q_NULLPTR)
        );
        tabWidget->setTabText(tabWidget->indexOf(tagScreening), QApplication::translate("ConfigWidget", "Tag Screening", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        assumeJuvenileCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "When all interrogation, recapture, and mortality data is known to be from the juvenile out-migration, this box may be checked. The program will assume that any oibservation is a juvenile observation. If any adult observations exist in the data set, the output will be invalid.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        assumeJuvenileCheckBox->setText(QApplication::translate("ConfigWidget", "Assume all juvenile observations", Q_NULLPTR));
        groupBox_18->setTitle(QApplication::translate("ConfigWidget", "Adult Settings", Q_NULLPTR));
        steelheadYearCB->setText(QApplication::translate("ConfigWidget", "Use steelhead return year (July 1 - June 30)", Q_NULLPTR));
        groupBox_11->setTitle(QApplication::translate("ConfigWidget", "Stage determination", Q_NULLPTR));
        migrationYearRadio->setText(QApplication::translate("ConfigWidget", "Migration year (yyyy):", Q_NULLPTR));
        juvCutoffRadio->setText(QApplication::translate("ConfigWidget", "Juvenile cutoff date (yyyymmdd):", Q_NULLPTR));
        migrYearEdit->setInputMask(QString());
        juvCutoffEdit->setInputMask(QString());
        juvCutoffEdit->setText(QString());
        groupBox_10->setTitle(QApplication::translate("ConfigWidget", "Minijacks", Q_NULLPTR));
        miniJackTextLabel->setText(QApplication::translate("ConfigWidget", "Minijack (adult returning during migration year) can be handled in either of 2 ways:", Q_NULLPTR));
        combineJacksCheckBox->setText(QApplication::translate("ConfigWidget", "Combine minijacks and first ocean age class into one age class (age class A)", Q_NULLPTR));
        removeJacksCheckBox->setText(QApplication::translate("ConfigWidget", "Remove minijacks", Q_NULLPTR));
        groupBox_8->setTitle(QApplication::translate("ConfigWidget", "Adult fallback transformations", Q_NULLPTR));
        textLabel2->setText(QApplication::translate("ConfigWidget", "Method:", Q_NULLPTR));
        lastRouteRadio->setText(QApplication::translate("ConfigWidget", "Last route", Q_NULLPTR));
        anyRouteRadio->setText(QApplication::translate("ConfigWidget", "Any route", Q_NULLPTR));
        groupBox_9->setTitle(QApplication::translate("ConfigWidget", "Residualization", Q_NULLPTR));
        removeResSwitch->setText(QApplication::translate("ConfigWidget", "Remove fish observed on known juvenile detectors subsequent to the migration year.", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        resCutoffCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "This is an effort to remove residualizing fish assuming that spring observations in the year following the migration year are probably residualizing fish. The cutoff date is user specified so that the user can decide when this spring cutoff is.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        resCutoffCheckBox->setText(QApplication::translate("ConfigWidget", "Remove fish observed during the spring of the year following juvenile out migration:", Q_NULLPTR));
        label->setText(QApplication::translate("ConfigWidget", "Cutoff date (yyyymmdd):", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(adultCriteria), QApplication::translate("ConfigWidget", "Adult Settings", Q_NULLPTR));
        label_3->setText(QApplication::translate("ConfigWidget", "The following settings only affect ROSTER formatted output.", Q_NULLPTR));
        groupBox_16->setTitle(QApplication::translate("ConfigWidget", "Tranportation sites", Q_NULLPTR));
        label_2->setText(QApplication::translate("ConfigWidget", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:MS Shell Dlg 2; font-size:8.25pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:MS; font-size:8pt;\">If a transportation site does not appear in the following list, all raceway detections at the site will be flagged as <span style=\" font-weight:600;\">unknown</span> instead of <span style=\" font-weight:600;\">transported</span>. Usually this will result in censoring of those fish unless a subsequent return to river detection occurs.</p></body></html>", Q_NULLPTR));
        addTransSiteButton->setText(QApplication::translate("ConfigWidget", "&Add", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        addTransSiteButton->setShortcut(QApplication::translate("ConfigWidget", "Alt+A", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_WHATSTHIS
        sortTransSitesButton->setWhatsThis(QApplication::translate("ConfigWidget", "Sort the sites in upstream to downstream order.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        sortTransSitesButton->setText(QApplication::translate("ConfigWidget", "Sort", Q_NULLPTR));
        groupBox_17->setTitle(QApplication::translate("ConfigWidget", "Settings", Q_NULLPTR));
        sampTransCheckBox->setText(QApplication::translate("ConfigWidget", "Treat sampled fish at the above sites as transported fish", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(trans), QApplication::translate("ConfigWidget", "Transportation", Q_NULLPTR));
        groupBox_14->setTitle(QApplication::translate("ConfigWidget", "Outcome determination", Q_NULLPTR));
        methodTextLabel->setText(QApplication::translate("ConfigWidget", "Method:", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        removalTrumpsRadio->setWhatsThis(QApplication::translate("ConfigWidget", "The entire detection history at a site is taken into consideration. This type of outcome determination depends on Interrogation Detail data from PTAGIS. The trump order is sampled/held, returned, and transported.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        removalTrumpsRadio->setText(QApplication::translate("ConfigWidget", "Removal trumps all", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        lastDetectionRadio->setWhatsThis(QApplication::translate("ConfigWidget", "Use only the last detection (sorted by observation time) of a fish at a given site as the outcome indicator.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        lastDetectionRadio->setText(QApplication::translate("ConfigWidget", "Last detection", Q_NULLPTR));
        groupBox_13->setTitle(QApplication::translate("ConfigWidget", "Recapture data", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        ignoreReRecapsCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "When a fish is recaptured it is censored at the defined site prior to the recapture in the observation sequence. In practice, fish are often recapture at the release site, and downstream observations should be included as valid. Check this box to include those recapture.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        ignoreReRecapsCheckBox->setText(QApplication::translate("ConfigWidget", "Ignore recaptures at the release site", Q_NULLPTR));
        groupBox_12->setTitle(QApplication::translate("ConfigWidget", "Miscellaneous", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        singleCoilCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "Allow a single hit at a site for a fish to be counted.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        singleCoilCheckBox->setText(QApplication::translate("ConfigWidget", "Allow single coil detections", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        tagCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "Produce a capture history for a fish found in the interrogation data, even if there is no record for the fish in the tag data.", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        tagCheckBox->setText(QApplication::translate("ConfigWidget", "Allow observed fish not found in tag file (not recommended)", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        warningsCheckBox->setWhatsThis(QApplication::translate("ConfigWidget", "Display warning messages, either when the program cannot find detector data for an interrogation record, or when a transported fish is detected downstream as a juvenile (except at the Estuary Towed Array or any of the \"Bird\" islands)", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        warningsCheckBox->setText(QApplication::translate("ConfigWidget", "Display warning messages", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(advanced), QApplication::translate("ConfigWidget", "Advanced", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConfigWidget: public Ui_ConfigWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGWIDGET_H
