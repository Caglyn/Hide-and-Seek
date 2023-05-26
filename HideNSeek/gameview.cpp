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
    scene->setBackgroundBrush(QBrush(QImage(":/Images/Sprites/sky.jpg")));

    setRenderHint(QPainter::Antialiasing);
    player1 = new Player(":/Images/Sprites/alienGreen.png"); // Replace ":/images/player1.png" with the actual path to player1's image file
    player2 = new Player(":/Images/Sprites/alienPink.png"); // Replace ":/images/player2.png" with the actual path to player2's image file
    player1->setPos(200, 50);// Set initial position for player1
    player2->setPos(100, 50);// Set initial position for player2



    scene->addItem(player1);
    scene->addItem(player2);

    addGhost(":/Images/Sprites/ghost_normal.png", 100, 100); // Replace ":/images/ghost1.png" with the actual path to the ghost image file
    addGhost(":/Images/Sprites/ghost_normal.png", 300, 200); // Replace ":/images/ghost2.png" with the actual path to the ghost image file
    addGhost(":/Images/Sprites/ghost_normal.png", 400, 300); // Replace ":/images/ghost3.png" with the actual path to the ghost image file
    addGhost(":/Images/Sprites/ghost_normal.png", 200, 400); // Replace ":/images/ghost4.png" with the actual path to the ghost image file
    addGhost(":/Images/Sprites/ghost_normal.png", 350, 150); // Replace ":/images/ghost5.png" with the actual path to the ghost image file


    setWindowTitle("Hide and Seek");


    QTimer* collisionTimer = new QTimer(this);
    connect(collisionTimer, &QTimer::timeout, this, &GameView::checkCollisions);
    collisionTimer->start(100); // Adjust the interval as needed
}

//Destructor
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

//Using the inline function
inline void GameView::checkCollisions()
{
    foreach (Ghost* ghost, ghosts) {
        ghost->setVisible(false);
        if (ghost->collidesWithItem(player1->vision)) {
            ghost->setVisible(true);
            QTimer::singleShot(1000, ghost, [ghost, this]() {
                scene->removeItem(ghost);
                ghosts.removeOne(ghost);
                updateScore(player1);
                delete ghost;
            });
        } else if (ghost->collidesWithItem(player2->vision)) {
            ghost->setVisible(true);
            QTimer::singleShot(2000, ghost, [ghost, this]() {
                scene->removeItem(ghost);
                ghosts.removeOne(ghost);
                updateScore(player1);
                delete ghost;
            });
        }
        else
            ghost->setVisible(false);
    }

    QString message;
    if (ghosts.isEmpty()) {
        // Game over, determine the winner
        if (scorePlayer1 > scorePlayer2) {
            message = "Green Alien wins!"; // Pink alien is player1
        } else {
            message = "Pink Alien wins!"; // Green alien is player2
        }
        QMessageBox::information(this, "Game Over", message);
        QApplication::quit();
    }

}

void GameView::addGhost(const QString& imagePath, qreal x, qreal y)
{
    //explicit heap dynamic variable
    Ghost* ghost = new Ghost(imagePath);
    ghost->setPos(x, y);
    scene->addItem(ghost);
    ghosts.append(ghost);
    ghost->startMoving();
}

//Using of exception handling
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
