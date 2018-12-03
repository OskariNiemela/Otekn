#ifndef GRAPHICALHEX_HH
#define GRAPHICALHEX_HH

/* Oskari Niemelä 263440
 * Aki Kaipio 267041
 *
 * Header file for the GraphicalHex class
 * Takes care of drawing the hex and any game pieces
 * within it
 */

#include "cubecoordinate.hh"
#include "hex.hh"
#include "pawn.hh"
#include "actor.hh"
#include "transport.hh"

#include <iostream>
#include <cmath>
#include <QWidget>
#include <QGraphicsItem>
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QPolygon>
#include <QPoint>
#include <QColor>
#include <QBrush>
#include <QString>
#include <QImage>

const double PI = 3.14159265359;
const double MIN_SIZE = 20;
const double MAX_SIZE = 40;
const int COLOR_MULTIPLIER = 85;

namespace Student
{

class GraphicalHex : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    /**
     * @brief Constructor
     */
    GraphicalHex();

    /**
     * @brief Sets the clickable area of the item
     * @return returns a QRectF object containing
     * the wanted drawing area
     * @post exception guarantee: no throw
     */
    virtual QRectF boundingRect() const;

    /**
     * @brief Paints the actual hex
     * @param painter, the object doing the painting
     * @param option
     * @param widget
     * @post hex is painted, exception guarantee: basic
     */
    virtual void paint(QPainter *painter,
              const QStyleOptionGraphicsItem *option,
              QWidget *widget);

    /**
     * @brief Draws the shape of the clickable area
     * @return QPainterPath object containing the
     * area constituting the shape of the object
     * @post the shape of the clickable area is set
     * exception guarantee: no throw
     */
    virtual QPainterPath shape() const;

    /**
     * @brief Sets the position of the hex inside
     * the scene based on the cube coordinates
     * given to it
     * @param Coordinate of the hex, in cube
     * coordinates
     * @post the position of the hex is set
     * exception guarantee: nothrow
     */
    void setPosition(Common::CubeCoordinate coord);

    /**
     * @brief Sets a pointer to the "real" hex
     * @param hex that we want to point to
     * @post the "real" hex is set
     * exception guarantee: nothrow
     */
    void setHex(std::shared_ptr<Common::Hex> newHex);

    /**
     * @brief Sets the background color of the hex
     * @post sets the background color exception guarantee: nothrow
     */
    void setBackground();

    /**
     * @brief Sets the background image of the hex
     * @post sets the background image exception guarantee: nothrow
     */
    void setActorOrTransportImage();

    /**
     * @brief Returns the cube coordinates of the
     * graphical hex
     * @return Coordinates of the hex
     * @post exception guarantee: nothrow
     */
    Common::CubeCoordinate getCoordinates() const;

    /**
     * @brief Sets the pressed_ boolean to true,
     * making the outline of the hex red
     * @post exception guarantee: nothrow
     */
    void select();

    /**
     * @brief Sets the pressed_ boolean to false,
     * making the outline black once more
     * @post exception guarantee: nothrow
     */
    void deSelect();

    /**
     * @brief Get the player pawn from the real hex,
     * if there is one
     * @param Id of the player whose pawn we want
     * @return pointer to pawn, or nullptr
     * @post exception guarantee: strong
     */
    std::shared_ptr<Common::Pawn> getPlayerPawn(int playerId);

    /**
     * @brief Increases the _size variable and calculates the new
     * position
     * @post exception guarantee: noThrow
     */
    void increaseSize();

    /**
     * @brief Decreases the _size variable and calculates the new
     * position
     * @post exception guarantee: noThrow
     */
    void decreaseSize();

protected:
    /**
     * @brief ReImplemented mousepressevent
     * @param event
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    bool pressed_;
    Common::CubeCoordinate coordinate_;
    std::shared_ptr<Common::Hex> realHex_;
    QImage actorOrTransportImage_;
    QColor backgroundColor_;
    double size_ = 28.0;

    // Background colors for different tile types
    std::map<std::string, QColor> colorMap_ = {{"Water", QColor{153, 217, 234}},
                                               {"Coral", QColor{255, 186, 253}},
                                               {"Beach", QColor{255, 240, 193}},
                                               {"Forest", QColor{139, 232, 139}},
                                               {"Mountain", QColor{165, 165, 165}},
                                               {"Peak", QColor{209, 209, 209}}};

    // Image paths for actors and transports
    std::map<std::string, QString> imageMap_ = {{"boat", ":Images/boat.png"},
                                                {"dolphin", ":Images/dolphin.png"},
                                                {"shark", ":Images/shark.png"},
                                                {"kraken", ":Images/kraken.png"},
                                                {"seamunster", ":Images/seamonster.png"},
                                                {"vortex", ":Images/vortex.png"}};

signals:
    /**
     * @brief Signal for when we click a graphical hex
     * @param the real hex connected to the graphic hex
     */
    void hexClicked(std::shared_ptr<Common::Hex> hexClick);

public slots:
    /**
     * @brief Updates the graphics of the hex
     */
    void updateGraphicHex();
};

}
#endif // GRAPHICALHEX_HH
