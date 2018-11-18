#include "gamestate.hh"

namespace Student
{

GameState::GameState():
    _currentPlayer(0),
    _gamePhase(Common::GamePhase::MOVEMENT)
{

}

int GameState::currentPlayer() const
{
    return _currentPlayer;
}

Common::GamePhase GameState::currentGamePhase() const
{
    return _gamePhase;
}

void GameState::changeGamePhase(Common::GamePhase nextPhase)
{
    _gamePhase = nextPhase;
}

void GameState::changePlayerTurn(int nextPlayer)
{
    _currentPlayer = nextPlayer;
}
}
