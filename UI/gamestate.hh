#ifndef GAMESTATE_HH
#define GAMESTATE_HH

#include "igamestate.hh"


class GameState : public Common::IGameState
{
public:
    GameState();
    ~GameState();
    int currentPlayer() const;
    Common::GamePhase currentGamePhase();
    void changeGamePhase(Common::GamePhase nextPhase);
    void changePlayerTurn(int nextPlayer);

private:
    int _currentPlayer;
};

#endif // GAMESTATE_HH
