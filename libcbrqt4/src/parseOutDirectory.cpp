#include "parseOutDirectory.h"
#include <QStringList>

QString parseOutDirectory(const QString& filename)
{
	QString splitString = filename.contains("\\\\") ? "\\\\" : "/";
	QStringList parts = filename.split(splitString);
	QString directory = parts[0];
	for (int i=1; i < parts.size()-1; ++i)
		directory += splitString + parts[i];
	return directory;
}
