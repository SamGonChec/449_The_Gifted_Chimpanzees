#ifndef TST_GAMELOGIC_H
#define TST_GAMELOGIC_H
#include <QtTest>
#include <QTest>
#include <QCoreApplication>

#include "include/game.h"

class GameLogic : public QObject
{
    Q_OBJECT

public:
    GameLogic();
    ~GameLogic();

private:
    QGraphicsScene testScene;

private slots:

    void testClickMove();
    //AC 2.1-3
    void testSwitchingTurns();


};
#endif // TST_GAMELOGIC_H
