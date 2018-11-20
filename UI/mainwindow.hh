#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "gameengine.hh"
#include "graphicalhex.hh"
#include "ioexception.hh"
#include "gameexception.hh"
#include "initialize.hh"
#include "illegalmoveexception.hh"
#include "scoretracker.hh"

#include <iostream>
#include <QMainWindow>
#include <QPolygon>
#include <QVector>
#include <QPoint>
#include <QPainter>
#include <QPen>
#include <QFrame>
#include <QPainterPath>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QVBoxLayout>
//Testailuun
#include <QLabel>
#include <QPixmap>

namespace Student
{
class Mainwindow : public QMainWindow
{
    Q_OBJECT
public:
    Mainwindow(QWidget *parent = 0);
    ~Mainwindow();
protected:
    //void paintEvent(QPaintEvent *event);

private:
    void setupLayout();

    std::shared_ptr<Student::GameBoard> _board;
    std::shared_ptr<Student::GameState> _gameState;
    std::vector<std::shared_ptr<Common::IPlayer>> _players;
    std::shared_ptr<Common::IGameRunner> _gameEngine;
    std::shared_ptr<Student::ScoreTracker> _trackingScore;


    int pawnCount;

    //Muuttujat joita käytetään nappien liikuttelussa
    std::shared_ptr<Common::Hex> selectedHex;
    std::shared_ptr<Common::Pawn> selectedPawn;


    void changePlayers(Common::GamePhase phase);

    //Variables for showing the gameBoard
    QGraphicsScene* _scene;
    QWidget* _widget;
    QGraphicsView* _gameView;

public slots:
    void initializePlayers(int amount);
    void hexClick(std::shared_ptr<Common::Hex> chosenHex);

    void hexScore();
signals:
    void updateHexes();
};


}

#endif // MAINWINDOW_HH
