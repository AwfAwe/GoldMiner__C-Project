#include "app.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    app GoldMiner_app;
    GoldMiner_app.run();
    return a.exec();
}
