#include "mainwindowlifegame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowLifeGame w;
    w.show();
    return a.exec();
}
