#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"

namespace Student
{
class Player : public Common::IPlayer
{
public:
    Player(int playerID);
    virtual ~Player() {}
    int getPlayerId() const;
    void setActionsLeft(unsigned int actionsLeft);
    unsigned int getActionsLeft() const;

private:
    int _playerId = 0;
};
}
#endif // PLAYER_HH
