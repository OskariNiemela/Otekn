#include "graphicalwheel.hh"

namespace Student {
GraphicalWheel::GraphicalWheel()
{

}

void GraphicalWheel::initializeSegments(Common::SpinnerLayout layout)
{
    // Make a copy of the layout
    _layout = layout;

    // Calculate how many segments needs to be drawn
    _segments = 0;
    for (Common::SpinnerLayout::iterator it = _layout.begin(); it != _layout.end(); it++) {
        for (auto steps : _layout.at(it->first)) {
            _segments++;
        }
    }
}

void GraphicalWheel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor segmentColor{255, 255, 255};
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(1);
    QBrush brush;

    // Segments
    Common::SpinnerLayout::iterator animal;
    int currentSegment = 0;
    for (animal = _layout.begin(); animal != _layout.end(); animal++) {

        // Different background color for each animal
        if (animal->first == "dolphin") {
            segmentColor.setRgb(138, 243, 255);
        }
        else if (animal->first == "kraken") {
            segmentColor.setRgb(248, 182, 197);
        }
        else if (animal->first == "seamunster") {
            segmentColor.setRgb(107, 233, 209);
        }
        else if (animal->first == "shark") {
            segmentColor.setRgb(192, 192, 192);
        }

        brush.setColor(segmentColor);

        for (auto steps : animal->second) {
            QRectF segmentRect{RADIUS, RADIUS, 2*RADIUS, 2*RADIUS};
            int startAngle = 5760 / _segments * currentSegment;
            int spanAngle = 5760 / _segments;
            painter->drawPie(segmentRect, startAngle, spanAngle);
        }
    }

    // Paint the spin button
    // Paint the arrow
}

QRectF GraphicalWheel::boundingRect() const
{
    return QRectF(-RADIUS, -RADIUS, 2*RADIUS, 2*RADIUS);
}

QPainterPath GraphicalWheel::shape() const
{
    QPainterPath path;
    path.addEllipse(QPointF(0, 0), RADIUS*2, RADIUS*2);
    return path;
}

void GraphicalWheel::setScene(QGraphicsScene *scene)
{
    _scene = scene;
}

QGraphicsView *GraphicalWheel::showScene()
{
    QGraphicsView* view = new QGraphicsView(_scene);
    return view;
}

}
