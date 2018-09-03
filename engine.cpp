#include "engine.h"
#include "graphicsscene.h"
#include "playeritem.h"
#include <QDebug>
#include "player.h"
#include "event.h"

Engine::Engine()
{

}

Engine::~Engine()
{

}

bool Engine::event(QEvent *e)
{
    if (e->type() == MyType) {
        qDebug() << "recive event";
        return true;
    }
    return QObject::event(e);
}

void Engine::startGame(GraphicsScene *scene)
{
    qDebug() << QThread::currentThreadId();

    panel = scene->getPanel();

//    scene->addItem(new PlayerItem(new Player));
}

void Engine::reciveEvent(GameEvent *event)
{
    event = nullptr;
}
