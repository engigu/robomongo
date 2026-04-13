#include "robomongo/gui/widgets/workarea/WelcomeTab.h"

#include <QTextBrowser>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QScrollArea>

namespace Robomongo {

    WelcomeTab::WelcomeTab(QScrollArea *parent) :
        QWidget(parent), _parent(parent)
    {
        _browser = new QTextBrowser(this);
        _browser->setOpenExternalLinks(true);
        _browser->setFrameStyle(QFrame::NoFrame);
        
        // Using a simpler HTML/CSS layout compatible with QTextBrowser (Qt 5.15)
        // Note: QTextBrowser doesn't support flexbox, so we use center alignment and padding.
        _browser->setHtml(tr(R"(
            <html>
            <body style="background-color: #f9fbf9; margin: 0; padding: 40px;">
                <div align="center">
                    <div style="background-color: white; padding: 40px; border: 1px solid #eee; width: 600px; text-align: left; color: #333;">
                        <div style="background-color: #e8f5e8; color: #2d862d; padding: 5px 10px; font-weight: bold; font-size: 11px;">
                            Reborn v%1 - Standard Release
                        </div>
                        <h1 style="color: #1a1a1a; margin-top: 20px;">Welcome back to Robo 3T</h1>
                        <p style="font-size: 14px; line-height: 1.6; color: #555;">
                            This is the community-maintained, optimized version of Robo 3T. 
                            We've removed the noise and fixed the core, so you can focus on your data.
                        </p>
                        
                        <div style="margin: 20px 0;">
                            <b style="color: #2d862d;">Key Highlights:</b>
                            <ul style="margin-top: 10px; color: #444;">
                                <li><b>Stability First:</b> Resolved critical memory leaks and compilation issues.</li>
                                <li><b>Security Hardened:</b> Integrated stable OpenSSL 1.1.1u toolkit.</li>
                                <li><b>Modern Toolchain:</b> Rebuilt with Qt 5.15.2 and Ninja.</li>
                                <li><b>100% Native:</b> Removed Chromium kernel for minimum memory footprint.</li>
                            </ul>
                        </div>

                        <hr style="border: 0; border-top: 1px solid #eee; margin: 30px 0;" />
                        <div style="font-size: 12px; color: #999; font-style: italic;">
                            "Your data, your rules. Thank you for supporting the community edition."
                        </div>
                    </div>
                </div>
            </body>
            </html>
        )").arg(PROJECT_VERSION));

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
