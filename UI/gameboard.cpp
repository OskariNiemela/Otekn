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

}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord)
{

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

}

//Kun scene on rakennettu, palautetaan se mainwindowille
QGraphicsView* GameBoard::showScene()
{
    QGraphicsView* view = new QGraphicsView(scene_);
    return view;
}

}


