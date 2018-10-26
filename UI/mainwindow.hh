#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "gameengine.hh"
#include <QMainWindow>

class Mainwindow : public QMainWindow
{
    Q_OBJECT
public:
    Mainwindow(QWidget *parent = 0);

private:
    std::vector<Common::IPlayer*> _players;
    Logic::GameEngine _gameEngine;
};

#endif // MAINWINDOW_HH
