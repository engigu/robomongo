#include "robomongo/gui/widgets/explorer/ExplorerFavoritesItem.h"
#include "robomongo/core/AppRegistry.h"
#include "robomongo/core/settings/SettingsManager.h"
#include "robomongo/core/EventBus.h"
#include "robomongo/core/events/MongoEvents.h"

#include <QDir>
#include <QFile>
#include <QVariant>
#include <QTextStream>
#include <QMenu>
#include <QAction>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <parser.h>
#include <serializer.h>

namespace
{
    using namespace Robomongo;

    QVariantList serializeFavorites(QTreeWidgetItem *parent)
    {
        QVariantList list;
        for (int i = 0; i < parent->childCount(); ++i) {
            QTreeWidgetItem *child = parent->child(i);
            QVariantMap entry;
            if (auto folder = dynamic_cast<ExplorerFavoritesFolderItem *>(child)) {
                entry.insert("name", folder->name());
                entry.insert("type", "folder");
                entry.insert("children", serializeFavorites(folder));
            } else if (auto favorite = dynamic_cast<ExplorerFavoriteItem *>(child)) {
                entry.insert("name", favorite->name());
                // Store path relative to FavoritesScriptsDir
                QString path = favorite->filePath();
                if (path.startsWith(FavoritesScriptsDir)) {
                    path = path.mid(FavoritesScriptsDir.length());
                }
                entry.insert("file", path);
            }
            list.append(entry);
        }
        return list;
    }

    void saveFavoritesTree(ExplorerFavoritesRootItem *root)
    {
        QVariantList metadata = serializeFavorites(root);
        QFile metaFileOut(FavoritesMetadataPath);
        if (metaFileOut.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            QJson::Serializer serializer;
            serializer.setIndentMode(QJson::IndentFull);
            bool okSerialize = false;
            QByteArray jsonBytes = serializer.serialize(metadata, &okSerialize);
            if (okSerialize) {
                metaFileOut.write(jsonBytes);
            }
            metaFileOut.close();
            AppRegistry::instance().bus()->publish(new FavoritesChangedEvent(nullptr));
        }
    }

    void buildFavorites(QTreeWidgetItem *parent, const QVariantList &list)
    {
        for (const QVariant &v : list) {
            QVariantMap entry = v.toMap();
            QString name = entry.value("name").toString();
            QString type = entry.value("type").toString();

            if (type == "folder") {
                auto folder = new ExplorerFavoritesFolderItem(parent, name);
                buildFavorites(folder, entry.value("children").toList());
            } else {
                QString relativePath = entry.value("file").toString();
                QString fullPath = FavoritesScriptsDir + relativePath;
                new ExplorerFavoriteItem(parent, name, fullPath);
            }
        }
    }
}

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

    void ExplorerFavoriteItem::setName(const QString &name)
    {
        QString oldPath = _filePath;
        QFileInfo info(oldPath);
        QString newPath = info.dir().absolutePath() + "/" + name + ".js";

        if (oldPath != newPath && QFile::exists(oldPath)) {
            if (QFile::rename(oldPath, newPath)) {
                _filePath = newPath;
            }
        }
        _name = name;
        setText(0, _name);
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

    ExplorerFavoritesFolderItem::ExplorerFavoritesFolderItem(QTreeWidgetItem *parent, const QString &name) :
        ExplorerTreeItem(parent),
        _name(name)
    {
        setText(0, _name);
        setIcon(0, QIcon(":robomongo/icons/database_16x16.png")); 
    }

    void ExplorerFavoritesFolderItem::setName(const QString &name)
    {
        QString oldPath = physicalPath();
        _name = name;
        setText(0, _name);
        QString newPath = physicalPath();

        if (oldPath != newPath && QDir().exists(oldPath)) {
            QDir().rename(oldPath, newPath);
        }
    }

    QString ExplorerFavoritesFolderItem::physicalPath() const
    {
        QString path = name();
        QTreeWidgetItem *curr = parent();
        while (curr) {
            if (auto folder = dynamic_cast<ExplorerFavoritesFolderItem *>(curr)) {
                path = folder->name() + "/" + path;
            } else if (dynamic_cast<ExplorerFavoritesRootItem *>(curr)) {
                break;
            }
            curr = curr->parent();
        }
        return FavoritesScriptsDir + path;
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
                    buildFavorites(this, metadata);
                }
            }
        }

        setExpanded(true);
    }

    void ExplorerFavoriteItem::showContextMenuAtPos(const QPoint &pos)
    {
        QTreeWidgetItem *curr = this;
        while (curr->parent()) curr = curr->parent();
        if (auto root = dynamic_cast<ExplorerFavoritesRootItem *>(curr))
            root->showContextMenuAtPos(pos);
    }

    void ExplorerFavoritesFolderItem::showContextMenuAtPos(const QPoint &pos)
    {
        QTreeWidgetItem *curr = this;
        while (curr->parent()) curr = curr->parent();
        if (auto root = dynamic_cast<ExplorerFavoritesRootItem *>(curr))
            root->showContextMenuAtPos(pos);
    }

    void ExplorerFavoritesRootItem::showContextMenuAtPos(const QPoint &pos)
    {
        QTreeWidgetItem *item = treeWidget()->itemAt(pos);
        if (!item) return;

        QMenu menu;
        
        QAction *renameAction = nullptr;
        QAction *deleteAction = nullptr;
        
        if (item != this) {
            renameAction = menu.addAction(tr("Rename"));
            deleteAction = menu.addAction(tr("Delete"));
            menu.addSeparator();
        }
        
        auto newFolderAction = menu.addAction(tr("New Folder"));

        QAction *selectedAction = menu.exec(treeWidget()->mapToGlobal(pos));

        if (selectedAction && selectedAction == renameAction) {
            QString oldName;
            if (auto fav = dynamic_cast<ExplorerFavoriteItem *>(item)) oldName = fav->name();
            else if (auto fol = dynamic_cast<ExplorerFavoritesFolderItem *>(item)) oldName = fol->name();

            bool ok;
            QString newName = QInputDialog::getText(treeWidget(), tr("Rename"), tr("Enter new name:"), QLineEdit::Normal, oldName, &ok);
            if (ok && !newName.isEmpty()) {
                if (auto fav = dynamic_cast<ExplorerFavoriteItem *>(item)) fav->setName(newName);
                else if (auto fol = dynamic_cast<ExplorerFavoritesFolderItem *>(item)) fol->setName(newName);
                saveFavoritesTree(this);
            }
        } else if (selectedAction && selectedAction == deleteAction) {
            auto res = QMessageBox::question(treeWidget(), tr("Delete"), tr("Are you sure you want to delete this item?"), QMessageBox::Yes | QMessageBox::No);
            if (res == QMessageBox::Yes) {
                if (auto fol = dynamic_cast<ExplorerFavoritesFolderItem *>(item)) {
                    QDir(fol->physicalPath()).removeRecursively();
                } else if (auto fav = dynamic_cast<ExplorerFavoriteItem *>(item)) {
                    QFile::remove(fav->filePath());
                }
                delete item;
                saveFavoritesTree(this);
            }
        } else if (selectedAction && selectedAction == newFolderAction) {
            bool ok;
            QString folderName = QInputDialog::getText(treeWidget(), tr("New Folder"), tr("Enter folder name:"), QLineEdit::Normal, tr("New Group"), &ok);
            if (ok && !folderName.isEmpty()) {
                QTreeWidgetItem *parent = item;
                if (dynamic_cast<ExplorerFavoriteItem *>(item)) parent = item->parent();
                
                auto folder = new ExplorerFavoritesFolderItem(parent, folderName);
                QDir().mkpath(folder->physicalPath());
                folder->setExpanded(true);
                saveFavoritesTree(this);
            }
        }
    }
}
