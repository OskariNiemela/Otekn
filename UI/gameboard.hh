#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <map>
#include <unordered_map>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>

#include "igameboard.hh"
#include "hex.hh"
#include "graphicalhex.hh"
#include "pawn.hh"
#include "actor.hh"
#include "actorfactory.hh"

namespace Student
{
class GameBoard : public QObject, public Common::IGameBoard
{
    Q_OBJECT
public:
    GameBoard();
    ~GameBoard();
    int checkTileOccupation(Common::CubeCoordinate tileCoord) const;
    bool isWaterTile(Common::CubeCoordinate tileCoord) const;
    std::shared_ptr<Common::Hex> getHex(Common::CubeCoordinate hexCoord) const;
    void addPawn(int playerId, int pawnId);
    void addPawn(int playerId, int pawnId, Common::CubeCoordinate coord);
    void movePawn(int pawnId, Common::CubeCoordinate pawnCoord);
    void removePawn(int pawnId);
    void addActor(std::shared_ptr<Common::Actor> actor, Common::CubeCoordinate actorCoord);
    void moveActor(int actorId, Common::CubeCoordinate actorCoord);
    void removeActor(int actorId);
    void addHex(std::shared_ptr<Common::Hex> newHex);
    void addTransport(std::shared_ptr<Common::Transport> transport, Common::CubeCoordinate coord);
    void moveTransport(int id, Common::CubeCoordinate coord);
    void removeTransport(int id);
    void flipTile(Common::CubeCoordinate coord);
    QGraphicsView *showScene();
    std::shared_ptr<Common::Pawn> getPlayerPawn(Common::CubeCoordinate coord, int playerId);
    void setSelected(Common::CubeCoordinate coord);
    void deSelect(Common::CubeCoordinate coord);
public slots:
    void hexClick(std::shared_ptr<Common::Hex> clickedHex);
    void deleteOldPawn(Common::CubeCoordinate coordDelete, std::shared_ptr<Common::Pawn> pawn, Common::CubeCoordinate goTo);
signals:
    void hexClicked(std::shared_ptr<Common::Hex> clickHex);
    void getHexFrom(Common::CubeCoordinate);
private:
    std::map<Common::CubeCoordinate,std::shared_ptr<Common::Hex>> _map_tiles;
    std::map<Common::CubeCoordinate,Student::graphicalHex*> graphic_tiles;
    std::vector<std::shared_ptr<Common::Hex>> _tiles;
    std::map<int, std::shared_ptr<Common::Pawn>> _game_pawns;
    std::map<int, std::shared_ptr<Common::Actor>> _actors;
    QGraphicsScene* scene_;

};
}

#endif // GAMEBOARD_HH

