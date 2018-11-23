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
#include "wheellayoutparser.hh"
#include "graphicalwheel.hh"

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
    /**
     * @brief Constructor that initializes vartiables
     */
    explicit Mainwindow(QWidget *parent = 0);
    /**
     * @brief destructor that destroys raw pointers
     */
    ~Mainwindow();
protected:


private:
    std::shared_ptr<Student::GameBoard> _board;
    std::shared_ptr<Student::GameState> _gameState;
    std::vector<std::shared_ptr<Common::IPlayer>> _players;
    std::shared_ptr<Common::IGameRunner> _gameEngine;
    std::shared_ptr<Student::ScoreTracker> _trackingScore;
    std::shared_ptr<Student::GraphicalWheel> _wheel;


    int pawnCount;

    //Muuttujat joita käytetään nappien liikuttelussa
    std::shared_ptr<Common::Hex> selectedHex;
    std::shared_ptr<Common::Pawn> selectedPawn;
    std::shared_ptr<Common::Actor> selectedActor;
    std::pair<std::string,std::string> _pair;

    void changePlayers(Common::GamePhase phase);
    void checkPlayersPawns();
    void checkPawnValidity();

    //Variables for showing the gameBoard
    QGraphicsScene* _scene;
    QWidget* _widget;
    QGraphicsView* _gameView;
    QGraphicsView* _wheelView = new QGraphicsView();
    QGraphicsScene _wheelScene;
    bool wheelClicked;

public slots:
    /**
     * @brief Initializes the game with the given amount of players
     * @param number of players
     */
    void initializeGame(int players);
    /**
     * @brief Run when a hex is clicked
     * @param pointer to hex that has been clicked
     */
    void hexClick(std::shared_ptr<Common::Hex> chosenHex);

    /**
     * @brief Run when we click the wheel to spin it
     */
    void wheelClick();

    /**
     * @brief Run when a player scores a point
     */
    void hexScore();

    /**
     * @brief skips the current players turn
     */
    void skipPlayerTurn();
signals:
    /**
     * @brief updates the graphical hexes
     */
    void updateHexes();
};


}

#endif // MAINWINDOW_HH
