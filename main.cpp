#include "mainwindow.h"
#include "settings.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    g_Config.init();

    MainWindow w;
    w.show();

    return a.exec();
}
