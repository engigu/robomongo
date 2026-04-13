#pragma once

#include "robomongo/gui/widgets/explorer/ExplorerTreeItem.h"

namespace Robomongo
{
    class ExplorerFavoriteItem : public ExplorerTreeItem
    {
        Q_OBJECT
    public:
        ExplorerFavoriteItem(QTreeWidgetItem *parent, const QString &name, const QString &filePath);
        QString script() const;
        QString name() const { return _name; }

    private:
        QString _name;
        QString _filePath;
    };

    class ExplorerFavoritesRootItem : public ExplorerTreeItem
    {
        Q_OBJECT
    public:
        ExplorerFavoritesRootItem(QTreeWidget *view);
        void refresh();
    };
}
