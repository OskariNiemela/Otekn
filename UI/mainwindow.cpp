#include "mainwindow.hh"



Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent),
      _board(std::make_shared<Student::GameBoard>()),
      _gameState(std::make_shared<Student::GameState>()),
      _gameEngine(nullptr),
      pawnCount(0)
      //_gameEngine(Logic::GameEngine(_board, _gameState, _players))
{
    //connect(_board.get(),&Student::GameBoard::hexClicked,this,&Mainwindow::hexClick);

}

void Mainwindow::initializePlayers(int amount)
{
    for(int a = 0;a<amount;a++)
    {
        std::shared_ptr<Common::IPlayer> newPlayer = std::make_shared<Student::Player>(a);
        _players.push_back(newPlayer);


    }
    _gameEngine = std::make_shared<Logic::GameEngine>(_board,_gameState,_players);
    for(auto player:_players)
    {
        int ID = player->getPlayerId();
        //TO DO: CREATE PAWN AND ADD IT TO THE 0,0,0 COORDINATES
        _board->addPawn(ID,pawnCount);
        pawnCount++;
    }

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

void Mainwindow::hexClick(std::shared_ptr<Common::Hex>)
{
    //TO DO: MAKE HEX CLICKS DO STUFF
}





