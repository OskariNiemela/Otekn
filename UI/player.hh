#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"

namespace Student
{
class Player : public Common::IPlayer
{
public:
    Player(int playerID);
    virtual ~Player() = default;
    int getPlayerId() const;
    void setActionsLeft(unsigned int actionsLeft);
    unsigned int getActionsLeft() const;

private:
    int _playerId ;
    unsigned int _actions;
};
}
#endif // PLAYER_HH
