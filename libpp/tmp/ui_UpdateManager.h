/********************************************************************************
** Form generated from reading UI file 'UpdateManager.ui'
**
** Created: Thu Mar 10 16:42:32 2022
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEMANAGER_H
#define UI_UPDATEMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UpdateManager
{
public:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *verticalLayout_main;
    QHBoxLayout *horizontalLayout_title;
    QLabel *label_pixmap;
    QLabel *label_title;
    QTableWidget *updateTable;
    QHBoxLayout *horizontalLayout_buttons;
    QProgressBar *progressBar;
    QSpacerItem *spacer_buttons;
    QPushButton *updateButton;
    QPushButton *refeshButton;
    QPushButton *doneButton;

    void setupUi(QDialog *UpdateManager)
    {
        if (UpdateManager->objectName().isEmpty())
            UpdateManager->setObjectName(QString::fromUtf8("UpdateManager"));
        UpdateManager->resize(560, 295);
        vboxLayout = new QVBoxLayout(UpdateManager);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout_main = new QVBoxLayout();
        verticalLayout_main->setSpacing(6);
        verticalLayout_main->setObjectName(QString::fromUtf8("verticalLayout_main"));
        verticalLayout_main->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_title = new QHBoxLayout();
        horizontalLayout_title->setSpacing(6);
        horizontalLayout_title->setObjectName(QString::fromUtf8("horizontalLayout_title"));
        horizontalLayout_title->setContentsMargins(0, 0, 0, 0);
        label_pixmap = new QLabel(UpdateManager);
        label_pixmap->setObjectName(QString::fromUtf8("label_pixmap"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_pixmap->sizePolicy().hasHeightForWidth());
        label_pixmap->setSizePolicy(sizePolicy);
        label_pixmap->setMaximumSize(QSize(32, 32));
        label_pixmap->setPixmap(QPixmap(QString::fromUtf8(":/icons/download_manager.png")));
        label_pixmap->setScaledContents(true);

        horizontalLayout_title->addWidget(label_pixmap);

        label_title = new QLabel(UpdateManager);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        font.setPointSize(18);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        label_title->setFont(font);
        label_title->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        horizontalLayout_title->addWidget(label_title);


        verticalLayout_main->addLayout(horizontalLayout_title);

        updateTable = new QTableWidget(UpdateManager);
        updateTable->setObjectName(QString::fromUtf8("updateTable"));

        verticalLayout_main->addWidget(updateTable);

        horizontalLayout_buttons = new QHBoxLayout();
        horizontalLayout_buttons->setSpacing(6);
        horizontalLayout_buttons->setObjectName(QString::fromUtf8("horizontalLayout_buttons"));
        horizontalLayout_buttons->setContentsMargins(0, 0, 0, 0);
        progressBar = new QProgressBar(UpdateManager);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        horizontalLayout_buttons->addWidget(progressBar);

        spacer_buttons = new QSpacerItem(50, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_buttons->addItem(spacer_buttons);

        updateButton = new QPushButton(UpdateManager);
        updateButton->setObjectName(QString::fromUtf8("updateButton"));

        horizontalLayout_buttons->addWidget(updateButton);

        refeshButton = new QPushButton(UpdateManager);
        refeshButton->setObjectName(QString::fromUtf8("refeshButton"));

        horizontalLayout_buttons->addWidget(refeshButton);

        doneButton = new QPushButton(UpdateManager);
        doneButton->setObjectName(QString::fromUtf8("doneButton"));

        horizontalLayout_buttons->addWidget(doneButton);


        verticalLayout_main->addLayout(horizontalLayout_buttons);


        vboxLayout->addLayout(verticalLayout_main);


        retranslateUi(UpdateManager);
        QObject::connect(doneButton, SIGNAL(clicked()), UpdateManager, SLOT(close()));

        QMetaObject::connectSlotsByName(UpdateManager);
    } // setupUi

    void retranslateUi(QDialog *UpdateManager)
    {
        UpdateManager->setWindowTitle(QApplication::translate("UpdateManager", "Update Manager", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        UpdateManager->setWhatsThis(QApplication::translate("UpdateManager", "The update manager checks the current program and configuration versions against what is available on the Columbia Basin Research web site (www.cbr.washington.edu/paramest/pitpro). If a newer version is available, a check mark icon is displayed on the PitPro main page. If the sites configuration is out of date, the update manager allows for automatic update of the sites configuration file. Currently, the program can not be updated in this way, but the at least this provides notification that a newer version exists for download. Please visit the above site to download the latest version of the program.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label_title->setText(QApplication::translate("UpdateManager", "PitPro Configuration Update Manager", 0, QApplication::UnicodeUTF8));
        updateButton->setText(QApplication::translate("UpdateManager", "Update", 0, QApplication::UnicodeUTF8));
        refeshButton->setText(QApplication::translate("UpdateManager", "Refesh", 0, QApplication::UnicodeUTF8));
        doneButton->setText(QApplication::translate("UpdateManager", "Done", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UpdateManager: public Ui_UpdateManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEMANAGER_H
