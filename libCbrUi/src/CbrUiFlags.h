#ifndef CbrUiFlags_h
#define CbrUiFlags_h

#include <QFlags>

namespace cbr
{
	enum WFlag {
		WindowNavDockWidget = 0x02000000,
		WindowOutputDockWidget = 0x04000000
	};

	Q_DECLARE_FLAGS(WFlags, WFlag)

}

Q_DECLARE_OPERATORS_FOR_FLAGS(cbr::WFlags)

#endif