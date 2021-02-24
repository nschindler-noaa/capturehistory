/*
 */

#ifndef DataConverterImpl_h
#define DataConverterImpl_h

#include "ui_DataConverter.h"
#include <QEvent>

class QString;
class QComboBox;
class QTimer;

class DataConverterCT;
class PitProWindowImpl;


class DataConverterImpl : public QDialog, public Ui::DataConverter
{
    Q_OBJECT

public:
    DataConverterImpl(PitProWindowImpl* w = 0, Qt::WindowFlags fl = 0 );
    ~DataConverterImpl();

    void customEvent( QEvent* e );

public slots:
    void refresh();
    void convert();
    void obsFileChanged();
    void tagFileChanged();
    void dataDirChanged(const QString&);

signals:
    void dataConverted();

protected:
    void showEvent( QShowEvent* );
    void reject();

private:
    PitProWindowImpl* w;
    DataConverterCT* converter;
    QTimer* timer;

    void updateDataList( const QString& dirPath, const QString& suffix, QComboBox* combo, bool noneOk );
    void setStatusText( const QString& text, int duration = -1 );


};

#endif // DataConverterImpl_h
