#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "settings.h"

namespace Ui {
class QNotePadEditor;
}

class QNotePadEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit QNotePadEditor(QWidget *parent = nullptr);
    ~QNotePadEditor();

    void closeEvent(QCloseEvent *event);

public slots:
    // File menu actions
    void New();
    void Open();
    void Save();
    void SaveAs();
    void Quit();

    // Edit menu actions
    void Undo();
    void Redo();
    void Cut();
    void Copy();
    void Paste();
    void SelectAll();
    void callSettings();

    // about menu action
    void About();

    //other slots
    void onSettingsContextChanged(const SettingsContext &context);
    void highlightCurrentLine();

private:
    void connect_menu_actions();
    void init_settings_form();
    void init_highlight_current_line();
    void refreshWindowName();

    Ui::QNotePadEditor *ui;
    Settings* settings_;

    QString file_path_;
    SettingsContext settings_context_;

    const QString editor_name_ = "QNotePad";
};

#endif // MAINWINDOW_H
