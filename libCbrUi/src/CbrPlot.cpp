/*
 */

#include <algorithm>

#include <QVariant>
#include <QPen>
#include <QPrinter>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QFrame>
#include <QFont>
#include <QLabel>
#include <QVBoxLayout>
#include <QImageWriter>

#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_scale_engine.h>
#include <qwt_scale_div.h>
#include <qwt_text.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_symbol.h>
#include <qwt_picker.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_interval.h>
#include <qwt_plot_renderer.h>

#include "CbrPlot.h"
#include "CbrPlotControls.h"

using namespace std;
using namespace cbr;

CbrPlot::CbrPlot() : QwtPlot(),
picker_(0), highlightRect_(0),
gridLevel_(PLOT_GRID_HIGH), fontFamily_("Tahoma") {
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setAutoDelete(true);
    setCanvasBackground(QColor(Qt::white));
    QwtPlotLayout *layout = plotLayout();
    layout->setCanvasMargin(10);

    // zoomer / panner
    //(void)new QwtPlotZoomer(plot_->canvas());
    (void) new QwtPlotPanner(canvas());
    (void) new QwtPlotMagnifier(canvas());

    // picker
    picker_ = new QwtPlotPicker(
            QwtPlot::xBottom, QwtPlot::yLeft,
            QwtPlotPicker::NoRubberBand, QwtPicker::AlwaysOff,
            canvas());
    connect(picker_, SIGNAL(moved(const QPoint &)), SLOT(moved(const QPoint &)));
    connect(picker_, SIGNAL(selected(const QPolygon &)), SLOT(selected(const QPolygon &)));

    highlightRect_ = new QwtPlotMarker();
    QwtSymbol *rect = new QwtSymbol(QwtSymbol::Rect, QBrush(), QPen(Qt::red), QSize(10, 10));
    highlightRect_->setSymbol(rect);

    // axis formatting
    QFont axisFont(fontFamily_, 8);
    setAxisFont(axisFont);

    // grid
    setGrid();

    // legend
    QwtLegend *legend = new QwtLegend();
    insertLegend(legend, QwtPlot::BottomLegend);


    // plot colors
    colors_ << Qt::blue;
    colors_ << Qt::green;
    colors_ << Qt::magenta;
    colors_ << Qt::darkGreen;
    colors_ << Qt::darkCyan;
    currentColor_ = 0;

    // plot pens
    /*
    pens_ << QPen(Qt::blue, 2, Qt::DashLine);
    pens_ << QPen(Qt::green, 2, Qt::DotLine);
    pens_ << QPen(Qt::magenta, 2, Qt::DashDotLine);
    pens_ << QPen(Qt::darkGreen, 2, Qt::DashDotDotLine);
    pens_ << QPen(Qt::darkCyan, 2, Qt::CustomDashLine);
     */
    pens_ << QPen(Qt::blue);
    pens_ << QPen(Qt::green);
    pens_ << QPen(Qt::magenta);
    pens_ << QPen(Qt::darkGreen);
    pens_ << QPen(Qt::darkCyan);
    currentPen_ = 0;

    // plot symbols
    QVector<QwtSymbol::Style> symbolStyles;
    symbolStyles.append(QwtSymbol::Diamond);
    symbolStyles.append(QwtSymbol::Triangle);
    symbolStyles.append(QwtSymbol::Cross);
    symbolStyles.append(QwtSymbol::Rect);
    symbolStyles.append(QwtSymbol::Ellipse);
    symbolStyles.append(QwtSymbol::Star1);

    foreach(QwtSymbol::Style style, symbolStyles) {
        QwtSymbol *symbol = new QwtSymbol();

        symbol->setStyle(style);
        symbol->setSize(4);
        QColor color = nextColor();
        symbol->setPen(QPen(color));
        symbol->setBrush(color);

        symbols_.append(symbol);
    }


    currentColor_ = 0;
    currentSymbol_ = 0;

}

CbrPlot::~CbrPlot() {
    delete highlightRect_;
    delete picker_;
	foreach (QwtSymbol *sym, symbols_)
		delete sym;
}

void CbrPlot::setGrid(int level) {
    if (level != -1)
        gridLevel_ = static_cast<PlotGridLevel> (level);

    detachItems(QwtPlotItem::Rtti_PlotGrid);

    if (gridLevel_ != PLOT_GRID_OFF) {
        //QwtScaleEngine scaleEngine;

        QwtPlotGrid *grid = new QwtPlotGrid;
        if (gridLevel_ == PLOT_GRID_HIGH) {
            grid->enableXMin(true);
            grid->enableYMin(true);
        }
        grid->setMajorPen(QPen(Qt::black, 0, Qt::DotLine));
        grid->setMinorPen(QPen(Qt::gray, 0, Qt::DotLine));
        grid->attach(this);
    }

    replot();
}

void CbrPlot::setAxisFont(const QFont& font) {
    QwtPlot::setAxisFont(QwtPlot::xTop, font);
    QwtPlot::setAxisFont(QwtPlot::yRight, font);
    QwtPlot::setAxisFont(QwtPlot::xBottom, font);
    QwtPlot::setAxisFont(QwtPlot::yLeft, font);
}

void CbrPlot::setTitle(const QString& title) {
    QFont font(fontFamily_, 12, QFont::Bold);
    QwtText t(title);
    t.setFont(font);
    QwtPlot::setTitle(t);
}

void CbrPlot::setAxisTitle(int axisId, const QString& title) {
    QFont font(fontFamily_, 8, QFont::Bold);
    QwtText t(title);
    t.setFont(font);
    QwtPlot::setAxisTitle(axisId, t);
}

int CbrPlot::getBin(double val, double min, double binSize) {
    return (val - min) / binSize;
}

QVector<QwtIntervalSample>& CbrPlot::makeBars(const QVector<double>& values) {
    double min = *min_element(values.begin(), values.end());
    double max = *max_element(values.begin(), values.end());
    int numBins = 20;
    double binSize = (max - min) / (numBins - 1);

    bars_.clear();
    bars_.resize(numBins);

    for (int i = 0; i < numBins; i++) {
        bars_[i].interval = QwtInterval(min + i * binSize, min + (i + 1) * binSize);
        bars_[i].value = 0;
    }

    foreach(double val, values) {
        int bin = getBin(val, min, binSize);
        bars_[bin].value += 1;
    }

    return bars_;
}

void CbrPlot::print(QPrinter *printer) {
    if (!printer)
        return;

    QwtPlotRenderer rend;
    rend.renderTo(this, *printer);
}

void CbrPlot::save(const QString& fileName, int width, int height) {
    QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();

    QString format = QString::null;
    if (imageFormats.contains("png"))
        format = "png";
    else if (imageFormats.count() > 0)
        format = imageFormats.at(0);

    save(fileName, format, width, height);
}


// 
// Width and Height are in pixels, but we must convert to mm. Use (pixels / 75 dpi ) * 25.4 mm/in

void CbrPlot::save(const QString& fileName, const QString& format, int width, int height) {
    QwtPlotRenderer rend;

    width = (width / 75.0) * 25.4;
    height = (height / 75.0) * 25.4;

    rend.renderDocument(this, fileName, format, QSizeF(width, height), 100);
}

int CbrPlot::getIndex(const QVector<double> &x, const QVector<double> &y, const QPoint& pos) {
    if (x.size() == 0 || y.size() == 0 || x.size() != y.size())
        return -1;

    const int thresh = 15;

    int xpos = pos.x();
    int ypos = pos.y();

    int i0 = -1;
    int dx0 = -1;
    for (int i = 0; i < x.size(); ++i) {
        double xi = transform(QwtPlot::xBottom, x[i]);
        double yi = transform(QwtPlot::yLeft, y[i]);
        double dx = sqrt(pow(xpos - xi, 2) + pow(ypos - yi, 2));
        if (dx0 == -1 || (dx < thresh && dx0 > dx)) {
            dx0 = dx;
            i0 = i;
        }
    }
    return i0;
}

void CbrPlot::showHighlightRect(double x, double y) {
    highlightRect_->detach();
    highlightRect_->setXValue(x);
    highlightRect_->setYValue(y);
    highlightRect_->attach(this);
    replot();
}

void CbrPlot::addLine(double x0, double y0, double x1, double y1, const QPen &pen, bool legend, bool autoScale) {
    QVector<double> x(2);
    x[0] = x0;
    x[1] = x1;
    QVector<double> y(2);
    y[0] = y0;
    y[1] = y1;

    QwtPlotCurve *crv = new QwtPlotCurve();
    crv->setPen(pen);
    crv->setSamples(x, y);
    crv->setItemAttribute(QwtPlotItem::Legend, legend);
    crv->setItemAttribute(QwtPlotItem::AutoScale, autoScale);

    crv->attach(this);

    replot();
}

void CbrPlot::resetColor() {
    currentColor_ = 0;
}

Qt::GlobalColor CbrPlot::nextColor() {
    if (currentColor_ >= colors_.size())
        currentColor_ = 0;
    return colors_[currentColor_++];
}

void CbrPlot::resetPen() {
    currentPen_ = 0;
}

const QPen &CbrPlot::nextPen() {
    if (currentPen_ >= pens_.size())
        currentPen_ = 0;
    return pens_[currentPen_++];
}

void CbrPlot::resetSymbol() {
    currentSymbol_ = 0;
}

const QwtSymbol *CbrPlot::nextSymbol() {
    if (currentSymbol_ >= symbols_.size())
        currentSymbol_ = 0;
	QwtSymbol *symbol = new QwtSymbol();
	const QwtSymbol *refSymbol = symbols_.at(currentSymbol_++);
	symbol->setStyle(refSymbol->style());
	symbol->setSize(refSymbol->size());
	symbol->setPen(refSymbol->pen());
	symbol->setBrush(refSymbol->brush());
//    QwtSymbol *symbol = new QwtSymbol(symbols_[currentSymbol_++]);
    return symbol;
}



