#include <QApplication>
#include "gameview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameView view;
    view.setSceneRect(0, 0, 400, 400);
    view.setFixedSize(400, 400);
    view.show();

    return app.exec();
}
