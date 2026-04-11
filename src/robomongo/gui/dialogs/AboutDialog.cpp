#include "robomongo/gui/dialogs/AboutDialog.h"

#include <QDate>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QTextBrowser>
#include <QFile>
#include <Qsci/qsciglobal.h>

#include "robomongo/gui/GuiRegistry.h"
#include "robomongo/core/utils/QtUtils.h"

namespace
{
    auto const YEAR  { QString::number(QDate::currentDate().year()) };
    auto const MONTH { QString::number(QDate::currentDate().month()) };

    const char *description =
        "<h3>%1 %2 (Build %3 - %4/%5)</h3>"
        "Shell-centric MongoDB management tool.<br/>"
        "<a href=\"https://%6\">Submit</a> issues/proposals on GitHub.<br/>"
        "<br/>"

        "<a href=\"https://%7\">%7</a> <br/>"
        "Copyright 2014-%5"
        " <a href= %8 >%9</a>. All rights reserved.<br/>"
        "<br/>"

        "The program is provided AS IS with NO WARRANTY OF ANY KIND, "
        "INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A "
        "PARTICULAR PURPOSE.<br/>"
        "<br>"

        "<b>Dependencies: <br></b>"
        "Mongo-Shell %10<br>"
        "Qt %11<br>"
        "OpenSSL %12<br>"
        "libssh2 %13<br>"
        "QJson %14<br>"
        "QScintilla %15<br>"
        "Google Test %16<br>"
        "ESPRIMA %17<br>"
        "<br>"

        "<b>Credits: <br/></b>"
        "Some icons are designed by Freepik <a href=https://www.flaticon.com>www.flaticon.com</a>"
        "<br/>";
}

namespace Robomongo
{
    AboutDialog::AboutDialog(QWidget *parent)
        : QDialog(parent)
    {
        setWindowTitle(tr("About ") + PROJECT_NAME_TITLE);

        //// About tab
        auto aboutTab = new QWidget;
        aboutTab->setWindowIcon(GuiRegistry::instance().mainWindowIcon());
        aboutTab->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
        auto layout = new QGridLayout(this);
        layout->setSizeConstraint(QLayout::SetFixedSize);

        QString const desc = tr(description)
            .arg(PROJECT_NAME_TITLE).arg(PROJECT_VERSION).arg(BUILD_NUMBER).arg(MONTH).arg(YEAR)
            .arg(PROJECT_GITHUB_ISSUES).arg(PROJECT_DOMAIN).arg(PROJECT_COMPANYNAME_DOMAIN).arg(PROJECT_COMPANYNAME)
            .arg(MongoDB_VERSION).arg(PROJECT_QT_VERSION).arg(OPENSSL_VERSION).arg(LIBSSH2_VERSION).arg(QJSON_VERSION)
            .arg(QSCINTILLA_VERSION_STR).arg(GOOGLE_TEST_VERSION).arg(ESPRIMA_VERSION);

        auto copyRightLabel = new QLabel(desc);
        copyRightLabel->setWordWrap(true);
        copyRightLabel->setOpenExternalLinks(true);
        copyRightLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

        QIcon icon = GuiRegistry::instance().mainWindowIcon();
        QPixmap iconPixmap = icon.pixmap(128, 128);

        auto logoLabel = new QLabel;
        logoLabel->setPixmap(iconPixmap);
        layout->addWidget(logoLabel, 0, 0, 1, 1);
        layout->addWidget(copyRightLabel, 0, 1, 4, 4);
        aboutTab->setLayout(layout);

        //// License Agreement tab
        auto licenseTab = new QWidget;
        auto textBrowser = new QTextBrowser;
        textBrowser->setOpenExternalLinks(true);
        textBrowser->setOpenLinks(true);
        QFile file(":gnu_gpl3_license.html");
        if (file.open(QFile::ReadOnly | QFile::Text))
            textBrowser->setText(file.readAll());
        
        auto licenseTabLay = new QVBoxLayout;
        licenseTabLay->addWidget(textBrowser);
        licenseTab->setLayout(licenseTabLay);

        //// Button box
        auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
        QPushButton *closeButton = buttonBox->button(QDialogButtonBox::Close);
        buttonBox->addButton(closeButton, QDialogButtonBox::ButtonRole(QDialogButtonBox::RejectRole |
                                                                       QDialogButtonBox::AcceptRole));
        VERIFY(connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject())));

        //// Main layout
        auto tabWidget = new QTabWidget;
        tabWidget->addTab(aboutTab, tr("About"));
        tabWidget->addTab(licenseTab, tr("License Agreement"));

        auto mainLayout = new QVBoxLayout;
        mainLayout->addWidget(tabWidget);
        mainLayout->addWidget(buttonBox);
        setLayout(mainLayout);
    }
}
