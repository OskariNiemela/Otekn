#ifndef GRAPHICALWHEEL_HH
#define GRAPHICALWHEEL_HH

#include "wheellayoutparser.hh"
#include "igamerunner.hh"
//Included for pi
#include "graphicalhex.hh"

#include <iostream>
#include <vector>
#include <utility>
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
#include <QGraphicsView>
#include <QFont>


namespace Student {

const int RADIUS = 200;
const QColor WATER_COLOR = QColor{153, 217, 234};
const QColor BUTTON_BGCOLOR = QColor{255, 127, 39};
const int FONT_SIZE = 20;

class GraphicalWheel : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    GraphicalWheel() = default;
    /**
     * @brief Sets the layout for the wheel and sets the arrow to default
     * position
     * @param layout: Information about the actors, transports and their
     * movement options in the wheel
     * @post layout and arrow angle have been set
     */
    void initializeSegments(Common::SpinnerLayout layout);

    /**
     * @brief sets a new angle for the arrow
     * @param pair: Who to move and how much
     */
    void setValue(std::pair<std::string,std::string> pair);

    /**
     * @brief Paints the wheel
     * @param painter, the object doing the painting
     * @param option
     * @param widget
     * @post wheel is painted, exception guarantee: basic
     */
    virtual void paint(QPainter *painter,
              const QStyleOptionGraphicsItem *option,
              QWidget *widget);

    /**
     * @brief Sets the clickable area of the item
     * @return returns a QRectF object containing
     * the wanted drawing area
     * @post exception guarantee: no throw
     */
    QRectF boundingRect() const final;

    /**
     * @brief Draws the shape of the clickable area
     * @return QPainterPath object containing the
     * area constituting the shape of the object
     * @post the shape of the clickable area is set
     * exception guarantee: no throw
     */
    virtual QPainterPath shape() const;

protected:
    /**
     * @brief ReImplemented mousepressevent
     * @param event
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    /**
     * @brief Signal for when we click the wheel
     */
    void wheelClicked();



private:
    Common::SpinnerLayout layout_;
    int segments_ = 0;
    QGraphicsScene *scene_;
    std::pair<std::string,std::string> toMove_;
    double arrowAngle_ = 0.0;


    void drawSegments(QPainter *painter);
    void drawArrow(QPainter *painter, double angle);
    void drawSpinButton(QPainter *painter);
};

}

#endif // GRAPHICALWHEEL_HH
