#ifndef GRAPHICALHEX_HH
#define GRAPHICALHEX_HH

#include "cubecoordinate.hh"
#include "hex.hh"
#include "pawn.hh"
#include "actor.hh"
#include "transport.hh"

#include <iostream>
#include <QWidget>
#include <QGraphicsItem>
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <cmath>
#include <QPolygon>
#include <QPoint>
#include <QColor>
#include <QBrush>
#include <QString>
#include <QImage>
#include <QTransform>

const int SIZE = 28;
const double pi = 3.14159265359;

namespace Student
{

enum PLAYER_COLORS{Blue,Red,Green,Black};

class graphicalHex : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     */
    graphicalHex();
    /**
     * @brief Sets the clickable area of the item
     * @return returns a QRectF object containing
     * the wanted drawing area
     * @post exception guarantee: no throw
     */
    QRectF boundingRect() const;

    /**
     * @brief Paints the actual hex
     * @param painter, the object doing the painting
     * @param option
     * @param widget
     * @post hex is painted, exception guarantee: basic
     */
    void paint(QPainter *painter,
              const QStyleOptionGraphicsItem *option,
              QWidget *widget);

    /**
     * @brief Draws the shape of the clickable area
     * @return QPainterPath object containing the
     * area constituting the shape of the object
     * @post the shape of the clickable area is set
     * exception guarantee: no throw
     */
    QPainterPath shape() const;

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
     * @brief Sets the background image of the hex
     * @post sets the background exception guarantee: nothrow
     */
    void setBackground();

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

protected:
    /**
     * @brief ReImplemented mousepressevent
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


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

private:
    bool pressed_;
    Common::CubeCoordinate coordinate_;
    std::shared_ptr<Common::Hex> realHex_;
    QColor backgroundColor;
    QImage _backgroundImage;
};
}
#endif // GRAPHICALHEX_HH
