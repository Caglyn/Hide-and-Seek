#include <QApplication>
#include "gameview.h"
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameView view;
    view.setSceneRect(0, 0, 800, 600);
    view.setFixedSize(800, 600);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view.show();

    return app.exec();
}
