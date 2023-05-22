#include "Player.h"
#include <QKeyEvent>
#include <QGraphicsScene>

Player::Player(){
    QImage playerImg(":/Images/kenney_platformer-art-extended-enemies/Alien sprites/alienGreen.png");
    QImage playerImgScaled = playerImg.scaled(50, 50, Qt::KeepAspectRatio);

    setPixmap(QPixmap::fromImage(playerImgScaled));
}


void Player::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_Left){
        if(pos().x() > 0)
            setPos(x()-10, y());
    }
    else if(event->key() == Qt::Key_Right){
        if(pos().x() + 100 < 800)
            setPos(x()+10, y());
    }
    else if(event->key() == Qt::Key_Up){
        setPos(x(), y()-10);
    }
    else if(event->key() == Qt::Key_Down){
        setPos(x(), y()+10);
    }

}
