#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include <QDialog>

namespace Ui {
class DataConverter;
}

class DataConverter : public QDialog
{
    Q_OBJECT

public:
    explicit DataConverter(QWidget *parent = 0);
    ~DataConverter();

private:
    Ui::DataConverter *ui;
};

#endif // DATACONVERTER_H
