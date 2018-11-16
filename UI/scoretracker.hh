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
    void scorePlayer(int playerId);
public slots:
    void changePlayer(int currentPlayer);
    void initializeScores(int playerAmount);
    void changeGamePhase(Common::GamePhase phase);

private:
    int currPlayer;
    QLabel* playerTurn;
    QLabel* gamePhase;
    std::vector<int> playerScores;
    QVBoxLayout* layout;
    std::vector<QLabel*> playerLabels;

};


}


#endif // SCORETRACKER_HH