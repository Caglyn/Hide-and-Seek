#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include "player.h"
#include "ghost.h"
#include <QGraphicsTextItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>

class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    GameView(QWidget *parent = nullptr);
    ~GameView();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void checkCollisions();


private:
    QGraphicsScene* scene;
    Player* player1;
    Player* player2;
    QList<Ghost*> ghosts;
    int scorePlayer1;
    int scorePlayer2;
    QGraphicsTextItem* scoreTextPlayer1;
    QGraphicsTextItem* scoreTextPlayer2;

    void addGhost(const QString& imagePath, qreal x, qreal y);
    void updateScore(Player* player);
};

#endif // GAMEVIEW_H
