#include "Player.h"
#include <QKeyEvent>

PlayerTwo::PlayerTwo(){
    QImage playerImg(":/Images/kenney_platformer-art-extended-enemies/Alien sprites/alienPink.png");
    QImage playerImgScaled = playerImg.scaled(50, 50, Qt::KeepAspectRatio);

    setPixmap(QPixmap::fromImage(playerImgScaled));
}

void PlayerTwo::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_A){
        setPos(x()-10, y());
    }
    else if(event->key() == Qt::Key_D){
        setPos(x()+10, y());
    }
    else if(event->key() == Qt::Key_W){
        setPos(x(), y()-10);
    }
    else if(event->key() == Qt::Key_S){
        setPos(x(), y()+10);
    }

}
