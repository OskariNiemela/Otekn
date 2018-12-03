#ifndef GAMESTATE_HH
#define GAMESTATE_HH

/* Oskari Niemelä 263440
 * Aki Kaipio 267041
 *
 * Implements the IGameState interface class
 */

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
    virtual ~GameState() = default;

    /**
     * @copydoc Common::IGameState::currentGamePhase
     */
    virtual Common::GamePhase currentGamePhase() const;

    /**
     * @copydoc Common::IGameState::currentPlayer
     */
    virtual int currentPlayer() const;

    /**
     * @copydoc Common::IGameState::changeGamePhase
     */
    virtual void changeGamePhase(Common::GamePhase nextPhase);

    /**
     * @copydoc Common::IGameState::changePlayerTurn
     */
    virtual void changePlayerTurn(int nextPlayer);

private:
    int currentPlayer_;
    Common::GamePhase gamePhase_;
};

}

#endif // GAMESTATE_HH
