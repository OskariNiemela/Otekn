#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

/* Oskari Niemelä 263440
 * Aki Kaipio 267041
 * Header file for the GameBoard class
 * Implements the IGameBoard inteface class
 */


#include "igameboard.hh"
#include "hex.hh"
#include "graphicalhex.hh"
#include "pawn.hh"
#include "actor.hh"
#include "actorfactory.hh"
#include "gameexception.hh"
#include "transport.hh"

#include <map>
#include <unordered_map>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>

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

    /**
     * @brief Destructor
     */
    virtual ~GameBoard();

    /**
     * @copydoc Common::IGameBoard::checkTileOccupation
     */
    int checkTileOccupation(Common::CubeCoordinate tileCoord) const override;

    /**
     * @copydoc Common::IGameBoard::isWaterTile
     */
    bool isWaterTile(Common::CubeCoordinate tileCoord) const override;

    /**
     * @copydoc Common::IGameBoard::getHex
     */
    std::shared_ptr<Common::Hex> getHex(Common::CubeCoordinate hexCoord) const override;

    /**
     * @copydoc Common::IGameBoard::addPawn
     */
    void addPawn(int playerId,
                         int pawnId) override;

    /**
     * @copydoc Common::IGameBoard::addPawn
     */
    void addPawn(int playerId,
                         int pawnId,
                         Common::CubeCoordinate coord) override;

    /**
     * @copydoc Common::IGameBoard::movePawn
     */
    void movePawn(int pawnId, Common::CubeCoordinate pawnCoord) override;

    /**
     * @copydoc Common::IGameBoard::removePawn
     */
    void removePawn(int pawnId) override;

    /**
     * @copydoc Common::IGameBoard::addActor
     */
    void addActor(std::shared_ptr<Common::Actor> actor,
                          Common::CubeCoordinate actorCoord) override;

    /**
     * @copydoc Common::IGameBoard::moveActor
     */
    void moveActor(int actorId,
                           Common::CubeCoordinate actorCoord) override;

    /**
     * @copydoc Common::IGameBoard::removeActor
     */
    void removeActor(int actorId) override;

    /**
     * @copydoc Common::IGameBoard::addHex
     */
    void addHex(std::shared_ptr<Common::Hex> newHex) override;

    /**
     * @copydoc Common::IGameBoard::addTransport
     */
    void addTransport(std::shared_ptr<Common::Transport> transport,
                              Common::CubeCoordinate coord) override;

    /**
     * @copydoc Common::IGameBoard::moveTransport
     */
    void moveTransport(int id, Common::CubeCoordinate coord) override;

    /**
     * @copydoc Common::IGameBoard::removeTransport
     */
    void removeTransport(int id) override;

    /**
     * @brief changes the background of a flipped tile, so
     * @param coordinate of the hex to be flipped
     */
    void flipTile(Common::CubeCoordinate coord);

    /**
     * @brief showScene, once the scene is done we show it to the player and return the view
     * @return the view in which the scene is shown
     * @pre scene_ must exist
     * @post scene_ is added to QGraphicsView. Exception guarantee: basic
     */
    QGraphicsView *showScene();

    /**
     * @brief gets a pawn belonging to player with playerId
     * @param coordinate which from to look for the pawn
     * @param id of the player whose pawn were looking for
     * @return returns pointer to player pawn,
     * if no pawn of the player is present returns nullptr
     * @post exception guarantee: nothrow
     */
    std::shared_ptr<Common::Pawn> getPlayerPawn(Common::CubeCoordinate coord,
                                                        int playerId);
    /**
     * @brief sets the hex at coord to selected
     * (meaning its outline will be drawn in red)
     * @param coordinate to set selected at
     * @post Exception guarantee: noThrow
     */
    void setSelected(Common::CubeCoordinate coord);

    /**
     * @brief sets the hex at coord to not selected
     * (meaning the outline will be black once more)
     * @param coordinate to change the hex at
     * @post Exception guarantee: nothrow
     */
    void deSelect(Common::CubeCoordinate coord);

    /**
     * @brief Sets the scene to be shown
     * @param scene to add
     * @post Exception Guarantee: nothrow
     */
    void setScene(QGraphicsScene *scene);

    /**
     * @brief returns whether player has any pawns ingame
     * @param player id whose pawn situation we want to taḱe a look at
     * @return true if there is pawns, otherwise false
     * @post Exception guarantee: nothrow
     */
    bool playerHasPawns(int playerId);

    /**
     * @brief Tells whether there are any pawns in the game
     * @return true if there are pawns, otherwise false
     * @post Exception guarantee: nothrow
     */
    bool anyPawnsIngame();

    /**
     * @brief checks that the pawns in _gamePawns are in the hexes
     * where their coordinates say they are, if not then delete
     * the pawn from the _gamePawns map
     * @pre all pawns must be valid
     * @post exception guarantee: basic
     */
    void checkPawnValidity();

    /**
     * @brief checks that the actors in _actors are in the hexes
     * where their hex_ pointer say they are, if not then delete
     * the actor from the _actors map
     * @pre all actors in _actors must be valid
     * @post exception guarantee: basic
     */
    void checkActorValidity();

    /**
     * @brief checks if there is an actor with the given type in
     * the game
     * @param type of the actor we're looking for
     * @return boolean based on whether the actor is present or not
     * @post exception guarantee: no throw
     */
    bool checkActor(std::string type);

    /**
     * @brief checks if there is a transport with the given type in
     * the game
     * @param type of the transport we're looking for
     * @return boolean based on whether the transport is present or not
     * @post exception guarantee: no throw
     */
    bool checkTransport(std::string type);

    /**
     * @brief gets an actor of the specified type from the
     * specified coordinates
     * @param coordinate to look for the actor from
     * @param type of the actor we're looking for
     * @return returns a pointer to the actor, or nullptr
     * if there is no such actor
     * @post exception guarantee: strong
     */
    std::shared_ptr<Common::Actor> getActor(Common::CubeCoordinate coord,
                                            std::string type);

    /**
     * @brief gets a transport of the specified type from the
     * specified coordinates
     * @param coordinate to look for the transport from
     * @param type of the transport we're looking for
     * @return returns a pointer to the transport, or nullptr
     * if there is no such transport
     * @post exception guarantee: strong
     */
    std::shared_ptr<Common::Transport> getTransport(Common::CubeCoordinate coord,
                                                    std::string type);


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

    /**
     * @brief Calls increaseSize-method for all GraphicalHex objects on the board
     */
    void zoomIn();

    /**
     * @brief Calls decreaseSize-method for all GraphicalHex objects on the board
     */
    void zoomOut();

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
    std::map<Common::CubeCoordinate,std::shared_ptr<Common::Hex>> tiles_;
    std::map<Common::CubeCoordinate,std::shared_ptr<Student::GraphicalHex>> graphicTiles_;


    std::map<int, std::shared_ptr<Common::Pawn>> gamePawns_;
    std::map<int, std::shared_ptr<Common::Actor>> actors_;
    std::map<int, std::shared_ptr<Common::Transport>> transports_;
    QGraphicsScene* scene_;

};
}

#endif // GAMEBOARD_HH

