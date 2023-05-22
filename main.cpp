#include <QApplication>
#include <QGraphicsScene>
#include "Player.h"
#include <QGraphicsView>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //create a scene
    QGraphicsScene * scene = new QGraphicsScene();

    //create an item to put into the scene
    Player * player = new Player();

    PlayerTwo * player2 = new PlayerTwo();
    //add the item to the scene
    scene->addItem(player);

    scene->addItem(player2);
    //make rect focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    player2->setFlag(QGraphicsItem::ItemIsFocusable);
    player2->setFocus();

    //add a view
    QGraphicsView * view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();
    view->setFixedSize(800, 600);
    scene->setSceneRect(0, 0, 800, 600);


    player->setPos(view->width()/2, view->height()/2);
    player2->setPos(view->width() - 600, view->height() - 600);
    return a.exec();
}
