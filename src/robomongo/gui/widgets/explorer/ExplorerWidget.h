#pragma once

#include <QWidget>
QT_BEGIN_NAMESPACE
class QTreeWidget;
class QTreeWidgetItem;
class QLabel;
class QLineEdit;
QT_END_NAMESPACE

#include "robomongo/core/events/MongoEvents.h"

namespace Robomongo
{
    class MainWindow;
    class ExplorerFavoritesRootItem;

    /**
     * @brief Explorer widget (usually you'll see it at the left of main window)
     */
    class ExplorerWidget : public QWidget
    {
        Q_OBJECT

    public:
        typedef QWidget BaseClass;
        ExplorerWidget(MainWindow *parent);
        ~ExplorerWidget();

        QTreeWidgetItem* getSelectedTreeItem() const;

    protected Q_SLOTS:
        void handle(ConnectingEvent *event);
        void handle(ConnectionEstablishedEvent *event);
        void handle(ConnectionFailedEvent *event);
        void handle(FavoritesChangedEvent *event);
    private Q_SLOTS:
        void ui_itemExpanded(QTreeWidgetItem *item);
        void ui_itemDoubleClicked(QTreeWidgetItem *item, int column);
        void ui_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
        void ui_filterTextChanged(const QString &text);
        void ui_rowsInserted(const QModelIndex &parent, int start, int end);
        void ui_applyFilter();
        void ui_treePrintableKeyPressed(const QString &text);

    protected:
        void keyPressEvent(QKeyEvent *event) override;   

    private:
        QSize sizeHint() const override;

        void filterTree(const QString &text);
        bool filterItem(QTreeWidgetItem *item, const QString &text, bool parentMatches);

        int _progress;
        void increaseProgress();
        void decreaseProgress();
        QLabel *_progressLabel;
        QTreeWidget *_treeWidget;
        QLineEdit *_filterLineEdit;
        ExplorerFavoritesRootItem *_favoritesRoot;

        MongoServer *_lastServer = nullptr;
        MongoDatabase *_lastDatabase = nullptr;
    };
}
