#include "q_note_pad_editor.h"
#include "ui_q_note_pad_editor.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QCloseEvent>
#include <QSettings>

#include "qsettings_keys.h"
#include "utils.h"

QNotePadEditor::QNotePadEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QNotePadEditor),
    file_path_("")
{
    ui->setupUi(this);

    this->setCentralWidget(ui->textEdit);

    connect_menu_actions();
    init_settings_form();
    init_highlight_current_line();
    about_ = new About();
    refreshWindowName();
}

QNotePadEditor::~QNotePadEditor()
{
    delete ui;
    delete settings_;
    delete about_;
}

void QNotePadEditor::connect_menu_actions() {
    connect(ui->actionNew, &QAction::triggered,this,&QNotePadEditor::New);
    connect(ui->actionOpen, &QAction::triggered,this,&QNotePadEditor::Open);
    connect(ui->actionSave, &QAction::triggered,this,&QNotePadEditor::Save);
    connect(ui->actionSave_As, &QAction::triggered,this,&QNotePadEditor::SaveAs);
    connect(ui->actionQuit, &QAction::triggered,this,&QNotePadEditor::Quit);

    connect(ui->actionUndo, &QAction::triggered,this,&QNotePadEditor::Undo);
    connect(ui->actionRedo, &QAction::triggered,this,&QNotePadEditor::Redo);
    connect(ui->actionCut, &QAction::triggered,this,&QNotePadEditor::Cut);
    connect(ui->actionCopy, &QAction::triggered,this,&QNotePadEditor::Copy);
    connect(ui->actionPaste, &QAction::triggered,this,&QNotePadEditor::Paste);
    connect(ui->actionSelect_All, &QAction::triggered,this,&QNotePadEditor::SelectAll);
    connect(ui->actionSettings, &QAction::triggered,this,&QNotePadEditor::callSettings);

    connect(ui->actionAbout, &QAction::triggered,this,&QNotePadEditor::About_menu);
}

void QNotePadEditor::init_settings_form() {
    settings_ = new Settings;
    connect(settings_,&Settings::newContextApplied,this,&QNotePadEditor::onSettingsContextChanged);

    QPalette pallete = ui->textEdit->palette();
    QFont font = ui->textEdit->font();

    QSettings settings(QSettingsKeys::organisation_name,QSettingsKeys::application_name);

    QString font_family = settings.value(QSettingsKeys::ThemeKeys::font_key_,font.family()).toString();
    int font_size = settings.value(QSettingsKeys::ThemeKeys::font_point_size_key_,font.pointSize()).toInt();

    QString text_color = settings.value(QSettingsKeys::ThemeKeys::text_color_key_,pallete.text().color().name()).toString();
    QString selection_color = settings.value(QSettingsKeys::ThemeKeys::selection_color_key_,
                                             pallete.highlight().color().name()).toString();
    QString editor_background_color = settings.value(QSettingsKeys::ThemeKeys::editor_background_color_key_,
                                                     pallete.base().color().name()).toString();
    QString current_line_highlighting_selection_color = settings.value(QSettingsKeys::ThemeKeys::current_line_highlighting_selection_color_key_,
                                                                QColor(Qt::yellow).lighter(100).name()).toString();
    bool checkbox_line_number = settings.value(QSettingsKeys::CheckboxesKeys::line_number_key,false).toBool();
    bool checkbox_current_line_hihglight = settings.value(QSettingsKeys::CheckboxesKeys::current_line_hihglight_key,false).toBool();

    SettingsContext init_context;
    init_context.font = QFont(font_family,font_size);

    init_context.text_color = QColor(text_color);
    init_context.selection_color = QColor(selection_color);
    init_context.editor_background_color = QColor(editor_background_color);
    init_context.current_line_highlighting_selection_color = QColor(current_line_highlighting_selection_color);

    init_context.check_boxes_state.enable_line_number = checkbox_line_number;
    init_context.check_boxes_state.enable_current_line_hihglight = checkbox_current_line_hihglight;

    settings_->setSettingsContext(init_context);
    onSettingsContextChanged(init_context);

    QSettings settings_default(QSettingsKeys::organisation_name,QSettingsKeys::application_name_default);

    settings_default.setValue(QSettingsKeys::ThemeKeys::font_key_,font.family());
    settings_default.setValue(QSettingsKeys::ThemeKeys::font_point_size_key_,font.pointSize());
    settings_default.setValue(QSettingsKeys::ThemeKeys::text_color_key_,pallete.text().color().name());
    settings_default.setValue(QSettingsKeys::ThemeKeys::selection_color_key_,pallete.highlight().color().name());
    settings_default.setValue(QSettingsKeys::ThemeKeys::editor_background_color_key_,pallete.base().color().name());
    settings_default.setValue(QSettingsKeys::ThemeKeys::current_line_highlighting_selection_color_key_,QColor(Qt::yellow).lighter(100).name());

    settings_default.setValue(QSettingsKeys::CheckboxesKeys::line_number_key,false);
    settings_default.setValue(QSettingsKeys::CheckboxesKeys::current_line_hihglight_key,false);
    settings_default.sync();
}

void QNotePadEditor::init_highlight_current_line() {
    connect(ui->textEdit,&QTextEdit::cursorPositionChanged, this, &QNotePadEditor::highlightCurrentLine);
    highlightCurrentLine();
}

void QNotePadEditor::closeEvent(QCloseEvent *event) {
    QMessageBox::Button button = QMessageBox::question(this,"Exit","Do you want to quit?");
    if (button == QMessageBox::Button::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void QNotePadEditor::refreshWindowName() {
    if (file_path_.isEmpty()) {
        this->setWindowTitle(QString("%1 -- %2").arg(editor_name_,"untitled"));
    } else {
        QFileInfo path(file_path_);
        QString filename(path.fileName());
        this->setWindowTitle(QString("%1 -- %2[%3]").arg(editor_name_,filename,path.absoluteDir().absolutePath()));
    }
}

void QNotePadEditor::New() {
    file_path_ = "";
    ui->textEdit->clear();
    refreshWindowName();
}

void QNotePadEditor::Open() {
    file_path_ = QFileDialog::getOpenFileName(this,"Open file");
    QString text;
    utils::readFile(this, file_path_, text);
    ui->textEdit->setText(text);
    ui->statusBar->showMessage(QString("Opening %1...").arg(file_path_),1000);
    refreshWindowName();
}

void QNotePadEditor::Save() {
    if (file_path_.isEmpty()) {
        SaveAs();
        if (file_path_.isEmpty())
            return;
    }
    utils::writeFile(this,file_path_,ui->textEdit->toPlainText());
    ui->statusBar->showMessage(QString("Saving %1...").arg(file_path_),1000);
}

void QNotePadEditor::SaveAs() {
    file_path_ = QFileDialog::getSaveFileName(this,"Save as");
    if (file_path_.isEmpty())
        return;
    Save();
    refreshWindowName();
}

void QNotePadEditor::Quit() {
    this->close();
}

void QNotePadEditor::Undo() {
    ui->textEdit->undo();
}

void QNotePadEditor::Redo() {
    ui->textEdit->redo();
}

void QNotePadEditor::Cut() {
    ui->textEdit->cut();
}

void QNotePadEditor::Copy() {
    ui->textEdit->copy();
}

void QNotePadEditor::Paste() {
    ui->textEdit->paste();
}

void QNotePadEditor::SelectAll() {
    ui->textEdit->selectAll();
}

void QNotePadEditor::callSettings() {
    settings_->show();
}

void QNotePadEditor::About_menu() {
    about_->show();
}

void QNotePadEditor::onSettingsContextChanged(const SettingsContext &context) {
    settings_context_ = context;

    ui->textEdit->setFont(settings_context_.font);
    QPalette palette = ui->textEdit->palette();
    palette.setColor(QPalette::Text,settings_context_.text_color);
    palette.setColor(QPalette::Highlight, settings_context_.selection_color);
    palette.setColor(QPalette::Base,settings_context_.editor_background_color);
    ui->textEdit->setPalette(palette);

    QSettings settings(QSettingsKeys::organisation_name,QSettingsKeys::application_name);

    settings.setValue(QSettingsKeys::ThemeKeys::font_key_,context.font.family());
    settings.setValue(QSettingsKeys::ThemeKeys::font_point_size_key_,context.font.pointSize());
    settings.setValue(QSettingsKeys::ThemeKeys::text_color_key_,context.text_color.name());
    settings.setValue(QSettingsKeys::ThemeKeys::selection_color_key_,context.selection_color.name());
    settings.setValue(QSettingsKeys::ThemeKeys::editor_background_color_key_,context.editor_background_color.name());
    settings.setValue(QSettingsKeys::ThemeKeys::current_line_highlighting_selection_color_key_,context.current_line_highlighting_selection_color.name());

    settings.setValue(QSettingsKeys::CheckboxesKeys::line_number_key,context.check_boxes_state.enable_line_number);
    settings.setValue(QSettingsKeys::CheckboxesKeys::current_line_hihglight_key,context.check_boxes_state.enable_current_line_hihglight);
    settings.sync();

    highlightCurrentLine();
}

void QNotePadEditor::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelection;

    if(!ui->textEdit->isReadOnly() && settings_context_.check_boxes_state.enable_current_line_hihglight) {
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(settings_context_.current_line_highlighting_selection_color);
        selection.format.setProperty(QTextFormat::FullWidthSelection,true);
        selection.cursor = ui->textEdit->textCursor();
        selection.cursor.clearSelection();
        extraSelection.append(selection);
    }
    ui->textEdit->setExtraSelections(extraSelection);
}
