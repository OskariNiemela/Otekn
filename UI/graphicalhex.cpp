#include "graphicalhex.hh"

namespace Student
{

graphicalHex::graphicalHex():
    pressed_(false)
{
}

QRectF graphicalHex::boundingRect() const
{
    return QRectF(-SIZE,-SIZE,2*SIZE,2*SIZE);
}

void graphicalHex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // QPolygon object for the painter to paint
    QPolygon hexShape;

    // Calculate the hexes points
    double angle_deg;
    double angle_rad;

    for(int i = 1; i <= 6; i++)
    {
        angle_deg = 60 * i - 30;
        angle_rad = pi / 180 * angle_deg;
        hexShape << QPoint(SIZE * cos(angle_rad), SIZE * sin(angle_rad));

    }
    //sets the background image
    QBrush brush(_backgroundImage);
    QTransform transform;
    transform.scale(0.35, 0.4);
    transform.translate(-60, -60);
    brush.setTransform(transform);

    QPen pen(Qt::black, 1);

    //If the hex is selected
    if (pressed_) {
        pen.setColor(Qt::red);
        pen.setWidth(1);
    }

    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(brush);
    painter->drawPolygon(hexShape);

    QString pawnMarker = "X";
    std::vector<std::shared_ptr<Common::Pawn>> pawnsHere
            = realHex_->getPawns();

    std::vector<std::shared_ptr<Common::Pawn>>::const_iterator vecIterator
            = pawnsHere.begin();

    //Draw the pawns inside the hex
    for(int c=0;c<=3;c++)
    {
        if (vecIterator == pawnsHere.end())
        {
            break;
        }
        angle_deg = 140*c-120;
        angle_rad = pi/180*angle_deg;


        switch(vecIterator->get()->getPlayerId())
        {
            case 0:
                pen.setColor(Qt::blue);
                painter->setPen(pen);
                painter->drawText(QPoint( (SIZE/2) * cos(angle_rad),
                                          (SIZE/2) * sin(angle_rad)),
                                          pawnMarker);
            break;

            case 1:
                pen.setColor(Qt::red);
                painter->setPen(pen);
                painter->drawText(QPoint( (SIZE/2) * cos(angle_rad),
                                          (SIZE/2) * sin(angle_rad)),
                                           pawnMarker);
            break;

            case 2:
                pen.setColor(Qt::green);
                painter->setPen(pen);
                painter->drawText(QPoint( (SIZE/2) * cos(angle_rad),
                                          (SIZE/2) * sin(angle_rad)),
                                          pawnMarker);
            break;

            default:
                pen.setColor(Qt::black);
                painter->setPen(pen);
                painter->drawText(QPoint( (SIZE/2) * cos(angle_rad),
                                          (SIZE/2) * sin(angle_rad)),
                                          pawnMarker);
            break;

        }


        ++vecIterator;
    }

}

QPainterPath graphicalHex::shape() const
{
    QPolygon polygon;
    QPainterPath path;

    double angle_deg;
    double angle_rad;
    //Make the shape the same as the drawn polygon
    for(int i = 1; i <= 6; i++)
    {
        angle_deg = 60 * i - 30;
        angle_rad = pi / 180 * angle_deg;
        polygon << QPoint(SIZE * cos(angle_rad), SIZE * sin(angle_rad));

    }
    path.addPolygon(polygon);
    return path;

}

void graphicalHex::setPosition(Common::CubeCoordinate coord)
{
    coordinate_ = coord;
    //Calculate the x and y position of the hex from
    //the cube coordinates
    double y_pos = (-3 * SIZE * coord.z) / 2 + 250;
    double x_pos = SIZE * (sqrt(3) * coord.y  +  sqrt(3)/2 * coord.z);
    setPos(x_pos, y_pos);
}

void graphicalHex::setHex(std::shared_ptr<Common::Hex> newHex)
{
    realHex_ = newHex;
}

void graphicalHex::setBackground()
{
    // Actors on tile
    if (!realHex_->getActorTypes().empty()) {
        if (realHex_->getActorTypes().at(0) == "shark") {
            _backgroundImage.load(":Images/shark.png");
        }
        else if (realHex_->getActorTypes().at(0) == "seamunster") {
            _backgroundImage.load(":Images/seamonster.png");
        }
        else if (realHex_->getActorTypes().at(0) == "kraken") {
            _backgroundImage.load(":Images/kraken.png");
        }
        else{
            _backgroundImage.load(":Images/vortex.png");
        }
    }
    // Transports on tile
    else if (!realHex_->getTransports().empty()) {
        if (realHex_->getTransports().at(0)->getTransportType() == "dolphin") {
            _backgroundImage.load(":Images/dolphin.png");
        }
        else{
            _backgroundImage.load(":Images/boat.png");
        }
    }
    // Background color based on piece type
    else {
        if (realHex_->getPieceType() == "Peak") {
            _backgroundImage.load(":Images/peak.png");
        }
        else if (realHex_->getPieceType() == "Mountain") {
            _backgroundImage.load(":Images/mountain.png");
        }
        else if (realHex_->getPieceType() == "Forest") {
            _backgroundImage.load(":Images/forest.png");
        }
        else if (realHex_->getPieceType() == "Beach") {
            _backgroundImage.load(":Images/beach.png");
        }
        else if (realHex_->getPieceType() == "Water") {
            _backgroundImage.load(":Images/water.png");
        }
        else{
            _backgroundImage.load(":Images/coral.png");
        }
    }
    update();
}


Common::CubeCoordinate graphicalHex::getCoordinates() const
{
    return coordinate_;
}

void graphicalHex::select()
{
    pressed_ = true;
}

void graphicalHex::deSelect()
{
    pressed_ = false;
}




std::shared_ptr<Common::Pawn> graphicalHex::getPlayerPawn(int playerId)
{
    std::vector<std::shared_ptr<Common::Pawn>> pawns = realHex_->getPawns();
    //Search the pawns in the hex and finds the one matching the player id
    for(std::shared_ptr<Common::Pawn> pawn:pawns)
    {
        if(pawn->getPlayerId() == playerId)
        {
            return pawn;
        }
    }

    return nullptr;
}


void graphicalHex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    emit hexClicked(realHex_);
    update();
    QGraphicsItem::mousePressEvent(event);
}

void graphicalHex::updateGraphicHex()
{
    setBackground();
    update();
}
}
