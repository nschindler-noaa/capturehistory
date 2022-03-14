#ifndef NavPanelItem_H
#define NavPanelItem_H

#include <QList>
#include <QAction>
#include <QStringList>


namespace cbr {
    class NavPanelModel;

    class NavPanelItem : public QAction {

        Q_OBJECT

    public:
        enum ItemType {
            Action = 0, Config, Report, Effects, Heading, Plot, Text, Selectable, Status, SubHeading
        };

        NavPanelItem(const QString &label, NavPanelModel *navPanelModel, NavPanelItem *parent = 0, QObject* action_parent = 0);
        ~NavPanelItem();

        NavPanelItem *parent() const {
            return parent_;
        }

        int numChildren() const {
            return children_.count();
        }

        const QString &label() const {
            return label_;
        }

        bool isItemEnabled() const {
            return itemEnabled_;
        }
        void setItemEnabled(bool itemEnabled);
        void addChild(NavPanelItem *childItem);
        int row() const;
        NavPanelItem *child(int index);
        void removeChildren();
        QList<NavPanelItem*> & getChildren() { return children_; }
        // remove children before clearing
        void clearChildren() { children_.clear(); }

        void setItemType(ItemType type) {
            type_ = type;
        }

        ItemType getItemType() const {
            return type_;
        }

        bool isSelected() const {
            return selected_;
        }

        void setSelected(bool rhs) {
            selected_ = rhs;
        }

        bool isLocked() const {
            return locked_;
        }

        void setLocked(bool rhs) {
            locked_ = rhs;
        }

        bool isActive() const {
            return active_;
        }

        void setActive(bool rhs) {
            active_ = rhs;
        }

        // a general purpose field for tying the nav item to a database row

        void setId(int id) {
            id_ = id;
        }

        int getId() const {
            return id_;
        }

    private:
        int id_;
        ItemType type_;
        bool selected_;
        bool active_;
        bool locked_;

        const QString label_;
        NavPanelModel *navPanelModel_;
        NavPanelItem *parent_;
        QList<NavPanelItem*> children_;
        bool itemEnabled_;
    };
}

#endif
