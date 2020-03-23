#include <QtWidgets/QApplication>

#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
    Run r(NBR_OF_RUNS_GAME);        // create run
    QApplication a(argc, argv);
    MainWindow w;
    w.InitGames(&r);                // run and other values
    w.show();

    return a.exec();
}
