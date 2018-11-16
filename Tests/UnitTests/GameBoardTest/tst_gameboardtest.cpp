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
    void testCase1();
};

GameBoardTest::GameBoardTest()
{
}

void GameBoardTest::testCase1()
{
    Student::GameBoard board;
    std::shared_ptr<Common::Hex> newHex = std::make_shared<Common::Hex>();
    Common::CubeCoordinate coord(0,0,0);
    newHex->setCoordinates(coord);
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(GameBoardTest)

#include "tst_gameboardtest.moc"
