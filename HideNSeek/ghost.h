
#ifndef GHOST_H
#define GHOST_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Ghost : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Ghost(const QString& imagePath, QGraphicsItem* parent = nullptr);
    virtual ~Ghost(); // Virtual destructor

    void startMoving();

private slots:
    void move();

private:
    QTimer* timer;
    int stepSize;
};

#endif // GHOST_H
