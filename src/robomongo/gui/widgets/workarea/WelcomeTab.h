#pragma once

#include <QWidget>
#include <QUrl>

QT_BEGIN_NAMESPACE
class QTextBrowser;
class QScrollArea;
QT_END_NAMESPACE

namespace Robomongo
{
    class WelcomeTab : public QWidget
    {
        Q_OBJECT
    public:
        WelcomeTab(QScrollArea* parent = nullptr);
        QScrollArea* getParent() const { return _parent; }
        void resize();

    private:
        QScrollArea* _parent;
        QTextBrowser* _browser;
    };
}
