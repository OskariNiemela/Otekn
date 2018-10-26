#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <map>
#include <unordered_map>
#include <vector>

#include "igameboard.hh"
#include "hex.hh"

class GameBoard : public Common::IGameBoard
{
public:
    GameBoard();
    ~GameBoard();
    /*int checkTileOccupation(Common::CubeCoordinate tileCoord) const;
    bool isWaterTile(Common::CubeCoordinate tileCoord) const;
    std::shared_ptr<Common::Hex> getHex(Common::CubeCoordinate hexCoord) const;
    void addPawn(int playerId, int pawnId);
    void movePawn(int pawnId, Common::CubeCoordinate pawnCoord);
    void removePawn(int pawnId);
    void moveActor(int actorId, Common::CubeCoordinate actorCoord);
    void removeActor(int actorId)*/
    void addHex(std::shared_ptr<Common::Hex> newHex);

private:
    std::vector<std::shared_ptr<Common::Hex>> _tiles;

};
#endif // GAMEBOARD_HH
