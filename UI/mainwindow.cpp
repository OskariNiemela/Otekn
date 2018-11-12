#include "mainwindow.hh"



Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent),
      _board(std::make_shared<Student::GameBoard>()),
      _gameState(std::make_shared<Student::GameState>()),
      _gameEngine(nullptr),
      pawnCount(1),
      selectedHex(nullptr),
      moveTo(nullptr),
      selectedPawn(nullptr)
      //_gameEngine(Logic::GameEngine(_board, _gameState, _players))
{
    connect(_board.get(),&Student::GameBoard::hexClicked,this,&Mainwindow::hexClick);
    connect(_board.get(),&Student::GameBoard::getHexFrom,this,&Mainwindow::giveHexFrom);
    connect(this,&Mainwindow::deleteOldPawn,_board.get(),&Student::GameBoard::deleteOldPawn);
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

void Mainwindow::hexClick(std::shared_ptr<Common::Hex> chosenHex)
{
    //TO DO: MAKE HEX CLICKS DO STUFF
    if(_gameState->currentGamePhase() == Common::MOVEMENT)
    {
        if (selectedHex == nullptr)
        {
            selectedHex = chosenHex;
            int currentPlayer = _gameState->currentPlayer();
            //Find a pawn belonging to the current player
            selectedPawn = _board->getPlayerPawn(selectedHex->getCoordinates(),currentPlayer);
            if (selectedPawn == nullptr)
            {

                selectedHex = nullptr;
            }
            else
            {
                _board->setSelected(selectedHex->getCoordinates());
            }
        }
        else
        {
            //If we already have a hex selected
            _gameEngine->movePawn(selectedHex->getCoordinates(),chosenHex->getCoordinates(),selectedPawn->getId());

        }
    }
}

void Mainwindow::giveHexFrom(Common::CubeCoordinate coorTo)
{
    Common::CubeCoordinate coord = selectedHex->getCoordinates();
    _board->deSelect(selectedHex->getCoordinates());
    emit deleteOldPawn(coord,selectedPawn,coorTo);

    selectedHex = nullptr;
    selectedPawn = nullptr;
}





