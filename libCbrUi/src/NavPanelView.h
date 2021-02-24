#ifndef NavPanelView_h
#define NavPanelView_h

#include <QTreeView>
#include <QWidget>

class event;

namespace cbr
{
    class NavPanelView : public QTreeView
    {
        Q_OBJECT

    public:
        NavPanelView(QWidget *parent = nullptr);
    };
}

#endif
