#ifndef CbrPlot_h
#define CbrPlot_h

#include <QVector>
#include <QDialog>
#include <QWidget>
#include <QString>
#include <QFont>

// TODO: Fix Plots
//#include <qwt_plot.h>
//#include <qwt_series_data.h>
//#include <qwt_symbol.h>

#include <QPrinter>
#include <QLabel>
//#include <qwt_plot_marker.h>
//#include <qwt_plot_picker.h>

//class QLabel;

//class QwtPlotMarker;
//class QwtPlotPicker;

namespace cbr {

    class CbrPlot {//: public QwtPlot {

        Q_OBJECT

    public:
        enum PlotGridLevel {
            PLOT_GRID_HIGH = 0,
            PLOT_GRID_LOW,
            PLOT_GRID_OFF
        };

        CbrPlot();
        virtual ~CbrPlot();

        void print(QPrinter *printer);
        void save(const QString& fileName, int width, int height); // backwards compatibility
        void save(const QString& fileName, const QString& format, int width, int height);

        void setAxisFont(const QFont& font);
        void setAxisTitle(int axisId, const QString& title);
        void setTitle(const QString& title);

        void resetColor();
        Qt::GlobalColor nextColor();
        void resetPen();
        const QPen &nextPen();
        void resetSymbol();
//        const QwtSymbol *nextSymbol();

        const QString& getShortName() const {
            return shortName_;
        }

        void setShortName(const QString& s) {
            shortName_ = s;
        }

    public slots:
        void setGrid(int level = -1);

        virtual void moved(const QPoint &) {
        }

        virtual void selected(const QPolygon &) {
        }
        int getIndex(const QVector<double> &x, const QVector<double> &y, const QPoint& pos);

    protected:
//        QwtPlotPicker *picker_;
//        QwtPlotMarker *highlightRect_;
        void showHighlightRect(double x, double y);

//        QVector<QwtIntervalSample>& makeBars(const QVector<double>& values);
        PlotGridLevel gridLevel_;

        void addLine(double x0, double y0, double x1, double y1,
                const QPen &pen, bool legend = false, bool autoScale = false);

    private:
        QString fontFamily_;
        QString shortName_; /* used for output file names by some programs */

//        QVector<QwtIntervalSample> bars_;
        int getBin(double val, double min, double binSize);

        QVector<Qt::GlobalColor> colors_;
        int currentColor_;
        QVector<QPen> pens_;
        int currentPen_;
//        QVector<QwtSymbol*> symbols_;
        int currentSymbol_;

    };
};

#endif
