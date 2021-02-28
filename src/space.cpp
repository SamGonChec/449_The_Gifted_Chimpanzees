#include "include/space.h"

Space::Space(int x, int y) {
    rectangle = QRectF(x,y,20,20);
    setAcceptHoverEvents(true);
    hover = false;
    white = true;
    occupied = false;
    validMove = true;
}

void Space::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/) {
/*Overloading function to implement appearance*/
    if (hover) {
        //Green fill if mouse hover and valid move
        if (validMove) {
            painter->setBrush(Qt::green);
        //Red fill if mouse hover and invalid move
        } else {
            painter->setBrush(Qt::red);
        }
    }
    painter->drawEllipse(rectangle);
}

void Space::mousePressEvent(QGraphicsSceneMouseEvent */*event*/) {
/*Signals mouse clicked on space if not occupied*/
    if (!occupied && validMove) {
        emit clicked(this);
    }
}

void Space::hoverEnterEvent(QGraphicsSceneHoverEvent */*event*/) {
/*Changes appearance when mouse enters rect*/
    hover = true;
    update();
}

void Space::hoverLeaveEvent(QGraphicsSceneHoverEvent */*event*/) {
/*Reverts appearance when mouse leaves rect*/
    hover = false;
    update();
}
