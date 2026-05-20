#pragma once

#include <QTreeWidget>

namespace Robomongo
{
    class ExplorerTreeWidget : public QTreeWidget
    {
        Q_OBJECT
    public:
        explicit ExplorerTreeWidget(QWidget *parent = 0);
    Q_SIGNALS:
        void printableKeyPressed(const QString &text);
    protected:
        virtual void contextMenuEvent(QContextMenuEvent *event) override;
        virtual void dropEvent(QDropEvent *event) override;
        virtual void keyPressEvent(QKeyEvent *event) override;
    };
}
