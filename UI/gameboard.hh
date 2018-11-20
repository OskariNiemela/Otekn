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
#include "gameexception.hh"
#include "transport.hh"

/**
* @brief contains classess that have been created by students
*/
namespace Student
{
/**
* @brief Implements the intefrace IGameBoard
*/
class GameBoard : public QObject, public Common::IGameBoard
{
    Q_OBJECT
public:
    /**
     * @brief Constructor.
     */
    GameBoard();
    ~GameBoard();
    /**
     * @copydoc Common::IGameBoard::checkTileOccupation
     */
    virtual int checkTileOccupation(Common::CubeCoordinate tileCoord) const final;

    /**
     * @copydoc Common::IGameBoard::isWaterTile
     */
    virtual bool isWaterTile(Common::CubeCoordinate tileCoord) const final;

    /**
     * @copydoc Common::IGameBoard::getHex
     */
    virtual std::shared_ptr<Common::Hex> getHex(Common::CubeCoordinate hexCoord) const final;

    /**
     * @copydoc Common::IGameBoard::addPawn
     */
    virtual void addPawn(int playerId,
                         int pawnId) final;

    /**
     * @copydoc Common::IGameBoard::addPawn
     */
    virtual void addPawn(int playerId,
                         int pawnId,
                         Common::CubeCoordinate coord) final;

    /**
     * @copydoc Common::IGameBoard::movePawn
     */
    virtual void movePawn(int pawnId, Common::CubeCoordinate pawnCoord) final;

    /**
     * @copydoc Common::IGameBoard::removePawn
     */
    virtual void removePawn(int pawnId) final;

    /**
     * @copydoc Common::IGameBoard::addActor
     */
    virtual void addActor(std::shared_ptr<Common::Actor> actor,
                          Common::CubeCoordinate actorCoord) final;

    /**
     * @copydoc Common::IGameBoard::moveActor
     */
    virtual void moveActor(int actorId,
                           Common::CubeCoordinate actorCoord) final;

    /**
     * @copydoc Common::IGameBoard::removeActor
     */
    virtual void removeActor(int actorId) final;

    /**
     * @copydoc Common::IGameBoard::addHex
     */
    virtual void addHex(std::shared_ptr<Common::Hex> newHex) final;

    /**
     * @copydoc Common::IGameBoard::addTransport
     */
    virtual void addTransport(std::shared_ptr<Common::Transport> transport,
                              Common::CubeCoordinate coord) final;

    /**
     * @copydoc Common::IGameBoard::moveTransport
     */
    virtual void moveTransport(int id, Common::CubeCoordinate coord) final;

    /**
     * @copydoc Common::IGameBoard::removeTransport
     */
    virtual void removeTransport(int id) final;

    /**
     * @brief changes the background of a flipped tile, so
     * @param coordinate of the hex to be flipped
     */
    virtual void flipTile(Common::CubeCoordinate coord) final;

    /**
     * @brief showScene, once the scene is done we show it to the player and return the view
     * @return the view in which the scene is shown
     * @pre scene_ must exist
     * @post scene_ is added to QGraphicsView. Exception guarantee: basic
     */
    virtual QGraphicsView *showScene() final;

    /**
     * @brief gets a pawn belonging to player with playerId
     * @param coordinate which from to look for the pawn
     * @param id of the player whose pawn were looking for
     * @return returns pointer to player pawn,
     * if no pawn of the player is present returns nullptr
     * @post exception guarantee: nothrow
     */
    virtual std::shared_ptr<Common::Pawn> getPlayerPawn(Common::CubeCoordinate coord,
                                                        int playerId) final;
    /**
     * @brief sets the hex at coord to selected
     * (meaning its outline will be drawn in red)
     * @param coordinate to set selected at
     * @post Exception guarantee: noThrow
     */
    virtual void setSelected(Common::CubeCoordinate coord) final;

    /**
     * @brief sets the hex at coord to not selected
     * (meaning the outline will be black once more)
     * @param coordinate to change the hex at
     * @post Exception guarantee: nothrow
     */
    virtual void deSelect(Common::CubeCoordinate coord) final;

    /**
     * @brief Sets the scene to be shown
     * @param scene to add
     */
    virtual void setScene(QGraphicsScene *scene) final;

    /**
     * @brief returns whether player has any pawns ingame
     * @param player id whose pawn situation we want to taḱe a look at
     * @return true if there is pawns, otherwise false
     * @post Exception guarantee: nothrow
     */
    virtual bool playerHasPawns(int playerId) final;

    /**
     * @brief Tells whether there are any pawns in the game
     * @return true if there are pawns, otherwise false
     * @post Exception guarantee: nothrow
     */
    virtual bool anyPawnsIngame() final;
public slots:
    /**
     * @brief Code run when a hex emits the hexClicked signal
     * @param pointer to the hex that has been clicked
     */
    void hexClick(std::shared_ptr<Common::Hex> clickedHex);
    /**
     * @brief updates all the appearances of hexes
     */
    void updateHexes();
signals:
    /**
     * @brief Signal to send when a hex is clicked
     * @param the "real" hex that has been clicked
     * not the graphical hex
     */
    void hexClicked(std::shared_ptr<Common::Hex> clickHex);
    /**
     * @brief Run when a player scores a point
     */
    void hexScore();
    /**
     * @brief Update the appearances of hexes
     */
    void hexUpdate();
private:
    std::map<Common::CubeCoordinate,std::shared_ptr<Common::Hex>> _tiles;
    std::map<Common::CubeCoordinate,std::shared_ptr<Student::graphicalHex>> graphic_tiles;

    std::map<int, std::shared_ptr<Common::Pawn>> _game_pawns;
    std::map<int, std::shared_ptr<Common::Actor>> _actors;
    std::map<int, std::shared_ptr<Common::Transport>> _transports;
    QGraphicsScene* scene_;

};
}

#endif // GAMEBOARD_HH

