/*
*/

#include <QFont>
#include <QColor>
#include <QPixmap>
#include <QResource>

#include "NavPanelModel.h"
#include "NavPanelItem.h"

namespace cbr {

	NavPanelModel::NavPanelModel(QObject *parent) : QAbstractItemModel(parent), rootItem_(0) {
	}

	NavPanelModel::~NavPanelModel() {
	}

	int NavPanelModel::rowCount(const QModelIndex &parent) const {
		NavPanelItem *parentItem;

		if (!parent.isValid())
			parentItem = rootItem_;
		else
			parentItem = static_cast<NavPanelItem*> (parent.internalPointer());

		return parentItem->numChildren();
	}

	int NavPanelModel::columnCount(const QModelIndex&) const {
		return 1;
	}

	QVariant NavPanelModel::headerData(int, Qt::Orientation, int) const {
		return QVariant();
	}

	QVariant NavPanelModel::data(const QModelIndex &modelIndex, int role) const {
		if (!modelIndex.isValid())
			return QVariant();

		QVariant var;

		NavPanelItem *item = static_cast<NavPanelItem*> (modelIndex.internalPointer());
		NavPanelItem::ItemType type = item->getItemType();

		if (role == Qt::FontRole) 
		{
			QFont f = item->font();

			if (type == NavPanelItem::Status || type == NavPanelItem::Text || !item->isEnabled()) {
				f.setItalic(true);
			} else if (type == NavPanelItem::Heading) {
				f.setBold(true);
			}

			var = f;
		} 
		else if (role == Qt::ForegroundRole) 
		{
			if (type == NavPanelItem::Heading || type == NavPanelItem::SubHeading || type == NavPanelItem::Text)
				return QColor(Qt::black);
			else if (!item->isItemEnabled())
				return QColor(Qt::lightGray);
			else if (!item->isEnabled())
				return QColor(Qt::lightGray);
			else
				return QColor(Qt::blue);
		} 
		else if (role == Qt::ToolTipRole)
		{
			return item->toolTip();
		}
		else if (role == Qt::DisplayRole)
			var = item->label();
		else if (role == Qt::DecorationRole) 
		{
			if (item->isLocked())
				var = QPixmap(":/cbrui/npm_locked.png");
			else if (item->isSelected())
				var = QPixmap(":/cbrui/npm_selected.png");
			else if (item->isActive())
				var = QPixmap(":/cbrui/npm_active.png");
			//else if (type == NavPanelItem::Action) 
			//var = QPixmap(":/cbrui/npm_action.png");
			else if (type == NavPanelItem::Report)
				var = QPixmap(":/cbrui/npm_report.png");
			else if (type == NavPanelItem::Plot)
				var = QPixmap(":/cbrui/npm_plot.png");
			//else if (type == NavPanelItem::Config)
			//var = QPixmap(":/cbrui/npm_config.png");
		}


		return var;
	}

	QModelIndex NavPanelModel::parent(const QModelIndex &modelIndex) const {
		if (!modelIndex.isValid())
			return QModelIndex();

		NavPanelItem *childItem = static_cast<NavPanelItem*> (modelIndex.internalPointer());
		NavPanelItem *parentItem = childItem->parent();

		if (parentItem == rootItem_)
			return QModelIndex();

		return createIndex(parentItem->row(), 0, parentItem);
	}

	QModelIndex NavPanelModel::index(int row, int column, const QModelIndex &parent) const {
		NavPanelItem *parentItem;

		if (!parent.isValid())
			parentItem = rootItem_;
		else
			parentItem = static_cast<NavPanelItem*> (parent.internalPointer());

		NavPanelItem *childItem = parentItem->child(row);

		if (childItem)
			return createIndex(row, column, childItem);

		return QModelIndex();
	}

	NavPanelItem *NavPanelModel::addItem(const QString &label, NavPanelItem *parentItem) {
		NavPanelItem *item = new NavPanelItem(label, this, parentItem);
		if (!parentItem)
			rootItem_ = item;
		else {
			QModelIndex parentIndex = createIndex(parentItem->row(), 0, parentItem);
			beginInsertRows(parentIndex, parentItem->numChildren(), parentItem->numChildren());
			parentItem->addChild(item);
			endInsertRows();
		}

		return item;
	}

	void NavPanelModel::removeChildren(NavPanelItem *child) {
		if (child && child->numChildren() > 0) {
			QModelIndex parent = createIndex(child->row(), 0, child);
			beginRemoveRows(parent, 0, child->numChildren() - 1);
			child->removeChildren();
			endRemoveRows();
		}
	}

	void NavPanelModel::removeRootChildren()
	{
		QList<NavPanelItem*> children = rootItem_->getChildren();
		foreach (NavPanelItem *child, children)
		{
			removeChildren(child);
		}
		rootItem_->clearChildren();
	}

	void NavPanelModel::setItemSelected(NavPanelItem *item, bool rhs) {
		item->setSelected(rhs);
		QModelIndex idx = createIndex(item->row(), 0, item);
		emit dataChanged(idx, idx);
	}

	void NavPanelModel::setItemLocked(NavPanelItem *item, bool rhs)
	{
		item->setLocked(rhs);
		QModelIndex idx = createIndex(item->row(), 0, item);
		emit dataChanged(idx, idx);
	}

	void NavPanelModel::setItemActive(NavPanelItem *item, bool rhs) {
		item->setActive(rhs);
		QModelIndex idx = createIndex(item->row(), 0, item);
		emit dataChanged(idx, idx);
	}

	void NavPanelModel::updateLayout() {
		emit layoutChanged();
	}

}