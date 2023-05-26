#include "gameview.h"
#include "qapplication.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QString>

//constructor
GameView::GameView(QWidget *parent) : QGraphicsView(parent), scene(new QGraphicsScene(this)), scorePlayer1(0), scorePlayer2(0)
{
    setScene(scene);
    //scene->setBackgroundBrush(Qt::black);
    scene->setBackgroundBrush(QBrush(QImage(":/Images/kenney_platformer-art-extended-enemies/Sky/sky.jpg")));

    player1 = new Player(":/Images/kenney_platformer-art-extended-enemies/Alien sprites/alienPink.png"); // Replace ":/images/player1.png" with the actual path to player1's image file
    player2 = new Player(":/Images/kenney_platformer-art-extended-enemies/Alien sprites/alienGreen.png"); // Replace ":/images/player2.png" with the actual path to player2's image file
    player1->setPos(200, 50);// Set initial position for player1
    player2->setPos(100, 50);// Set initial position for player2

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
//destructor
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

//using the inline function
inline void GameView::checkCollisions()
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
    if (ghosts.isEmpty()) {
        // Game over, determine the winner
        Player* winner = nullptr;
        if (scorePlayer1 > scorePlayer2) {
            winner = player1;
        } else if (scorePlayer2 > scorePlayer1) {
            winner = player2;
        }

        QString message;
        if (winner == player1) {
            message = "Pink Alien wins!";
        }
        else if (winner == player2) {
            message = "Green Alien wins!";
        }

        QMessageBox::information(this, "Game Over", message);
        QApplication::quit();
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

//using of exception handling
void GameView::updateScore(Player* player)
{
    try {
        if (player == player1) {
            scorePlayer1++;
            qDebug() << "Player 1 Score: " << scorePlayer1;
        } else if (player == player2) {
            scorePlayer2++;
            qDebug() << "Player 2 Score: " << scorePlayer2;
        } else {
            throw std::invalid_argument("Invalid player provided.");
        }
    } catch (const std::exception& e) {
        qDebug() << "Error updating score: " << e.what();
    }
}

