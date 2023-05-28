#include "player.h"
#include <QPainter>

Player::Player(const QString& imagePath, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), viewRange(150)
{
    QPixmap playerImage(imagePath);
    setPixmap(playerImage.scaled(50, 50)); // Set the size of the player image
    stepSize = 10;
    setZValue(1); // Set a higher zValue for the player items
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

// Using the default parameter
void Player::setViewRange(qreal range=1){
    for(int i = 0; i < range; ++i) {
        viewRange = range;
    }
}

QRectF Player::boundingRect() const{
    return QRectF(-viewRange + 25, -viewRange + 25, viewRange * 2, viewRange * 2);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    setViewRange(75);
    QPointF center = boundingRect().center();

    // Create the ellipse as a child item of the player
    vision = new QGraphicsEllipseItem(-viewRange, -viewRange, viewRange * 2, viewRange * 2, this);
    vision->setPos(center);
    vision->setPen(Qt::NoPen);
    vision->setBrush(QColor(250, 150, 150, 1));
    vision->setZValue(-1);

    QGraphicsPixmapItem::paint(painter, option, widget);
}
