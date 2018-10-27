#include "mainwindow.hh"

Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent),
      _board(std::make_shared<GameBoard>()),
      _gameState(std::make_shared<GameState>()),
      _gameEngine(Logic::GameEngine(_board, _gameState, _players))
{

}

void Mainwindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
    painter.drawLine(0,0,200,200);
}




