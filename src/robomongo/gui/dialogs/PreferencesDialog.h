#pragma once

#include <QDialog>
QT_BEGIN_NAMESPACE
class QFontComboBox;
class QSpinBox;
class QPushButton;
QT_END_NAMESPACE

namespace Robomongo
{
    class PreferencesDialog : public QDialog
    {
        Q_OBJECT
        typedef QDialog BaseClass;
    public:
        explicit PreferencesDialog(QWidget *parent = nullptr);

    public slots:
        void accept() override;
        void onRestoreDefaultsRequested();

    private:
        void syncWithSettings();
    private:
        QFontComboBox *_fontFamilyComboBox;
        QSpinBox *_fontSizeSpinBox;
        QPushButton *_restoreDefaultsButton;
    };
}
