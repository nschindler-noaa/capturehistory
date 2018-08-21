/*
 * ImageDimSpinBox.h
 */

#ifndef ImageDimSpinBox_h
#define ImageDimSpinBox_h

#include <qspinbox.h>
 
class ImageDimSpinBox : public QSpinBox  
{
	Q_OBJECT

public:
	enum DimType { INCHES, PIXELS };
	ImageDimSpinBox(QWidget* parent = 0, const char* name = 0 );

	QString mapValueToText(int value);
	int mapTextToValue(bool *ok);

private:
	int dpi;
	DimType dimType;

public slots:
	void setDpi(int rhs);
	void setDimType(DimType type);

};

#endif // !ImageDimSpinBox_h
