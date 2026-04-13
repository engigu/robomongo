#include "robomongo/gui/widgets/workarea/WelcomeTab.h"

#include <QTextBrowser>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QScrollArea>
#include <QTranslator>
#include <QApplication>

namespace Robomongo {

    WelcomeTab::WelcomeTab(QScrollArea *parent) :
        QWidget(parent), _parent(parent)
    {
        // Lazy Load Welcome Translation
        static bool welcomeLoaded = false;
        if (!welcomeLoaded) {
            QTranslator *translator = new QTranslator(qApp);
            if (translator->load("robomongo_zh_CN_welcome", ":/translations")) {
                qApp->installTranslator(translator);
            }
            welcomeLoaded = true;
        }

        _browser = new QTextBrowser(this);
        _browser->setOpenExternalLinks(true);
        _browser->setFrameStyle(QFrame::NoFrame);
        
        // Using a simpler HTML/CSS layout compatible with QTextBrowser (Qt 5.15)
        // Note: QTextBrowser doesn't support flexbox, so we use center alignment and padding.
        QString html = R"(
            <html>
            <body style="background-color: #f9fbf9; margin: 0; padding: 40px;">
                <div align="center">
                    <div style="background-color: white; padding: 45px; border: 1px solid #eee; width: 600px; text-align: left; color: #333;">
                        <div style="background-color: #e8f5e8; color: #2d862d; padding: 5px 10px; font-weight: bold; font-size: 11px;">
                            %1
                        </div>
                        <h1 style="color: #1a1a1a; margin-top: 25px;">%2</h1>
                        <p style="font-size: 15px; line-height: 1.7; color: #555;">
                            %3
                        </p>
                        
                        <div style="margin: 25px 0;">
                            <b style="color: #2d862d; font-size: 16px;">%4</b>
                            <ul style="margin-top: 12px; color: #444; line-height: 1.6;">
                                <li>%5</li>
                                <li>%6</li>
                                <li>%7</li>
                                <li>%8</li>
                            </ul>
                        </div>

                        <hr style="border: 0; border-top: 1px solid #eee; margin: 30px 0;" />
                        <div style="font-size: 13px; color: #999; font-style: italic;">
                            "%9"
                        </div>
                    </div>
                </div>
            </body>
            </html>
        )";

        _browser->setHtml(html
            .arg(tr("Reborn v%1 - Standard Release").arg(PROJECT_VERSION))
            .arg(tr("Welcome back to Robo 3T"))
            .arg(tr("This is the community-maintained, optimized version of Robo 3T. We've removed the noise and fixed the core, so you can focus on your data."))
            .arg(tr("Key Highlights:"))
            .arg(tr("<b>Stability First:</b> Resolved critical Windows compilation issues and memory leaks."))
            .arg(tr("<b>Security Hardened:</b> Integrated stable OpenSSL 1.1.1u toolkit."))
            .arg(tr("<b>Modern Toolchain:</b> Rebuilt with Qt 5.15.2 and Ninja for lightning-fast performance."))
            .arg(tr("<b>100% Native:</b> Removed Chromium kernel for minimum memory footprint."))
            .arg(tr("Your data, your rules. Thank you for supporting the community edition."))
        );

        auto mainLayout = new QVBoxLayout;
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->addWidget(_browser);
        setLayout(mainLayout);
    }

    void WelcomeTab::resize()
    {
        // QTextBrowser handles its own resizing within the layout
    }
}
