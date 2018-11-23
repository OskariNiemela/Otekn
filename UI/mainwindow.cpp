#include "mainwindow.hh"

namespace Student
{

Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent),
      _board(std::make_shared<Student::GameBoard>()),
      _gameState(std::make_shared<Student::GameState>()),
      _gameEngine(nullptr),
      _trackingScore(std::make_shared<Student::ScoreTracker>()),
      pawnCount(1),
      selectedHex(nullptr),
      selectedPawn(nullptr),
      _scene(new QGraphicsScene),
      _widget(nullptr),
      _gameView(nullptr),
      _wheel(std::make_shared<Student::GraphicalWheel>()),
      wheelClicked(false)
{
    _board->setScene(_scene);

    connect(this,&Mainwindow::updateHexes,
            _board.get(),&Student::GameBoard::updateHexes);

    connect(_board.get(),&Student::GameBoard::hexClicked,
            this,&Mainwindow::hexClick);

    connect(_board.get(),&Student::GameBoard::hexScore,
            this,&Mainwindow::hexScore);

    connect(_wheel.get(),&Student::GraphicalWheel::wheelClicked,
            this, &Mainwindow::wheelClick);
    connect(_trackingScore.get(),&Student::ScoreTracker::skipPlayerTurn,
            this, &Mainwindow::skipPlayerTurn);
}

Mainwindow::~Mainwindow()
{
    delete _scene;
    delete _widget;
    delete _gameView;
}



void Mainwindow::changePlayers()
{
    if(!_board->anyPawnsIngame())
    {
        _trackingScore->displayWinner();
        return;
    }
    Common::GamePhase phase = _gameState->currentGamePhase();
    switch(phase)
    {
        case Common::MOVEMENT:
            //Change player turn
            //Check that the next player exists
            if (_gameEngine->playerAmount()-1 > _gameState->currentPlayer())
            {
                _gameState->changePlayerTurn(_gameState->currentPlayer()+1);

                //Update the player display
                _trackingScore->changePlayer(_gameState->currentPlayer());
                _players.at(_gameState->currentPlayer())->setActionsLeft(3);
            }
            //If they dont exist, that means we need to change the gamephase
            else
            {
                //If were on the last players turn, change the phase
                _gameState->changeGamePhase(Common::SINKING);
                //Change the displayed game phase
                _trackingScore->changeGamePhase(_gameState->currentGamePhase());
                _gameState->changePlayerTurn(0);
                _trackingScore->changePlayer(_gameState->currentPlayer());
                break;
            }

            checkPlayersPawns();

        break;

        case Common::SINKING:
            if (_gameEngine->playerAmount()-1 > _gameState->currentPlayer())
            {

                _gameState->changePlayerTurn(_gameState->currentPlayer()+1);
                _trackingScore->changePlayer(_gameState->currentPlayer());
            }
            else
            {
                _gameState->changeGamePhase(Common::SPINNING);
                _trackingScore->changeGamePhase(_gameState->currentGamePhase());
                _gameState->changePlayerTurn(0);
                _trackingScore->changePlayer(_gameState->currentPlayer());

            }
        break;

        default:
            if (_gameEngine->playerAmount()-1 > _gameState->currentPlayer())
            {
                _gameState->changePlayerTurn(_gameState->currentPlayer()+1);
                _trackingScore->changePlayer(_gameState->currentPlayer());
            }
            else
            {
                _gameState->changePlayerTurn(0);
                _players.at(_gameState->currentPlayer())->setActionsLeft(3);
                _gameState->changeGamePhase(Common::MOVEMENT);
                _trackingScore->changePlayer(_gameState->currentPlayer());
                _trackingScore->changeGamePhase(_gameState->currentGamePhase());

                checkPlayersPawns();
            }
        break;


    }

}


void Mainwindow::checkPlayersPawns()
{
    //While the current player has no pawns
    while(!_board->playerHasPawns(_gameState->currentPlayer()))
    {
        //Change the player until we either find a player with pawns
        if (_gameEngine->playerAmount()-1 > _gameState->currentPlayer())
        {
            _gameState->changePlayerTurn(_gameState->currentPlayer()+1);
            _trackingScore->changePlayer(_gameState->currentPlayer());
            _players.at(_gameState->currentPlayer())->setActionsLeft(3);
        }
        //Or we change the gamephase
        else
        {
            _gameState->changeGamePhase(Common::SINKING);
            _trackingScore->changeGamePhase(_gameState->currentGamePhase());
            _gameState->changePlayerTurn(0);
            _trackingScore->changePlayer(_gameState->currentPlayer());
            break;
        }
    }
}

void Mainwindow::playerTurnMovement(std::shared_ptr<Common::Hex> hex)
{
    if (selectedHex == nullptr)
    {
        selectedHex = hex;
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
    //If we already have a hex selected
    else
    {
        //If we clicked the same hex as we have selected, unselect it
        if(hex == selectedHex)
        {
            _board->deSelect(selectedHex->getCoordinates());
            selectedHex = nullptr;
            selectedPawn = nullptr;
            return;
        }
        try
        {
            //Move the pawn
            _gameEngine->movePawn(selectedHex->getCoordinates(),hex->getCoordinates(),selectedPawn->getId());
            //Reset the selectedhex and selected pawn pointers
            selectedHex = nullptr;
            selectedPawn = nullptr;
            //If the player has no actions left
            if(_players.at(_gameState->currentPlayer())->getActionsLeft() <= 0)
            {
                changePlayers();

            }
        }
        catch(Common::IllegalMoveException &exception)
        {
            std::cout<<exception.msg()<<std::endl;
        }
    }
}

void Mainwindow::playerTurnSinking(std::shared_ptr<Common::Hex> hex)
{
    try
    {
        //Try to flip the chosen tile
        _gameEngine->flipTile(hex->getCoordinates());

        _board->flipTile(hex->getCoordinates());
        //Change player turn
        _board->checkPawnValidity();
        changePlayers();
        _board->checkActorValidity();

    }
    catch (Common::IllegalMoveException &exception)
    {
        std::cout<<exception.msg()<<std::endl;
    }
}

void Mainwindow::playerTurnSpinning(std::shared_ptr<Common::Hex> hex)
{
    //If we have clicked the wheel already
    if (selectedHex == nullptr && wheelClicked)
    {
        selectedHex = hex;
        //Find a pawn belonging to the current player
        selectedActor = _board->getActor(selectedHex->getCoordinates(),_pair.first);
        if (selectedActor == nullptr)
        {

            selectedHex = nullptr;
        }
        else
        {
            _board->setSelected(selectedHex->getCoordinates());
        }
    }
    else if(wheelClicked)
    {
        //If we already have a hex selected
        if(hex == selectedHex)
        {
            _board->deSelect(selectedHex->getCoordinates());
            selectedHex = nullptr;
            selectedActor= nullptr;
            return;
        }
        try
        {
            _gameEngine->moveActor(selectedHex->getCoordinates(),
                                   hex->getCoordinates(),
                                   selectedActor->getId(),
                                   _pair.second);
            _board->deSelect(selectedHex->getCoordinates());
            selectedHex = nullptr;
            selectedActor = nullptr;
            wheelClicked = false;
            //We need to check the pawn validity of the pawns in the gameboards
            //game pawns, because they could be eaten by the actors
            _board->checkPawnValidity();
            changePlayers();

        }
        catch (Common::IllegalMoveException &exception)
        {
            std::cout<<exception.msg()<<std::endl;
        }

    }
    //If we've not clicked the wheel yet to determine which actor to move
    else
    {
        std::cout<<"Please spin the wheel before trying to move actors"<<std::endl;
    }
}

void Mainwindow::initializeGame(int players)
{
    // Setup players
    for(int a = 0;a<players;a++)
    {
        std::shared_ptr<Common::IPlayer> newPlayer =
                std::make_shared<Student::Player>(a);

        _players.push_back(newPlayer);
    }

    // Now the game engine can be initialized
    _gameEngine = Common::Initialization::getGameRunner(_board,_gameState,_players);


    for(auto player:_players)
    {
        int ID = player->getPlayerId();
        _board->addPawn(ID,pawnCount);
        pawnCount++;
    }

    // Initialize the wheel
    _wheelLayout = _gameEngine->getSpinnerLayout();
    _wheel->initializeSegments(_wheelLayout);
    _wheelScene.addItem(_wheel.get());
    _wheelView->setScene(&_wheelScene);

    _gameView = _board->showScene();
    QHBoxLayout* hLayout = new QHBoxLayout(this);

    hLayout->addWidget(_gameView);

    QVBoxLayout* vLayout = new QVBoxLayout(this);


    _trackingScore->changeGamePhase(_gameState->currentGamePhase());
    _trackingScore->initializeScores(_gameEngine->playerAmount());
    vLayout->addWidget(_trackingScore.get());

    // add the wheel to the UI
    vLayout->addWidget(_wheelView);


    hLayout->addLayout(vLayout);

    _widget = new QWidget();
    _widget->setLayout(hLayout);
    _widget->show();
    emit updateHexes();
}

void Mainwindow::hexClick(std::shared_ptr<Common::Hex> chosenHex)
{

    if(_gameState->currentGamePhase() == Common::MOVEMENT)
    {
        playerTurnMovement(chosenHex);
    }
    else if (_gameState->currentGamePhase()==Common::SINKING)
    {
        playerTurnSinking(chosenHex);
    }
    else
    {
        playerTurnSpinning(chosenHex);
    }
    emit updateHexes();
}

void Mainwindow::wheelClick()
{
    if(_gameState->currentGamePhase() == Common::SPINNING && !wheelClicked)
    {
        _pair = _gameEngine->spinWheel();
        _wheel->setValue(_pair);
        _wheel->update();


        //Check if there is even an actor of the given type
        if(!_board->checkActor(_pair.first))
        {
            changePlayers();
            return;
        }
        //we have clicked the wheel, this ensures a player cant click the wheel twice
        //in one turn.
        wheelClicked = true;
    }

}



void Mainwindow::hexScore()
{
    _trackingScore->scorePlayer(_gameEngine->currentPlayer());
}

void Mainwindow::skipPlayerTurn()
{
    changePlayers();
}


}
