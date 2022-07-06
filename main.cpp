#include "mainwindow.h"
#include ".\view\view.h"
#include ".\view\start_page_view.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    start_page_view w;

    w.show();
    return a.exec();
}
