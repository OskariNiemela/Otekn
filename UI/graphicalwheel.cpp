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
    QColor backgroundColor;
    backgroundColor.setRgb(153, 217, 234);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(backgroundColor);

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(1);

    QFont font = painter->font();
    font.setPixelSize(20);

    painter->setPen(pen);
    painter->setBrush(brush);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setFont(font);

    QImage animalImage;

    // Segments
    Common::SpinnerLayout::iterator animal;
    int currentSegment = 0;
    for (animal = _layout.begin(); animal != _layout.end(); animal++) {

        // Different image for each animal
        if (animal->first == "dolphin") {
            animalImage.load(":/Images/dolphin.png");
        }
        else if (animal->first == "kraken") {
            animalImage.load(":/Images/kraken.png");
        }
        else if (animal->first == "seamunster") {
            animalImage.load(":/Images/seamonster.png");
        }
        else if (animal->first == "shark") {
            animalImage.load(":/Images/shark.png");
        }

        for (std::pair<std::string, unsigned> steps : animal->second) {

            // Calculate segment size and draw it
            double startAngle = 360.0 / _segments * currentSegment;
            double spanAngle = 360.0 / _segments;
            painter->drawPie(-RADIUS, -RADIUS, 2*RADIUS, 2*RADIUS, 16*startAngle, 16*spanAngle);

            // Calculate image coordinates and draw it
            QRectF imageArea;
            double imageX = (4.0/5) * RADIUS * cos((startAngle + (1.0/2) * spanAngle) * M_PI / 180) - 20;
            double imageY = -(4.0/5) * RADIUS * sin((startAngle + (1.0/2) * spanAngle) * M_PI / 180) - 20;
            imageArea.setRect(imageX, imageY, 40, 40);
            painter->drawImage(imageArea, animalImage);

            // Draw the amount of steps
            QString stepString = QString::fromStdString(std::get<0>(steps));
            QRectF textArea;
            double textX = (3.0/5) * RADIUS * cos((startAngle + (1.0/2) * spanAngle) * M_PI / 180) - 10;
            double textY = -(3.0/5) * RADIUS * sin((startAngle + (1.0/2) * spanAngle) * M_PI / 180) - 10;
            textArea.setRect(textX, textY, 30, 30);
            painter->drawText(textArea, stepString);

            currentSegment++;
        }
    }

    // Draw the arrow


    // Draw the spin button
    brush.setColor(Qt::red);
    painter->setBrush(brush);
    painter->drawEllipse(QPoint(0, 0), 30, 30);
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

}
