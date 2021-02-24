/*
 */


#include <string>

#include <qdir.h>
#include <qcombobox.h>
#include <qstring.h>
#include <qlineedit.h>
#include <qevent.h>
#include <qprogressbar.h>
#include <qpushbutton.h>
#include <QMessageBox>
#include <qlabel.h>
#include <qtimer.h>
#include <qcheckbox.h>

#include <QShowEvent>
#include <QtEvents>

#include <ComputationThread.h>
#include <ComputationEvent.h>

#include "PitProWindowImpl.h"
#include "DataConverterImpl.h"
#include "DataConverterCT.h"
#include "PitProSettings.h"

using std::string;

/*
 */
DataConverterImpl::DataConverterImpl( PitProWindowImpl* w, Qt::WindowFlags fl )
    : QDialog( w, fl ), w(w), converter( nullptr ), timer( nullptr )
{
    setupUi(this);

    // signals and slots connections
    connect( buttonConvert, SIGNAL( clicked() ), this, SLOT( convert() ) );
    connect( buttonDone, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( tagCheckBox, SIGNAL( toggled(bool) ), tagSourceGroupBox, SLOT( setEnabled(bool) ) );
    connect( tagCheckBox, SIGNAL( toggled(bool) ), tagTargetGroupBox, SLOT( setEnabled(bool) ) );
    connect( obsCheckBox, SIGNAL( toggled(bool) ), obsSourceGroupBox, SLOT( setEnabled(bool) ) );
    connect( obsCheckBox, SIGNAL( toggled(bool) ), obsTargetGroupBox, SLOT( setEnabled(bool) ) );
    connect( obsCombo, SIGNAL( activated(const QString&) ), this, SLOT( obsFileChanged() ) );
    connect( tagCombo, SIGNAL( activated(const QString&) ), this, SLOT( tagFileChanged() ) );
}


void DataConverterImpl::showEvent( QShowEvent* ) {
    refresh();
}

/*
 *  Destroys the object and frees any allocated resources
 */
DataConverterImpl::~DataConverterImpl()
{
    // no need to delete child widgets, Qt does it all for us
}

void DataConverterImpl::reject() {
    if ( converter )
        converter->setStatus( ComputationThread::Cancel );
    QDialog::reject();
}

void DataConverterImpl::refresh() {
    PitProSettings& settings = PitProSettings::getInstance();
    QString dataDir = settings.getValue( PitProSettings::DataDir );

    updateDataList( dataDir, "obs", obsCombo, false );
    updateDataList( dataDir, "tag", tagCombo, false );
    updateDataList( dataDir, "rel", relCombo, true );
    obsFileChanged();
    tagFileChanged();

}

void DataConverterImpl::updateDataList( const QString& dirPath, const QString& suffix, QComboBox* combo, bool noneOk ) {
    QDir dir( dirPath );
    dir.setNameFilters(QStringList(QString("*.%1").arg(suffix)));
//	dir.setNameFilter( "*." + suffix );

    combo->clear();
    if ( noneOk )
        combo->addItem( "none" );
    combo->addItems(dir.entryList() );
}

void DataConverterImpl::convert() {
    if (!converter)
        converter = new DataConverterCT( this, "DataConverter" );
    if ( buttonConvert->text().compare( "Cancel" ) == 0 )
        converter->setStatus( ComputationThread::Cancel );
    else {
        PitProSettings& settings = PitProSettings::getInstance();
        QString dataDir = settings.getValue(PitProSettings::DataDir);
        QString obs = obsCombo->currentText();
        QString tag = tagCombo->currentText();
        QString rel = relCombo->currentText();
        QString tobs = obsInput->text();
        QString ttag = tagInput->text();

        if ( obs.isEmpty() || tag.isEmpty() || rel.isEmpty() || tobs.isEmpty() || ttag.isEmpty() ) {
        }
        else {
            if ( !rel.compare( "none" ) )
                rel = QString::null;
            else
                rel = dataDir + "/" + rel;

            converter->setFiles(
                    dataDir + "/" + obs,
                    dataDir + "/" + tag,
                    rel,
                    dataDir + "/" + tobs,
                    dataDir + "/" + ttag
                    );

            converter->setStatus(ComputationThread::Ok);
            if (tagCheckBox->isChecked() && obsCheckBox->isChecked())
                converter->setConvertType(DataConverterCT::Both);
            else if (tagCheckBox->isChecked())
                converter->setConvertType(DataConverterCT::Tag);
            else if (obsCheckBox->isChecked())
                converter->setConvertType(DataConverterCT::Obs);

            converter->start();
            buttonConvert->setText("Cancel");
        }
    }
}

void DataConverterImpl::customEvent(QEvent* e) {
    ComputationEvent* ce = static_cast<ComputationEvent*>(e);
    ComputationEvent::Type cetype = static_cast<ComputationEvent::Type>(ce->type());

    if (cetype == ComputationEvent::Canceled) {
        setStatusText("Canceled.", 2000);
        progressBar->reset();
        buttonConvert->setText("Convert");
    }
    else if (cetype == ComputationEvent::Completed) {
        setStatusText("Done.", 2000);
        QMessageBox::information(this, "PitPro", "Data conversion complete.");
        buttonConvert->setText("Convert");
        progressBar->reset();
        emit dataConverted();
    }
    else if (cetype == ComputationEvent::Error) {
        QMessageBox::critical(this, "PitPro", ce->getMessage());
    }
    else if (cetype == ComputationEvent::Status) {
        setStatusText(ce->getMessage());
    }
    else if (cetype == ComputationEvent::NumSteps) {
        progressBar->setRange(0, ce->getNumSteps());
//		progressBar->setTotalSteps( ce->getNumSteps() );
    }
    else if (cetype == ComputationEvent::CurrentStep) {
        progressBar->setValue(ce->getCurrentStep());
//		progressBar->setProgress( ce->getCurrentStep() );
    }
}

void DataConverterImpl::setStatusText(const QString& text, int duration) {
    statusText->setText(text);
    statusText->repaint();
    if (duration > 0) {
        if (!timer) {
            timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), statusText, SLOT(clear()));
        }


        timer->start(duration); //, true );
    }
}

void DataConverterImpl::obsFileChanged() {
    QString fileName = obsCombo->currentText();
    PitProSettings& settings = PitProSettings::getInstance();
    QString obsSuffix = settings.getValue(PitProSettings::ObsSuffix);
    fileName.replace(".obs", "_v4." + obsSuffix);
    obsInput->setText(fileName);
}

void DataConverterImpl::tagFileChanged() {
    QString fileName = tagCombo->currentText();
    PitProSettings& settings = PitProSettings::getInstance();
    QString tagSuffix = settings.getValue(PitProSettings::TagSuffix);
    fileName.replace(".tag", "_v4." + tagSuffix);
    tagInput->setText(fileName);

}

void DataConverterImpl::dataDirChanged( const QString& ) {
    refresh();
}
