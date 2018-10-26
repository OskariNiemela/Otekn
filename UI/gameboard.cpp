#include "gameboard.hh"
#include <iostream>

GameBoard::GameBoard()
{

}

GameBoard::~GameBoard()
{

}

void GameBoard::addHex(std::shared_ptr<Common::Hex> newHex)
{
    std::cout << "Kutsuttu addhex" << std::endl;
    _tiles.push_back(newHex);
}
