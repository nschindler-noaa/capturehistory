#include "parseOutDirectory.h"
#include <QStringList>

namespace cbr
{
	QPair<QString, QString> parseOutDirectory(const QString& fileName)
	{
		QString splitString = fileName.contains("\\\\") ? "\\\\" : "/";
		QStringList parts = fileName.split(splitString);
		QString directory = parts[0];
		for (int i=1; i < parts.size()-1; ++i)
			directory += splitString + parts[i];
		QString baseFileName = parts.at(parts.size()-1);
		return QPair<QString, QString>(directory, baseFileName);
	}
};