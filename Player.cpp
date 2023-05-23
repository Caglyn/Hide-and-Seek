#include "player.h"

Player::Player(const QString& imagePath, QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    QPixmap playerImage(imagePath);
    setPixmap(playerImage.scaled(50, 50)); // Set the size of the player image
    stepSize = 10;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        if(pos().x() > 0)
            moveBy(-stepSize, 0);
        break;
    case Qt::Key_Right:
        if(pos().x() + 40 < 800)
            moveBy(stepSize, 0);
        break;
    case Qt::Key_Up:
        if(pos().y() > 0)
            moveBy(0, -stepSize);
        break;
    case Qt::Key_Down:
        if(pos().y() + 50 < 600)
            moveBy(0, stepSize);
        break;
    case Qt::Key_A:
        if(pos().x() > 0)
            moveBy(-stepSize, 0);
        break;
    case Qt::Key_D:
        if(pos().x() + 40 < 800)
            moveBy(stepSize, 0);
        break;
    case Qt::Key_W:
        if(pos().y() > 0)
            moveBy(0, -stepSize);
        break;
    case Qt::Key_S:
        if(pos().y() + 50 < 600)
            moveBy(0, stepSize);
        break;
    default:
        break;
    }
}
