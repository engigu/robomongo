#include "robomongo/gui/widgets/explorer/ExplorerFavoritesItem.h"
#include "robomongo/core/AppRegistry.h"
#include "robomongo/core/settings/SettingsManager.h"
#include "robomongo/core/EventBus.h"
#include "robomongo/core/events/MongoEvents.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMenu>
#include <QAction>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QDirIterator>
#include "robomongo/gui/GuiRegistry.h"

namespace
{
    using namespace Robomongo;

    void buildLocalTree(QTreeWidgetItem *parent, const QString &dirPath)
    {
        QDir dir(dirPath);
        
        // Add folders first
        QStringList folders = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
        for (const QString &folderName : folders) {
            auto folder = new ExplorerFavoritesFolderItem(parent, folderName);
            buildLocalTree(folder, dir.absoluteFilePath(folderName));
        }

        // Add files
        QStringList files = dir.entryList(QStringList() << "*.js", QDir::Files, QDir::Name);
        for (const QString &fileName : files) {
            QString name = fileName;
            if (name.endsWith(".js")) {
                name = name.left(name.length() - 3);
            }
            new ExplorerFavoriteItem(parent, name, dir.absoluteFilePath(fileName));
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
        setFlags(flags() | Qt::ItemIsDragEnabled);
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
        setIcon(0, GuiRegistry::instance().folderIcon()); 
        setFlags(flags() | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
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

        QString fullPath = AppRegistry::instance().settingsManager()->favoritesScriptsDir() + path;
        if (!fullPath.endsWith("/")) {
            fullPath += "/";
        }
        return fullPath;
    }

    ExplorerFavoritesRootItem::ExplorerFavoritesRootItem(QTreeWidget *view) :
        ExplorerTreeItem(view)
    {
        setText(0, tr("Favorites (⭐️)"));
        setIcon(0, QIcon(":robomongo/icons/mongodb_16x16.png"));
        setFlags(flags() | Qt::ItemIsDropEnabled);
        refresh();
    }

    void ExplorerFavoritesRootItem::refresh()
    {
        // Clear existing children
        qDeleteAll(takeChildren());

        if (QDir(AppRegistry::instance().settingsManager()->favoritesScriptsDir()).exists()) {
            buildLocalTree(this, AppRegistry::instance().settingsManager()->favoritesScriptsDir());
        }

        setExpanded(true);
    }

    void ExplorerFavoriteItem::showContextMenuAtPos(const QPoint &pos)
    {
        QTreeWidgetItem *curr = this;
        while (curr->parent()) curr = curr->parent();
        if (auto root = dynamic_cast<ExplorerFavoritesRootItem *>(curr))
            root->showContextMenuAtPos(treeWidget()->mapFromGlobal(pos));
    }

    void ExplorerFavoritesFolderItem::showContextMenuAtPos(const QPoint &pos)
    {
        QTreeWidgetItem *curr = this;
        while (curr->parent()) curr = curr->parent();
        if (auto root = dynamic_cast<ExplorerFavoritesRootItem *>(curr))
            root->showContextMenuAtPos(treeWidget()->mapFromGlobal(pos));
    }

    void ExplorerFavoritesRootItem::showContextMenuAtPos(const QPoint &pos)
    {
        QTreeWidgetItem *item = treeWidget()->itemAt(pos);
        if (!item) return;

        QMenu menu;
        
        QAction *renameAction = nullptr;
        QAction *deleteAction = nullptr;
        QAction *refreshAction = menu.addAction(tr("Refresh"));
        menu.addSeparator();
        
        if (item != this) {
            renameAction = menu.addAction(tr("Rename"));
            deleteAction = menu.addAction(tr("Delete"));
            menu.addSeparator();
        }
        
        auto newFolderAction = menu.addAction(tr("New Folder"));

        QAction *selectedAction = menu.exec(QCursor::pos());

        if (selectedAction && selectedAction == refreshAction) {
            refresh();
        } else if (selectedAction && selectedAction == renameAction) {
            QString oldName;
            if (auto fav = dynamic_cast<ExplorerFavoriteItem *>(item)) oldName = fav->name();
            else if (auto fol = dynamic_cast<ExplorerFavoritesFolderItem *>(item)) oldName = fol->name();

            bool ok;
            QString newName = QInputDialog::getText(treeWidget(), tr("Rename"), tr("Enter new name:"), QLineEdit::Normal, oldName, &ok);
            if (ok && !newName.isEmpty()) {
                if (auto fav = dynamic_cast<ExplorerFavoriteItem *>(item)) fav->setName(newName);
                else if (auto fol = dynamic_cast<ExplorerFavoritesFolderItem *>(item)) fol->setName(newName);
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
            }
        }
    }
}
