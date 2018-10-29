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
    QRectF rect = boundingRect();

    if(pressed_)
    {
        QPen pen(Qt::red,3);
        painter->setPen(pen);
        QPainterPath path;

        int angle_deg = 60*1 -30;
        double angle_rad = M_PI/180 * angle_deg;

        path.moveTo(0+50*cos(angle_rad),0+50*sin(angle_rad));

        for(int i = 2; i<=7;i++)
        {
            angle_deg = 60*i-30;
            angle_rad = M_PI/180*angle_deg;
            path.lineTo(0+50*cos(angle_rad),0+50*sin(angle_rad));
            path.moveTo(0+50*cos(angle_rad),0+50*sin(angle_rad));

        }


        painter->drawPath(path);
    }
    else
    {
        QPen pen(Qt::black,3);
        painter->setPen(pen);
        QPainterPath path;

        int angle_deg = 60*1 -30;
        double angle_rad = M_PI/180 * angle_deg;

        path.moveTo(0+50*cos(angle_rad),0+50*sin(angle_rad));

        for(int i = 2; i<=7;i++)
        {
            angle_deg = 60*i-30;
            angle_rad = M_PI/180*angle_deg;
            path.lineTo(0+50*cos(angle_rad),0+50*sin(angle_rad));
            path.moveTo(0+50*cos(angle_rad),0+50*sin(angle_rad));

        }


        painter->drawPath(path);
    }

}

//Asettaa graafisen hexan muodon johon sitä voi painaa
QPainterPath graphicalHex::shape() const
{
    QPolygon polygon;


    QPainter* painter = new QPainter();
    QPen pen(Qt::black,1);
    painter->setPen(pen);

    QPainterPath path;

    int angle_deg = 60*1 -30;
    double angle_rad = M_PI/180 * angle_deg;

    polygon << QPoint(50*cos(angle_rad),50*sin(angle_rad));

    for(int i = 2; i<=6;i++)
    {
        angle_deg = 60*i-30;
        angle_rad = M_PI/180*angle_deg;
        polygon<<QPoint(50*cos(angle_rad),50*sin(angle_rad));

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
                xpos -= 50*sqrt(3);
            }
            else if(coord.x>0 and coord.y<0)
            {
                coord.x = coord.x-1;
                coord.y = coord.y+1;
                xpos += 50*sqrt(3);
            }
            else if(coord.z<0 and coord.y>0)
            {
                coord.z = coord.z+1;
                coord.y = coord.y-1;
                xpos -= 25*sqrt(3);
                ypos -= 50*2-25;
            }
            else if(coord.x>0 and coord.z<0)
            {
                coord.z = coord.z+1;
                coord.x = coord.x-1;
                xpos += 25*sqrt(3);
                ypos -= 50*2-25;
            }
            else if(coord.x<0 and coord.z>0)
            {
                coord.z = coord.z-1;
                coord.x = coord.x+1;
                ypos += 50*2-25;
                xpos -= 25*sqrt(3);
            }
            else if(coord.z>0 and coord.y<0)
            {
                coord.z = coord.z-1;
                coord.y = coord.y+1;
                ypos += 50*2-25;
                xpos += 25*sqrt(3);
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
