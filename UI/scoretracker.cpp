#include "scoretracker.hh"

namespace Student
{

ScoreTracker::ScoreTracker():
    currPlayer(0),
    playerTurn(new QLabel(this)),
    gamePhase(new QLabel(this)),
    layout(new QVBoxLayout(this)),
    skipTurn(new QPushButton(this))
{
    changePlayer(0);
    skipTurn->setText("Skip Turn");
    setFrameStyle(QFrame::Box | QFrame::Sunken);
    //Size(QSize(100,100));
    //frameShadow(Sunken);
    layout->addWidget(playerTurn);
    layout->addWidget(gamePhase);
    layout->addWidget(skipTurn);
    connect(skipTurn,&QPushButton::clicked,this,&ScoreTracker::skipPlayerTurn);
}

ScoreTracker::~ScoreTracker()
{
    delete playerTurn;
    delete gamePhase;
    for(QLabel* label:playerLabels)
    {
        delete label;
    }
    delete layout;
}

void ScoreTracker::scorePlayer(int playerId)
{
    playerScores.at(playerId)++;
    //Make the text we want to display
    std::string scoreText = "Player " + std::to_string(playerId) + " score: " +
                            std::to_string(playerScores.at(playerId));
    QString scoreTextQ = QString::fromStdString(scoreText);
    playerLabels.at(playerId)->setText(scoreTextQ);
}

std::vector<int> ScoreTracker::getScores()
{
    return playerScores;
}

void ScoreTracker::displayWinner()
{
    for(auto a:playerLabels)
    {
        a->setText("");
    }
    std::string phaseText = "Congrats";
    QString phaseTextQ = QString::fromStdString(phaseText);
    gamePhase->setText(phaseTextQ);


    int player = -1;
    int maxScore = -1;
    int nowPlayer = 0;
    //Iterate through the player scores to compare which is the highest
    for(int a:playerScores)
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
    playerTurn->setText(playerTextQ);
}


void ScoreTracker::changePlayer(int currentPlayer)
{
    std::string playerText = "Player " + std::to_string(currentPlayer)
            + " Turn";
    QString playerTextQ = QString::fromStdString(playerText);
    playerTurn->setText(playerTextQ);
}


void ScoreTracker::initializeScores(int playerAmount)
{
    //Initializing the number of QLabels we need to display all the scores
    for(int i=0 ; i < playerAmount; ++i)
    {
        //The initial score is 0 for all players
        playerScores.push_back(0);
        //build the string that displays the player score
        std::string playerText = "Player " + std::to_string(i) + " score: " +
                std::to_string(0);
        QString playerTextQ = QString::fromStdString(playerText);
        //Make the necessary label and push it into a vector
        QLabel* playerLabel = new QLabel(this);
        playerLabel->setText(playerTextQ);
        playerLabels.push_back(playerLabel);
        layout->addWidget(playerLabel);
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
            skipTurn->setEnabled(true);
            break;
        }

        case Common::SINKING:
        {
            phaseText = "Phase: Sinking";
            skipTurn->setEnabled(false);
            break;
        }

        default:
        {
            phaseText = "Phase: Spinning";
            skipTurn->setEnabled(false);
            break;
        }

    }
    QString phaseTextQ = QString::fromStdString(phaseText);
    gamePhase->setText(phaseTextQ);
}
}
