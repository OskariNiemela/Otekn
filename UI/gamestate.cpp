#include "gamestate.hh"

namespace Student
{

GameState::GameState():
    currentPlayer_(0),
    gamePhase_(Common::GamePhase::MOVEMENT)
{

}

int GameState::currentPlayer() const
{
    return currentPlayer_;
}

Common::GamePhase GameState::currentGamePhase() const
{
    return gamePhase_;
}

void GameState::changeGamePhase(Common::GamePhase nextPhase)
{
    gamePhase_ = nextPhase;
}

void GameState::changePlayerTurn(int nextPlayer)
{
    currentPlayer_ = nextPlayer;
}

}
