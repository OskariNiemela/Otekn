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
    explicit Player(int playerID);
    /**
    * @brief default destructor
    */
    virtual ~Player() = default;
    /**
     * @copydoc Common::IPlayer::getPlayerId
     */
    int getPlayerId() const;

    /**
     * @copydoc Common::IPlayer::setActionsLeft
     */
    void setActionsLeft(unsigned int actionsLeft);
    /**
     * @copydoc Common::IPlayer::getActionsLeft
     */
    unsigned int getActionsLeft() const;

private:
    int _playerId ;
    unsigned int _actions;
};
}
#endif // PLAYER_HH
