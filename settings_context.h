#ifndef SETTINGS_CONTEXT_H
#define SETTINGS_CONTEXT_H

#include <QFont>
#include <QColor>

struct CheckBoxesState {
    bool enable_line_number;
    bool enable_current_line_hihglight;

    CheckBoxesState() :
        enable_line_number(),
        enable_current_line_hihglight()
    {}
    CheckBoxesState(const CheckBoxesState& state) :
        enable_line_number(state.enable_line_number),
        enable_current_line_hihglight(state.enable_current_line_hihglight)
    {}
};

struct SettingsContext {
    QFont font;
    QColor text_color;
    QColor selection_color;
    QColor editor_background_color;

    CheckBoxesState check_boxes_state;

    SettingsContext() :
        font(),
        text_color(),
        selection_color(),
        editor_background_color(),
        check_boxes_state()
    {}
    SettingsContext(const SettingsContext& context) :
        font(context.font),
        text_color(context.text_color),
        selection_color(context.selection_color),
        editor_background_color(context.editor_background_color),
        check_boxes_state(context.check_boxes_state)
    {}
};

#endif // SETTINGS_CONTEXT_H
