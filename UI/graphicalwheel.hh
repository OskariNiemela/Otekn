#ifndef GRAPHICALWHEEL_HH
#define GRAPHICALWHEEL_HH

#include "wheellayoutparser.hh"
#include "igamerunner.hh"
//Included for pi
#include "graphicalhex.hh"

#include <iostream>
#include <vector>
#include <utility>
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
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QFont>
#include <QString>


namespace Student {

const int RADIUS = 200;

class GraphicalWheel : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    GraphicalWheel() = default;
    void initializeSegments(Common::SpinnerLayout layout);
    void setValue(std::pair<std::string,std::string> pair);
    void paint(QPainter *painter,
              const QStyleOptionGraphicsItem *option,
              QWidget *widget);
    QRectF boundingRect() const final;
    QPainterPath shape() const;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void wheelClicked();



private:
    Common::SpinnerLayout _layout;
    int _segments = 0;
    QGraphicsScene* _scene;
    std::pair<std::string,std::string> _toMove;
    double _arrowAngle = 0.0;

    void drawSegments(QPainter *painter);
    void drawArrow(QPainter *painter, double angle);
    void drawSpinButton(QPainter *painter);
};

}

#endif // GRAPHICALWHEEL_HH
