#ifndef SCORETRACKER_HH
#define SCORETRACKER_HH

#include "igamestate.hh"

#include <QFrame>
#include <QLabel>
#include <QString>
#include <vector>
#include <string>
#include <QVBoxLayout>
#include <QPushButton>

namespace Student
{
class ScoreTracker : public QFrame
{
     Q_OBJECT
public:
    ScoreTracker();
    ~ScoreTracker();
    /**
     * @brief Increases player score by one
     * @param id of the player whose score we want to increase
     * @post player score increased by one, Exception Guarantee: no throw
     */
    void scorePlayer(int playerId);
    /**
     * @brief Gives the playerscores in a vector
     * @return Returns the player scores in a vector
     * @post exception guarantee: nothrow
     */
    std::vector<int> getScores();
    /**
     * @brief displays the winner of the game
     * @post exception guarantee: basic
     */
    void displayWinner();
public slots:
    /**
     * @brief change the player turn text
     * @param player number we want to change to
     */
    void changePlayer(int currentPlayer);
    /**
     * @brief Initializes the player score labels
     * @param how many players there are
     * @post exception guarantee: basic
     */
    void initializeScores(int playerAmount);
    /**
     * @brief change the displayed game phase
     * @param phase to change to
     * @post exception guarantee: no throw
     */
    void changeGamePhase(Common::GamePhase phase);
signals:
    /**
     * @brief signal we send when the skip turn button is pressed
     */
    void skipPlayerTurn();

private:
    int currPlayer;
    QLabel* playerTurn;
    QLabel* gamePhase;
    std::vector<int> playerScores;
    QVBoxLayout* layout;
    QPushButton* skipTurn;
    std::vector<QLabel*> playerLabels;


};


}


#endif // SCORETRACKER_HH
