/* Oskari Niemelä 263440
 * Aki Kaipio 267041
 *
 * Implementation of the Player class
 */

#include "player.hh"

namespace Student
{
Player::Player(int playerID):
    playerId_(playerID),
    actions_(3)
{

}

int Player::getPlayerId() const
{
    return playerId_;
}

void Player::setActionsLeft(unsigned int actionsLeft)
{
    actions_ = actionsLeft;
}

unsigned int Player::getActionsLeft() const
{
    return actions_;
}



}
