/*
*/

#include <QString>
#include <QFileDialog>

#include "CbrSubWidget.h"

using namespace cbr;

QString CbrSubWidget::getFileName(WidgetType widgetType, const QString &prefix)
{
	QString fileName;
	if (widgetType == Text)
	{
		QString rtfFilter = "Rich Text Format (*.rtf)";

		QString selectedFilter;
		QString startFile = prefix + ".rtf";
		fileName = QFileDialog::getSaveFileName(this, tr("Save Report"),
			startFile, rtfFilter, &selectedFilter);
	}
	else if (widgetType == Plot)
	{
		QString pngFilter = "Images (*.png)";
		QString selectedFilter;
		QString startFile = prefix + ".png";
		fileName = QFileDialog::getSaveFileName(this, tr("Save Plot"),
			startFile, pngFilter, &selectedFilter);
	}

	return fileName;

}