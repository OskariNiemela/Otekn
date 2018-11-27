#include "graphicalhex.hh"

namespace Student
{

graphicalHex::graphicalHex():
    pressed_(false)
{
}

QRectF graphicalHex::boundingRect() const
{
    return QRectF(-_size,-_size,2*_size,2*_size);
}

void graphicalHex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // QPolygon object for the painter to paint
    QPolygon hexShape;

    // Calculate the corners of the hexagon
    double angle_deg;
    double angle_rad;

    for(int i = 1; i <= 6; i++)
    {
        angle_deg = 60 * i - 30;
        angle_rad = pi / 180 * angle_deg;
        hexShape << QPoint(_size * cos(angle_rad), _size * sin(angle_rad));

    }

    QBrush brush(_backgroundColor);
    QPen pen(Qt::black, 1);

    //If the hex is selected
    if (pressed_) {
        pen.setColor(Qt::red);
        pen.setWidth(1);
    }

    // Draw the background
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(brush);
    painter->drawPolygon(hexShape);

    // Draw the actor or transport image if the hex has one on it
    if (!_backgroundImage.isNull()) {
        QRectF imageArea;
        double imageX = -_size * (3.0 / 5.0);
        double imageY = -_size * (3.0 / 5.0);
        imageArea.setRect(imageX, imageY, (6.0 / 5.0) * _size, (6.0 / 5.0) * _size);
        painter->drawImage(imageArea, _backgroundImage);
    }

    // Draw the pawns
    QString pawnMarker = "♟";
    std::vector<std::shared_ptr<Common::Pawn>> pawnsHere
            = realHex_->getPawns();

    for (std::size_t pawn = 0; pawn < pawnsHere.size(); pawn++) {
        QRectF pawnArea;
        double pawnX = cos(pi / 180 * (pawn * 90)) * (_size / 2) - (_size / 4);
        double pawnY = sin(pi / 180 * (pawn * 90)) * (_size / 2) - (_size / 4);
        pawnArea.setRect(pawnX, pawnY, _size, _size);
        pen.setColor(QColor{pawnsHere.at(pawn)->getPlayerId() * 85, 0, 0});
        painter->setPen(pen);
        painter->drawText(pawnArea, pawnMarker);
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
        polygon << QPoint(_size * cos(angle_rad), _size * sin(angle_rad));

    }
    path.addPolygon(polygon);
    return path;

}

void graphicalHex::setPosition(Common::CubeCoordinate coord)
{
    coordinate_ = coord;

    //Calculate the x and y position of the hex from
    //the cube coordinates
    double y_pos = _size * (3.0 / 2.0 * coord.z);
    double x_pos = _size * (sqrt(3) * coord.x  +  sqrt(3) / 2.0 * coord.z);
    setPos(x_pos, y_pos);
}

void graphicalHex::setHex(std::shared_ptr<Common::Hex> newHex)
{
    realHex_ = newHex;
}

void graphicalHex::setBackground()
{
    _backgroundColor = _colorMap.at(realHex_->getPieceType());

}

void graphicalHex::setActorOrTransportImage()
{
    if (!realHex_->getTransports().empty()) {
        _backgroundImage.load(_imageMap.at(realHex_->getTransports().at(0)->getTransportType()));
    }
    else if (!realHex_->getActorTypes().empty()) {
        _backgroundImage.load(_imageMap.at(realHex_->getActorTypes().at(0)));
    }
    else {
        _backgroundImage = QImage();
    }
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

void graphicalHex::increaseSize()
{
    if (_size < MAX_SIZE) {
        _size += 1.0;
    }
    setPosition(coordinate_);
}

void graphicalHex::decreaseSize()
{
    if (_size > MIN_SIZE) {
        _size -= 1.0;
    }
    setPosition(coordinate_);
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
    setActorOrTransportImage();
    update();
}
}
