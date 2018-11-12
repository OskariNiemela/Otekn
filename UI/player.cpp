#include "player.hh"

namespace Student
{
Player::Player(int playerID):
    _playerId(playerID),
    _actions(3)
{

}

int Player::getPlayerId() const
{
    return _playerId;
}

void Player::setActionsLeft(unsigned int actionsLeft)
{

}

unsigned int Player::getActionsLeft() const
{
    return _actions;
}



}
