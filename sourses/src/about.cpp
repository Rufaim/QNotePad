#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("About");
}

About::~About()
{
    delete ui;
}
