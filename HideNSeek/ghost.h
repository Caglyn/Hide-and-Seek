#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsPixmapItem>
#include <QTimer>

class Ghost : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Ghost(const QString& imagePath, QGraphicsItem* parent = nullptr);
    void startMoving();

signals:
    void ghostCaught();

private slots:
    void move();

private:
    QTimer* timer;
    int stepSize;
};

#endif // GHOST_H
