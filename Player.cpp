#include "player.h"

Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    QPixmap playerImage(":/Images/kenney_platformer-art-extended-enemies/Alien sprites/alienGreen.png"); // Replace ":/images/player.png" with the actual path to your image file
    setPixmap(playerImage.scaled(50, 50)); // Set the size of the player image
    stepSize = 10;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        moveBy(-stepSize, 0);
        break;
    case Qt::Key_Right:
        moveBy(stepSize, 0);
        break;
    case Qt::Key_Up:
        moveBy(0, -stepSize);
        break;
    case Qt::Key_Down:
        moveBy(0, stepSize);
        break;
    case Qt::Key_A:
        moveBy(-stepSize, 0);
        break;
    case Qt::Key_D:
        moveBy(stepSize, 0);
        break;
    case Qt::Key_W:
        moveBy(0, -stepSize);
        break;
    case Qt::Key_S:
        moveBy(0, stepSize);
        break;
    default:
        break;
    }
}
