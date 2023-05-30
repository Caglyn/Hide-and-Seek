#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include "Player.h"
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
    void handleTimerTimeout();

public slots:
    void startGame();

private:
    QTimer* timer;// Variable to store the remaining time


    QGraphicsScene* scene;
    Player* player1;
    Player* player2;
    QList<Ghost*> ghosts;
    int scorePlayer1;
    int scorePlayer2;
    QGraphicsTextItem* scoreTextPlayer1;
    QGraphicsTextItem* zamanTxt;
    QGraphicsTextItem* scoreTextPlayer2;

    int remainingTime;
    QGraphicsTextItem* currentPlayerText;
    // Add this line as a member variable in the GameView class
    bool isPlayer1Turn;


    void addGhost(const QString& imagePath, qreal x, qreal y, qreal mx, qreal my);
    void updateScore(Player* player);
    void endGame();
};

#endif // GAMEVIEW_H
