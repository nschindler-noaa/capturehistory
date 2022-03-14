#ifndef CbrPlotControls_h
#define CbrPlotControls_h

#include <QWidget>
#include <QList>
#include <QVariant>

namespace cbr {

    class CbrPlotControls : public QWidget {

        Q_OBJECT

    public:
        CbrPlotControls(QWidget * parent = 0, Qt::WindowFlags f = 0) : QWidget(parent, f) { }

        virtual void configure() { }

        virtual QVariant get(int /*key*/) const {
            return QVariant();
        }

        virtual void set(int /*key*/, const QVariant& /*value*/) { }

    signals:
        void currentChanged();
        void gridLevelChanged(int);

    protected:
        void add(QWidget *control);

        void disconnectControls();
        void connectControls();

        QList<QWidget*> drawControls_;
    };
}


#endif
