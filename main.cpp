#include "q_note_pad_editor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QNotePadEditor w;
    w.show();

    return a.exec();
}
