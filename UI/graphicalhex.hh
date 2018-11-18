#ifndef GRAPHICALHEX_HH
#define GRAPHICALHEX_HH

#include "cubecoordinate.hh"
#include "hex.hh"
#include "pawn.hh"

#include <QWidget>
#include <QGraphicsItem>
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <math.h>
#include <cmath>
#include <QPolygon>
#include <QPoint>
#include <QColor>
#include <QBrush>
#include <QString>

const int SIZE = 28;

namespace Student
{

enum PLAYER_COLORS{Blue,Red,Green,Black};

class graphicalHex : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    graphicalHex();
    QRectF boundingRect() const final;
    void paint(QPainter *painter,
              const QStyleOptionGraphicsItem *option,
              QWidget *widget);

    QPainterPath shape() const;

    void setPosition(Common::CubeCoordinate coord);
    void setHex(std::shared_ptr<Common::Hex> newHex);
    void setColor();

    Common::CubeCoordinate getCoordinates();
    void select();
    void deSelect();
    std::shared_ptr<Common::Pawn> getPlayerPawn(int playerId);

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void hexClicked(std::shared_ptr<Common::Hex> hexClick);
public slots:
    void updateGraphicHex();

private:
    bool pressed_;
    Common::CubeCoordinate coordinate_;
    std::shared_ptr<Common::Hex> realHex_;
    QColor backgroundColor;
};
}
#endif // GRAPHICALHEX_HH
