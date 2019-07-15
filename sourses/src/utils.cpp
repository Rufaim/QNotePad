#include "utils.h"

#include <QMessageBox>
#include <QTextStream>

bool utils::readFile(QWidget* parent, const QString& file_path, QString& text) {
    QFileInfo file_info(file_path);
    if (!file_info.isFile()) {
        QMessageBox::warning(parent,"Is File", "Should be a file");
        return false;
    }
    QFile file(file_path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(parent,"File", "Can not open file");
        return false;
    }

    QTextStream out(&file);
    text = out.readAll();
    file.close();
    return true;
}

bool utils::writeFile(QWidget *parent, const QString &file_path, const QString &text) {
    QFileInfo file_info(file_path);
    if (file_info.isDir()) {
        QMessageBox::warning(parent,"Is Dir", "Can not write over dir");
        return false;
    }
    QFile file(file_path);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(parent,"File", "Can not open file");
        return false;
    }

    QTextStream out(&file);
    out << text;
    file.flush();
    file.close();
    return true;
}

void utils::setButtonBackgroundColor(const QColor &color, QPushButton* button) {
    QString text_color = color.name();
    QString text_style("QPushButton {background-color: %1;}");
    text_style = text_style.arg(text_color);
    button->setStyleSheet(text_style);
}
