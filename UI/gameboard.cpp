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
    if (_tiles.find(pawnCoord) == _tiles.end()
            || _game_pawns.find(pawnId)==_game_pawns.end())
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

void GameBoard::addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord)
{
    // Tarkistaa onko ruutu ja actor olemassa
    if (_tiles.find(actorCoord) != _tiles.end() && actor != nullptr) {

        // Lisää hex-oliolle actorin
        actor->addHex(_tiles.at(actorCoord));

        // Lisää actorin erilliseen mappiin
        _actors.insert(std::pair<int, std::shared_ptr<Common::Actor>>(actor->getId(), actor));
    }
}

void GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord)
{
    // Tarkistetaan onko koordinaatit olemassa
    if (_tiles.find(actorCoord) != _tiles.end()) {

        // Asetetaan actor-osoitin uusiin koordinaatteihin
        _actors.at(actorId)->move(_tiles.at(actorCoord));
    }
}

void GameBoard::removeActor(int actorId)
{
    if (_actors.find(actorId) != _actors.end()) {
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
    }
    //Sets the position of the graphical hex in the scene
    hex->setPosition(newHex->getCoordinates());
    //Links the "real" hex and the graphical representation
    hex->setHex(newHex);
    hex->setBackground();

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
    _tiles.at(coord)->addTransport(transport);
    _transports.insert(std::pair<int, std::shared_ptr<Common::Transport>>(transport->getId(), transport));
}

void GameBoard::moveTransport(int id, Common::CubeCoordinate coord)
{
    if (_tiles.find(coord) != _tiles.end()) {
        // Remove transport from its previous location
        _transports.at(id)->getHex()->removeTransport(_transports.at(id));

        // Add transport to new coordinates
        _tiles.at(coord)->addTransport(_transports.at(id));
    }
}

void GameBoard::removeTransport(int id)
{
    // Remove transport from hex and _transports map
    _transports.at(id)->getHex()->removeTransport(_transports.at(id));
    _transports.erase(id);
}

void GameBoard::flipTile(Common::CubeCoordinate coord)
{
    if(graphic_tiles.find(coord) != graphic_tiles.end())
    {
       // Jos ruudussa on actor, suoritetaan sen toiminto
       if (_tiles.at(coord)->getActors().size() != 0) {
           _tiles.at(coord)->getActors().at(0)->doAction();

       }

       // Jos ruudussa on transport


       graphic_tiles.at(coord)->setBackground();
    }





}

//Kun scene on rakennettu, palautetaan se mainwindowille
QGraphicsView* GameBoard::showScene()
{

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
    //Make a const iterator and set it to the beginning of _game_pawns
    for(std::map<int,std::shared_ptr<Common::Pawn>>::const_iterator it =_game_pawns.begin();
        it!=_game_pawns.end();it++)
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


}


