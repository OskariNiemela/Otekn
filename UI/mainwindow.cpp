#include "mainwindow.hh"

namespace Student
{



Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent),
      _board(new Student::GameBoard()),
      _gameState(std::make_shared<Student::GameState>()),
      _gameEngine(Logic::GameEngine(_board, _gameState, _players))
{
    QGraphicsView* gameView = _board->showScene();

    QHBoxLayout* hLayout = new QHBoxLayout(this);

    hLayout->addWidget(gameView);

    QVBoxLayout* vLayout = new QVBoxLayout(this);

    QColor colour(100,100,100);
    QPixmap colorMap(64,64);

    QLabel* label = new QLabel(this);

    colorMap.fill(colour);

    label->setPixmap(colorMap);

    vLayout->addWidget(label);


    hLayout->addLayout(vLayout);

    QWidget* widget = new QWidget();
    widget->setLayout(hLayout);
    widget->show();
}

void Mainwindow::initializePlayers(int amount)
{
    for(int a = 0;a<amount;a++)
    {
        std::shared_ptr<Common::IPlayer> newPlayer = std::make_shared<Student::Player>(a);
        _players.push_back(newPlayer);
    }
}
}




