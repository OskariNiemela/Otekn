#ifndef GRAPHICALWHEEL_HH
#define GRAPHICALWHEEL_HH

#include "wheellayoutparser.hh"
#include "igamerunner.hh"

#include <iostream>
#include <vector>
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

namespace Student {

const int RADIUS = 100;
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
    void setScene(QGraphicsScene *scene);
    QGraphicsView *showScene();

private:
    Common::SpinnerLayout _layout;
    int _segments = 0;
    QGraphicsScene* _scene;
};

}

#endif // GRAPHICALWHEEL_HH
