/* Oskari Niemelä 263440
 * Aki Kaipio 267041
 *
 * Implementation of the ScoreTracker class
 */

#include "scoretracker.hh"

namespace Student
{

ScoreTracker::ScoreTracker():
    playerTurn_(new QLabel(this)),
    gamePhase_(new QLabel(this)),
    layout_(new QVBoxLayout(this)),
    skipTurn_(new QPushButton(this))
{
    changePlayer(0);
    skipTurn_->setText("Skip Turn");
    setFrameStyle(QFrame::Box | QFrame::Sunken);
    layout_->addWidget(playerTurn_);
    layout_->addWidget(gamePhase_);
    layout_->addWidget(skipTurn_);
    connect(skipTurn_,&QPushButton::clicked,this,&ScoreTracker::skipPlayerTurn);
}

ScoreTracker::~ScoreTracker()
{
    delete playerTurn_;
    delete gamePhase_;
    for(QLabel* label : playerLabels_)
    {
        delete label;
    }
    delete layout_;
}

void ScoreTracker::scorePlayer(int playerId)
{
    playerScores_.at(playerId);
    // Make the text we want to display
    std::string scoreText = "Player " + std::to_string(playerId) + " score: " +
                            std::to_string(playerScores_.at(playerId));
    QString scoreTextQ = QString::fromStdString(scoreText);
    playerLabels_.at(playerId)->setText(scoreTextQ);
}

std::vector<int> ScoreTracker::getScores()
{
    return playerScores_;
}

void ScoreTracker::displayWinner()
{
    for(auto a:playerLabels_)
    {
        a->setText("");
    }
    std::string phaseText = "Congrats";
    QString phaseTextQ = QString::fromStdString(phaseText);
    gamePhase_->setText(phaseTextQ);


    int player = -1;
    int maxScore = -1;
    int nowPlayer = 0;

    // Iterate through the player scores to compare which is the highest
    for(int a:playerScores_)
    {
        if(a>maxScore)
        {
            maxScore = a;
            player = nowPlayer;
        }

        ++nowPlayer;
    }
    std::string playerText = "Player " + std::to_string(player) + " Wins";
    QString playerTextQ = QString::fromStdString(playerText);
    playerTurn_->setText(playerTextQ);
}


void ScoreTracker::changePlayer(int currentPlayer)
{
    std::string playerText = "Player " + std::to_string(currentPlayer)
            + " Turn";
    QString playerTextQ = QString::fromStdString(playerText);
    playerTurn_->setText(playerTextQ);
}


void ScoreTracker::initializeScores(int playerAmount)
{
    //Initializing the number of QLabels we need to display all the scores
    for(int i=0 ; i < playerAmount; ++i)
    {
        //The initial score is 0 for all players
        playerScores_.push_back(0);
        //build the string that displays the player score
        std::string playerText = "Player " + std::to_string(i) + " score: " +
                std::to_string(0);
        QString playerTextQ = QString::fromStdString(playerText);
        //Make the necessary label and push it into a vector
        QLabel* playerLabel = new QLabel(this);
        playerLabel->setText(playerTextQ);
        playerLabels_.push_back(playerLabel);
        layout_->addWidget(playerLabel);
    }
}

void ScoreTracker::changeGamePhase(Common::GamePhase phase)
{
    //Switch the phase text based on the current gamephase
    std::string phaseText;
    switch (phase)
    {
        case Common::MOVEMENT:
        {
            phaseText = "Phase: Movement";
            skipTurn_->setEnabled(true);
            break;
        }

        case Common::SINKING:
        {
            phaseText = "Phase: Sinking";
            skipTurn_->setEnabled(false);
            break;
        }

        default:
        {
            phaseText = "Phase: Spinning";
            skipTurn_->setEnabled(false);
            break;
        }

    }
    QString phaseTextQ = QString::fromStdString(phaseText);
    gamePhase_->setText(phaseTextQ);
}


}
