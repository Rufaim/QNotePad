#ifndef ABOUT_H
#define ABOUT_H

#include <QFrame>

namespace Ui {
class About;
}

class About : public QFrame
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

private:
    Ui::About *ui;
};

#endif // ABOUT_H
