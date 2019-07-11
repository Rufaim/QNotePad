#ifndef SETTINGS_H
#define SETTINGS_H

#include <QFrame>

#include "settings_context.h"

namespace Ui {
class Settings;
}

class Settings : public QFrame
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    SettingsContext getSettingsContext();
    void setSettingsContext(const SettingsContext& context);

public slots:
    void LineNumberCheckStateChanged(int);
    void HighlightLineCheckStateChanged(int);

    void FontButtonClick();

    void TextColorButtonClick();
    void SelectionColorButtonClick();
    void EditorBackgroundColorButton();

    void ApplyChanges();
    void CancelChanges();

signals:
    void newContextApplied(const SettingsContext &context);

private:
    void init_settings_form();

    void refreshAll();
    void refreshGeneralSection();
    void refreshFontSectionFont();
    void refreshFontSectionColor();

    Ui::Settings *ui;
    SettingsContext current_context_;
    SettingsContext previous_context_;
};

#endif // SETTINGS_H
