#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "gameengine.hh"
#include "graphicalhex.hh"

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


class Mainwindow : public QMainWindow
{
    Q_OBJECT
public:
    Mainwindow(QWidget *parent = 0);

protected:
    //void paintEvent(QPaintEvent *event);

private:
    void setupLayout();

    std::shared_ptr<Student::GameBoard> _board;
    std::shared_ptr<Student::GameState> _gameState;
    std::vector<std::shared_ptr<Common::IPlayer>> _players;
    std::shared_ptr<Logic::GameEngine> _gameEngine;

    int pawnCount;

    //Muuttujat joita käytetään nappien liikuttelussa
    std::shared_ptr<Common::Hex> selectedHex;
    std::shared_ptr<Common::Hex> moveTo;
    std::shared_ptr<Common::Pawn> selectedPawn;


public slots:
    void initializePlayers(int amount);
    void hexClick(std::shared_ptr<Common::Hex> chosenHex);
    void giveHexFrom(Common::CubeCoordinate coorTo);
signals:
    void deleteOldPawn(Common::CubeCoordinate,std::shared_ptr<Common::Pawn> pawnId,Common::CubeCoordinate coorTo);

};

#endif // MAINWINDOW_HH
