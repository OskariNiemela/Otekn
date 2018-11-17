#include "mainwindow.hh"

namespace Student
{

Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent),
      _board(std::make_shared<Student::GameBoard>()),
      _gameState(std::make_shared<Student::GameState>()),
      _gameEngine(nullptr),
      pawnCount(1),
      selectedHex(nullptr),
      moveTo(nullptr),
      selectedPawn(nullptr),
      _trackingScore(std::make_shared<Student::ScoreTracker>()),
      _scene(new QGraphicsScene),
      _widget(nullptr)
      //_gameEngine(Logic::GameEngine(_board, _gameState, _players))
{
    _board->setScene(_scene);

    connect(this,&Mainwindow::updateHexes,
            _board.get(),&Student::GameBoard::updateHexes);

    connect(_board.get(),&Student::GameBoard::hexClicked,
            this,&Mainwindow::hexClick);

    //connect(_board.get(),&Student::GameBoard::getHexFrom,
    //        this,&Mainwindow::giveHexFrom);

    connect(_board.get(),&Student::GameBoard::hexScore,
            this,&Mainwindow::hexScore);
}

void Mainwindow::changePlayers(Common::GamePhase phase)
{
    switch(phase)
    {
        case Common::MOVEMENT:
            //Change player turn
            if (_gameEngine->playerAmount()-1 > _gameState->currentPlayer())
            {
                _gameState->changePlayerTurn(_gameState->currentPlayer()+1);
                _trackingScore->changePlayer(_gameState->currentPlayer());
                _players.at(_gameState->currentPlayer())->setActionsLeft(3);
            }
            else
            {
                _gameState->changeGamePhase(Common::SINKING);
                _trackingScore->changeGamePhase(_gameState->currentGamePhase());
                _gameState->changePlayerTurn(0);
                _trackingScore->changePlayer(_gameState->currentPlayer());
            }
        break;

        case Common::SINKING:
            if (_gameEngine->playerAmount()-1 > _gameState->currentPlayer())
            {
                _gameState->changePlayerTurn(_gameState->currentPlayer()+1);
                _trackingScore->changePlayer(_gameState->currentPlayer());
            }
            else
            {
                _gameState->changeGamePhase(Common::MOVEMENT);
                _trackingScore->changeGamePhase(_gameState->currentGamePhase());
                _gameState->changePlayerTurn(0);
                _trackingScore->changePlayer(_gameState->currentPlayer());
                _players.at(_gameState->currentPlayer())->setActionsLeft(3);
            }
        break;

        default:

        break;


    }

}

void Mainwindow::initializePlayers(int amount)
{
    for(int a = 0;a<amount;a++)
    {
        std::shared_ptr<Common::IPlayer> newPlayer =
                std::make_shared<Student::Player>(a);

        _players.push_back(newPlayer);
    }

    _gameEngine = Common::Initialization::getGameRunner(_board,_gameState,_players);

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


    _trackingScore->changeGamePhase(_gameState->currentGamePhase());
    _trackingScore->initializeScores(_gameEngine->playerAmount());
    vLayout->addWidget(_trackingScore.get());


    hLayout->addLayout(vLayout);

    _widget = new QWidget();
    _widget->setLayout(hLayout);
    _widget->show();
}

void Mainwindow::hexClick(std::shared_ptr<Common::Hex> chosenHex)
{

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
            emit updateHexes();
        }
        else
        {
            //If we already have a hex selected
            if(chosenHex == selectedHex)
            {
                return;
            }
            try
            {
                //Move the pawn while setting the actions left of the player
                _players.at(_gameState->currentPlayer())->setActionsLeft(static_cast<unsigned int>(_gameEngine->movePawn(selectedHex->getCoordinates(),chosenHex->getCoordinates(),selectedPawn->getId())));
                selectedHex = nullptr;
                selectedPawn = nullptr;
                if(_players.at(_gameState->currentPlayer())->getActionsLeft() <= 0)
                {
                    changePlayers(_gameState->currentGamePhase());

                }
            }
            catch(Common::IllegalMoveException i)
            {
                std::cout<<i.msg()<<std::endl;
            }


        }
    }
    else if (_gameState->currentGamePhase()==Common::SINKING)
    {
        try
        {
            _gameEngine->flipTile(chosenHex->getCoordinates());
            _board->flipTile(chosenHex->getCoordinates());
            //Change player turn

            changePlayers(_gameState->currentGamePhase());

        }
        catch (Common::IllegalMoveException i)
        {
            std::cout<<i.msg()<<std::endl;
        }
    }
    else
    {

    }
    emit updateHexes();
}



void Mainwindow::hexScore()
{
    _trackingScore->scorePlayer(_gameEngine->currentPlayer());
}


}
