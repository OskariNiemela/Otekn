#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <map>
#include <unordered_map>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "igameboard.hh"
#include "hex.hh"
#include "graphicalhex.hh"
#include "pawn.hh"
#include "actor.hh"

namespace Student
{
class GameBoard : public Common::IGameBoard
{
public:
    GameBoard();
    ~GameBoard();
    int checkTileOccupation(Common::CubeCoordinate tileCoord) const;
    bool isWaterTile(Common::CubeCoordinate tileCoord) const;
    std::shared_ptr<Common::Hex> getHex(Common::CubeCoordinate hexCoord) const;
    void addPawn(int playerId, int pawnId);
    void movePawn(int pawnId, Common::CubeCoordinate pawnCoord);
    void removePawn(int pawnId);
    void moveActor(int actorId, Common::CubeCoordinate actorCoord);
    void removeActor(int actorId);
    void addHex(std::shared_ptr<Common::Hex> newHex);
    void addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord);
    void moveTransport(int id, Common::CubeCoordinate coord) ;
    void removeTransport(int id);
    void addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord);
    QGraphicsView *showScene();


private:
    std::map<Common::CubeCoordinate,std::shared_ptr<Common::Hex>> _map_tiles;
    std::vector<std::shared_ptr<Common::Hex>> _tiles;
    std::map<int, std::shared_ptr<Common::Actor>> _actors;
    QGraphicsScene* scene_;

};
}

#endif // GAMEBOARD_HH

