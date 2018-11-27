#include "gameboard.hh"
#include <iostream>


namespace Student
{



GameBoard::GameBoard():
    scene_(nullptr)
{

}

GameBoard::~GameBoard()
{
    if(scene_!=nullptr)
    {
        delete(scene_);
    }
}

int GameBoard::checkTileOccupation(Common::CubeCoordinate tileCoord) const
{
    // Onko ruutu olemassa
    if (_tiles.find(tileCoord) == _tiles.end()) {
        return -1;
    }

    // Pawnien lukumäärä
    return _tiles.at(tileCoord)->getPawnAmount();
}

bool GameBoard::isWaterTile(Common::CubeCoordinate tileCoord) const
{
    // Onko ruutu olemassa
    if (_tiles.find(tileCoord) == _tiles.end()) {
        return false;
    }

    if (_tiles.at(tileCoord)->getPieceType() == "Water") {
        return true;
    }

    return false;
}

std::shared_ptr<Common::Hex> GameBoard::getHex(Common::CubeCoordinate hexCoord) const
{
    if (_tiles.find(hexCoord) != _tiles.end())
    {
        return _tiles.at(hexCoord);
    }
    return nullptr;
}

void GameBoard::addPawn(int playerId, int pawnId)
{
    //The coordinates that by default we add the pawns to is 0,0,0
    Common::CubeCoordinate coord(0,0,0);
    std::shared_ptr<Common::Pawn> newPawn = std::make_shared<Common::Pawn>();
    newPawn->setId(pawnId,playerId);
    newPawn->setCoordinates(coord);
    _tiles[coord]->addPawn(newPawn);
    _game_pawns[pawnId] = newPawn;

}

void GameBoard::addPawn(int playerId, int pawnId, Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Pawn> newPawn = std::make_shared<Common::Pawn>();
    newPawn->setId(pawnId,playerId);
    newPawn->setCoordinates(coord);
    _tiles[coord]->addPawn(newPawn);
    _game_pawns[pawnId] = newPawn;
}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord)
{
    if ((_tiles.find(pawnCoord) == _tiles.end())
            || (_game_pawns.find(pawnId)==_game_pawns.end()))
    {
        return;
    }
    if(_tiles.at(pawnCoord)->getPieceType() != "Coral")
    {
        std::shared_ptr<Common::Pawn> movingPawn= _game_pawns.at(pawnId);

        //Deselect the graphic tile that were moving from
        graphic_tiles.at(movingPawn->getCoordinates())->deSelect();

        //remove the pawn from the coordinate it is in before moving
        _tiles.at(movingPawn->getCoordinates())->removePawn(movingPawn);

        //Set the new coordinate for the pawn
        _game_pawns.at(pawnId)->setCoordinates(pawnCoord);
        //Add the pawn at the appropriate hex coordinate
        _tiles.at(pawnCoord)->addPawn(movingPawn);

    }
    //If were moving into a coral tile
    else
    {

        std::shared_ptr<Common::Pawn> movingPawn= _game_pawns.at(pawnId);

        graphic_tiles.at(movingPawn->getCoordinates())->deSelect();

        //Remove the pawn from the game
        _tiles.at(movingPawn->getCoordinates())->removePawn(movingPawn);
        _game_pawns.erase(pawnId);

        //And give the player a point for a job well done
        emit hexScore();
    }

}

void GameBoard::removePawn(int pawnId)
{
    if(_game_pawns.find(pawnId) != _game_pawns.end())
    {
        std::shared_ptr<Common::Pawn> pawnRemoved = _game_pawns.at(pawnId);
        _game_pawns.erase(pawnId);
        _tiles.at(pawnRemoved->getCoordinates())->removePawn(pawnRemoved);
    }
}

void GameBoard::addActor(std::shared_ptr<Common::Actor> actor,
                         Common::CubeCoordinate actorCoord)
{
    //Checks that the hex and the actor exist
    if (_tiles.find(actorCoord) != _tiles.end() && actor != nullptr) {

        // Add an actor to the hex
        actor->addHex(_tiles.at(actorCoord));

        // Adds the actor to a map
        _actors.insert(std::pair<int, std::shared_ptr<Common::Actor>>(actor->getId(), actor));
    }
}

void GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord)
{
    // Check if the coordinates exist
    if (_tiles.find(actorCoord) != _tiles.end()) {

        // Call the move function
        _actors.at(actorId)->move(_tiles.at(actorCoord));
        _actors.at(actorId)->doAction();
    }
}

void GameBoard::removeActor(int actorId)
{
    if (_actors.find(actorId) != _actors.end()) {
        std::shared_ptr<Common::Actor> actor = _actors.at(actorId);
        std::shared_ptr<Common::Hex> hex = actor->getHex();
        hex->removeActor(actor);
        _actors.erase(actorId);
    }
}

void GameBoard::addHex(std::shared_ptr<Common::Hex> newHex)
{
    //Add hex to hex map
    _tiles[newHex->getCoordinates()] = newHex;
    std::shared_ptr<graphicalHex> hex = std::make_shared<graphicalHex>();
    if(scene_ != nullptr)
    {
        scene_->addItem(hex.get());
        //Sets the position of the graphical hex in the scene
        hex->setPosition(newHex->getCoordinates());
        //Links the "real" hex and the graphical representation
        hex->setHex(newHex);
        hex->setBackground();
    }


    //Add graphical hex to its own map
    graphic_tiles[hex->getCoordinates()] = hex;

    //Connect the hexclicked signal to our hexClick slot
    //Needed to process hex clicks
    connect(hex.get(),&graphicalHex::hexClicked,this,&GameBoard::hexClick);

    //Connects our hexUpdate to graphical hexes updateGraphicHex,
    //needed to make the hexes update when moving pawns for example.
    connect(this,&GameBoard::hexUpdate,hex.get(),&graphicalHex::updateGraphicHex);
}

void GameBoard::addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord)
{
    if(_tiles.find(coord) != _tiles.end())
    {
        transport->addHex(_tiles.at(coord));
        _transports[transport->getId()] = transport;
    }

}

void GameBoard::moveTransport(int id, Common::CubeCoordinate coord)
{

    if (_tiles.find(coord) != _tiles.end())
    {
    //If we find the transport in our transport map
        if(_transports.find(id)!=_transports.end())
        {
            //Move the found transport to the desired coordinates
            std::shared_ptr<Common::Transport> transport =_transports.at(id);
            transport->move(_tiles.at(coord));
        }
    }
}

void GameBoard::removeTransport(int id)
{

    if(_transports.find(id)!=_transports.end())
    {
        // Remove transport from hex and _transports map
        std::shared_ptr<Common::Transport> transport = _transports.at(id);
        std::shared_ptr<Common::Hex> hex = transport->getHex();

        hex->removeTransport(transport);
        _transports.erase(id);
    }


}

void GameBoard::flipTile(Common::CubeCoordinate coord)
{


    if(graphic_tiles.find(coord) != graphic_tiles.end())
    {
       // Jos ruudussa on transport
       graphic_tiles.at(coord)->setBackground();
    }

     // If the tile has an actor, do its action
    if (_tiles.at(coord)->getActors().size() != 0)
    {
        std::shared_ptr<Common::Actor> actor = _tiles.at(coord)->getActors().at(0);
        _tiles.at(coord)->getActors().at(0)->doAction();

    }


}


QGraphicsView* GameBoard::showScene()
{
    //Once the view has been built, return it to the mainwindow
    QGraphicsView* view = new QGraphicsView(scene_);
    return view;
}

std::shared_ptr<Common::Pawn> GameBoard::getPlayerPawn(Common::CubeCoordinate coord, int playerId)
{
    if(graphic_tiles.find(coord) != graphic_tiles.end())
    {
        return graphic_tiles.at(coord)->getPlayerPawn(playerId);
    }
    return nullptr;
}

void GameBoard::setSelected(Common::CubeCoordinate coord)
{
    if(graphic_tiles.find(coord)!=graphic_tiles.end())
    {
        graphic_tiles.at(coord)->select();
    }

}

void GameBoard::deSelect(Common::CubeCoordinate coord)
{
    if(graphic_tiles.find(coord)!=graphic_tiles.end())
    {
        graphic_tiles.at(coord)->deSelect();
    }
}

void GameBoard::setScene(QGraphicsScene* scene)
{
    scene_ = scene;
}

void GameBoard::hexClick(std::shared_ptr<Common::Hex> clickedHex)
{
    //When hex is clicked, emit it to the mainwindow which will actually
    //process the click
    emit hexClicked(clickedHex);
}

void GameBoard::updateHexes()
{
    //Updates all the appearances of the hexes
    emit hexUpdate();
}



bool GameBoard::playerHasPawns(int playerId)
{
    //Make a for loop that goes through the pawns we have in a map
    for(std::map<int,std::shared_ptr<Common::Pawn>>::const_iterator
        it =_game_pawns.begin();
        it!=_game_pawns.end();++it)
    {
        if(it->second->getPlayerId() == playerId)
        {
            return true;
        }
    }

    return false;
}

bool GameBoard::anyPawnsIngame()
{
    if(_game_pawns.size()>0)
    {
        return true;
    }
    return false;
}

void GameBoard::checkPawnValidity()
{
    std::map<int, std::shared_ptr<Common::Pawn>>::iterator
            all_pawns = _game_pawns.begin();
    while(all_pawns!=_game_pawns.end())
    {
        //Check if pawn is in the pawn map of the hex it is supposed to be in
        Common::CubeCoordinate coordinate = all_pawns->second->getCoordinates();
        if(_tiles.at(coordinate)->givePawn(all_pawns->second->getId()) == nullptr)
        {
            all_pawns = _game_pawns.erase(all_pawns);
        }
        else
        {
            ++all_pawns;
        }

    }
}

void GameBoard::checkActorValidity()
{
    std::map<int, std::shared_ptr<Common::Actor>>::iterator
            actor = _actors.begin();
    while(actor != _actors.end())
    {
        std::shared_ptr<Common::Hex> hex = actor->second->getHex();
        //Check if the actor is in the hexes actor map
        if(hex->giveActor(actor->second->getId()) == nullptr)
        {
            actor = _actors.erase(actor);
        }
        else
        {
            ++actor;
        }
    }
}

bool GameBoard::checkActor(std::string type)
{
    std::map<int,std::shared_ptr<Common::Actor>>::const_iterator it = _actors.begin();
    //Checks that there is an actor of the specified type in our actors map
    while(it != _actors.end())
    {
        if(it->second->getActorType() == type)
        {
            return true;
        }
        ++it;
    }
    return false;

}

bool GameBoard::checkTransport(std::string type)
{
    std::map<int,std::shared_ptr<Common::Transport>>::const_iterator it = _transports.begin();
    //Checks that there is an actor of the specified type in our actors map
    while(it != _transports.end())
    {
        if(it->second->getTransportType() == type)
        {
            return true;
        }
        ++it;
    }
    return false;
}

std::shared_ptr<Common::Actor> GameBoard::getActor(Common::CubeCoordinate coord, std::string type)
{
    if(_tiles.find(coord)!=_tiles.end())
    {
        //Get the actors and put them into a vector
        std::vector<std::shared_ptr<Common::Actor>> actors =_tiles.at(coord)->getActors();
        for(std::shared_ptr<Common::Actor> actor:actors)
        {
            //If the actors type matches the specific type we're looking for
            //return a pointer to it
            if(actor->getActorType()==type)
            {
                return actor;
            }
        }
    }
    return nullptr;
}

std::shared_ptr<Common::Transport> GameBoard::getTransport(Common::CubeCoordinate coord, std::string type)
{
    if(_tiles.find(coord)!=_tiles.end())
    {
        // Get the transports and put them into a vector
        std::vector<std::shared_ptr<Common::Transport>> transports =_tiles.at(coord)->getTransports();
        for(std::shared_ptr<Common::Transport> transport : transports)
        {
            // If the transport's type matches the specific type we're looking for
            // return a pointer to it
            if(transport->getTransportType() == type)
            {
                return transport;
            }
        }
    }
    return nullptr;
}

void GameBoard::zoomIn()
{
    std::map<Common::CubeCoordinate, std::shared_ptr<Student::graphicalHex>>::iterator it;
    for (it = graphic_tiles.begin(); it != graphic_tiles.end(); it++) {
        it->second->increaseSize();
        it->second->update();
    }
}

void GameBoard::zoomOut()
{
    std::map<Common::CubeCoordinate, std::shared_ptr<Student::graphicalHex>>::iterator it;
    for (it = graphic_tiles.begin(); it != graphic_tiles.end(); it++) {
        it->second->decreaseSize();
        it->second->update();
    }
}


}


