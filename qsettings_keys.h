#ifndef QSETTINGS_KEYS_H
#define QSETTINGS_KEYS_H

#include <QString>

namespace QSettingsKeys {
    static const QString organisation_name = "QNotePad";
    static const QString application_name = "QNotePad_current";
    static const QString application_name_default = "QNotePad_default";

    // settings keys
    namespace CheckboxesKeys {
        static const QString line_number_key = "checkboxes/enable_line_number";
        static const QString current_line_hihglight_key =
                                        "checkboxes/enable_current_line_hihglight";
    }

    namespace ThemeKeys {
        static const QString font_key_ = "theme/font";
        static const QString font_point_size_key_ = "theme/font_point_size";
        static const QString text_color_key_ = "theme/text_color";
        static const QString selection_color_key_ = "theme/selection_color";
        static const QString editor_background_color_key_ =
                                            "theme/editor_background_color";
        static const QString current_line_highlighting_selection_color_key_ =
                                            "theme/current_line_highlighting_selection_color";
    }
}

#endif // QSETTINGS_KEYS_H
