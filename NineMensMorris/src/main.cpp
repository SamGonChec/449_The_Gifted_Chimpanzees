#include "include/board.h"
#include "include/piece.h"
#include "include/space.h"
#include "include/game.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    QGraphicsScene scene;
    QGraphicsView view;
    Game game(&scene);

    //Adjusting the view, setting the scene
    view.resize(1000,900);
    view.setScene(&scene);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view.show();
    return application.exec();
}
