#include "graphicalhex.hh"

namespace Student
{

GraphicalHex::GraphicalHex():
    pressed_(false)
{
}

QRectF GraphicalHex::boundingRect() const
{
    // A square that is a bit larger than the hex
    return QRectF(-size_, -size_, 2 * size_, 2 * size_);
}

void GraphicalHex::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
{
    // QPolygon object for the painter to paint
    QPolygon hexShape;

    // Calculate the corner points of the hexagon in relation to the
    // center (0,0)
    double angleDeg;
    double angleRad;

    for(int i = 1; i <= 6; ++i)
    {
        angleDeg = (60.0 * i) - 30.0;
        angleRad = (PI / 180.0) * angleDeg;
        hexShape << QPoint(size_ * cos(angleRad), size_ * sin(angleRad));

    }

    QBrush brush(backgroundColor_);
    QPen pen(Qt::black, 1);

    // Borders are painted to red if the user selects this hex
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
    if (!actorOrTransportImage_.isNull()) {
        QRectF imageArea;
        double imageX = -size_ * (3.0 / 5.0);
        double imageY = -size_ * (3.0 / 5.0);
        imageArea.setRect(imageX, imageY, (6.0 / 5.0) * size_,
                                          (6.0 / 5.0) * size_);
        painter->drawImage(imageArea, actorOrTransportImage_);
    }

    // Draw the pawns
    QString pawnMarker = "♟";
    std::vector<std::shared_ptr<Common::Pawn>> pawnsHere
            = realHex_->getPawns();
    std::size_t numberOfPawns = pawnsHere.size();

    for (std::size_t pawn = 0; pawn < numberOfPawns; ++pawn) {
        QRectF pawnArea;
        double pawnX = cos((PI / 180) * (pawn * 90)) * (size_ / 2)
                - (size_ / 4);
        double pawnY = sin((PI / 180) * (pawn * 90)) * (size_ / 2)
                - (size_ / 4);
        pawnArea.setRect(pawnX, pawnY, size_, size_);
        pen.setColor(QColor{pawnsHere.at(pawn)->getPlayerId()
                            * COLOR_MULTIPLIER, 0, 0});
        painter->setPen(pen);
        painter->drawText(pawnArea, pawnMarker);
    }
}

QPainterPath GraphicalHex::shape() const
{
    QPolygon polygon;
    QPainterPath path;

    double angleDeg;
    double angleRad;
    //Make the shape the same as the drawn polygon
    for(int i = 1; i <= 6; ++i)
    {
        angleDeg = (60.0 * i) - 30.0;
        angleRad = (PI / 180.0) * angleDeg;
        polygon << QPoint(size_ * cos(angleRad), size_ * sin(angleRad));

    }
    path.addPolygon(polygon);
    return path;

}

void GraphicalHex::setPosition(Common::CubeCoordinate coord)
{
    coordinate_ = coord;

    //Calculate the x and y position of the hex from
    //the cube coordinates
    double yPos = size_ * ((3.0 / 2.0) * coord.z);
    double xPos = size_ * ((sqrt(3.0) * coord.x) + (sqrt(3.0) / 2.0)
                           * coord.z);
    setPos(xPos, yPos);
}

void GraphicalHex::setHex(std::shared_ptr<Common::Hex> newHex)
{
    realHex_ = newHex;
}

void GraphicalHex::setBackground()
{
    backgroundColor_ = colorMap_.at(realHex_->getPieceType());

}

void GraphicalHex::setActorOrTransportImage()
{
    // If the hex has transports on it, add image of the first one
    if (!realHex_->getTransports().empty()) {
        actorOrTransportImage_.load(imageMap_.at(realHex_->getTransports().
                                                 at(0)->getTransportType()));
    }
    // If the hex has actors on it, add image of the first one
    else if (!realHex_->getActorTypes().empty()) {
        actorOrTransportImage_.load(imageMap_.at(realHex_->getActorTypes().
                                                 at(0)));
    }
    // The image will be empty by default
    else {
        actorOrTransportImage_ = QImage();
    }
}

Common::CubeCoordinate GraphicalHex::getCoordinates() const
{
    return coordinate_;
}

void GraphicalHex::select()
{
    pressed_ = true;
}

void GraphicalHex::deSelect()
{
    pressed_ = false;
}

std::shared_ptr<Common::Pawn> GraphicalHex::getPlayerPawn(int playerId)
{
    //Search the pawns in the hex and find the one matching the player's id
    std::vector<std::shared_ptr<Common::Pawn>> pawns = realHex_->getPawns();
    for(std::shared_ptr<Common::Pawn> pawn:pawns)
    {
        if(pawn->getPlayerId() == playerId)
        {
            return pawn;
        }
    }
    return nullptr;
}

void GraphicalHex::increaseSize()
{
    if (size_ < MAX_SIZE) {
        size_ += 1.0;
    }
    setPosition(coordinate_);
}

void GraphicalHex::decreaseSize()
{
    if (size_ > MIN_SIZE) {
        size_ -= 1.0;
    }
    setPosition(coordinate_);
}

void GraphicalHex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit hexClicked(realHex_);
    update();
    QGraphicsItem::mousePressEvent(event);
}

void GraphicalHex::updateGraphicHex()
{
    setBackground();
    setActorOrTransportImage();
    update();
}
}
