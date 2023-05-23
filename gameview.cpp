#include "gameview.h"
#include "Player.h"
#include "QtCore/qobject.h"
#include "QtWidgets/qgraphicsscene.h"

GameView::GameView(QWidget *parent) : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);

    player1 = new Player();
    player2 = new Player();
    player2->setPos(200, 200); // Set initial position for player2

    scene->addItem(player1);
    scene->addItem(player2);

    setRenderHint(QPainter::Antialiasing);
    setWindowTitle("Keyboard Input Game");
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
