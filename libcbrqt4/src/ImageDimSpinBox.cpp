/*
 * ImageDimSpinBox.cpp
 */


#include "ImageDimSpinBox.h"


ImageDimSpinBox::ImageDimSpinBox(QWidget* parent, const char* name) : QSpinBox(parent),
	dimType(INCHES)
{
	QSpinBox::setObjectName (name);
	setMinimum(100);
	setMaximum(3600);
	setSingleStep(100);
}

/*
 * Map the value to the text. If the dim type is inches,
 * translate the pixels to inches. Otherwise, just return
 * the pixels.
 */
QString ImageDimSpinBox::mapValueToText(int value) {
	if (dimType == PIXELS)
		return QString::number(value);
	else {
		if (dpi == 0)
			return 0;
		else {
			double f = (double)value / dpi;

			return QString::number(f, 'f', 2);
		}
	}
}

/*
 * Map the text to the value.
 */
int ImageDimSpinBox::mapTextToValue(bool*) {
	if (dimType == PIXELS)
		return text().toInt();
	else {
		return 0;
	}
}
        
/*
 * Update the dimension type: inches or pixels. Make
 * sure the spin box updates it's display based on this
 * type.
 */
void ImageDimSpinBox::setDimType(DimType type) {
	dimType = type;
//	updateDisplay();
}

/*
 * 
 */
void ImageDimSpinBox::setDpi(int d) {
	dpi= d;
//	updateDisplay();
}
