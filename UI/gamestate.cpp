#include "gamestate.hh"

GameState::GameState():
    _currentPlayer(0)
{

}

GameState::~GameState()
{

}

int GameState::currentPlayer() const
{
    return _currentPlayer;
}

Common::GamePhase GameState::currentGamePhase()
{
    return 0;
}

void GameState::changeGamePhase(Common::GamePhase nextPhase)
{

}

void GameState::changePlayerTurn(int nextPlayer)
{
    _currentPlayer = nextPlayer;
}
