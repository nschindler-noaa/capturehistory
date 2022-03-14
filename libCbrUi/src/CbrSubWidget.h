#ifndef CbrSubWidget_h
#define CbrSubWidget_h

#include <QWidget>

class QPushButton;
class QPrinter;

namespace cbr
{
    class CbrSubWidget : public QWidget
    {
    public:
        virtual ~CbrSubWidget() {}

        virtual QPushButton *getDoneButton() const { return 0; }
        virtual QPushButton *getApplyButton() const { return 0; }
        virtual void updateDataset(int /*datasetId*/) {}
        virtual void updateWidget() {}
        virtual void print(QPrinter * /*printer*/) {}
        virtual QString save(const QString& /*fileName*/, int /*width*/, int /*height*/) { return QString(); }

    protected:
        enum WidgetType { Plot, Text };
        QString getFileName(WidgetType widgetType, const QString &prefix);
    };
}


#endif
