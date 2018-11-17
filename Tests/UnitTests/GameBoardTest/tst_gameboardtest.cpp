#include <QString>
#include <QtTest>
#include <QGraphicsScene>

#include "gameboard.hh"

class GameBoardTest : public QObject
{
    Q_OBJECT

public:
    GameBoardTest();

private Q_SLOTS:
    void testAddHex();
    void testAddPawn();
    void testRemovePawn();
    void testTileOccupation();
    void testMovePawn();
};

GameBoardTest::GameBoardTest()
{
}

void GameBoardTest::testAddHex()
{
    Student::GameBoard board;
    std::shared_ptr<Common::Hex> newHex = std::make_shared<Common::Hex>();
    Common::CubeCoordinate coord(0,0,0);
    newHex->setCoordinates(coord);
    board.addHex(newHex);
    QCOMPARE(board.getHex(coord),newHex);
}

void GameBoardTest::testAddPawn()
{
    Student::GameBoard board;
    std::shared_ptr<Common::Hex> newHex = std::make_shared<Common::Hex>();
    Common::CubeCoordinate coord(0,0,0);
    newHex->setCoordinates(coord);
    board.addHex(newHex);
    board.addPawn(0,0,coord);
    board.addPawn(1,2);
    QCOMPARE(board.getPawnCoordinate(0),coord);
    QCOMPARE(board.getPawnCoordinate(2),coord);
    QVERIFY_EXCEPTION_THROWN(board.getPawnCoordinate(1),Common::GameException);
}

void GameBoardTest::testRemovePawn()
{
    Student::GameBoard board;
    std::shared_ptr<Common::Hex> newHex = std::make_shared<Common::Hex>();
    Common::CubeCoordinate coord(0,0,0);
    newHex->setCoordinates(coord);
    board.addHex(newHex);
    board.addPawn(0,0,coord);
    board.removePawn(0);
    QVERIFY_EXCEPTION_THROWN(board.getPawnCoordinate(0),Common::GameException);
}

void GameBoardTest::testTileOccupation()
{
    Student::GameBoard board;
    std::shared_ptr<Common::Hex> newHex = std::make_shared<Common::Hex>();
    Common::CubeCoordinate coord(0,0,0);
    newHex->setCoordinates(coord);
    board.addHex(newHex);
    board.addPawn(0,0,coord);
    QCOMPARE(board.checkTileOccupation(coord),1);
    board.addPawn(1,1,coord);
    QCOMPARE(board.checkTileOccupation(coord),2);
}

void GameBoardTest::testMovePawn()
{
    Student::GameBoard board;
    std::shared_ptr<Common::Hex> newHex = std::make_shared<Common::Hex>();
    Common::CubeCoordinate coord(0,0,0);
    newHex->setCoordinates(coord);
    board.addHex(newHex);
    std::shared_ptr<Common::Hex> newHex2 = std::make_shared<Common::Hex>();
    Common::CubeCoordinate coord2(1,-1,0);
    newHex2->setCoordinates(coord2);
    board.addHex(newHex2);
    board.addPawn(0,0,coord);
    QCOMPARE(board.checkTileOccupation(coord) ,1);
    board.movePawn(0,coord2);
    QCOMPARE(board.checkTileOccupation(coord2),1);
    QCOMPARE(board.checkTileOccupation(coord) ,0);
}



QTEST_APPLESS_MAIN(GameBoardTest)

#include "tst_gameboardtest.moc"
