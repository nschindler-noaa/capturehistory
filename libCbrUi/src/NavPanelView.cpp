/*
*/

#include <QEvent>
#include <QHelpEvent>
#include <QToolTip>
#include <QAbstractItemModel>

#include "NavPanelView.h"
#include "NavPanelItem.h"

namespace cbr
{
	NavPanelView::NavPanelView(QWidget *parent) : QTreeView(parent) 
	{
		setExpandsOnDoubleClick(false);
		setHeaderHidden(true);
	}

}
