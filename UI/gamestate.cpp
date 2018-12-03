/* Oskari Niemelä 263440
 * Aki Kaipio 267041
 *
 * Implementation of the GameState class
 */

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
