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
    if (_map_tiles.find(tileCoord) == _map_tiles.end()) {
        return -1;
    }

    // Pawnien lukumäärä
    return _map_tiles.at(tileCoord)->getPawnAmount();
}

bool GameBoard::isWaterTile(Common::CubeCoordinate tileCoord) const
{
    // Onko ruutu olemassa
    if (_map_tiles.find(tileCoord) == _map_tiles.end()) {
        return false;
    }

    if (_map_tiles.at(tileCoord)->getPieceType() == "Water") {
        return true;
    }

    return false;
}

std::shared_ptr<Common::Hex> GameBoard::getHex(Common::CubeCoordinate hexCoord) const
{
    if(_map_tiles.find(hexCoord) != _map_tiles.end())
    {
        return _map_tiles.at(hexCoord);
    }
    return nullptr;
}

void GameBoard::addPawn(int playerId, int pawnId)
{
    Common::CubeCoordinate coord(0,0,0);
    std::shared_ptr<Common::Pawn> newPawn = std::make_shared<Common::Pawn>();
    newPawn->setId(pawnId,playerId);
    newPawn->setCoordinates(coord);
    _map_tiles[coord]->addPawn(newPawn);
    _game_pawns[pawnId] = newPawn;

}

void GameBoard::addPawn(int playerId, int pawnId, Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Pawn> newPawn = std::make_shared<Common::Pawn>();
    newPawn->setId(pawnId,playerId);
    newPawn->setCoordinates(coord);
    _map_tiles[coord]->addPawn(newPawn);
    _game_pawns[pawnId] = newPawn;
}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord)
{
    //emit getHexFrom(pawnCoord);
    if(_map_tiles.at(pawnCoord)->getPieceType() != "Coral")
    {
        std::shared_ptr<Common::Pawn> movingPawn= _game_pawns.at(pawnId);
        graphic_tiles.at(movingPawn->getCoordinates())->deSelect();
        _map_tiles.at(movingPawn->getCoordinates())->removePawn(movingPawn);
        _game_pawns.at(pawnId)->setCoordinates(pawnCoord);
        _map_tiles.at(pawnCoord)->addPawn(movingPawn);

    }
    else
    {
        std::shared_ptr<Common::Pawn> movingPawn= _game_pawns.at(pawnId);
        graphic_tiles.at(movingPawn->getCoordinates())->deSelect();
        _map_tiles.at(movingPawn->getCoordinates())->removePawn(movingPawn);
        _game_pawns.erase(pawnId);
        emit hexScore();
    }

}

void GameBoard::removePawn(int pawnId)
{
    if(_game_pawns.find(pawnId) != _game_pawns.end())
    {
        std::shared_ptr<Common::Pawn> pawnRemoved = _game_pawns.at(pawnId);
        _game_pawns.erase(pawnId);
        _map_tiles.at(pawnRemoved->getCoordinates())->removePawn(pawnRemoved);
    }
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
    if(scene_ != nullptr)
    {
        scene_->addItem(hex);
    }
    hex->setPosition(newHex->getCoordinates());
    hex->setHex(newHex);
    hex->setColor();
    graphic_tiles[hex->getCoordinates()] = hex;
    connect(hex,&graphicalHex::hexClicked,this,&GameBoard::hexClick);
    connect(this,&GameBoard::hexUpdate,hex,&graphicalHex::updateGraphicHex);
}

void GameBoard::addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord)
{
    _map_tiles.at(coord)->addTransport(transport);
}

void GameBoard::moveTransport(int id, Common::CubeCoordinate coord)
{

}

void GameBoard::removeTransport(int id)
{

}

void GameBoard::flipTile(Common::CubeCoordinate coord)
{
    graphic_tiles.at(coord)->setColor();
}

//Kun scene on rakennettu, palautetaan se mainwindowille
QGraphicsView* GameBoard::showScene()
{
    QGraphicsView* view = new QGraphicsView(scene_);
    return view;
}

std::shared_ptr<Common::Pawn> GameBoard::getPlayerPawn(Common::CubeCoordinate coord, int playerId)
{
    return graphic_tiles.at(coord)->getPlayerPawn(playerId);
}

void GameBoard::setSelected(Common::CubeCoordinate coord)
{
    graphic_tiles.at(coord)->select();
}

void GameBoard::deSelect(Common::CubeCoordinate coord)
{
    graphic_tiles.at(coord)->deSelect();
}

void GameBoard::initializeScene()
{
    scene_ = new QGraphicsScene(this);
}

void GameBoard::setScene(QGraphicsScene* scene)
{
    scene_ = scene;
}

void GameBoard::hexClick(std::shared_ptr<Common::Hex> clickedHex)
{
    emit hexClicked(clickedHex);
}

void GameBoard::updateHexes()
{
    emit hexUpdate();
}

std::shared_ptr<Common::Pawn> GameBoard::getPawn(int pawnId) const
{
    if(_game_pawns.find(pawnId) != _game_pawns.end())
    {
        return _game_pawns.at(pawnId);
    }
    return nullptr;
}

Common::CubeCoordinate GameBoard::getPawnCoordinate(int pawnId) const
{
    if(_game_pawns.find(pawnId) != _game_pawns.end())
    {
        return _game_pawns.at(pawnId)->getCoordinates();
    }
    throw Common::GameException("No such pawn when getting pawn coordinate");
}


}


