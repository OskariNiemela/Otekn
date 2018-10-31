#include "graphicalhex.hh"

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
    //Asettaa koordinaatteihin 250,250 jos koordinaatti on 0,0,0
    if((coord.x==0)and(coord.y==0)and(coord.z==0))
    {
        setPos(250,250);
    }
    else
    {

        double xpos = 250;
        double ypos = 250;
        //Liikutetaan xpos ja ypos kunnes olemme oikeassa paikassa (eli koordinaatit on 0,0,0)
        while(coord.x!=0 or coord.y!=0 or coord.z!=0)
        {
            if(coord.x<0 and coord.y>0)
            {
                coord.x = coord.x+1;
                coord.y = coord.y-1;
                xpos -= SIZE * sqrt(3);
            }
            else if(coord.x>0 and coord.y<0)
            {
                coord.x = coord.x-1;
                coord.y = coord.y+1;
                xpos += SIZE * sqrt(3);
            }
            else if(coord.z<0 and coord.y>0)
            {
                coord.z = coord.z+1;
                coord.y = coord.y-1;
                xpos -= (SIZE / 2) * sqrt(3);
                ypos -= SIZE * 2 - (SIZE / 2);
            }
            else if(coord.x>0 and coord.z<0)
            {
                coord.z = coord.z+1;
                coord.x = coord.x-1;
                xpos += (SIZE / 2) *sqrt(3);
                ypos -= SIZE * 2- (SIZE / 2);
            }
            else if(coord.x<0 and coord.z>0)
            {
                coord.z = coord.z-1;
                coord.x = coord.x+1;
                ypos += SIZE * 2- (SIZE / 2);
                xpos -= (SIZE / 2) * sqrt(3);
            }
            else if(coord.z>0 and coord.y<0)
            {
                coord.z = coord.z-1;
                coord.y = coord.y+1;
                ypos += SIZE * 2- (SIZE / 2);
                xpos += (SIZE / 2) * sqrt(3);
            }
        }
        setPos(xpos,ypos);
    }
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
