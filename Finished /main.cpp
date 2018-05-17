#include "sudokuwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SudokuWidget w;
    w.show();

    return a.exec();
}
