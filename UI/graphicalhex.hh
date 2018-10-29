#ifndef GRAPHICALHEX_HH
#define GRAPHICALHEX_HH

#include "cubecoordinate.hh"
#include "hex.hh"

#include <QWidget>
#include <QGraphicsItem>
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <math.h>
#include <cmath>
#include <QPolygon>
#include <QPoint>

class graphicalHex : public QGraphicsItem
{
public:
    graphicalHex();
    QRectF boundingRect() const final;
    void paint(QPainter *painter,
              const QStyleOptionGraphicsItem *option,
              QWidget *widget);

    QPainterPath shape() const;

    void setPosition(Common::CubeCoordinate coord);
    void setHex(std::shared_ptr<Common::Hex> newHex);
protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

public slots:


private:
    bool pressed_;
    std::shared_ptr<Common::Hex> realHex_;
};

#endif // GRAPHICALHEX_HH
