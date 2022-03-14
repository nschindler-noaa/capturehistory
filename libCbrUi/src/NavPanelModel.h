#ifndef NavPanelModel_H
#define NavPanelModel_H

#include <QAbstractItemModel>
#include <QList>

namespace cbr
{
    class NavPanelItem;

    class NavPanelModel : public QAbstractItemModel
    {
        Q_OBJECT
    public:
        NavPanelModel(QObject *parent = 0);
        ~NavPanelModel();
        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        int columnCount(const QModelIndex &parent = QModelIndex()) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
        QVariant data(const QModelIndex &modelIndex, int role = Qt::DisplayRole) const;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
        QModelIndex parent(const QModelIndex &modelIndex) const;

        NavPanelItem *addItem(const QString &label, NavPanelItem *parent = 0);

        void removeChildren(NavPanelItem *child);
        void removeRootChildren();

        void updateLayout();

        void setItemLocked(NavPanelItem *item, bool rhs);
    public slots:
        void setItemSelected(NavPanelItem *item, bool rhs);
        void setItemActive(NavPanelItem *item, bool rhs);

    signals:
        void currentItemChanged(NavPanelItem *item);

    private:
        NavPanelItem *rootItem_;
    };
}

#endif
