#include "robomongo/gui/dialogs/PreferencesDialog.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QFontComboBox>
#include <QSpinBox>
#include <QFontDatabase>
#include <QFont>

#include "robomongo/gui/GuiRegistry.h"
#include "robomongo/gui/AppStyle.h"
#include "robomongo/gui/utils/ComboBoxUtils.h"
#include "robomongo/core/utils/QtUtils.h"
#include "robomongo/core/AppRegistry.h"
#include "robomongo/core/settings/SettingsManager.h"

namespace Robomongo
{
    PreferencesDialog::PreferencesDialog(QWidget *parent)
        : BaseClass(parent)
    {
        setWindowIcon(GuiRegistry::instance().mainWindowIcon());

        setWindowTitle(tr("Preferences %1").arg(PROJECT_NAME_TITLE));
        setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
        setFixedSize(450, 200); 

        QVBoxLayout *layout = new QVBoxLayout(this);

        QHBoxLayout *fontLayout = new QHBoxLayout();
        QLabel *fontFamilyLabel = new QLabel(tr("Font Family:"));
        fontLayout->addWidget(fontFamilyLabel);
        _fontFamilyComboBox = new QFontComboBox();
        _fontFamilyComboBox->setFontFilters(QFontComboBox::MonospacedFonts);
        fontLayout->addWidget(_fontFamilyComboBox);

        QLabel *fontSizeLabel = new QLabel(tr("Size:"));
        fontLayout->addWidget(fontSizeLabel);
        _fontSizeSpinBox = new QSpinBox();
        _fontSizeSpinBox->setRange(6, 72);
        fontLayout->addWidget(_fontSizeSpinBox);
        layout->addLayout(fontLayout);

        _restoreDefaultsButton = new QPushButton(tr("Restore Defaults"));
        VERIFY(connect(_restoreDefaultsButton, SIGNAL(clicked()), this, SLOT(onRestoreDefaultsRequested())));
        layout->addWidget(_restoreDefaultsButton);   

        layout->addStretch();

        QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Save);
        VERIFY(connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept())));
        VERIFY(connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject())));
        layout->addWidget(buttonBox);
        setLayout(layout);

        syncWithSettings();
    }

    void PreferencesDialog::syncWithSettings()
    {
        _fontFamilyComboBox->setCurrentFont(GuiRegistry::instance().font());
        _fontSizeSpinBox->setValue(GuiRegistry::instance().font().pointSize());
    }

    void PreferencesDialog::accept()
    {
        Robomongo::AppRegistry::instance().settingsManager()->setTextFontFamily(_fontFamilyComboBox->currentFont().family());
        Robomongo::AppRegistry::instance().settingsManager()->setTextFontPointSize(_fontSizeSpinBox->value());
        GuiRegistry::instance().refreshFont();

        Robomongo::AppRegistry::instance().settingsManager()->save();

        return BaseClass::accept();
    }

    void PreferencesDialog::onRestoreDefaultsRequested()
    {
#if defined(Q_OS_MAC)
        _fontFamilyComboBox->setCurrentFont(QFont("Monaco"));
        _fontSizeSpinBox->setValue(12);
#elif defined(Q_OS_UNIX)
        _fontFamilyComboBox->setCurrentFont(QFont("Monospace"));
        _fontSizeSpinBox->setValue(10); 
#elif defined(Q_OS_WIN)
        _fontFamilyComboBox->setCurrentFont(QFont("Courier"));
        _fontSizeSpinBox->setValue(10);
#endif
    }
}
