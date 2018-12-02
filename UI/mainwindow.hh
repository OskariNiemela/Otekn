#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include "gamestate.hh"
#include "player.hh"
#include "gameengine.hh"
#include "graphicalhex.hh"
#include "ioexception.hh"
#include "formatexception.hh"
#include "gameexception.hh"
#include "initialize.hh"
#include "illegalmoveexception.hh"
#include "scoretracker.hh"
#include "wheellayoutparser.hh"
#include "graphicalwheel.hh"
#include "exceptionwindow.hh"

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
const int PLAYER_MOVES = 3;

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
    std::shared_ptr<Student::GameBoard> board_;
    std::shared_ptr<Student::GameState> gameState_;
    std::vector<std::shared_ptr<Common::IPlayer>> players_;
    std::shared_ptr<Common::IGameRunner> gameEngine_;
    std::shared_ptr<Student::ScoreTracker> trackingScore_;
    std::shared_ptr<Student::GraphicalWheel> wheel_;
    Common::SpinnerLayout wheelLayout_;

    // Variables that are used when moving pawns,actors and transports
    std::shared_ptr<Common::Hex> selectedHex_;
    std::shared_ptr<Common::Pawn> selectedPawn_;
    std::shared_ptr<Common::Actor> selectedActor_;
    std::shared_ptr<Common::Transport> selectedTransport_;
    std::pair<std::string,std::string> pair_;

    //Variables for showing the gameBoard
    QGraphicsScene* scene_;
    QWidget* widget_;
    QGraphicsView* gameView_;
    QGraphicsView* wheelView_;
    QGraphicsScene wheelScene_;
    bool wheelClicked_;

    QPushButton* increaseButton_ = new QPushButton();
    QPushButton* decreaseButton_ = new QPushButton();

    int pawnCount_ = 1;

    /**
     * @brief changes the player to the next one in line
     * @post exception guarantee: nothrow
     */
    void changePlayers();
    /**
     * @brief checks if the player has any pawns, if not
     * skip their turn
     * @post exception guarantee: nothrow
     */
    void checkPlayersPawns();

    /**
     * @brief Does the player turn when moving
     * @param hex we clicked
     * @post exception guarantee: nothrow
     */
    void playerTurnMovement(std::shared_ptr<Common::Hex> hex);
    /**
     * @brief Does the player turn when sinking tiles
     * @param Hex we want to sink
     * @post exception guarantee: nothrow
     */
    void playerTurnSinking(std::shared_ptr<Common::Hex> hex);
    /**
     * @brief Does the player turn when spinning the wheel
     * @param hex we've clicked
     * @post exception guarantee: nothrow
     */
    void playerTurnSpinning(std::shared_ptr<Common::Hex> hex);

<<<<<<< HEAD

    //Variables for showing the gameBoard
    QGraphicsScene* scene_;
    QWidget* widget_;
    QGraphicsView* gameView_;
    QGraphicsView* wheelView_;
    QGraphicsScene wheelScene_;
    bool wheelClicked_;

    QPushButton* increaseButton_ = new QPushButton();
    QPushButton* decreaseButton_ = new QPushButton();


=======
>>>>>>> d05906810540f49e43a84a2cf829afdb8fdd0d71
public slots:
    /**
     * @brief Initializes the game with the given amount of players
     * @param number of players
     * @post exception guarantee: basic
     */
    void initializeGame(int players);
    /**
     * @brief Run when a hex is clicked
     * @param pointer to hex that has been clicked
     * @post exception guarantee: nothrow
     */
    void hexClick(std::shared_ptr<Common::Hex> chosenHex);

    /**
     * @brief Run when we click the wheel to spin it
     * @post exception guarantee: nothrow
     */
    void wheelClick();

    /**
     * @brief Run when a player scores a point
     * @post exception guarantee: nothrow
     */
    void hexScore();

    /**
     * @brief skips the current players turn
     * @post exception guarantee: nothrow
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
