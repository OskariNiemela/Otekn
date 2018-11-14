#include "scoretracker.hh"

namespace Student
{

ScoreTracker::ScoreTracker():
    currPlayer(0),
    playerTurn(new QLabel(this)),
    layout(new QVBoxLayout(this)),
    gamePhase(new QLabel(this))
{
    changePlayer(0);
    setFrameStyle(QFrame::Box | QFrame::Sunken);
    //Size(QSize(100,100));
    //frameShadow(Sunken);
    layout->addWidget(playerTurn);
    layout->addWidget(gamePhase);

}


void ScoreTracker::changePlayer(int currentPlayer)
{
    std::string playerText = "Player " + std::to_string(currentPlayer) +" Turn";
    QString playerTextQ = QString::fromStdString(playerText);
    playerTurn->setText(playerTextQ);
}


void ScoreTracker::initializeScores(int playerAmount)
{
    for(int i=0;i<playerAmount;i++)
    {
        playerScores.push_back(0);
        std::string playerText = "Player " + std::to_string(i) +" score: " + std::to_string(0);
        QString playerTextQ = QString::fromStdString(playerText);
        QLabel* playerLabel = new QLabel(this);
        playerLabel->setText(playerTextQ);
        playerLabels.push_back(playerLabel);
        layout->addWidget(playerLabel);
    }
}

void ScoreTracker::changeGamePhase(Common::GamePhase phase)
{
    switch (phase)
    {
        case Common::MOVEMENT:
        {
            std::string phaseText = "Phase: Movement";
            QString phaseTextQ = QString::fromStdString(phaseText);
            gamePhase->setText(phaseTextQ);
            break;
        }



        case Common::SINKING:
        {
            std::string phaseText = "Phase: Sinking";
            QString phaseTextQ = QString::fromStdString(phaseText);
            gamePhase->setText(phaseTextQ);

            break;
        }


        case Common::SPINNING:
        {
            std::string phaseText = "Phase: Spinning";
            QString phaseTextQ = QString::fromStdString(phaseText);
            gamePhase->setText(phaseTextQ);
            break;
        }

    }
}
}
