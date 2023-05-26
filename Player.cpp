#include "player.h"
#include <QPainter>

Player::Player(const QString& imagePath, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), viewRange(150)
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

//using the default parameter
void Player::setViewRange(qreal range=1){
    for(int i = 0; i < range; ++i) {
        viewRange = range;
}
}
QRectF Player::boundingRect() const{
    return QRectF(-viewRange + 25, -viewRange + 25, viewRange * 2, viewRange * 2);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    setViewRange(75);
    QPointF center = boundingRect().center();

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(250, 250, 250, 150));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawEllipse(center, viewRange, viewRange);

    QGraphicsPixmapItem::paint(painter, option, widget);
}
