#pragma once
#include <QPair>
#include <QString>

namespace cbr
{
	/** Returns (1) the directory, and (2) the base file name */
	QPair<QString, QString> parseOutDirectory(const QString& fileName);
}
