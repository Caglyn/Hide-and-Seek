#include "ghost.h"
#include "QtWidgets/qgraphicsscene.h"
#include <QRandomGenerator>

Ghost::Ghost(const QString& imagePath, QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem(parent)
{
// Explicitly allocate QPixmap on the heap
    QPixmap* ghostImage = new QPixmap(imagePath);
    setPixmap(ghostImage->scaled(25, 25));
    stepSize = 5;
    setZValue(1);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Ghost::move);
}

void Ghost::startMoving()
{
    timer->start(200);
}

void Ghost::move()
{
    if (0 < pos().x() && pos().x() < 780 && 0 < pos().y() && pos().y() < 580) {
        // Simple movement pattern: diagonal movement
        int dx = QRandomGenerator::global()->bounded(-stepSize, stepSize + 2);
        int dy = QRandomGenerator::global()->bounded(-stepSize, stepSize + 2);

        QRectF sceneBounds = scene()->sceneRect();
        QRectF ghostBounds = boundingRect().translated(pos() + QPointF(dx, dy));
        if (sceneBounds.contains(ghostBounds)) {
            moveBy(dx, dy);
        }
    }
}

Ghost::~Ghost()
{
    delete timer; // Release the dynamically allocated memory for the timer
}
