#include "q_note_pad_editor.h"
#include "ui_q_note_pad_editor.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QCloseEvent>

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
    refreshWindowName();

    //TODO:
    // 1) document autosave
    // 2) settings save/load
    // 3) About
    // 4) line number
    // 5) line highlight
    // 6) redesign colors section
    // 7) add highligtedText color button
    // 8) text colored selection
    // 9) bold, italic, underline text
    // 10) ask about save when exit
}

QNotePadEditor::~QNotePadEditor()
{
    delete ui;
    delete settings_;
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

    connect(ui->actionAbout, &QAction::triggered,this,&QNotePadEditor::About);
}

void QNotePadEditor::init_settings_form() {
    QFontInfo info = ui->textEdit->fontInfo();
    settings_ = new Settings;

    SettingsContext init_context;
    init_context.font = ui->textEdit->font();
    QPalette pallete = ui->textEdit->palette();

    init_context.text_color = pallete.text().color();
    init_context.selection_color = pallete.highlight().color();
    init_context.editor_background_color = pallete.base().color();
    settings_->setSettingsContext(init_context);
    onSettingsContextChanged(init_context);

    connect(settings_,&Settings::newContextApplied,this,&QNotePadEditor::onSettingsContextChanged);
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

void QNotePadEditor::About() {
    //TODO: about section
}

void QNotePadEditor::onSettingsContextChanged(const SettingsContext &context) {
    ui->textEdit->setFont(context.font);
    QPalette palette = ui->textEdit->palette();
    palette.setColor(QPalette::Text,context.text_color);
    palette.setColor(QPalette::Highlight, context.selection_color);
    palette.setColor(QPalette::Base,context.editor_background_color);
    ui->textEdit->setPalette(palette);

    checkboxes_state_ = context.check_boxes_state;
}
