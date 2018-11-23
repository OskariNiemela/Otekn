#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include "igamestate.hh"

namespace Student
{

class GameState : public Common::IGameState
{
public:
    /**
     * @brief Constructor
     */
    GameState();
    /**
     * @brief default destructor
     */
    ~GameState() = default;
    /**
     * @copydoc Common;;IGameState::currentGamePhase
     */
    Common::GamePhase currentGamePhase() const;

    /**
     * @copydoc Common;;IGameState::currentPlayer
     */
    int currentPlayer() const;

    /**
     * @copydoc Common;;IGameState::changeGamePhase
     */
    void changeGamePhase(Common::GamePhase nextPhase);
    /**
     * @copydoc Common;;IGameState::changePlayerTurn
     */
    void changePlayerTurn(int nextPlayer);

private:
    int _currentPlayer;
    Common::GamePhase _gamePhase;
};
}

#endif // GAMESTATE_HH
