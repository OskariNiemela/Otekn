#ifndef PLAYER_HH
#define PLAYER_HH

#include "iplayer.hh"

namespace Student
{
class Player : public Common::IPlayer
{
public:
    /**
     * @brief constructs the player
     * @param Id of the player
     */
    Player(int playerID);
    /**
    * @brief default destructor
    */
    virtual ~Player() = default;
    /**
     * @brief gives the id of the player
     * @return id of the player
     */
    int getPlayerId() const;

    void setActionsLeft(unsigned int actionsLeft);
    unsigned int getActionsLeft() const;

private:
    int _playerId ;
    unsigned int _actions;
};
}
#endif // PLAYER_HH
