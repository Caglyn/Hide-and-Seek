#include "gameview.h"

GameView::GameView(QWidget *parent) : QGraphicsView(parent), scene(new QGraphicsScene(this)), scorePlayer1(0), scorePlayer2(0)
{
    setScene(scene);
    //scene->setBackgroundBrush(Qt::black);
    scene->setBackgroundBrush(QBrush(QImage(":/Images/kenney_platformer-art-extended-enemies/Sky/sky.jpg")));
    player1 = new Player(":/Images/kenney_platformer-art-extended-enemies/Alien sprites/alienPink.png"); // Replace ":/images/player1.png" with the actual path to player1's image file
    player2 = new Player(":/Images/kenney_platformer-art-extended-enemies/Alien sprites/alienGreen.png"); // Replace ":/images/player2.png" with the actual path to player2's image file
    player2->setPos(200, 200);// Set initial position for player2

    //player1->setZValue(1);
    //player2->setZValue(1);
setFrameShape(QFrame::NoFrame);
    scene->addItem(player1);
    scene->addItem(player2);

    addGhost(":/Images/kenney_platformer-art-extended-enemies/Enemy sprites/ghost_normal.png", 100, 100); // Replace ":/images/ghost1.png" with the actual path to the ghost image file
    addGhost(":/Images/kenney_platformer-art-extended-enemies/Enemy sprites/ghost_normal.png", 300, 200); // Replace ":/images/ghost2.png" with the actual path to the ghost image file
    addGhost(":/Images/kenney_platformer-art-extended-enemies/Enemy sprites/ghost_normal.png", 400, 300); // Replace ":/images/ghost3.png" with the actual path to the ghost image file
    addGhost(":/Images/kenney_platformer-art-extended-enemies/Enemy sprites/ghost_normal.png", 200, 400); // Replace ":/images/ghost4.png" with the actual path to the ghost image file
    addGhost(":/Images/kenney_platformer-art-extended-enemies/Enemy sprites/ghost_normal.png", 350, 150); // Replace ":/images/ghost5.png" with the actual path to the ghost image file

    setRenderHint(QPainter::Antialiasing);
    setWindowTitle("Keyboard Input Game");

    QTimer* collisionTimer = new QTimer(this);
    connect(collisionTimer, &QTimer::timeout, this, &GameView::checkCollisions);
    collisionTimer->start(100); // Adjust the interval as needed
}

GameView::~GameView()
{
    qDeleteAll(ghosts);
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);

    if (event->key() == Qt::Key_A || event->key() == Qt::Key_D || event->key() == Qt::Key_W || event->key() == Qt::Key_S) {
        // Forward key press event to Player 2
        player2->keyPressEvent(event);
    } else {
        // Forward key press event to Player 1
        player1->keyPressEvent(event);
    }
}

void GameView::checkCollisions()
{
    foreach (Ghost* ghost, ghosts) {
        if (ghost->collidesWithItem(player1)) {
            scene->removeItem(ghost);
            ghosts.removeOne(ghost);
            updateScore(player1);
            delete ghost;
        } else if (ghost->collidesWithItem(player2)) {
            scene->removeItem(ghost);
            ghosts.removeOne(ghost);
            updateScore(player2);
            delete ghost;
        }
    }
}

void GameView::addGhost(const QString& imagePath, qreal x, qreal y)
{
    Ghost* ghost = new Ghost(imagePath);
    ghost->setPos(x, y);
    scene->addItem(ghost);
    ghosts.append(ghost);
    ghost->startMoving();
}

void GameView::updateScore(Player* player)
{
    if (player == player1) {
        scorePlayer1++;
        qDebug() << "Player 1 Score: " << scorePlayer1;
    } else if (player == player2) {
        scorePlayer2++;
        qDebug() << "Player 2 Score: " << scorePlayer2;
    }
}

