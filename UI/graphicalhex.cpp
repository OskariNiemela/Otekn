#include "graphicalhex.hh"

namespace Common
{

graphicalHex::graphicalHex():
    pressed_(false)
{
}
//Asettaa hexan maksimi piirto alueen
QRectF graphicalHex::boundingRect() const
{
    return QRectF(-50,-50,100,100);
}

//Piirtää hexan
void graphicalHex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Polygon-olio hexShape painteria varten
    QPolygon hexShape;

    // Lasketaan kuusikulmion kulmapisteet
    double angle_deg;
    double angle_rad;

    for(int i = 1; i <= 6; i++)
    {
        angle_deg = 60 * i - 30;
        angle_rad = M_PI / 180 * angle_deg;
        hexShape << QPoint(SIZE * cos(angle_rad), SIZE * sin(angle_rad));

    }

    QBrush brush(backgroundColor);
    QPen pen(Qt::black, 1);
    if (pressed_) {
        pen.setColor(Qt::red);
        pen.setWidth(1);
    }

    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(brush);
    painter->drawPolygon(hexShape);
}

//Asettaa graafisen hexan muodon johon sitä voi painaa
QPainterPath graphicalHex::shape() const
{
    QPolygon polygon;
    QPainterPath path;

    double angle_deg;
    double angle_rad;
    for(int i = 1; i <= 6; i++)
    {
        angle_deg = 60 * i - 30;
        angle_rad = M_PI / 180 * angle_deg;
        polygon << QPoint(SIZE * cos(angle_rad), SIZE * sin(angle_rad));

    }
    path.addPolygon(polygon);
    return path;

}
/*
 * Asettaa hexan graafiseen sceneen oikeisiin coordinaatteihin
 * Param: hexan koordinaatit CubeCoordinaattina
 *
 */
void graphicalHex::setPosition(Common::CubeCoordinate coord)
{

    double y_pos = (-3 * SIZE * coord.z) / 2 + 250;
    double x_pos = SIZE * (sqrt(3) * coord.y  +  sqrt(3)/2 * coord.z);
    setPos(x_pos, y_pos);
}

//Asettaa graafisen hexan koodihexa parin
void graphicalHex::setHex(std::shared_ptr<Common::Hex> newHex)
{
    realHex_ = newHex;
}

void graphicalHex::setColor()
{
    if (realHex_->getPieceType() == "Peak") {
        backgroundColor.setRgb(198, 198, 198);
    }
    else if (realHex_->getPieceType() == "Mountain") {
        backgroundColor.setRgb(132, 132, 132);
    }
    else if (realHex_->getPieceType() == "Forest") {
        backgroundColor.setRgb(48, 178, 56);
    }
    else if (realHex_->getPieceType() == "Beach") {
        backgroundColor.setRgb(219, 210, 129);
    }
    else if (realHex_->getPieceType() == "Water") {
        backgroundColor.setRgb(112, 187, 224);
    }
    else if (realHex_->getPieceType() == "Coral") {
        backgroundColor.setRgb(237, 216, 255);
    }
}

//Kun hiirellä painetaan hexaa
void graphicalHex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed_ = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void graphicalHex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed_ = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
}
