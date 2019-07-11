#include "settings.h"
#include "ui_settings.h"

#include <QFontDialog>
#include <QColorDialog>

#include "utils.h"

Settings::Settings(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    this->setWindowTitle("Settings");
    this->setFixedSize(this->size());

    init_settings_form();
    refreshAll();
}

Settings::~Settings() {
    delete ui;
}

SettingsContext Settings::getSettingsContext() {
    return previous_context_;
}

void Settings::setSettingsContext(const SettingsContext& context) {
    previous_context_ = context;
    current_context_ = context;
    refreshAll();
}

void Settings::LineNumberCheckStateChanged(int) {
    current_context_.check_boxes_state.enable_line_number = ui->lineNumberCheckBox->isChecked();
}

void Settings::HighlightLineCheckStateChanged(int) {
    current_context_.check_boxes_state.enable_current_line_hihglight = ui->HighlightCurrentLineCheckBox->isChecked();
    refreshFontSectionColor();
}

void Settings::FontButtonClick() {
    bool ok = false;
    QFont new_font = QFontDialog::getFont(&ok,this);
    if (ok) {
        current_context_.font = new_font;
        refreshFontSectionFont();
    }
}

void Settings::TextColorButtonClick() {
    QColor text_color = QColorDialog::getColor(current_context_.text_color,this,"Text color");
    if (text_color.isValid()) {
        current_context_.text_color = text_color;
        refreshFontSectionColor();
    }
}

void Settings::SelectionColorButtonClick() {
    QColor selection_color = QColorDialog::getColor(current_context_.selection_color,this,"Text background color");
    if (selection_color.isValid()) {
        current_context_.selection_color = selection_color;
        refreshFontSectionColor();
    }
}

void Settings::EditorBackgroundColorButtonClick() {
    QColor background_color = QColorDialog::getColor(current_context_.selection_color,this,"Editor background color");
    if (background_color.isValid()) {
        current_context_.editor_background_color = background_color;
        refreshFontSectionColor();
    }
}

void Settings::CurrentLineHighlightColorButtonClick() {
    QColor background_color = QColorDialog::getColor(current_context_.selection_color,this,"Current line selection background color");
    if (background_color.isValid()) {
        current_context_.current_line_highlighting_selection_color = background_color;
        refreshFontSectionColor();
    }
}

void Settings::ApplyChanges() {
    previous_context_ = current_context_;
    this->hide();
    refreshAll();
    emit newContextApplied(previous_context_);
}

void Settings::CancelChanges() {
    current_context_ = previous_context_;
    this->hide();
    refreshAll();
}

void Settings::init_settings_form() {
    current_context_.font.setFamily(current_context_.font.defaultFamily());

    previous_context_ = current_context_;

    connect(ui->HighlightCurrentLineCheckBox,&QCheckBox::stateChanged,this,&Settings::HighlightLineCheckStateChanged);
    connect(ui->lineNumberCheckBox,&QCheckBox::stateChanged,this,&Settings::LineNumberCheckStateChanged);

    connect(ui->FontButton,&QPushButton::clicked,this,&Settings::FontButtonClick);

    connect(ui->textColorButton,&QPushButton::clicked,this,&Settings::TextColorButtonClick);
    connect(ui->selectionColorButton,&QPushButton::clicked,this,&Settings::SelectionColorButtonClick);
    connect(ui->TextEditBackgroundColorButton,&QPushButton::clicked,this,&Settings::EditorBackgroundColorButtonClick);
    connect(ui->lineSelectionColorPushButton,&QPushButton::clicked,this,&Settings::CurrentLineHighlightColorButtonClick);

    connect(ui->applyButton,&QPushButton::clicked,this,&Settings::ApplyChanges);
    connect(ui->cancelButton,&QPushButton::clicked,this,&Settings::CancelChanges);
}

void Settings::refreshAll() {
    refreshGeneralSection();
    refreshFontSectionFont();
    refreshFontSectionColor();
}

void Settings::refreshGeneralSection() {
    ui->lineNumberCheckBox->setChecked(current_context_.check_boxes_state.enable_line_number);
    ui->HighlightCurrentLineCheckBox->setChecked(current_context_.check_boxes_state.enable_current_line_hihglight);
}

void Settings::refreshFontSectionFont() {
    int pixelsize = current_context_.font.pointSize();
    QString font_name = current_context_.font.family();
    ui->FontButton->setText(QString("%1 | %2").arg(font_name,QString::number(pixelsize)));
}

void Settings::refreshFontSectionColor() {
    utils::setButtonBackgroundColor(current_context_.text_color,ui->textColorButton);
    utils::setButtonBackgroundColor(current_context_.selection_color,ui->selectionColorButton);
    utils::setButtonBackgroundColor(current_context_.editor_background_color,ui->TextEditBackgroundColorButton);
    ui->lineSelectionColorPushButton->setEnabled(current_context_.check_boxes_state.enable_current_line_hihglight);
    utils::setButtonBackgroundColor(current_context_.current_line_highlighting_selection_color,ui->lineSelectionColorPushButton);
}


