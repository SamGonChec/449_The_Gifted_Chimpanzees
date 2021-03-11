#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QWidget>
#include "include/game.h"

class Menu : public QObject{
    Q_OBJECT
private:
    QPushButton* twoPlayerButton;
public:
    QGraphicsScene* scene;
    Menu(QGraphicsScene *scene);
    void mainMenuScreen();
    QPushButton *returnTwoPlayerPushButton() {return twoPlayerButton;}
signals:
    void buttonClicked();

};

#endif // MENU_H
