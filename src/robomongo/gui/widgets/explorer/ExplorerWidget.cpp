#include "robomongo/gui/widgets/explorer/ExplorerWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMovie>
#include <QKeyEvent>
#include <QMessageBox>

#include "robomongo/core/AppRegistry.h"
#include "robomongo/core/domain/App.h"
#include "robomongo/core/domain/MongoServer.h"
#include "robomongo/core/domain/MongoDatabase.h"
#include "robomongo/core/utils/QtUtils.h"
#include "robomongo/core/EventBus.h"
#include "robomongo/core/events/MongoEvents.h"
#include "robomongo/gui/MainWindow.h"
#include "robomongo/gui/widgets/explorer/ExplorerTreeWidget.h"
#include "robomongo/gui/widgets/explorer/ExplorerServerTreeItem.h"
#include "robomongo/gui/widgets/workarea/WorkAreaTabWidget.h"
#include "robomongo/gui/widgets/workarea/QueryWidget.h"
#include "robomongo/gui/widgets/explorer/ExplorerCollectionTreeItem.h"
#include "robomongo/gui/widgets/explorer/ExplorerCollectionIndexesDir.h"
#include "robomongo/gui/widgets/explorer/ExplorerDatabaseCategoryTreeItem.h"
#include "robomongo/gui/widgets/explorer/ExplorerReplicaSetTreeItem.h"
#include "robomongo/gui/widgets/explorer/ExplorerReplicaSetFolderItem.h"
#include "robomongo/gui/widgets/explorer/ExplorerUserTreeItem.h"
#include "robomongo/gui/widgets/explorer/ExplorerFavoritesItem.h"
#include "robomongo/gui/widgets/explorer/ExplorerDatabaseTreeItem.h"
#include "robomongo/utils/common.h"

namespace Robomongo
{

    ExplorerWidget::ExplorerWidget(MainWindow *parentMainWindow) : BaseClass(parentMainWindow),
        _progress(0)
    {
        _treeWidget = new ExplorerTreeWidget(this);
        
        // Add Favorites root node
        _favoritesRoot = new ExplorerFavoritesRootItem(_treeWidget);
        _treeWidget->addTopLevelItem(_favoritesRoot);

        QHBoxLayout *vlaout = new QHBoxLayout();
        vlaout->setMargin(0);
        vlaout->addWidget(_treeWidget, Qt::AlignJustify);

        VERIFY(connect(_treeWidget, SIGNAL(itemExpanded(QTreeWidgetItem *)), this, SLOT(ui_itemExpanded(QTreeWidgetItem *))));
        VERIFY(connect(_treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), 
                       this, SLOT(ui_itemDoubleClicked(QTreeWidgetItem *, int))));
        VERIFY(connect(_treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), 
                       this, SLOT(ui_currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *))));

        setLayout(vlaout);

        QMovie *movie = new QMovie(":robomongo/icons/loading.gif", QByteArray(), this);
        _progressLabel = new QLabel(this);
        _progressLabel->setMovie(movie);
        _progressLabel->hide();
        movie->start();

        AppRegistry::instance().bus()->subscribe(this, ConnectingEvent::Type);
        AppRegistry::instance().bus()->subscribe(this, ConnectionEstablishedEvent::Type);
        AppRegistry::instance().bus()->subscribe(this, ConnectionFailedEvent::Type);
        AppRegistry::instance().bus()->subscribe(this, FavoritesChangedEvent::Type);
    }

    ExplorerWidget::~ExplorerWidget()
    {
        saveSetting("ExplorerWidget/size", size());
    }

    QTreeWidgetItem* ExplorerWidget::getSelectedTreeItem() const
    {
        return _treeWidget->currentItem();
    }

    void ExplorerWidget::keyPressEvent(QKeyEvent *event)
    {
        if ((event->key() == Qt::Key_Return) || (event->key() == Qt::Key_Enter))
        {
            QList<QTreeWidgetItem*> items = _treeWidget->selectedItems();

            if (items.count() != 1) {
                BaseClass::keyPressEvent(event);
                return;
            }

            QTreeWidgetItem *item = items[0];

            if (!item) {
                BaseClass::keyPressEvent(event);
                return;
            }

            ui_itemDoubleClicked(item, 0);

            return;
        }

        BaseClass::keyPressEvent(event);
    }

    QSize ExplorerWidget::sizeHint() const
    {
        auto size { getSetting("ExplorerWidget/size").toSize() };        
        if(QSize(-1, -1) == size)
           size = QSize(180, -1);

        return(size);
    }

    void ExplorerWidget::increaseProgress()
    {
        ++_progress;
        _progressLabel->move(width() / 2 - 8, height() / 2 - 8);
        _progressLabel->show();
    }

    void ExplorerWidget::decreaseProgress()
    {
        --_progress;

        if (_progress < 0)
            _progress = 0;

        if (!_progress)
            _progressLabel->hide();
    }

    void ExplorerWidget::handle(ConnectingEvent *event)
    {
        increaseProgress();
    }

    void ExplorerWidget::handle(ConnectionEstablishedEvent *event)
    {
        // Do not make UI changes for non PRIMARY connections
        if (event->connectionType != ConnectionPrimary)
            return;

        decreaseProgress();

        auto item = new ExplorerServerTreeItem(_treeWidget, event->server, event->connInfo);
        _treeWidget->addTopLevelItem(item);
        _treeWidget->setCurrentItem(item);
        _treeWidget->setFocus();
    }

    void ExplorerWidget::handle(ConnectionFailedEvent *event)
    {
        decreaseProgress();
    }

    void ExplorerWidget::handle(FavoritesChangedEvent *event)
    {
        _favoritesRoot->refresh();
    }

    void ExplorerWidget::ui_itemExpanded(QTreeWidgetItem *item)
    {
        auto categoryItem = dynamic_cast<ExplorerDatabaseCategoryTreeItem *>(item);
        if (categoryItem) {
            categoryItem->expand();
            return;
        }

        auto serverItem = dynamic_cast<ExplorerServerTreeItem *>(item);
        if (serverItem) {
            serverItem->expand();
            return;
        }

        auto replicaSetFolder = dynamic_cast<ExplorerReplicaSetFolderItem *>(item);
        if (replicaSetFolder) {
            replicaSetFolder->expand();
            return;
        }
       
        auto dirItem = dynamic_cast<ExplorerCollectionIndexesDir *>(item);
        if (dirItem) {
            dirItem->expand();
        }
    }

    void ExplorerWidget::ui_itemDoubleClicked(QTreeWidgetItem *item, int column)
    {        
        if (auto collectionItem = dynamic_cast<ExplorerCollectionTreeItem *>(item)) {
            AppRegistry::instance().app()->openShell(collectionItem->collection());
            return;
        }

        if (auto userItem = dynamic_cast<ExplorerUserTreeItem *>(item)) {
            userItem->ui_viewUser();
            return;
        }

        if (auto favoriteItem = dynamic_cast<ExplorerFavoriteItem *>(item)) {
            QString script = favoriteItem->script();
            QString filePath = favoriteItem->filePath();

            // Try to find active MainWindow and its current tab
            MainWindow *mainWin = qobject_cast<MainWindow *>(window());
            if (mainWin) {
                // Find potential target QueryWidget
                WorkAreaTabWidget *workArea = mainWin->findChild<WorkAreaTabWidget *>();
                if (workArea) {
                    QueryWidget *currentQW = workArea->currentQueryWidget();
                    if (currentQW) {
                        auto result = QMessageBox::question(this, tr("Apply Favorite"),
                            tr("Do you want to apply this favorite to the current tab?\n(This will allow you to edit and save it directly.)"),
                            QMessageBox::Yes | QMessageBox::No);

                        if (result == QMessageBox::Yes) {
                            currentQW->applyFavorite(script, filePath);
                            return;
                        }
                    }
                }
            }
            
            MongoServer *server = nullptr;
            MongoDatabase *database = nullptr;
            QTreeWidgetItem *current = _treeWidget->currentItem();
            while (current) {
                if (auto dbItem = dynamic_cast<ExplorerDatabaseTreeItem *>(current)) {
                    database = dbItem->database();
                    break;
                }
                if (auto serverItem = dynamic_cast<ExplorerServerTreeItem *>(current)) {
                    server = serverItem->server();
                    break;
                }
                current = current->parent();
            }

            if (database) {
                AppRegistry::instance().app()->openShell(database, script);
            } else if (server) {
                AppRegistry::instance().app()->openShell(server, script);
            } else {
                // If context not found from the current favorite item's path (which is expected),
                // try to find context from the last selected item or active server.
                
                MongoServer* targetServer = nullptr;
                MongoDatabase* targetDatabase = nullptr;

                // 1. Try last stored context
                if (_lastDatabase || _lastServer) {
                    // Validate if server still alive
                    auto const& aliveServers = AppRegistry::instance().app()->getServers();
                    bool serverFound = false;
                    for (auto const& s : aliveServers) {
                        if (s.get() == _lastServer) {
                            serverFound = true;
                            break;
                        }
                    }

                    if (serverFound) {
                        targetServer = _lastServer;
                        targetDatabase = _lastDatabase;
                    }
                }

                // 2. If nothing from history, try to find the only server or first server
                if (!targetServer) {
                    auto const& aliveServers = AppRegistry::instance().app()->getServers();
                    if (aliveServers.size() == 1) {
                        targetServer = aliveServers[0].get();
                    } else if (aliveServers.size() > 1) {
                        // If multiple, maybe we can pick one that is expanded in the tree?
                        // For now let's at least pick the first one to avoid the error if one is available.
                        targetServer = aliveServers[0].get();
                    }
                }

                if (targetDatabase) {
                    AppRegistry::instance().app()->openShell(targetDatabase, script);
                } else if (targetServer) {
                    AppRegistry::instance().app()->openShell(targetServer, script);
                } else {
                    QMessageBox::information(this, tr("Favorites"), tr("Please select a server or database in the tree first to open this script."));
                }
            }
            return;
        }

        auto replicaMemberItem = dynamic_cast<ExplorerReplicaSetTreeItem*>(item);
        if (replicaMemberItem && replicaMemberItem->isUp()) {
            AppRegistry::instance().app()->openShell(replicaMemberItem->server(), 
                replicaMemberItem->connectionSettings(), ScriptInfo("", true));
            return;
        }

        // Toggle expanded state
        item->setExpanded(!item->isExpanded());
    }

    void ExplorerWidget::ui_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
    {
        if (!current)
            return;

        MongoServer *server = nullptr;
        MongoDatabase *database = nullptr;
        QTreeWidgetItem *item = current;
        while (item) {
            if (auto dbItem = dynamic_cast<ExplorerDatabaseTreeItem *>(item)) {
                database = dbItem->database();
                break;
            }
            if (auto serverItem = dynamic_cast<ExplorerServerTreeItem *>(item)) {
                server = serverItem->server();
                break;
            }
            item = item->parent();
        }

        if (database || server) {
            _lastDatabase = database;
            _lastServer = server;
        }
    }
}
