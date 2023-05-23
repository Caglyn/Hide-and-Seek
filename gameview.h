#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "player.h"

class GameView : public QGraphicsView
{
public:
    GameView(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Player *player1;
    Player *player2;
};

#endif // GAMEVIEW_H
