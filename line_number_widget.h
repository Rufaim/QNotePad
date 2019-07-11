#ifndef LINE_NUMBER_WIDGET_H
#define LINE_NUMBER_WIDGET_H

#include <QWidget>


class LineNumberWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LineNumberWidget(QWidget *parent = nullptr);

    QSize sizeHint() const;

    void updateNumber(int number);
    int getWidth() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    QWidget *parent_;

    int max_number_;
};

#endif // LINE_NUMBER_WIDGET_H
