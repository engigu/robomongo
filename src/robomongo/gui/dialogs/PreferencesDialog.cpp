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
        setFixedSize(550, 500); 

        QVBoxLayout *layout = new QVBoxLayout(this);

        QHBoxLayout *defLayout = new QHBoxLayout(this);
        QLabel *defDisplayModeLabel = new QLabel(tr("Default display mode:"));
        defLayout->addWidget(defDisplayModeLabel);
        _defDisplayModeComboBox = new QComboBox();
        for (int i = Text; i <= Custom; ++i)
        {
            ViewMode mode = static_cast<ViewMode>(i);
            _defDisplayModeComboBox->addItem(tr(convertViewModeToString(mode)), mode);
        }
        defLayout->addWidget(_defDisplayModeComboBox);
        layout->addLayout(defLayout);

        QHBoxLayout *timeZoneLayout = new QHBoxLayout(this);
        QLabel *timeZoneLabel = new QLabel(tr("Display Dates in:"));
        timeZoneLayout->addWidget(timeZoneLabel);
        _timeZoneComboBox = new QComboBox();
        for (int i = Utc; i <= LocalTime; ++i)
        {
            SupportedTimes time = static_cast<SupportedTimes>(i);
            _timeZoneComboBox->addItem(tr(convertTimesToString(time)), time);
        }
        timeZoneLayout->addWidget(_timeZoneComboBox);
        layout->addLayout(timeZoneLayout);

        QHBoxLayout *uuidEncodingLayout = new QHBoxLayout(this);
        QLabel *uuidEncodingLabel = new QLabel(tr("Legacy UUID Encoding:"));
        uuidEncodingLayout->addWidget(uuidEncodingLabel);
        _uuidEncodingComboBox = new QComboBox();
        for (int i = DefaultEncoding; i <= PythonLegacy; ++i)
        {
            UUIDEncoding encoding = static_cast<UUIDEncoding>(i);
            _uuidEncodingComboBox->addItem(tr(convertUUIDEncodingToString(encoding)), encoding);
        }
        uuidEncodingLayout->addWidget(_uuidEncodingComboBox);
        layout->addLayout(uuidEncodingLayout);        

        _loadMongoRcJsCheckBox = new QCheckBox(tr("Load .mongorc.js"));
        layout->addWidget(_loadMongoRcJsCheckBox);

        _disabelConnectionShortcutsCheckBox = new QCheckBox(tr("Disable connection shortcuts"));
        layout->addWidget(_disabelConnectionShortcutsCheckBox);

        QHBoxLayout *stylesLayout = new QHBoxLayout(this);
        QLabel *stylesLabel = new QLabel(tr("Styles:"));
        stylesLayout->addWidget(stylesLabel);
        _stylesComboBox = new QComboBox();
        _stylesComboBox->addItems(AppStyleUtils::getSupportedStyles());
        stylesLayout->addWidget(_stylesComboBox);
        layout->addLayout(stylesLayout);

        QHBoxLayout *fontLayout = new QHBoxLayout(this);
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

        int modeIndex = _defDisplayModeComboBox->findData(Robomongo::AppRegistry::instance().settingsManager()->viewMode());
        if (modeIndex >= 0) _defDisplayModeComboBox->setCurrentIndex(modeIndex);

        int timeIndex = _timeZoneComboBox->findData(Robomongo::AppRegistry::instance().settingsManager()->timeZone());
        if (timeIndex >= 0) _timeZoneComboBox->setCurrentIndex(timeIndex);

        int uuidIndex = _uuidEncodingComboBox->findData(Robomongo::AppRegistry::instance().settingsManager()->uuidEncoding());
        if (uuidIndex >= 0) _uuidEncodingComboBox->setCurrentIndex(uuidIndex);
        _loadMongoRcJsCheckBox->setChecked(AppRegistry::instance().settingsManager()->loadMongoRcJs());
        _disabelConnectionShortcutsCheckBox->setChecked(AppRegistry::instance().settingsManager()->disableConnectionShortcuts());
        utils::setCurrentText(_stylesComboBox, Robomongo::AppRegistry::instance().settingsManager()->currentStyle());

        _fontFamilyComboBox->setCurrentFont(GuiRegistry::instance().font());
        _fontSizeSpinBox->setValue(GuiRegistry::instance().font().pointSize());
    }

    void PreferencesDialog::accept()
    {
        ViewMode mode = static_cast<ViewMode>(_defDisplayModeComboBox->currentData().toInt());
        Robomongo::AppRegistry::instance().settingsManager()->setViewMode(mode);

        SupportedTimes time = static_cast<SupportedTimes>(_timeZoneComboBox->currentData().toInt());
        Robomongo::AppRegistry::instance().settingsManager()->setTimeZone(time);

        UUIDEncoding uuidC = static_cast<UUIDEncoding>(_uuidEncodingComboBox->currentData().toInt());
        Robomongo::AppRegistry::instance().settingsManager()->setUuidEncoding(uuidC);

        AppRegistry::instance().settingsManager()->setLoadMongoRcJs(_loadMongoRcJsCheckBox->isChecked());
        AppRegistry::instance().settingsManager()->setDisableConnectionShortcuts(_disabelConnectionShortcutsCheckBox->isChecked());
        Robomongo::AppRegistry::instance().settingsManager()->setCurrentStyle(_stylesComboBox->currentText());
        AppStyleUtils::applyStyle(_stylesComboBox->currentText());

        Robomongo::AppRegistry::instance().settingsManager()->setTextFontFamily(_fontFamilyComboBox->currentFont().family());
        Robomongo::AppRegistry::instance().settingsManager()->setTextFontPointSize(_fontSizeSpinBox->value());
        GuiRegistry::instance().refreshFont();

        Robomongo::AppRegistry::instance().settingsManager()->save();

        return BaseClass::accept();
    }

    void PreferencesDialog::onRestoreDefaultsRequested()
    {
        _fontFamilyComboBox->setCurrentIndex(-1); // Will use default logic in syncWithSettings if I reset settings
        // Actually, better to just set the defaults here:
#if defined(Q_OS_MAC)
        _fontFamilyComboBox->setCurrentFont(QFont("Monaco"));
        _fontSizeSpinBox->setValue(12);
#elif defined(Q_OS_UNIX)
        _fontFamilyComboBox->setCurrentFont(QFont("Monospace"));
        _fontSizeSpinBox->setValue(10); // Assume a reasonable default
#elif defined(Q_OS_WIN)
        _fontFamilyComboBox->setCurrentFont(QFont("Courier"));
        _fontSizeSpinBox->setValue(10);
#endif
    }
}
