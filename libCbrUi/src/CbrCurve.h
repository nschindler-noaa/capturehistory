#ifndef CbrCurve_h
#define CbrCurve_h


#include <qwt_plot_curve.h>

namespace cbr 
{
	class CbrCurve : public QwtPlotCurve
	{
	public:
		CbrCurve();
		virtual ~CbrCurve();
	};
};

#endif
