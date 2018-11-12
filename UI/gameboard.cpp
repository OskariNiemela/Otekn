#include "gameboard.hh"
#include <iostream>


namespace Student
{



GameBoard::GameBoard():
    scene_(new QGraphicsScene)
{

}

GameBoard::~GameBoard()
{

}

int GameBoard::checkTileOccupation(Common::CubeCoordinate tileCoord) const
{
    return 0;
}

bool GameBoard::isWaterTile(Common::CubeCoordinate tileCoord) const
{
    return false;
}

std::shared_ptr<Common::Hex> GameBoard::getHex(Common::CubeCoordinate hexCoord) const
{
    return nullptr;
}

void GameBoard::addPawn(int playerId, int pawnId)
{
    Common::CubeCoordinate coord(0,0,0);
    std::shared_ptr<Common::Pawn> newPawn = std::make_shared<Common::Pawn>();
    newPawn->setId(pawnId,playerId);
    newPawn->setCoordinates(coord);
    _map_tiles[coord]->addPawn(newPawn);
}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord)
{

}

void GameBoard::removePawn(int pawnId)
{

}

void GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord)
{
    // Tarkistetaan onko actor olemassa ja jos on, vaihdetaan sen sijaintia
    if (_actors.find(actorId) != _actors.end()) {
        _actors.at(actorId)->move(_map_tiles.at(actorCoord));
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

    _tiles.push_back(newHex);
    _map_tiles[newHex->getCoordinates()] = newHex;
    graphicalHex* hex = new graphicalHex();
    scene_->addItem(hex);
    hex->setPosition(newHex->getCoordinates());
    hex->setHex(newHex);
    hex->setColor();
}

void GameBoard::addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord)
{

}

void GameBoard::moveTransport(int id, Common::CubeCoordinate coord)
{

}

void GameBoard::removeTransport(int id)
{

}

void GameBoard::addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord)
{
    // Tarkistaa onko ruutu olemassa
    if (_map_tiles.find(actorCoord) != _map_tiles.end()) {

        // Lisää hex-oliolle actorin
        actor->addHex(_map_tiles.at(actorCoord));

        // Lisää actorin erilliseen mappiin
        _actors.insert(std::pair<int, std::shared_ptr<Common::Actor>>(actor->getId(), actor));
    }
}

//Kun scene on rakennettu, palautetaan se mainwindowille
QGraphicsView* GameBoard::showScene()
{
    QGraphicsView* view = new QGraphicsView(scene_);
    return view;
}

}


