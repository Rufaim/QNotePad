#include "line_number_widget.h"

#include "q_note_pad_editor.h"

LineNumberWidget::LineNumberWidget(QWidget *parent) : QWidget(parent) {
    parent_ = parent;
    max_number_ = 1;
}

QSize LineNumberWidget::sizeHint() const {
    return QSize(getWidth(),0);
}

void LineNumberWidget::updateNumber(int number) {
    max_number_ = qMax(number,1);
}

int LineNumberWidget::getWidth() const {
    int digits = 1;
    for (int max = max_number_; max>=10; max/=10){
        digits++;
    }
    int space = 3 + fontMetrics().horizontalAdvance("9") * digits;
    return space;
}

void LineNumberWidget::paintEvent(QPaintEvent *event) {
    static_cast<QNotePadEditor*>(parent_)->LineNumberWidgetPaintEvent(event);
}
