#include "mainwindow.hh"

namespace Student
{

Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent),
      board_(std::make_shared<Student::GameBoard>()),
      gameState_(std::make_shared<Student::GameState>()),
      gameEngine_(nullptr),
      trackingScore_(std::make_shared<Student::ScoreTracker>()),
      wheel_(std::make_shared<Student::GraphicalWheel>()),

      selectedHex_(nullptr),
      selectedPawn_(nullptr),
      selectedActor_(nullptr),
      selectedTransport_(nullptr),

      scene_(new QGraphicsScene),
      widget_(nullptr),
      gameView_(nullptr),
      wheelView_(new QGraphicsView),
      wheelClicked_(false),
      increaseButton_(new QPushButton),
      decreaseButton_(new QPushButton)
{
    board_->setScene(scene_);

    connect(this,&Mainwindow::updateHexes,
            board_.get(),&Student::GameBoard::updateHexes);

    connect(board_.get(),&Student::GameBoard::hexClicked,
            this,&Mainwindow::hexClick);

    connect(board_.get(),&Student::GameBoard::hexScore,
            this,&Mainwindow::hexScore);

    connect(wheel_.get(),&Student::GraphicalWheel::wheelClicked,
            this, &Mainwindow::wheelClick);

    connect(trackingScore_.get(),&Student::ScoreTracker::skipPlayerTurn,
            this, &Mainwindow::skipPlayerTurn);

    connect(increaseButton_, &QPushButton::clicked,
            board_.get(), &Student::GameBoard::zoomIn);

    connect(decreaseButton_, &QPushButton::clicked,
            board_.get(), &Student::GameBoard::zoomOut);
}

Mainwindow::~Mainwindow()
{
    delete scene_;
    delete widget_;
    delete gameView_;
}



void Mainwindow::changePlayers()
{
    //If there are no pawns in the game anymore, end the game
    if(!board_->anyPawnsIngame())
    {
        trackingScore_->displayWinner();
        return;
    }

    Common::GamePhase phase = gameState_->currentGamePhase();

    //If there are more players whose turns we need to go to
    if((gameEngine_->playerAmount()-1) > (gameState_->currentPlayer()))
    {
        gameState_->changePlayerTurn(gameState_->currentPlayer()+1);
       if(phase == Common::MOVEMENT)
       {
           checkPlayersPawns();
       }
    }
    // If we need to change the gameState, since we've gone through
    // all the needed player turns
    else
    {
        gameState_->changePlayerTurn(0);
        switch(phase)
        {
            case Common::MOVEMENT:
                gameState_->changeGamePhase(Common::SINKING);
            break;

            case Common::SINKING:
                gameState_->changeGamePhase(Common::SPINNING);
            break;

            default:
                gameState_->changeGamePhase(Common::MOVEMENT);
                checkPlayersPawns();
            break;

        }
    }
    trackingScore_->changeGamePhase(gameState_->currentGamePhase());
    trackingScore_->changePlayer(gameState_->currentPlayer());

}


void Mainwindow::checkPlayersPawns()
{
    players_.at(gameState_->currentPlayer())->setActionsLeft(PLAYER_MOVES);
    //While the current player has no pawns
    while(!board_->playerHasPawns(gameState_->currentPlayer()))
    {
        //Change the player until we either find a player with pawns
        if ((gameEngine_->playerAmount()-1) > (gameState_->currentPlayer()))
        {
            gameState_->changePlayerTurn(gameState_->currentPlayer()+1);
            trackingScore_->changePlayer(gameState_->currentPlayer());
            players_.at(gameState_->currentPlayer())->setActionsLeft(PLAYER_MOVES);
        }
        //Or we change the gamephase
        else
        {
            gameState_->changeGamePhase(Common::SINKING);
            break;
        }
    }
}

void Mainwindow::playerTurnMovement(std::shared_ptr<Common::Hex> hex)
{
    //If selectedHex_ is null, that means we havent chosen a pawn/transport yet
    if (selectedHex_ == nullptr)
    {
        selectedHex_ = hex;
        int currentPlayer = gameState_->currentPlayer();
        //Find a pawn belonging to the current player
        selectedPawn_ = board_->getPlayerPawn(selectedHex_->getCoordinates()
                                              ,currentPlayer);
        if (selectedPawn_ == nullptr)
        {

            selectedHex_ = nullptr;
        }
        else
        {
            board_->setSelected(selectedHex_->getCoordinates());
        }
    }
    //If we already have a hex selected
    else
    {
        //If we clicked the same hex as we have selected, unselect it
        if(hex == selectedHex_)
        {
            board_->deSelect(selectedHex_->getCoordinates());
            selectedHex_ = nullptr;
            selectedPawn_ = nullptr;
            return;
        }
        try
        {
            bool moved = false;

            // Check if there is a transport in the source hex
            std::vector<std::shared_ptr<Common::Transport>> transports
                    = selectedHex_->getTransports();
            for (auto transport : transports) {
                try {
                    // Player exits the transport
                    if (hex->getPieceType() != "Water") {
                        transport->removePawn(selectedPawn_);
                        gameEngine_->movePawn(selectedHex_->getCoordinates(),
                                              hex->getCoordinates(),selectedPawn_->getId());
                    }
                    // Player moves the transport
                    else {
                        gameEngine_->moveTransport(selectedHex_->getCoordinates()
                                                   ,hex->getCoordinates(),
                                                   transport->getId());
                    }
                } catch (Common::IllegalMoveException &exception) {
                    std::cout << exception.msg() << std::endl;
                }
                moved = true;
                break;
            }

            // No transport, so move a pawn normally
            if (!moved) {
                gameEngine_->movePawn(selectedHex_->getCoordinates(),
                                      hex->getCoordinates(),selectedPawn_->getId());

                // Check if the pawn moved into a transport
                std::vector<std::shared_ptr<Common::Transport>> targetTransports
                        = hex->getTransports();
                for (auto transport : targetTransports) {

                    // Add pawn into the first transport
                    transport->addPawn(hex->givePawn(selectedPawn_->getId()));
                    break;
                }
            }


            //Reset the selectedHex_ and selected pawn pointers
            board_->deSelect(selectedHex_->getCoordinates());
            selectedHex_ = nullptr;
            selectedPawn_ = nullptr;

            //If the player has no actions left
            if(players_.at(gameState_->currentPlayer())->getActionsLeft() <= 0)
            {
                changePlayers();
            }
        }
        catch(Common::IllegalMoveException &exception)
        {
            std::cout << exception.msg() << std::endl;
        }
    }
}

void Mainwindow::playerTurnSinking(std::shared_ptr<Common::Hex> hex)
{
    try
    {
        //Try to flip the chosen tile
        gameEngine_->flipTile(hex->getCoordinates());

        board_->flipTile(hex->getCoordinates());
        //Change player turn
        board_->checkPawnValidity();
        changePlayers();
        board_->checkActorValidity();

    }
    catch (Common::IllegalMoveException &exception)
    {
        std::cout << exception.msg() << std::endl;
    }
}

void Mainwindow::playerTurnSpinning(std::shared_ptr<Common::Hex> hex)
{
    //If we have clicked the wheel already
    if ((selectedHex_ == nullptr) && (wheelClicked_))
    {
        selectedHex_ = hex;

        // Find actor or transport in selected hex
        selectedActor_ = board_->getActor(selectedHex_->getCoordinates(),
                                          pair_.first);
        selectedTransport_ = board_->getTransport(selectedHex_->getCoordinates(),
                                                  pair_.first);

        if ((selectedActor_ == nullptr) && (selectedTransport_ == nullptr))
        {
            selectedHex_ = nullptr;
        }
        else
        {
            board_->setSelected(selectedHex_->getCoordinates());
        }
    }
    else if(wheelClicked_)
    {
        //If we already have a hex selected
        if(hex == selectedHex_)
        {
            board_->deSelect(selectedHex_->getCoordinates());
            selectedHex_ = nullptr;
            selectedActor_ = nullptr;
            selectedTransport_ = nullptr;
            return;
        }
        try
        {
            if (selectedActor_ != nullptr) {
                gameEngine_->moveActor(selectedHex_->getCoordinates(),
                                       hex->getCoordinates(),
                                       selectedActor_->getId(),
                                       pair_.second);
            }
            else if (selectedTransport_ != nullptr) {
                gameEngine_->moveTransportWithSpinner(
                            selectedHex_->getCoordinates(),
                            hex->getCoordinates(),
                            selectedTransport_->getId(),
                            pair_.second);
            }

            board_->deSelect(selectedHex_->getCoordinates());
            selectedHex_ = nullptr;
            selectedActor_ = nullptr;
            selectedTransport_ = nullptr;
            wheelClicked_ = false;

            //We need to check the pawn validity of the pawns in the gameboards
            //game pawns, because they could be eaten by the actors
            board_->checkPawnValidity();
            changePlayers();

        }
        catch (Common::IllegalMoveException &exception)
        {
            std::cout << exception.msg() << std::endl;
        }

    }
    //If we've not clicked the wheel yet to determine which actor to move
    else
    {
        std::cout<<"Spin the wheel before trying to move actors"<<std::endl;
    }
}

void Mainwindow::initializeGame(int players)
{
    // Setup players
    for(int a = 0;a<players;++a)
    {
        std::shared_ptr<Common::IPlayer> newPlayer =
                std::make_shared<Student::Player>(a);

        players_.push_back(newPlayer);
    }
    // Now the game engine can be initialized
    try
    {
        gameEngine_
                = Common::Initialization::getGameRunner(board_,gameState_,players_);
    }
    catch(Common::IoException &IoException)
    {
        std::cout<<IoException.msg()<<std::endl;
        Student::ExceptionWindow exception(IoException.msg());
        exception.exec();
    }
    catch(Common::FormatException &FormatException)
    {
        std::cout<<FormatException.msg()<<std::endl;
        Student::ExceptionWindow exception(FormatException.msg());
        exception.exec();
    }


    if(gameEngine_ != nullptr)
    {
        for(auto player:players_)
        {
            int id = player->getPlayerId();
            board_->addPawn(id,pawnCount_);
            ++pawnCount_;
        }

        // Initialize and add the wheel
        wheelLayout_ = gameEngine_->getSpinnerLayout();
        wheel_->initializeSegments(wheelLayout_);
        wheelScene_.addItem(wheel_.get());
        wheelView_->setScene(&wheelScene_);

        gameView_ = board_->showScene();


        QHBoxLayout* mainLayout = new QHBoxLayout(this);
        QVBoxLayout* leftLayout = new QVBoxLayout(this);
        QVBoxLayout* rightLayout = new QVBoxLayout(this);

        // View of the gameboard
        leftLayout->addWidget(gameView_);

        // Zoom controls for the board
        QHBoxLayout* zoomControls = new QHBoxLayout();
        QLabel* zoomLabel = new QLabel();
        zoomLabel->setText("Change the size of the board:");

        decreaseButton_->setText("-");
        increaseButton_->setText("+");

        zoomControls->addWidget(zoomLabel);
        zoomControls->addWidget(decreaseButton_);
        zoomControls->addWidget(increaseButton_);
        leftLayout->addLayout(zoomControls);

        // Information about the state of game
        trackingScore_->changeGamePhase(gameState_->currentGamePhase());
        trackingScore_->initializeScores(gameEngine_->playerAmount());
        rightLayout->addWidget(trackingScore_.get());

        // The wheel
        rightLayout->addWidget(wheelView_);

        mainLayout->addLayout(leftLayout);
        mainLayout->addLayout(rightLayout);

        widget_ = new QWidget();
        widget_->setLayout(mainLayout);
        widget_->show();
        emit updateHexes();
    }


}

void Mainwindow::hexClick(std::shared_ptr<Common::Hex> chosenHex)
{
    //Do different stuff based on the current gamephase
    if(gameState_->currentGamePhase() == Common::MOVEMENT)
    {
        playerTurnMovement(chosenHex);
    }
    else if (gameState_->currentGamePhase()==Common::SINKING)
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
    if((gameState_->currentGamePhase() == Common::SPINNING) && (!wheelClicked_))
    {
        pair_ = gameEngine_->spinWheel();
        wheel_->setValue(pair_);
        wheel_->update();

        //Check if there is even an actor of the given type
        bool actorOrTransportFound = board_->checkActor(pair_.first) ||
                board_->checkTransport(pair_.first);

        if(!actorOrTransportFound)
        {
            changePlayers();
            return;
        }
        // we have clicked the wheel, this ensures a player
        // cant click the wheel twice in one turn.
        wheelClicked_ = true;
    }

}



void Mainwindow::hexScore()
{
    trackingScore_->scorePlayer(gameEngine_->currentPlayer());
}

void Mainwindow::skipPlayerTurn()
{
    if(selectedHex_ != nullptr)
    {
        board_->deSelect(selectedHex_->getCoordinates());
        selectedHex_ = nullptr;
        selectedPawn_ = nullptr;
        emit updateHexes();
    }

    changePlayers();
}


}
