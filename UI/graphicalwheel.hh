#ifndef GRAPHICALWHEEL_HH
#define GRAPHICALWHEEL_HH

#include "wheellayoutparser.hh"
#include "igamerunner.hh"

#include <iostream>
#include <vector>
#include <utility>
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
#include <QImage>
#include <QTransform>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QFont>
#include <QString>

namespace Student {

const int RADIUS = 200;
const int BUTTON_RADIUS = 30;

class GraphicalWheel : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    GraphicalWheel();
    void initializeSegments(Common::SpinnerLayout layout);
    void paint(QPainter *painter,
              const QStyleOptionGraphicsItem *option,
              QWidget *widget);
    QRectF boundingRect() const final;
    QPainterPath shape() const;

private:
    Common::SpinnerLayout _layout;
    int _segments = 0;
    QGraphicsScene* _scene;
    std::pair<std::string,std::string> _toMove;
};

}

#endif // GRAPHICALWHEEL_HH
