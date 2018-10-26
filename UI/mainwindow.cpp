#include "mainwindow.hh"

Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent), _gameEngine(Logic::GameEngine(std::make_shared<GameBoard>(), std::make_shared<GameState>(), _players))
{

}

