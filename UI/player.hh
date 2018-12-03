#ifndef PLAYER_HH
#define PLAYER_HH

/* Oskari Niemelä 263440
 * Aki Kaipio 267041
 *
 * Implements the IPlayer interface class
 * Holds the player information
 */

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
    virtual int getPlayerId() const;

    /**
     * @copydoc Common::IPlayer::setActionsLeft
     */
    virtual void setActionsLeft(unsigned int actionsLeft);
    /**
     * @copydoc Common::IPlayer::getActionsLeft
     */
    virtual unsigned int getActionsLeft() const;

private:
    int playerId_ ;
    unsigned int actions_;
};
}
#endif // PLAYER_HH
