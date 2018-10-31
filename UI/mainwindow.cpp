#include "mainwindow.hh"

Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent),
      _board(std::make_shared<GameBoard>()),
      _gameState(std::make_shared<GameState>()),
      _gameEngine(Logic::GameEngine(_board, _gameState, _players))
{
    _board->showScene();
}





