#include "robomongo/gui/widgets/explorer/ExplorerFavoritesItem.h"
#include "robomongo/core/AppRegistry.h"
#include "robomongo/core/settings/SettingsManager.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <parser.h>

namespace Robomongo
{
    ExplorerFavoriteItem::ExplorerFavoriteItem(QTreeWidgetItem *parent, const QString &name, const QString &filePath) :
        ExplorerTreeItem(parent),
        _name(name),
        _filePath(filePath)
    {
        setText(0, _name);
        setIcon(0, QIcon(":robomongo/icons/bson_object_16x16.png"));
    }

    QString ExplorerFavoriteItem::script() const
    {
        QFile file(_filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            in.setCodec("UTF-8");
            return in.readAll();
        }
        return QString();
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

        if (QFile::exists(FavoritesMetadataPath)) {
            QFile metaFile(FavoritesMetadataPath);
            if (metaFile.open(QIODevice::ReadOnly)) {
                QJson::Parser parser;
                bool okMeta;
                QVariantList metadata = parser.parse(metaFile.readAll(), &okMeta).toList();
                metaFile.close();

                if (okMeta) {
                    for (const QVariant &v : metadata) {
                        QVariantMap entry = v.toMap();
                        QString name = entry.value("name").toString();
                        QString fileName = entry.value("file").toString();
                        QString fullPath = FavoritesScriptsDir + fileName;
                        
                        new ExplorerFavoriteItem(this, name, fullPath);
                    }
                }
            }
        }
        
        setExpanded(true);
    }
}
