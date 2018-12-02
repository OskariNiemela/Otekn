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


    Student::StartWindow* startingInfo = new Student::StartWindow;

    Student::Mainwindow* w = new Student::Mainwindow;

    QObject::connect(startingInfo, &Student::StartWindow::sendValue,
                     w, &Student::Mainwindow::initializeGame);

    startingInfo->exec();

    return a.exec();
}
