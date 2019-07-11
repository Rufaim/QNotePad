#ifndef UTILS_H
#define UTILS_H

#include <QDir>
#include <QColor>
#include <QPushButton>

namespace utils {
    bool readFile(QWidget* parent, const QString& file_path, QString& text);
    bool writeFile(QWidget* parent, const QString& file_path, const QString& text);

    int countTextLines(const QString& text);
    void setButtonBackgroundColor(const QColor& color, QPushButton* button);
}

#endif // UTILS_H
