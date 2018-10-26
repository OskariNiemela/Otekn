#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include "igamestate.hh"


class GameState : public Common::IGameState
{
public:
    GameState();
    ~GameState();
    Common::GamePhase currentGamePhase() const;
    int currentPlayer() const;
    void changeGamePhase(Common::GamePhase nextPhase);
    void changePlayerTurn(int nextPlayer);

private:
    int _currentPlayer;
};

#endif // GAMESTATE_HH
