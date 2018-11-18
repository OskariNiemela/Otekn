#include <QString>
#include <QtTest>

#include "gamestate.hh"

class GameStateTest : public QObject
{
    Q_OBJECT

public:
    GameStateTest() = default;

private Q_SLOTS:
    void testPlayerChanges();
    void testCurrentGamePhase();
};

void GameStateTest::testPlayerChanges()
{
    Student::GameState state;

    QCOMPARE(state.currentPlayer(),0);
    state.changePlayerTurn(2);
    QCOMPARE(state.currentPlayer(),2);
}

void GameStateTest::testCurrentGamePhase()
{
    Student::GameState state;
    QCOMPARE(state.currentGamePhase(),Common::GamePhase::MOVEMENT);
    state.changeGamePhase(Common::GamePhase::SINKING);
    QCOMPARE(state.currentGamePhase(),Common::GamePhase::SINKING);
    state.changeGamePhase(Common::GamePhase::SPINNING);
    QCOMPARE(state.currentGamePhase(),Common::GamePhase::SPINNING);
}

QTEST_APPLESS_MAIN(GameStateTest)

#include "tst_gamestatetest.moc"
