#include "gameview.h"
#include "qapplication.h"
#include <random>



// Constructor
GameView::GameView(QWidget *parent) : QGraphicsView(parent), scene(new QGraphicsScene(this)), scorePlayer1(0), scorePlayer2(0), remainingTime(60), isPlayer1Turn(true)
{
    setScene(scene);
    scene->setBackgroundBrush(QBrush(QImage(":/Images/Sprites/sky.jpg")));

    player1 = new Player(":/Images/Sprites/alienGreen.png");
    player2 = new Player(":/Images/Sprites/alienPink.png");
    player1->setPos(375, 225); // Set initial position for player1
    player2->setPos(375, 225); // Set initial position for player2

    player1->setVisible(true);
    player2->setVisible(false);

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

    zamanTxt = new QGraphicsTextItem();
    zamanTxt->setZValue(2);
    zamanTxt->setPos(500,10);
    scene->addItem(zamanTxt);

    // Add the players to the scene
    scene->addItem(player1);
    scene->addItem(player2);

    // Add the ghosts to the scene
    addGhost(":/Images/Sprites/ghost_normal.png", 100, 700, 100, 500);
    addGhost(":/Images/Sprites/ghost_normal.png", 100, 700, 100, 500);
    addGhost(":/Images/Sprites/ghost_normal.png", 100, 700, 100, 500);
    addGhost(":/Images/Sprites/ghost_normal.png", 100, 700, 100, 500);
    addGhost(":/Images/Sprites/ghost_normal.png", 100, 700, 100, 500);
    addGhost(":/Images/Sprites/ghost_normal.png", 100, 700, 100, 500);
    addGhost(":/Images/Sprites/ghost_normal.png", 100, 700, 100, 500);

    setFrameShape(QFrame::NoFrame);
    setRenderHint(QPainter::Antialiasing);
    setWindowTitle("Hide and Seek");

    QTimer* collisionTimer = new QTimer(this);
    connect(collisionTimer, &QTimer::timeout, this, &GameView::checkCollisions);
    collisionTimer->start(100); // Adjust the interval as needed

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameView::handleTimerTimeout);
    timer->start(1000);  // Start the timer with a 1-second interval

}

// Destructor
GameView::~GameView()
{
    qDeleteAll(ghosts);
}


// Using the inline function
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
        message = "You find all the ghosts!";
        QMessageBox::information(this, "Game Over", message);
        if(isPlayer1Turn)
            startGame();
        else
            endGame();
    }

}

void GameView::addGhost(const QString& imagePath, qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    // Generate random positions within the specified area
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disX(minX, maxX);
    std::uniform_real_distribution<> disY(minY, maxY);

    qreal x = disX(gen);
    qreal y = disY(gen);

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

void GameView::handleTimerTimeout()
{
    remainingTime--;

    int minutes = remainingTime / 60;  // Calculate the minutes
    int seconds = remainingTime % 60;  // Calculate the seconds
    QString currentPlayer;

    // Format the minutes and seconds as a string
    QString timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));

    // Update the QGraphicsTextItem to display the remaining time
    zamanTxt->setPlainText("Time: " + timeString);

    if (remainingTime == 0) {
        if(isPlayer1Turn) {currentPlayer="1"; } else { currentPlayer="2"; }
        // Display the "Game Over" alert
        QMessageBox::information(this, "Game Over!", "Time is up for Player" + currentPlayer + " !");
        // Stop the timer
        timer->stop();

        // Switch to the next player
        if (!isPlayer1Turn) {
            // Both players have finished their turns, end the game
            endGame();
        } else {
            // Start the game for the next player
            startGame();
        }
    }
}


void GameView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);


    // Player 1's turn
    if (isPlayer1Turn) {
        // Player 1's turn
        if (event->key() == Qt::Key_A || event->key() == Qt::Key_D || event->key() == Qt::Key_W || event->key() == Qt::Key_S) {
            // Forward key press event to Player 1
            player1->keyPressEvent(event);
        }
    } else {
        // Player 2's turn
        if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right || event->key() == Qt::Key_Up || event->key() == Qt::Key_Down) {
            // Forward key press event to Player 2
            player2->keyPressEvent(event);
        }
    }
}



void GameView::startGame()
{
    // Switch to the next player's turn
    isPlayer1Turn = !isPlayer1Turn;

    // Reset the remaining time
    remainingTime = 60;

    // Update the current player text
    QString currentPlayerText = isPlayer1Turn ? "Player 1's Turn" : "Player 2's Turn";
    //currentPlayerText->setPlainText(currentPlayerText);

    // Hide the inactive player
    if (isPlayer1Turn) {
        player2->setVisible(false);
        player1->setVisible(true);
    } else {
        player1->setVisible(false);
        player2->setVisible(true);
    }

    // Remove the existing ghosts from the scene
    foreach (Ghost* ghost, ghosts) {
        scene->removeItem(ghost);
        delete ghost;
    }
    ghosts.clear();

    // Add the new ghosts to the scene
    addGhost(":/Images/Sprites/ghost_normal.png", 100, 700, 100, 500);
    addGhost(":/Images/Sprites/ghost_normal.png", 100, 700, 100, 500);
    addGhost(":/Images/Sprites/ghost_normal.png", 100, 700, 100, 500);
    addGhost(":/Images/Sprites/ghost_normal.png", 100, 700, 100, 500);
    addGhost(":/Images/Sprites/ghost_normal.png", 100, 700, 100, 500);
    addGhost(":/Images/Sprites/ghost_normal.png", 100, 700, 100, 500);
    addGhost(":/Images/Sprites/ghost_normal.png", 100, 700, 100, 500);

    // Start the timer
    timer->start(1000);

    // Show the game view
    show();
}



void GameView::endGame()
{
    // Display the final scores
    QMessageBox::information(this, "Game Over", "Game has ended!\n\nPlayer 1 Score: " + QString::number(scorePlayer1) +
                                                    "\nPlayer 2 Score: " + QString::number(scorePlayer2));

    // Determine the winner
    QString winner;
    if (scorePlayer1 > scorePlayer2) {
        winner = "Player 1 (Green Alien)";
    } else if (scorePlayer2 > scorePlayer1) {
        winner = "Player 2 (Pink Alien)";
    } else {
        winner = "It's a tie!";
    }

    // Display the winner
    QMessageBox::information(this, "Winner", "The winner is: " + winner);

    // Quit the application
    QApplication::quit();
}
