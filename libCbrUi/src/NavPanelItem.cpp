/*
*/

#include <QFont>

#include "NavPanelItem.h"
#include "NavPanelModel.h"

using namespace cbr;

NavPanelItem::NavPanelItem(const QString &label, NavPanelModel *navPanelModel, NavPanelItem *parent, QObject* action_parent) : 
QAction(label, action_parent),
 id_(0), type_(Text),  
selected_(false), active_(false), locked_(false),
label_(label), navPanelModel_(navPanelModel), parent_(parent), itemEnabled_(true)
{
}

NavPanelItem::~NavPanelItem()
{
	removeChildren();
}

void NavPanelItem::addChild(NavPanelItem *childItem)
{
	children_.append(childItem);
}

int NavPanelItem::row() const
{
    if (parent_)
        return parent_->children_.indexOf(const_cast<NavPanelItem*>(this));
    return 0;
}

NavPanelItem *NavPanelItem::child(int index)
{
	if (index >= 0 && index < children_.size())
		return children_.at(index);
	return 0;
}

void NavPanelItem::setItemEnabled(bool itemEnabled)
{
	itemEnabled_ = itemEnabled;
	setEnabled(itemEnabled);
	NavPanelItem *child;
    foreach (child, children_) {
		child->setItemEnabled(itemEnabled);
    }
}

void NavPanelItem::removeChildren()
{
    while (!children_.isEmpty()) 
	{
		NavPanelItem * item = children_.takeFirst();
		item->disconnect();
        delete item;
	}
}
