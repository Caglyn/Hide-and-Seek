#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>

class Player: public QGraphicsPixmapItem{
public:
    Player();
    void keyPressEvent(QKeyEvent * event);
};

class PlayerTwo: public QGraphicsPixmapItem{
public:
    PlayerTwo();
    void keyPressEvent(QKeyEvent * event);
};

#endif // MYRECT_H
