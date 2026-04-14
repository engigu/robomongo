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
        QString filePath() const { return _filePath; }
        QString name() const { return _name; }
        void setName(const QString &name) { _name = name; setText(0, name); }
        void showContextMenuAtPos(const QPoint &pos) override;

    private:
        QString _name;
        QString _filePath;
    };

    class ExplorerFavoritesFolderItem : public ExplorerTreeItem
    {
        Q_OBJECT
    public:
        ExplorerFavoritesFolderItem(QTreeWidgetItem *parent, const QString &name);
        QString name() const { return _name; }
        void setName(const QString &name) { _name = name; setText(0, name); }
        void showContextMenuAtPos(const QPoint &pos) override;

    private:
        QString _name;
    };

    class ExplorerFavoritesRootItem : public ExplorerTreeItem
    {
        Q_OBJECT
    public:
        ExplorerFavoritesRootItem(QTreeWidget *view);
        void refresh();

    protected:
        void showContextMenuAtPos(const QPoint &pos) override;
    };
}
