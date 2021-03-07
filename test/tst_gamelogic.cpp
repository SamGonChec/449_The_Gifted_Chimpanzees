#include "tst_gamelogic.h"

GameLogic::GameLogic() {

}

GameLogic::~GameLogic() {

}
void GameLogic::testSwitchingTurns() {
    Game game(&testScene);
    QCOMPARE(game.testWhiteTurn(), true);
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testWhiteTurn(), false);
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testWhiteTurn(), true);
}

void GameLogic::testClickMovePhaseOne() {
    Game game(&testScene);
    QCOMPARE(game.getSpace(0)->isOccupied(), false);
    QCOMPARE(game.getSpace(23)->isOccupied(), false);
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.getSpace(0)->hasWhitePiece(), true);
    QCOMPARE(game.getSpace(23)->hasBlackPiece(), true);
}

void GameLogic::testClickOccupiedSpace() {
    Game game(&testScene);
    QSignalSpy spy(game.getSpace(23), SIGNAL(clicked(Space*)));
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.getSpace(23)->hasBlackPiece(), true);
    QCOMPARE(spy.count(), 1);
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.getSpace(23)->hasBlackPiece(), true);
    QCOMPARE(spy.count(), 1);
}

void GameLogic::testClickSelectWhitePiece() {
    Game game(&testScene);
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(3), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    game.deselectPiece(game.getWhitePiece(2));
    game.endPhaseOne();
    QCOMPARE(game.getWhitePiece(0)->isSelected(), false);
    QTest::mousePress(game.getWhitePiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.getWhitePiece(0)->isSelected(), true);
    QCOMPARE(game.getWhitePiece(1)->isSelected(), false);
    QTest::mousePress(game.getWhitePiece(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.getWhitePiece(0)->isSelected(), false);
    QCOMPARE(game.getWhitePiece(1)->isSelected(), true);
}

void GameLogic::testClickSelectBlackPiece() {
    Game game(&testScene);
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(3), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(4), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    game.deselectPiece(game.getBlackPiece(2));
    game.endPhaseOne();
    QCOMPARE(game.getBlackPiece(0)->isSelected(), false);
    QTest::mousePress(game.getBlackPiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.getBlackPiece(0)->isSelected(), true);
    QCOMPARE(game.getBlackPiece(1)->isSelected(), false);
    QTest::mousePress(game.getBlackPiece(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.getBlackPiece(0)->isSelected(), false);
    QCOMPARE(game.getBlackPiece(1)->isSelected(), true);
}

void GameLogic::testSelectMoveWhite() {
    Game game(&testScene);
    QSignalSpy spy(game.getWhitePiece(0), SIGNAL(turnTaken(Piece*)));
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    game.deselectPiece(game.getWhitePiece(1));
    game.endPhaseOne();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(game.getSpace(1)->isOccupied(), false);
    QTest::mousePress(game.getWhitePiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(spy.count(), 2);
    QCOMPARE(game.getSpace(1)->hasWhitePiece(), true);
}

void GameLogic::testSelectMoveBlack() {
    Game game(&testScene);
    QSignalSpy spy(game.getBlackPiece(0), SIGNAL(turnTaken(Piece*)));
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    game.deselectPiece(game.getBlackPiece(1));
    game.endPhaseOne();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(game.getSpace(22)->isOccupied(), false);
    QTest::mousePress(game.getBlackPiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(22), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(spy.count(), 2);
    QCOMPARE(game.getSpace(22)->hasBlackPiece(), true);
}

void GameLogic::testSelectMoveInvalid() {
    Game game(&testScene);
    QSignalSpy spy(game.getWhitePiece(0), SIGNAL(turnTaken(Piece*)));
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    game.deselectPiece(game.getWhitePiece(1));
    game.endPhaseOne();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(game.getSpace(23)->isOccupied(), false);
    QCOMPARE(game.testWhiteTurn(), true);
    QTest::mousePress(game.getWhitePiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(spy.count(), 1);
    QCOMPARE(game.getSpace(23)->isOccupied(), false);
    QCOMPARE(game.testWhiteTurn(), true);
}

void GameLogic::testWhiteCapture() {
    Game game(&testScene);
    QSignalSpy spy(game.getBlackPiece(1), SIGNAL(clickCapture(Piece*)));
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(22), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.getSpace(22)->isOccupied(), true);
    QCOMPARE(spy.count(), 0);
    QCOMPARE(game.testWhiteTurn(), true);
    QTest::mousePress(game.getBlackPiece(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.getSpace(22)->isOccupied(), false);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(game.testWhiteTurn(), false);
}

void GameLogic::testBlackCapture() {
    Game game(&testScene);
    QSignalSpy spy(game.getWhitePiece(1), SIGNAL(clickCapture(Piece*)));
    QTest::mousePress(game.getSpace(21), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(18), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(22), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.getSpace(18)->isOccupied(), true);
    QCOMPARE(spy.count(), 0);
    QCOMPARE(game.testWhiteTurn(), false);
    QTest::mousePress(game.getWhitePiece(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.getSpace(18)->isOccupied(), false);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(game.testWhiteTurn(), true);
}

void GameLogic::testCaptureWhiteFromMill() {
    Game game(&testScene);
    QSignalSpy spy(game.getWhitePiece(0), SIGNAL(clickCapture(Piece*)));
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(21), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(22), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getBlackPiece(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(4), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(19), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(7), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getBlackPiece(3), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(22), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(spy.count(), 0);
    QCOMPARE(game.testWhiteTurn(), false);
    QTest::mousePress(game.getWhitePiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(spy.count(), 1);
    QCOMPARE(game.testWhiteTurn(), true);
}

void GameLogic::testCaptureBlackFromMill() {
    Game game(&testScene);
    QSignalSpy spy(game.getBlackPiece(0), SIGNAL(clickCapture(Piece*)));
    QTest::mousePress(game.getSpace(4), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(21), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(22), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getWhitePiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(spy.count(), 0);
    QCOMPARE(game.testWhiteTurn(), true);
    QTest::mousePress(game.getBlackPiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(spy.count(), 1);
    QCOMPARE(game.testWhiteTurn(), false);
}

void GameLogic::testCaptureWhiteInvalid() {
    Game game(&testScene);
    QSignalSpy spy(game.getWhitePiece(0), SIGNAL(clickCapture(Piece*)));
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(21), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(22), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getBlackPiece(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(22), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(4), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(spy.count(), 0);
    QCOMPARE(game.testWhiteTurn(), false);
    QTest::mousePress(game.getWhitePiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(spy.count(), 0);
    QCOMPARE(game.testWhiteTurn(), false);
}

void GameLogic::testCaptureBlackInvalid() {
    Game game(&testScene);
    QSignalSpy spy(game.getBlackPiece(0), SIGNAL(clickCapture(Piece*)));
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(21), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(22), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(4), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getWhitePiece(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(4), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(12), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(spy.count(), 0);
    QCOMPARE(game.testWhiteTurn(), true);
    QTest::mousePress(game.getBlackPiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(spy.count(), 0);
    QCOMPARE(game.testWhiteTurn(), true);
}

void GameLogic::testWhiteFlying() {
    Game game(&testScene);
    for (int i = 4; i < 9; i++) {
        game.getWhitePiece(i)->setCaptured(true);
    }
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(17), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(6), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(14), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(20), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    game.deselectPiece(game.getBlackPiece(3));
    game.endPhaseOne();
    QTest::mousePress(game.getBlackPiece(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testWhiteFlying(), false);
    QTest::mousePress(game.getSpace(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getWhitePiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testWhiteFlying(), true);
}

void GameLogic::testBlackFlying() {
    Game game(&testScene);
    for (int i = 4; i < 9; i++) {
        game.getBlackPiece(i)->setCaptured(true);
    }
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(17), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(14), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(6), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    game.deselectPiece(game.getWhitePiece(3));
    game.endPhaseOne();
    QTest::mousePress(game.getWhitePiece(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testBlackFlying(), false);
    QTest::mousePress(game.getSpace(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getBlackPiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testBlackFlying(), true);
}

void GameLogic::testWhitePieceVictory() {
    Game game(&testScene);
    for (int i = 3; i < 9; i++) {
        game.getBlackPiece(i)->setCaptured(true);
    }
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(17), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(14), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(6), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    game.deselectPiece(game.getWhitePiece(3));
    game.endPhaseOne();
    QTest::mousePress(game.getWhitePiece(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testWhiteVictory(), false);
    QTest::mousePress(game.getSpace(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getBlackPiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testWhiteVictory(), true);
}

void GameLogic::testBlackPieceVictory() {
    Game game(&testScene);
    for (int i = 3; i < 9; i++) {
        game.getWhitePiece(i)->setCaptured(true);
    }
    QTest::mousePress(game.getSpace(23), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(17), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(1), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(6), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(14), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(20), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    game.deselectPiece(game.getBlackPiece(3));
    game.endPhaseOne();
    QTest::mousePress(game.getBlackPiece(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testBlackVictory(), false);
    QTest::mousePress(game.getSpace(2), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getWhitePiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testBlackVictory(), true);
}

void GameLogic::testWhiteMovesVictory() {
    Game game(&testScene);
    QTest::mousePress(game.getSpace(4), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(8), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(12), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(17), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(16), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(15), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(11), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(6), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    game.deselectPiece(game.getWhitePiece(4));
    game.endPhaseOne();
    QTest::mousePress(game.getWhitePiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testWhiteVictory(), false);
    QTest::mousePress(game.getSpace(7), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testWhiteVictory(), true);
}

void GameLogic::testBlackMovesVictory() {
    Game game(&testScene);
    QTest::mousePress(game.getSpace(7), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(12), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(17), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(16), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(15), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(11), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(6), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(4), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    game.deselectPiece(game.getWhitePiece(4));
    game.endPhaseOne();
    QTest::mousePress(game.getWhitePiece(0), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getSpace(8), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QTest::mousePress(game.getBlackPiece(3), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testBlackVictory(), false);
    QTest::mousePress(game.getSpace(7), Qt::LeftButton, Qt::KeyboardModifiers(), QPoint(10, 10));
    QCOMPARE(game.testBlackVictory(), true);
}

QTEST_MAIN(GameLogic)
