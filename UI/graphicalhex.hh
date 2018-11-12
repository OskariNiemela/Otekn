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
    void addPawn(std::shared_ptr<Common::Pawn> pawn);
    std::shared_ptr<Common::Pawn> getPawn;
    Common::CubeCoordinate getCoordinates();
    void setSelect();
protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void hexClicked(std::shared_ptr<Common::Hex> hexClick);
public slots:


private:
    bool pressed_;
    std::shared_ptr<Common::Hex> realHex_;
    Common::CubeCoordinate coordinate_;
    std::map<int,std::shared_ptr<Common::Pawn>> pawns_;
    QColor backgroundColor;
};
}
#endif // GRAPHICALHEX_HH
