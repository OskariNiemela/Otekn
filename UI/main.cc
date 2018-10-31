#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "mainwindow.hh"
#include "startwindow.hh"


#include <memory>
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    startWindow startingInfo;

    startingInfo.exec();

    Mainwindow w;

    //w.show();
    return a.exec();
}
