#include "robomongo/gui/widgets/explorer/ExplorerFavoritesItem.h"
#include "robomongo/core/AppRegistry.h"
#include "robomongo/core/settings/SettingsManager.h"

namespace Robomongo
{
    ExplorerFavoriteItem::ExplorerFavoriteItem(QTreeWidgetItem *parent, const QString &name, const QString &script) :
        ExplorerTreeItem(parent),
        _name(name),
        _script(script)
    {
        setText(0, _name);
        setIcon(0, QIcon(":robomongo/icons/bson_object_16x16.png"));
    }

    ExplorerFavoritesRootItem::ExplorerFavoritesRootItem(QTreeWidget *view) :
        ExplorerTreeItem(view)
    {
        setText(0, tr("Favorites (⭐️)"));
        setIcon(0, QIcon(":robomongo/icons/mongodb_16x16.png"));
        refresh();
    }

    void ExplorerFavoritesRootItem::refresh()
    {
        // Clear existing children
        qDeleteAll(takeChildren());

        auto settings = AppRegistry::instance().settingsManager();
        QVariantMap favorites = settings->favorites();

        for (auto it = favorites.begin(); it != favorites.end(); ++it) {
            new ExplorerFavoriteItem(this, it.key(), it.value().toString());
        }
        
        setExpanded(true);
    }
}
