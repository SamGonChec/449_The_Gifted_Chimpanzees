#include "tst_gamelogic.h"

GameLogic::GameLogic() {

}

GameLogic::~GameLogic() {

}

void GameLogic::testClickMove() {
    Game game(&testScene);
    QCOMPARE(game.getSpace(0)->isOccupied(), false);
    QCOMPARE(game.getSpace(23)->isOccupied(), false);
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.getSpace(0)->hasWhitePiece(), true);
    QCOMPARE(game.getSpace(23)->hasBlackPiece(), true);
}

void GameLogic::testSwitchingTurns() {
    Game game(&testScene);
    QCOMPARE(game.testWhiteTurn(), true);
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testWhiteTurn(), false);
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testWhiteTurn(), true);
}

QTEST_MAIN(GameLogic)
