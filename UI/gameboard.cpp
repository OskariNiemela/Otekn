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
    graphic_tiles[coord]->addPawn(newPawn);

}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord)
{
    emit getHexFrom(pawnCoord);
}

void GameBoard::removePawn(int pawnId)
{

}

void GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord)
{

}

void GameBoard::removeActor(int actorId)
{

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
    graphic_tiles[hex->getCoordinates()] = hex;
    connect(hex,&graphicalHex::hexClicked,this,&GameBoard::hexClick);
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



void GameBoard::hexClick(std::shared_ptr<Common::Hex> clickedHex)
{
    emit hexClicked(clickedHex);
}

void GameBoard::deleteOldPawn(Common::CubeCoordinate coordDelete, std::shared_ptr<Common::Pawn> pawn,Common::CubeCoordinate goTo)
{
    _map_tiles.at(goTo)->addPawn(pawn);
    graphic_tiles.at(goTo)->addPawn(pawn);
    _map_tiles.at(coordDelete)->removePawn(pawn);
    graphic_tiles.at(coordDelete)->removePawn(pawn);
}

}


