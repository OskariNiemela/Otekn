#include "gameboard.hh"
#include <iostream>

GameBoard::GameBoard()
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
    std::cout << "Kutsuttu addhex" << std::endl;
    _tiles.push_back(newHex);
}