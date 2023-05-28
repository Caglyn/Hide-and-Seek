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

    player1 = new Player(":/Images/Sprites/alienGreen.png");
    player2 = new Player(":/Images/Sprites/alienPink.png");
    player1->setPos(0, 0); // Set initial position for player1
    player2->setPos(750, 550); // Set initial position for player2

    // Create the score display items
    scoreTextPlayer1 = new QGraphicsTextItem();
    scoreTextPlayer1->setZValue(2);
    scoreTextPlayer2 = new QGraphicsTextItem();
    scoreTextPlayer2->setZValue(2);

    // Set the initial positions of the score text items
    scoreTextPlayer1->setPos(700, 10);
    scoreTextPlayer2->setPos(10, 550);

    // Set the font color of the score text items to white
    QFont font("Arial", 14, QFont::Bold);
    QBrush textBrush(QColorConstants::Svg::greenyellow);
    scoreTextPlayer1->setFont(font);
    scoreTextPlayer1->setDefaultTextColor(textBrush.color());
    textBrush.setColor(QColorConstants::Svg::pink);
    scoreTextPlayer2->setFont(font);
    scoreTextPlayer2->setDefaultTextColor(textBrush.color());

    scoreTextPlayer1->setPlainText("Score: " + QString::number(scorePlayer1));
    scoreTextPlayer2->setPlainText("Score: " + QString::number(scorePlayer2));

    // Add the score text items to the scene
    scene->addItem(scoreTextPlayer1);
    scene->addItem(scoreTextPlayer2);

    scene->addItem(player1);
    scene->addItem(player2);

    addGhost(":/Images/Sprites/ghost_normal.png", 725, 20); // Sağ yukarı
    addGhost(":/Images/Sprites/ghost_normal.png", 125, 550); // Sol aşağı
    addGhost(":/Images/Sprites/ghost_normal.png", 25, 400); // Sol aşağı sol çarpraz
    addGhost(":/Images/Sprites/ghost_normal.png", 650, 200); // Sağ yukarı sol çarpraz
    addGhost(":/Images/Sprites/ghost_normal.png", 400, 375);
    addGhost(":/Images/Sprites/ghost_normal.png", 200, 220);
    addGhost(":/Images/Sprites/ghost_normal.png", 400, 100);

    setFrameShape(QFrame::NoFrame);
    setRenderHint(QPainter::Antialiasing);
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
        if(!ghost->collidesWithItem(player1->vision) && !ghost->collidesWithItem(player2->vision)){
            ghost->setVisible(false);
        } else if (ghost->collidesWithItem(player1->vision)) {
            ghost->setVisible(true);
            QTimer::singleShot(1000, ghost, [ghost, this]() {
                scene->removeItem(ghost);
                ghosts.removeOne(ghost);
                updateScore(player1);
                delete ghost;
            });
        } else if (ghost->collidesWithItem(player2->vision)) {
            ghost->setVisible(true);
            QTimer::singleShot(1000, ghost, [ghost, this]() {
                scene->removeItem(ghost);
                ghosts.removeOne(ghost);
                updateScore(player2);
                delete ghost;
            });
        }
    }

    QString message;
    if (ghosts.isEmpty()) {
        // Game over, determine the winner
        if (scorePlayer1 > scorePlayer2) {
            message = "Green Alien wins!"; // Green alien is player1
        } else {
            message = "Pink Alien wins!"; // Pink alien is player2
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

void GameView::updateScore(Player* player)
{
    try {
        if(player == player1) {
            scorePlayer1++;
            scoreTextPlayer1->setPlainText("Score: " + QString::number(scorePlayer1));
        } else {
            scorePlayer2++;
            scoreTextPlayer2->setPlainText("Score: " + QString::number(scorePlayer2));
        }
    } catch (const std::exception& e) {
        qDebug() << "Error updating score: " << e.what();
    }
}
