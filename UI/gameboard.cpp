#include "gameboard.hh"
#include <iostream>


namespace Student
{



GameBoard::GameBoard():
    scene_(nullptr)
{

}

GameBoard::~GameBoard()
{
    if(scene_!=nullptr)
    {
        delete(scene_);
    }
}

int GameBoard::checkTileOccupation(Common::CubeCoordinate tileCoord) const
{
    // Onko ruutu olemassa
    if (tiles_.find(tileCoord) == tiles_.end()) {
        return -1;
    }

    // Pawnien lukumäärä
    return tiles_.at(tileCoord)->getPawnAmount();
}

bool GameBoard::isWaterTile(Common::CubeCoordinate tileCoord) const
{
    // Onko ruutu olemassa
    if (tiles_.find(tileCoord) == tiles_.end()) {
        return false;
    }

    if (tiles_.at(tileCoord)->getPieceType() == "Water") {
        return true;
    }

    return false;
}

std::shared_ptr<Common::Hex> GameBoard::getHex(Common::CubeCoordinate hexCoord) const
{
    if (tiles_.find(hexCoord) != tiles_.end())
    {
        return tiles_.at(hexCoord);
    }
    return nullptr;
}

void GameBoard::addPawn(int playerId, int pawnId)
{
    //The coordinates that by default we add the pawns to is 0,0,0
    Common::CubeCoordinate coord(0,0,0);
    std::shared_ptr<Common::Pawn> newPawn = std::make_shared<Common::Pawn>();
    newPawn->setId(pawnId,playerId);
    newPawn->setCoordinates(coord);
    tiles_[coord]->addPawn(newPawn);
    gamePawns_[pawnId] = newPawn;

}

void GameBoard::addPawn(int playerId, int pawnId, Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Pawn> newPawn = std::make_shared<Common::Pawn>();
    newPawn->setId(pawnId,playerId);
    newPawn->setCoordinates(coord);
    tiles_[coord]->addPawn(newPawn);
    gamePawns_[pawnId] = newPawn;
}

void GameBoard::movePawn(int pawnId, Common::CubeCoordinate pawnCoord)
{
    if ((tiles_.find(pawnCoord) == tiles_.end())
            || (gamePawns_.find(pawnId)==gamePawns_.end()))
    {
        return;
    }
    if(tiles_.at(pawnCoord)->getPieceType() != "Coral")
    {
        std::shared_ptr<Common::Pawn> movingPawn= gamePawns_.at(pawnId);

        //Deselect the graphic tile that were moving from
        graphicTiles_.at(movingPawn->getCoordinates())->deSelect();

        //remove the pawn from the coordinate it is in before moving
        tiles_.at(movingPawn->getCoordinates())->removePawn(movingPawn);

        //Set the new coordinate for the pawn
        gamePawns_.at(pawnId)->setCoordinates(pawnCoord);
        //Add the pawn at the appropriate hex coordinate
        tiles_.at(pawnCoord)->addPawn(movingPawn);

    }
    //If were moving into a coral tile
    else
    {

        std::shared_ptr<Common::Pawn> movingPawn= gamePawns_.at(pawnId);

        graphicTiles_.at(movingPawn->getCoordinates())->deSelect();

        //Remove the pawn from the game
        tiles_.at(movingPawn->getCoordinates())->removePawn(movingPawn);
        gamePawns_.erase(pawnId);

        //And give the player a point for a job well done
        emit hexScore();
    }

}

void GameBoard::removePawn(int pawnId)
{
    if(gamePawns_.find(pawnId) != gamePawns_.end())
    {
        std::shared_ptr<Common::Pawn> pawnRemoved = gamePawns_.at(pawnId);
        gamePawns_.erase(pawnId);
        tiles_.at(pawnRemoved->getCoordinates())->removePawn(pawnRemoved);
    }
}

void GameBoard::addActor(std::shared_ptr<Common::Actor> actor,
                         Common::CubeCoordinate actorCoord)
{
    //Checks that the hex and the actor exist
    if ((tiles_.find(actorCoord) != tiles_.end()) && (actor != nullptr)) {

        // Add an actor to the hex
        actor->addHex(tiles_.at(actorCoord));

        // Adds the actor to a map
        actors_.insert(std::pair<int, std::shared_ptr<Common::Actor>>(
                           actor->getId(), actor));
    }
}

void GameBoard::moveActor(int actorId, Common::CubeCoordinate actorCoord)
{
    // Check if the coordinates exist
    if (tiles_.find(actorCoord) != tiles_.end()) {

        // Call the move function
        actors_.at(actorId)->move(tiles_.at(actorCoord));
        actors_.at(actorId)->doAction();
    }
}

void GameBoard::removeActor(int actorId)
{
    if (actors_.find(actorId) != actors_.end()) {
        std::shared_ptr<Common::Actor> actor = actors_.at(actorId);
        std::shared_ptr<Common::Hex> hex = actor->getHex();
        hex->removeActor(actor);
        actors_.erase(actorId);
    }
}

void GameBoard::addHex(std::shared_ptr<Common::Hex> newHex)
{
    //Add hex to hex map
    tiles_[newHex->getCoordinates()] = newHex;
    std::shared_ptr<GraphicalHex> hex = std::make_shared<GraphicalHex>();

    if(scene_ != nullptr)
    {
        scene_->addItem(hex.get());
        //Sets the position of the graphical hex in the scene
        hex->setPosition(newHex->getCoordinates());
        //Links the "real" hex and the graphical representation
        hex->setHex(newHex);
        hex->setBackground();
    }


    //Add graphical hex to its own map
    graphicTiles_[hex->getCoordinates()] = hex;

    //Connect the hexclicked signal to our hexClick slot
    //Needed to process hex clicks
    connect(hex.get(),&GraphicalHex::hexClicked,this,&GameBoard::hexClick);

    //Connects our hexUpdate to graphical hexes updateGraphicHex,
    //needed to make the hexes update when moving pawns for example.
    connect(this,&GameBoard::hexUpdate,hex.get(),
            &GraphicalHex::updateGraphicHex);

}

void GameBoard::addTransport(std::shared_ptr<Common::Transport> transport,
                             Common::CubeCoordinate coord)
{
    if(tiles_.find(coord) != tiles_.end())
    {
        transport->addHex(tiles_.at(coord));
        transports_[transport->getId()] = transport;
    }

}

void GameBoard::moveTransport(int id, Common::CubeCoordinate coord)
{

    if (tiles_.find(coord) != tiles_.end())
    {
    //If we find the transport in our transport map
        if(transports_.find(id)!=transports_.end())
        {
            //Move the found transport to the desired coordinates
            std::shared_ptr<Common::Transport> transport =transports_.at(id);
            transport->move(tiles_.at(coord));
        }
    }
}

void GameBoard::removeTransport(int id)
{

    if(transports_.find(id)!=transports_.end())
    {
        // Remove transport from hex and transports_ map
        std::shared_ptr<Common::Transport> transport = transports_.at(id);
        std::shared_ptr<Common::Hex> hex = transport->getHex();

        hex->removeTransport(transport);
        transports_.erase(id);
    }


}

void GameBoard::flipTile(Common::CubeCoordinate coord)
{


    if(graphicTiles_.find(coord) != graphicTiles_.end())
    {
       // Jos ruudussa on transport
       graphicTiles_.at(coord)->setBackground();
    }

     // If the tile has an actor, do its action
    if (tiles_.at(coord)->getActors().size() != 0)
    {
        tiles_.at(coord)->getActors().at(0)->doAction();

    }


}


QGraphicsView* GameBoard::showScene()
{
    //Once the view has been built, return it to the mainwindow
    QGraphicsView* view = new QGraphicsView(scene_);
    return view;
}

std::shared_ptr<Common::Pawn> GameBoard::getPlayerPawn(
        Common::CubeCoordinate coord,
        int playerId)
{
    if(graphicTiles_.find(coord) != graphicTiles_.end())
    {
        return graphicTiles_.at(coord)->getPlayerPawn(playerId);
    }
    return nullptr;
}

void GameBoard::setSelected(Common::CubeCoordinate coord)
{
    if(graphicTiles_.find(coord)!=graphicTiles_.end())
    {
        graphicTiles_.at(coord)->select();
    }

}

void GameBoard::deSelect(Common::CubeCoordinate coord)
{
    if(graphicTiles_.find(coord)!=graphicTiles_.end())
    {
        graphicTiles_.at(coord)->deSelect();
    }
}

void GameBoard::setScene(QGraphicsScene* scene)
{
    scene_ = scene;
}

void GameBoard::hexClick(std::shared_ptr<Common::Hex> clickedHex)
{
    //When hex is clicked, emit it to the mainwindow which will actually
    //process the click
    emit hexClicked(clickedHex);
}

void GameBoard::updateHexes()
{
    //Updates all the appearances of the hexes
    emit hexUpdate();
}



bool GameBoard::playerHasPawns(int playerId)
{
    //Make a for loop that goes through the pawns we have in a map
    std::map<int,
            std::shared_ptr<Common::Pawn>>::const_iterator end = gamePawns_.end();
    for(std::map<int,std::shared_ptr<Common::Pawn>>::const_iterator
        it =gamePawns_.begin();
        it!=end;++it)
    {
        if(it->second->getPlayerId() == playerId)
        {
            return true;
        }
    }

    return false;
}

bool GameBoard::anyPawnsIngame()
{
    if(gamePawns_.size()>0)
    {
        return true;
    }
    return false;
}

void GameBoard::checkPawnValidity()
{
    std::map<int, std::shared_ptr<Common::Pawn>>::iterator
            allPawns = gamePawns_.begin();
    while(allPawns!=gamePawns_.end())
    {
        std::shared_ptr<Common::Pawn> pawn = allPawns->second;
        //Check if pawn is in the pawn map of the hex it is supposed to be in
        Common::CubeCoordinate coordinate = pawn->getCoordinates();
        if(tiles_.at(coordinate)->givePawn(pawn->getId()) == nullptr)
        {
            allPawns = gamePawns_.erase(allPawns);
        }
        else
        {
            ++allPawns;
        }

    }
}

void GameBoard::checkActorValidity()
{
    std::map<int, std::shared_ptr<Common::Actor>>::iterator
            actor = actors_.begin();
    while(actor != actors_.end())
    {
        std::shared_ptr<Common::Hex> hex = actor->second->getHex();
        //Check if the actor is in the hexes actor map
        if(hex->giveActor(actor->second->getId()) == nullptr)
        {
            actor = actors_.erase(actor);
        }
        else
        {
            ++actor;
        }
    }
}

bool GameBoard::checkActor(std::string type)
{
    std::map<int,std::shared_ptr<Common::Actor>>::const_iterator it
            = actors_.begin();
    //Checks that there is an actor of the specified type in our actors map
    while(it != actors_.end())
    {
        if(it->second->getActorType() == type)
        {
            return true;
        }
        ++it;
    }
    return false;

}

bool GameBoard::checkTransport(std::string type)
{
    std::map<int,std::shared_ptr<Common::Transport>>::const_iterator it
            = transports_.begin();
    //Checks that there is an actor of the specified type in our actors map
    while(it != transports_.end())
    {
        if(it->second->getTransportType() == type)
        {
            return true;
        }
        ++it;
    }
    return false;
}

std::shared_ptr<Common::Actor> GameBoard::getActor(Common::CubeCoordinate coord,
                                                   std::string type)
{
    if(tiles_.find(coord)!=tiles_.end())
    {
        //Get the actors and put them into a vector
        std::vector<std::shared_ptr<Common::Actor>> actors =tiles_.at(coord)->getActors();
        for(std::shared_ptr<Common::Actor> actor:actors)
        {
            //If the actors type matches the specific type we're looking for
            //return a pointer to it
            if(actor->getActorType()==type)
            {
                return actor;
            }
        }
    }
    return nullptr;
}

std::shared_ptr<Common::Transport> GameBoard::getTransport(
        Common::CubeCoordinate coord,
        std::string type)
{
    if(tiles_.find(coord)!=tiles_.end())
    {
        // Get the transports and put them into a vector
        std::vector<std::shared_ptr<Common::Transport>> transports
                =tiles_.at(coord)->getTransports();
        for(std::shared_ptr<Common::Transport> transport : transports)
        {
            // If the transport's type matches the specific type we're looking
            // for return a pointer to it
            if(transport->getTransportType() == type)
            {
                return transport;
            }
        }
    }
    return nullptr;
}

void GameBoard::zoomIn()
{

    std::map<Common::CubeCoordinate,
            std::shared_ptr<Student::GraphicalHex>>::iterator it;
    std::map<Common::CubeCoordinate,
            std::shared_ptr<Student::GraphicalHex>>::iterator end
                = graphicTiles_.end();
    for (it = graphicTiles_.begin(); it != end; ++it) {
        it->second->increaseSize();
        it->second->update();
    }
}

void GameBoard::zoomOut()
{

    std::map<Common::CubeCoordinate,
            std::shared_ptr<Student::GraphicalHex>>::iterator it;
    std::map<Common::CubeCoordinate,
            std::shared_ptr<Student::GraphicalHex>>::iterator end
            = graphicTiles_.end();
    for (it = graphicTiles_.begin(); it != end; ++it) {
        it->second->update();
    }
}


}


