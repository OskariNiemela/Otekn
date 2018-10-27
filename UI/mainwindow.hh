#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "gameengine.hh"
#include <QMainWindow>
#include <QPolygon>
#include <QVector>
#include <QPoint>
#include <QPainter>
#include <QPen>
#include <QFrame>
#include <QPainterPath>
#include <QtGui>

class Mainwindow : public QMainWindow
{
    Q_OBJECT
public:
    Mainwindow(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void setupLayout();

    std::shared_ptr<GameBoard> _board;
    std::shared_ptr<GameState> _gameState;
    std::vector<Common::IPlayer*> _players;
    Logic::GameEngine _gameEngine;

};

#endif // MAINWINDOW_HH
