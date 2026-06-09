#include "robomongo/gui/widgets/explorer/ExplorerTreeWidget.h"
#include "robomongo/core/AppRegistry.h"

#include "robomongo/gui/widgets/explorer/ExplorerTreeItem.h"
#include "robomongo/gui/widgets/explorer/ExplorerDatabaseTreeItem.h"
#include "robomongo/gui/widgets/explorer/ExplorerReplicaSetTreeItem.h"
#include <QContextMenuEvent>
#include <QDropEvent>
#include <QKeyEvent>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QDir>
#include <robomongo/gui/GuiRegistry.h>
#include "robomongo/core/settings/SettingsManager.h"
#include "robomongo/gui/widgets/explorer/ExplorerFavoritesItem.h"
#include <QMessageBox>
#include <algorithm>

namespace Robomongo
{
    namespace
    {
        void updateChildPaths(QTreeWidgetItem *parent, const QString &oldParentPath, const QString &newParentPath)
        {
            for (int i = 0; i < parent->childCount(); ++i) {
                QTreeWidgetItem *child = parent->child(i);
                if (auto fav = dynamic_cast<ExplorerFavoriteItem *>(child)) {
                    QString oldPath = fav->filePath();
                    QString newPath = oldPath;
                    newPath.replace(oldParentPath, newParentPath);
                    fav->setFilePath(newPath);
                } else if (auto folder = dynamic_cast<ExplorerFavoritesFolderItem *>(child)) {
                    updateChildPaths(folder, oldParentPath, newParentPath);
                }
            }
        }

        int getMaxSubfolderDepth(QTreeWidgetItem *item) {
            int maxDepth = 0;
            for (int i = 0; i < item->childCount(); ++i) {
                if (dynamic_cast<ExplorerFavoritesFolderItem*>(item->child(i))) {
                    maxDepth = std::max(maxDepth, 1 + getMaxSubfolderDepth(item->child(i)));
                }
            }
            return maxDepth;
        }

        int getFolderDepth(QTreeWidgetItem *item) {
            int depth = 0;
            while (item) {
                if (dynamic_cast<ExplorerFavoritesFolderItem*>(item)) depth++;
                else if (dynamic_cast<ExplorerFavoritesRootItem*>(item)) break;
                item = item->parent();
            }
            return depth;
        }
    }

    ExplorerTreeWidget::ExplorerTreeWidget(QWidget *parent) : QTreeWidget(parent)
    {
    #if defined(Q_OS_MAC)
        setAttribute(Qt::WA_MacShowFocusRect, false);
        QPalette palet = palette();
        palet.setColor(QPalette::Active, QPalette::Highlight, QColor(16, 108, 214));
        setPalette(palet);
    #endif
        setContextMenuPolicy(Qt::DefaultContextMenu);
        setObjectName("explorerTree");
        setIndentation(15);
        setHeaderHidden(true);
        setSelectionMode(QAbstractItemView::SingleSelection);
        setExpandsOnDoubleClick(false);

        // Enable drag and drop for Favorites
        setDragEnabled(true);
        setAcceptDrops(true);
        setDragDropMode(QAbstractItemView::InternalMove);
        setDropIndicatorShown(true);
    }

    void ExplorerTreeWidget::contextMenuEvent(QContextMenuEvent *event)
    {
        QTreeWidgetItem *item = itemAt(event->pos());
       
        // If the replica set item is not reachable, do not show context menu
        auto replicaSetItem = dynamic_cast<ExplorerReplicaSetTreeItem*>(item);
        if (replicaSetItem && !replicaSetItem->isUp())
            return;

        // If the database set item is disabled, do not show context menu
        auto dbItem = dynamic_cast<ExplorerDatabaseTreeItem*>(item);
        if (dbItem && dbItem->isDisabled()) 
            return;

        if (item) {
            auto explorerItem = dynamic_cast<ExplorerTreeItem *>(item);
            if (explorerItem) 
                explorerItem->showContextMenuAtPos(mapToGlobal(event->pos()));
        }
    }

    void ExplorerTreeWidget::dropEvent(QDropEvent *event)
    {
        QTreeWidgetItem *targetItem = itemAt(event->pos());
        QTreeWidgetItem *sourceItem = currentItem();

        if (sourceItem && targetItem) {
            auto favSource = dynamic_cast<ExplorerFavoriteItem *>(sourceItem);
            auto folderSource = dynamic_cast<ExplorerFavoritesFolderItem *>(sourceItem);
            
            auto favTarget = dynamic_cast<ExplorerFavoriteItem *>(targetItem);
            auto folderTarget = dynamic_cast<ExplorerFavoritesFolderItem *>(targetItem);
            auto rootTarget = dynamic_cast<ExplorerFavoritesRootItem *>(targetItem);

            // Re-parent target if it's an item to its folder
            if (favTarget) {
                targetItem = favTarget->parent();
                folderTarget = dynamic_cast<ExplorerFavoritesFolderItem *>(targetItem);
                rootTarget = dynamic_cast<ExplorerFavoritesRootItem *>(targetItem);
            }

            if ((favSource || folderSource) && (folderTarget || rootTarget)) {
                QString sourcePath;
                QString targetDirPath;

                if (favSource) sourcePath = favSource->filePath();
                else if (folderSource) sourcePath = folderSource->physicalPath();

                if (folderTarget) targetDirPath = folderTarget->physicalPath();
                else if (rootTarget) targetDirPath = AppRegistry::instance().settingsManager()->favoritesScriptsDir();

                if (!sourcePath.isEmpty() && !targetDirPath.isEmpty()) {
                    // Calculate target depth
                    int targetDepth = getFolderDepth(folderTarget);
                    // Calculate dragged folder subtree depth
                    int draggedDepth = folderSource ? (1 + getMaxSubfolderDepth(folderSource)) : 0;

                    if (targetDepth + draggedDepth > 4) {
                        QMessageBox::warning(this, tr("Favorites"), tr("Maximum folder depth (4) reached."));
                        event->ignore();
                        return;
                    }

                    // Remove trailing slashes to ensure QFileInfo::fileName() works for folders
                    if (sourcePath.endsWith("/")) sourcePath.chop(1);
                    if (targetDirPath.endsWith("/")) targetDirPath.chop(1);

                    QFileInfo sourceInfo(sourcePath);
                    QString newPath = targetDirPath + "/" + sourceInfo.fileName();

                    if (sourcePath != newPath) {
                        // Prevent dragging a folder into itself or its own subfolders
                        if (folderSource && (newPath == sourcePath || newPath.startsWith(sourcePath + "/"))) {
                            event->ignore();
                            return;
                        }

                        bool success = false;
                        if (favSource) success = QFile::rename(sourcePath, newPath);
                        else if (folderSource) success = QDir().rename(sourcePath, newPath);

                        if (success) {
                            if (favSource) {
                                favSource->setFilePath(newPath);
                            } else if (folderSource) {
                                // For folders, we must update all children's internal paths
                                updateChildPaths(folderSource, sourcePath, newPath);
                            }
                            // Fall through to default dropEvent to handle UI
                        } else {
                            event->ignore();
                            return;
                        }
                    }
                }
            }
        }

        QTreeWidget::dropEvent(event);
    }

    void ExplorerTreeWidget::keyPressEvent(QKeyEvent *event)
    {
        Qt::KeyboardModifiers modifiers = event->modifiers();
        if ((modifiers == Qt::NoModifier || modifiers == Qt::ShiftModifier) &&
            !event->text().isEmpty() && event->text()[0].isPrint())
        {
            emit printableKeyPressed(event->text());
            event->accept();
            return;
        }

        QTreeWidget::keyPressEvent(event);
    }
}
