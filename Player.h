#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>

class Player : public QGraphicsPixmapItem
{
public:
    Player(const QString& imagePath, QGraphicsItem *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void setViewRange(qreal range);

private:
    int stepSize;
    qreal viewRange;
};

#endif // PLAYER_H
